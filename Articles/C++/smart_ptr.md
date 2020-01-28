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

----
**custom deleter for a shared pointer**

why shared pointer don't need virtual destructor
why cost and non const and value pass smart pointer

#### References
[StackOverflow](https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c?rq=1)

### Authors

* **The Philomath**
