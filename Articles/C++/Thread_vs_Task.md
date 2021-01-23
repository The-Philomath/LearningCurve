## About
Is it better to create thread then a task or is it not. lets find out.

To run a function asynchronously we have 2 choices:

1. use thread API to create thread and pass the function to it.
    std::thread t(doSomeWork); // thread based approach

2. use `std::sync` to create a task and pass function to it.
    auto fut = std::async(doSomeWork); // std::async will return an object of std::future , task based approach

**Hardware thread** are the actual threads which run on machine. **Software thread** care created and managed by underlying OS. There can be more software threads than the hardware threads. `std::thread` are objects in c++ that provides handle to the underlying software threads. They can represent null handles(like when fn run finished).

Problem with thread API:
1. The `std::thread` API offers no direct way to get return values from asynchronously run functions and if those functions throw the program terminates.

2. If we want to create thread more than the maximum threads which OS can manage then `std::system_error` exception is thrown. This can be handled by running the function on current thread itself but that can lead to load balancing problem. These can be much observable if current thread is running a GUI based application. Other solution can be wait for other thread to complete execution but it is possible that other thread is waiting for the result of function which we want to execute in first place.

3. Oversubscription: If we want to create a number of thread than OS will do the scheduling for us. thread scheduling itself will tak much more time than the thread execution. This can also leads to situation when OS each time schedule the thread to a different hardware thread and cache mismatch be high. Even if on the same thread this can lead to replacement of some data by previously running thread.

All of these problems can be managed and solved by `std::async` if it runs with default launch policy so we don't need to worry about. `std::async` doesn't guarantee that it will create a new thread each time. It run the new task on the thread which want to run the function in first place. But that lead to same load balancing problem. In that case we can use `std::launch::async` to enforce that a new thread should be created.

**When to use `std::thread`**

* When we need to get the underlying threading implementation. `std::async` don't provide APIs for that.

* We need to and we can optimize thread usage for our applicaiton.

* We need to implement threading technology beyond the C++ concurrency API.

----
**`std::atomic` vs `volatile`**

`std::atomic` offer operations that are guaranteed to be seen as atomic by other threads. Once a `std::atomic` object has been constructed, operations on it behaves as if they were inside a mutex-protected critical sections. Operations are generally implemented using special machine instructions which are more efficient than the case when mutex is employed. Copy operations are restricted for `std::atomic` because compiler would have to genarate code for read and write in a single instruction and those could not be atomic.

`std::atomic` is a tool for writing concurrent software.  Two threads read-modify-writing a `std::atomic` variable can see the values in sequential order means if first update the value than second will see the updated value only.

`volatile` is for memory where read and writes should not be optimized away. It's a tool for working with special memory. Two threads read-modify-writing a `volatile` variable can see the different values or same values. `volatile` don't provide any multi threading supports.

One way of communicating first task to second that a particular value is available is `std::atomic<bool>`.

Generally if program have a set of assignments than compile or underlying hardware can rearrange those assignments to make the code run faster.

like
```
a = b;
c = y;
```
can be rearranged to
```
c = y;
a = b;
```

But using `std::atomic`(using sequential consistency) restricts this reordering. One restriction is that the no code which precedes a write to `std::atomic` may take place afterwards. So in below code it's guaranteed that the all assignments before `val = true;` will get completed before `val = true;`
```cpp
std::atomic<bool> val(false);
auto Value = computeValue();
val = true;
```
volatile don't provide restriction from such reordering.

Suppose we have these assignments
```
volatile int x;
auto y = x;
y = x;

x = 10;
x = 20;
```
Now compiler can optimize these statements like
```
volatile int x;
auto y = x;
x = 20;
```

That would be true if x had been `std::atomic` of a non `volatile` variable. But for `volatile` variables compiler can't optimize like this. Volatile tell compiler that variable belongs to special memory and it can be changes between two right or read operations. like a temperature value or a command on radio.

For `std::atomic` to get the value and write in another `std::atomic` variable we use `load()` and `store()` APIs.
```cpp
std::atomic<int> y(x.load());
y.store(x.load());
```
No copy operation. load and store are the function calls.no need to execute function call and assignment in a single instruction.

#### References

https://hackernoon.com/learn-c-multi-threading-in-5-minutes-8b881c92941f

### Authors

* **The Philomath**
