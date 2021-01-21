## About
Smart pointers releases memory once the pointer goes out of scope.

C++ offers 3 variants of smart pointers:-
* `unique_ptr` : there can only be 1 reference of a `unique_ptr`
* `shared_ptr` : a pointer shared by multiple objects.
* `weak_ptr` : a pointer that holds a non-owning reference to an object that is managed by `shared_ptr`

smart pointer holds only two pointers:
* the stored pointer (one returned by get());
* a pointer to control block.

The pointer held by the `shared_ptr` directly is the one returned by `get()`, while the pointer/object held by the control block is the one that will be deleted when the number of shared owners reaches zero. These pointers are not necessarily equal.

The destructor of `shared_ptr` decrements the number of shared owners of the control block. If that counter reaches zero, the control block calls the destructor of the managed object. The control block does not deallocate itself until the `std::weak_ptr` counter reaches zero as well.

In existing implementations, the number of weak pointers is incremented if there is a shared pointer to the same control block. Any sane implementation will represent it as the number of weak_ptrs, plus 1 if there are any shared_ptrs outstanding.

we can create a smart pointer by allocating memory by ourselves or by calling `make_unique`

    std::shared_ptr<usingSmartPtr> usp(new usingSmartPtr);
OR

    std::shared_ptr<usingSmartPtr> usp = make_shared<usingSmartPtr>();

In the first syntax two separate memory allocation happens. One by `new` operator call and another by the smart pointer for control block.

In the second syntax memory allocation happens only 1 time and that is for both the object and smart pointer's control block.


----
**Exception-Safety**

**NOTE**: This is not a problem since **C++17**, due to the changes in the evaluation order of function arguments. Specifically, each argument to a function is required to fully execute before evaluation of other arguments.

Consider this example:-
```cpp
void F(const std::shared_ptr<Lhs> &lhs, const std::shared_ptr<Rhs> &rhs) { /* ... */ }

F(std::shared_ptr<Lhs>(new Lhs("foo")),
  std::shared_ptr<Rhs>(new Rhs("bar")));
```
Because C++ allows arbitrary order of evaluation of subexpressions, one possible ordering is:
```cpp
new Lhs("foo"))
new Rhs("bar"))
std::shared_ptr<Lhs>
std::shared_ptr<Rhs>
```
Now, suppose we get an exception thrown at step 2 (e.g., out of memory exception, Rhs constructor threw some exception). We then lose memory allocated at step 1, since nothing will have had a chance to clean it up. The core of the problem here is that the raw pointer didn't get passed to the `std::shared_ptr` constructor immediately.

One way to fix this is to do them on separate lines so that this arbitary ordering cannot occur.
```cpp
auto lhs = std::shared_ptr<Lhs>(new Lhs("foo"));
auto rhs = std::shared_ptr<Rhs>(new Rhs("bar"));
F(lhs, rhs);
```
The preferred way to solve this of course is to use `std::make_shared` instead.
```cpp
F(std::make_shared<Lhs>("foo"), std::make_shared<Rhs>("bar"));
```
----
There is one **disadvantage** of second method. Since there there's only one allocation, the pointee's memory cannot be deallocated until the control block is no longer in use. A weak_ptr can keep the control block alive indefinitely.

But in first method we can do that. Take `usingSmartPtr *sp = new usingSmartPtr;` and pass it smart pointer.

    UsingSmartPtr *ptr = new UsingSmartPtr();
    std::unique_ptr<UsingSmartPtr> usp(ptr);

There is one more disadvantage that we can't use a custom `deleter` with the `make_shared`. continue to read for more detail

----
**Deleter**

Let's take an example:-
```cpp
int main(){
    ...
    std::vector<std::shared_ptr<void>> vsptr;
    {
        vsptr.push_back(std::shared_ptr<UsingSmartPtr>(new UsingSmartPtr));
    }
    ...
}
```
This code compiles fine.

Here I have created a vector of shared pointers of void type. After that I added a shared pointer of type `UsingSmartPtr`. How could this code compile fine? Isn't there a type mismatch?

The trick is that `std::shared_ptr` performs type erasure. Basically, when a new `shared_ptr` is created it will store internally a `deleter` function (which can be given as argument to the constructor but if not present defaults to calling delete). When the `shared_ptr` is destroyed, it calls that stored function and that will call the `deleter`.

