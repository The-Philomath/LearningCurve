## About

What is Copy and Swap idiom and why we should use it?

Before understanding copy and swap lets sink in some `C++` terminology

**Name lookup** is the process of identifying what a name means. Some names denote types or templates. In general, whenever a name is encountered it is necessary to determine whether that name denotes one of these entities before continuing to parse the program that contains it. The process that determines this is called name lookup.

**qualified lookup** Looking a name up in a given scope using the :: operator.

**unqualified lookup** Starting from the current scope, a name is looked up, escaping into the enclosing scopes and base classes if inside a class. Does not start from a specific named scope. This lookup form stops as soon as it finds a name. So a name in an inner scope (or class) hides a name found in an outer scope (or base class).

**Argument dependent lookup** You don’t have to qualify the namespace for functions if one or more argument types are defined in the namespace of the function.

```cpp
namespace MyNamespace
{
    class MyClass {};
    void doSomething(MyClass) {}
}
MyNamespace::MyClass obj; // global object

int main()
{
    doSomething(obj); // Works Fine - MyNamespace::doSomething() is called.
}
```
In the above example there is neither a `using-declaration` nor a `using-directive` but still the compiler correctly identifies the unqualified name `doSomething()` as the function declared in `namespace MyNamespace` by applying Koenig lookup(ADL).

**How ADL works**

The algorithm tells the compiler to not just look at local scope, but also the namespaces that contain the argument's type. Thus, in the above code, the compiler finds that the object `obj`, which is the argument of the function `doSomething()`, belongs to the `namespace MyNamespace`. So, it looks at that namespace to locate the declaration of `doSomething()`.

**Rule of three OR four OR five OR six OR three and half OR five and half OR zero** whatever you call it, its simple that either we define all of those functions which manage a resource or define none of them. Those are:-

Before `C++11`
1. Copy Constructor
2. Copy Assignment Operator
3. Destructor
4. OR 3.5 Non Throwing swap

Since `C++11`
5. Move Constructor
6. Move Assignment Operator

----

Defining a copy constructor and destructor is easy. But how should we define the Copy assignment operator. What is the correct way?

The **copy-and-swap** idiom is the solution, and elegantly assists the assignment operator in achieving two things: `avoiding code duplication`, and providing a `strong exception guarantee`.

**How does it work?**

Conceptually, it works by using the copy-constructor's functionality to create a local copy of the data, then takes the copied data with a `swap` function, swapping the old data with the new data. The temporary copy then destructs, taking the old data with it. We are left with a copy of the new data.

In order to use the copy-and-swap idiom, we need three things: a working copy-constructor, a working destructor (both are the basis of any wrapper, so should be complete anyway), and a `swap` function.

A swap function is a _non-throwing_ function that swaps two objects of a class, member for member. We might be tempted to use `std::swap` instead of providing our own, but this would be impossible; `std::swap` uses the copy-constructor and copy-assignment operator within its implementation, and we'd ultimately be trying to define the assignment operator in terms of itself!

This is how we generally define a copy constructor:
```cpp
class cs{
    int* mPtr;
    std::size_t mSize;
public:
    cs(std::size_t sz = 0):
        mSize(sz),
        mPtr((mSize > 0)? new int[mSize]() : nullptr){}

    cs(const cs& obj):
        mSize(obj.mSize),
        mPtr((mSize > 0)? new int[mSize](): nullptr){
            // note that this is non-throwing, because of the data
            // types being used; more attention to detail with regards
            // to exceptions must be given in a more general case, however
            std::copy(obj.mPtr, obj.mPtr + mSize, mPtr);
    }
    cs& operator=(const cs& obj){
        if(this != &obj)   // 1. Self assessment check. Would be better if self assessment works without it.
        {
           delete []mPtr; // 2. what if new at line 26 throws then at line 25 mSize has already been modified with mPtr as nullptr
           mPtr = nullptr;

           mSize = obj.mSize; // 3. Code duplicacy. Copy constructor already doing this.
           mPtr = (mSize > 0)? new int[mSize](): nullptr;

           std::copy(obj.mPtr, obj.mPtr + mSize, mPtr);
        }
        return *this;
    }

    ~cs(){
        delete []mPtr;
    }
};
```
There are 3 problems(marked as 1,2,3) in the copy assignment in above code.

Let's solve these problems with copy and swap idiom. A `swap` function should look like this
```cpp
   friend void swap(cs& obj1, cs& obj2) //nothrow. Just like std::swap which take 2 arguments we defined a 2 argument swap. Instead of polluting global space we added it inside the class so that it can only be find through ADL.
   {
       using std::swap; //enable ADL
       swap(obj1.mSize, obj2.mSize);
       swap(obj1.mPtr, obj2.mPtr);
   }

   cs& operator=(cs obj) //Parameter by value, no exception guarantee, no code duplicacy.
   {
       swap(*this, obj);
       return *this;
   }
```
Observe that upon entering the function that all the new data is already allocated, copied, and ready to be used. This is what gives us a strong exception guarantee for free: we won't even enter the function if construction of the copy fails, and it's therefore not possible to alter the state of `*this`. (What we did manually before for a strong exception guarantee, the compiler is doing for us now; how kind.)

At this point we are home-free, because swap is non-throwing. We swap our current data with the copied data, safely altering our state, and the old data gets put into the temporary. The old data is then released when the function returns. (Where upon the parameter's scope ends and its destructor is called.)

Because the idiom repeats no code, we cannot introduce bugs within the operator. Note that this means we are rid of the need for a self-assignment check, allowing a single uniform implementation of `operator=`. (Additionally, we no longer have a performance penalty on non-self-assignments.)

For move constructor
```cpp
    cs(cs && obj) noexcept:
        cs() //constructor delegation
    {
        swap(*this, obj);
    }
```
Goal of move-construction: to take the resources from another instance of the class, leaving it in a state guaranteed to be assignable and destructible.

So what we've done is simple: initialize via the default constructor (a `C++11` feature), then swap with `obj`; we know a default constructed instance of our class can safely be assigned and destructed, so we know `obj` will be able to do the same, after swapping.

There is no need to move assignment. Copy assignment is taking parameter by value. That parameter can be constructor from a rvalue reference. If we still want a move assignment we can define like this:

```cpp
cs& operator=(cs&& obj)
{
  cs temp(std::move(obj));
  swap(*this, temp);

  return *this;
}
```

#### Point to remember:

* **Don't repeat yourself**

* **A Class should manage only 1 resource**

#### References

[StackOverflow](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom?noredirect=1&lq=1)

[StackOverflow](https://stackoverflow.com/questions/5695548/public-friend-swap-member-function)

[StackOverflow](https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup)

[cppReference](https://en.cppreference.com/w/cpp/language/unqualified_lookup)

### Authors

* **The Philomath**
