## About
Thread library support in C++.

### Creation of thread object
```cpp
#include<iostream>
#include<thread>  // thread library

void func()  // new thread start point
{
    std::cout<<"concurrency!!";
}

int main()
{
    std::thread t(func); // new thread created, func is the entry point for new thread.
    t.join(); // parent thread will wait for thread t to finish before executing the next instruction.

    return 0;
}
```
**Output:-**

_concurrency!!_

We can pass any callable to thread not necessarily a function.
```cpp
#include<iostream>
#include<thread>

class functor
{
public:
    void operator ()()
    {
        std::cout<<"concurrent functor\n";
    }
};

int main()
{
    std::thread t1([](){
        std::cout<<"concurrent lambda\n";
    });
    t1.detach();  // don't wait for thread to complete.
    functor obj;
    std::thread t2(obj);
    t2.join();

    return 0;
}
```
**Output:-**

_concurrent functor_

_concurrent lambda_

As the main thread have the object of thread it has executed so it can wait for its execution by calling `t.join()`.

When the specified entry point function returns thread exits.

#### Points to remember during thread creation
**C++ most vexing parse** can cause an issue if we pass a temporary instead of a named object. We can handle this issue in two ways.
```cpp
std::thread myThread((backgroundTask())); //put an extra parentheses
std::thread myThread{backgroundTask()}; // uniform initalization
```
In the first example extra parentheses prevent interpretation as a function declaration, allowing myThread to be declared as a variable of type `std::thread`. The second example uses the new uniform initialization syntax with braces rather than parentheses and thus would also declare a variable.

>You should either `detach` the thread or `join` the thread before the thread object goes out of scope. If you don't decide before the `std::thread` object is destroyed, then your program is terminated(the `std::thread` destructor calls `std::terminate()`).

>It's a bad idea to create a thread within a function that has access to the local variables in that function, unless the thread to finish before the function exits. You must ensure that the thread must finish first if it holds pointer or reference to local variable of the function.

****

The act of calling `join()` also cleans up any storage associated with the thread, the `std::thread` object is no longer associated with the now finished thread; it isn't associated with nay thread. This means that you can calls `join()` only once for a given thread; once you've called `join()`, the `std::thread` object is no longer joinable, and `joinable()` will return `false`.

----
#### Exception-safety
An exception can be raised after starting the thread but before calling the `join()`. In this case application will get terminate as `terminate()` will get called.

If you don't want to wait for a thread to finish, you can avoid this exception-safety issue by detaching it. This breaks the association of the thread with the `std::thread` object and ensures that `std::terminate()` won't be called when the `std::thread` object is destroyed, even though the thread is still running in the background.

Detached threads are often called daemon threads after the **UNIX** concept of a daemon process that runs in the background without any explicit user interface.

Detach a thread by calling the `detach()` member function of the std::thread object. After the call completes, the `std::thread` object is no longer associated with the actual thread of execution and is therefore no longer joinable:
```cpp
std::thread t(doBackgroundWork);
t.detach();
assert(!t.joinable());
```

Another way to handle exception-safety is following **RAII**. You can call `join()` in the destructor. When exception will raised objects will get destroyed in reverse order of their creation.

```cpp
class threadGuard
{
    std::thread& m_t;
    public:
    threadGuard(std::thread& t):m_t(t){}
    ~threadGuard()
    {
        if(m_t.joinable())
        {
            m_t.join();
        }
    }
    threadGuard(threadGuard const&) = delete;
    threadGuard& operator=(threadGuard const& obj) = delete;
};
std::thread t2(someFunction);
threadGuard obj(t2); // no need to call join explicitly.
```

`Thread` library is just like `unique_ptr`. At a time only one reference will be there. So when the reference is passed to the **threadGuard** class then the function which created the thread don't have any reference to the thread object.

----
#### Passing argument to thread function
```cpp
void func(int i, std::string const& s);
std::thread t(func, 3, ”people”);
```
If the **func** is taking a reference or pointer then it may cause the dangling pointer problem if the parent thread got exited before the **func** completes its execution.

The below code will not work to pass a non-const reference of a local object. Although **func** expects the second parameter to be passed by reference, the `std::thread` constructor doesn’t know that; it’s oblivious to the types of the arguments expected by the function and blindly copies the supplied values. But the internal code passes copied arguments as **rvalues** in order to work with move-only types, and will thus try to call **func** with an **rvalue**.
```cpp
void func(int i, people& s);
std::thread t(func, 3, people_obj); // will not work!!
```
To pass a non-const reference of a local variable we must use the `std::ref`.
```cpp
std::thread t(func, 3, std::ref(people_obj));
```
To pass a member function as the starting point of thread.
```cpp
X obj;
std::thread t1(&X::memberFunc, &obj);
```
>Instances of `std::thread` are movable, even though they aren’t copyable.

```cpp
std::thread t1(some_function);
std::thread t2=std::move(t1); // Ownership of thread associated with t1 is moved to t2
```
Ownership of a thread can be transferred into a function, it can accept an instance of `std::thread` by value as one of the parameters.
```cpp
void f(std::thread t);
void g()
{
    void some_function();
    f(std::thread(some_function));
    std::thread t(some_function);
    f(std::move(t));
}
```
We can design a scoped_thread class which can manage its own thread by passing the newly created thread instance to the constructor.
> **C++20**'s `std::jthread` is just like the scoped_thread

**TODO:** implement jthread class

#### Choosing the number of threads at Runtime
`std::thread::hardware_concurrency()` returns the total number of threads that can truly run concurrently for a given execution of program. On a multi core machine it will give the number of cores. It's just a hint not always work.

> Thread identifiers of type `std::thread::id`

we can call `get_id()` function of thread object. If we need to check the thread if of current thread then we can call `std::this_thread::get_id()`.

If the `std::thread` object doesn’t have an associated thread of execution, the call to `get_id()` returns a default-constructed `std::thread::id` object, which indicates "not any thread."

`std::thread:id` can be the key of `std::hash`.


#### References

* Concurrency In action

### Authors

* **The Philomath**