Due to this reason shared pointer don't need virtual destructor in base class and both the derived and UsingSmartPtr destructors get called in below code. But for the `unique_ptr` we do need the virtual destructors. Becuase call of deleter is not same in the internal implementation of `unique_ptr` and `shared_ptr`.
```cpp
class UsingSmartPtr{

    public:
    UsingSmartPtr()
    {
        std::cout<<"smart pointer constructor"<<std::endl;
    }
    ~UsingSmartPtr()
    {
        std::cout<<"smart pointer destructor"<<std::endl;
    }
};
class derived: public UsingSmartPtr{

    public:
    derived()
    {
        std::cout<<"derived constructor"<<std::endl;
    }
    ~derived()
    {
        std::cout<<"derived destructor"<<std::endl;
    }
};

int main(){
    std::shared_ptr<UsingSmartPtr> sptr(new derived());
}
```

**Output:-**

  _smart pointer constructor  
  derived constructor  
  derived destructor  
  smart pointer destructor_

Here `deleter` is set to derived and it called derived destructor on deletion. Which further called the base destructor.

**Custom deleter**

We can create our own `deleter` function. All custom `deleter` accept a raw pointer(as an argument) to the object to be destroyed.

`deleters` that are function pointers grow the size of a unique_ptr from one word to two words. For functors size grows depending on how much states we are going to store inside functors.  

A simple sketch of the type erasure that is going on simplified with `std::function`, and avoiding all reference counting and other issues can be seen here:
```cpp
template <typename T>
void delete_deleter( void * p ) {
   delete static_cast<T*>(p);
}

template <typename T>
class my_unique_ptr {
  std::function< void (void*) > deleter;
  T * p;
  template <typename U>
  my_unique_ptr( U * p, std::function< void(void*) > deleter = &delete_deleter<U> )
     : p(p), deleter(deleter)
  {}
  ~my_unique_ptr() {
     deleter( p );   
  }
};

int main() {
   my_unique_ptr<void> p( new double ); // deleter == &delete_deleter<double>
}
// ~my_unique_ptr calls delete_deleter<double>(p)
```
When a `shared_ptr` is copied (or default constructed) from another the `deleter` is passed around, so that when you construct a `shared_ptr<T>` from a `shared_ptr<U>` the information on what destructor to call is also passed around in the `deleter`.

For our previous example a custom deleter looks like:-
```cpp
void customDeleter(derived *ptr)
{
    delete ptr;
}

int main(){
    std::shared_ptr<UsingSmartPtr> sptr(new derived(), customDeleter);
}

// with functor
struct customDeleter
{
    void operator ()(derived *ptr){
        delete ptr;
    }
};

int main(){
    std::shared_ptr<UsingSmartPtr> sptr(new derived(), customDeleter());
}

// lambda expression
int main(){
    std::shared_ptr<UsingSmartPtr> sptr(new derived(), [](derived *ptr){
        delete ptr;
    });
}
```

`unique_ptr` is move only. We can't copy it. Compiler deletes copy constructor of a `unique_ptr`. So passing of a `unique_ptr` to a function won't work.
```cpp
void func(std::unique_ptr<UsingSmartPtr> uptr)
{
    uptr->func();
}

int main(){
    std::unique_ptr<UsingSmartPtr> uptr(new UsingSmartPtr);
    func(uptr);
}
```

**Output:-**

  _error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = UsingSmartPtr; _Dp = std::default_delete<UsingSmartPtr>]'  
  func(uptr);_

To make it work we have to pass the ownership of `unique_ptr` to the function.
```cpp
    func(std::move(uptr));
```

That is also the reason why `auto_ptr` are deprecated now.
Also copying an `auto_ptr` sets it to NULL. Also its not possible to store `auto_ptr` in a container.

**How to use arrays with unique_ptr?**

First thing to know:

    std::unique_ptr<Test> p(new Test[10]);  // will not work!

The above code will compile, but when resources are about to be deleted only single delete will be called. So how do we ensure that delete[] is called?

Fortunately unique pointers have a proper partial specialization for arrays and we can write:

    std::unique_ptr<Test[]> tests(new Test[10]);

**How to use arrays with shared_ptr?**

Arrays with `shared_ptr` are a bit trickier that when using `unique_ptr`, but we can use our own `deleter` and have full control over them as well:

    std::shared_ptr<Test> sp(new Test[2], [](Test *p) { delete []p;});

We need to use custom `deleter` (here as a lambda expression). Additionally we cannot use `make_shared` construction.

**Passing a smart pointer to a function**

Remember shared pointer is not a pointer which is shared but its pointer to the shared. Here pointee is shared.

Sometimes a function want's to reseat a Widget. In this use-case, you should pass the `std::unique_ptr<Widget>` by a non-const reference.

