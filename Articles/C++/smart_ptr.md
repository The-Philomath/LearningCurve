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

***NOTE**: This is not a problem since **C++17**, due to the changes in the evaluation order of function arguments. Specifically, each argument to a function is required to fully execute before evaluation of other arguments.

Consider this example,
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

Due to this reason shared pointer don't need virtual destructor in base class and both the derived and UsingSmartPtr destructors get called in below code.
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

We can create our own deleter function.

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


why const and non const and value pass smart pointer

#### References
[Cppreference](https://en.cppreference.com/w/cpp/memory/shared_ptr)

[StackOverflow](https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c?rq=1)

[StackOverflow](https://stackoverflow.com/questions/5913396/why-do-stdshared-ptrvoid-work)

[Bartek's](https://www.bfilipek.com/2016/04/custom-deleters-for-c-smart-pointers.html)

### Authors

* **The Philomath**