```cpp
#include <memory>
#include <utility>

struct Widget{
    Widget(int){}
};

void reseat(std::unique_ptr<Widget>& uniqPtr){
    uniqPtr.reset(new Widget(2003));   // (0)
    // do something with uniqPtr
}

int main(){
    auto uniqPtr = std::make_unique<Widget>(1998);

    reseat(std::move(uniqPtr));       // (1) ERROR
    reseat(uniqPtr);                  // (2)
}
```

Now, the call (1) fails because you can not bind an rvalue to a non-const lvalue reference. This will not hold for the copy in (2). A lvalue can be bound to an lvalue reference. By the way. The call (0) will not only construct a new Widget(2003), it will also destruct the old Widget(1998).

Here are the three function signatures, we have to deal with.
```cpp
void share(std::shared_ptr<Widget> shaWid);
void reseat(std::shard_ptr<Widget>& shadWid);
void mayShare(const std::shared_ptr<Widget>& shaWid);
```
Let's look at each function signature in isolation. What does this mean from the function perspective?

`void share(std::shared_ptr<Widget> shaWid)`: I'm for the lifetime of the function body a shared owner of the `Widget`. At the begin of the function body, I will increase the reference counter; at the end of the function, I will decrease the reference counter; therefore, the `Widget` will stay alive, as long as I use it.

`void reseat(std::shared_ptr<Widget>& shaWid)`: I'm not a shared owner of the `Widget`, because I will not change the reference counter. I have not guaranteed that the `Widget` will stay alive during the execution of my function, but I can reseat the resource. A non-const lvalue reference is more like: I borrow the resource and can reseat it.

`void mayShare(const std::shared_ptr<Widget>& shaWid)`: I only borrow the resource. Either can I extend the lifetime of the resource nor can I reseat the resource. To be honest, you should use a pointer `(Widget*)` or a reference `(Widget&)` as a parameter instead, because there is no added value in using a `std::shared_ptr`.

In One line:- There is no reason to pass by value, unless the goal is to share ownership of an object.

----
**How to define copy constructor for a class having unique_ptr?**

The usual case to define `unique_ptr` in a class is so that `unique_ptr` is able to use inheritance.
First of all we have to do the deep copy of the contained pointer to ensure the derived class is copied correctly.

```cpp
struct Base
{
    //some stuff

    auto clone() const { return std::unique_ptr<Base>(clone_impl()); }
protected:
    virtual Base* clone_impl() const = 0;
};

struct Derived : public Base
{
    //some stuff

protected:
    virtual Derived* clone_impl() const override { return new Derived(*this); };                                                 
};

struct Foo
{
    std::unique_ptr<Base> ptr;  //points to Derived or some other derived class

    //rule of five
    ~Foo() = default;
    Foo(Foo const& other) : ptr(other.ptr->clone()) {}
    Foo(Foo && other) = default;
    Foo& operator=(Foo const& other) { ptr = other.ptr->clone(); return *this; }
    Foo& operator=(Foo && other) = default;
};
```
Two things are happening here:
* The first is the addition of copy and move constructors, which are implicitly deleted in Foo as the copy constructor of `unique_ptr` is deleted. The move constructor can be added simply by `= default`. which is just to let the compiler know that the usual move constructor shall not be deleted (this works, as `unique_ptr` already has a move constructor which can be used in this case).

For the copy constructor of `Foo`, there is no similar mechanism as there is no copy constructor of `unique_ptr`. So, one has to construct a new `unique_ptr`, fill it with a copy of the original pointee, and use it as member of the copied class.

* In case inheritance is involved, the copy of the original pointee must be done carefully. The reason is that doing a simple copy via `std::unique_ptr<Base>(*ptr)` in the code above would result in slicing, i.e., only the base component of the object gets copied, while the derived part is missing.

To avoid this, the copy has to be done via the clone-pattern. The idea is to do the copy through a virtual function `clone_impl()` which returns a `Base*` in the base class. In the derived class, however, it is extended via covariance to return a `Derived*`, and this pointer points to a newly created copy of the derived class. The base class can then access this new object via the base class pointer `Base*`, wrap it into a `unique_ptr`, and return it via the actual `clone()` function which is called from the outside.

#### References
[Cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr)

[StackOverflow](https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c?rq=1)

[StackOverflow](https://stackoverflow.com/questions/5913396/why-do-stdshared-ptrvoid-work)

[StackOverflow](https://stackoverflow.com/questions/16030081/copy-constructor-for-a-class-with-unique-ptr)

[Bartek's](https://www.bfilipek.com/2016/04/custom-deleters-for-c-smart-pointers.html)

[modernes](https://www.modernescpp.com/index.php/c-core-guidelines-passing-smart-pointer)

### Authors

* **The Philomath**
