## About
Is it better to create thread then a task or is it not. lets find out.

To run a function asynchronously we have 2 choices:

1. use thread API to create thread and pass the function to it.
    std::thread t(doSomeWork); // thread based approach

2. use `std::async` to create a task and pass function to it. Tasks consist of two components, which are connected by a communication channel. One component as endpoint of the channel produces the result, while the other endpoint consumes it. The producer is called Promise, the consumer Future.
    auto fut = std::async(doSomeWork); // std::async will return an object of std::future<T> , task based approach

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

```cpp
void Test::runMultiThread()
{
    std::thread t1(&Test::calculate, this,  0, 10);
    std::thread t2(&Test::calculate, this, 11, 20);
    t1.join();
    t2.join();
}
```
OR
```cpp
void Test::runMultiThread()
{
     auto f1 = std::async(&Test::calculate, this,  0, 10);
     auto f2 = std::async(&Test::calculate, this, 11, 20);

     auto res1 = f1.get(); // return result
     auto res2 = f2.get();
}
```
----

In C++17 most of the standard algorithms can be called with execution policies like this
```cpp
std::for_each(std::execution::seq, std::begin(v), std::end(v), function_call);
```
3 execution policies which we can use are:
`std::execution::seq` stands for sequential execution. It is the default if you do not specify the execution policy at all. It will force the implementation to execute all function calls in sequence. It is also guaranteed that everything is executed by the calling thread.

In contrast, `std::execution::par` and `std::execution::par_unseq` implies parallel execution. That means you promise that all invocations of the given function can be safely executed in parallel without violating any data dependencies. The implementation is allowed to use a parallel implementation, though it is not forced to do so.

`par_unseq` requires stronger guarantees than `par`, but allows additional optimizations. Specifically, `par_unseq` requires the option to interleave the execution of multiple function calls in the same thread.

----

In the words of `[futures.state]` a `std::future` is an asynchronous return object ("an object that reads results from a shared state") and a `std::promise` is an asynchronous provider ("an object that provides a result to a shared state") i.e. a promise is the thing that you set a result on, so that you can get it from the associated future.

----


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

----
Since `C++20`

**Atomic smart pointer** `std::shared_ptr` and `std::weak_ptr` provides the guarantee that the incrementing and decrementing of reference count will be atomic and underlying resource will be deleted only one. But they have mutable states and doesn't guarantee that access to shared resources will be atomic operations. So they are prone to _data race_ and UB.

Atomic smart pointers solved this issue
```cpp
std::atomic_shared_ptr
std::atomic_weak_ptr
```

**Future extension** before `C++20` `std::future` can not be composed. In `C++20` a future becomes ready, when

* its predecessor becomes ready:
`then`
```cpp
future<int> f1= async([]() {return 123;});
future<string> f2 = f1.then([](future<int> f) {     
  return f.get().to_string();
});
```
* one of its predecessors become ready:
`when_any`
```cpp
future<int> futures[] = {async([]() { return intResult(125); }),                          
                         async([]() { return intResult(456); })};
future<vector<future<int>>> any_f = when_any(begin(futures),end(futures));
```
* all of its predecessors become ready:
`when_all`
```cpp
future<int> futures[] = {async([]() { return intResult(125); }),                          
                         async([]() { return intResult(456); })};
future<vector<future<int>>> all_f = when_all(begin(futures), end(futures));
```

**latches and barriers**

You can use latches and barriers for waiting at a synchronisation point until the counter becomes zero. The difference is, `std::latch` can only be used once; `std::barrier` and `std::flex_barrier` more the once. In contrary to a `std::barrier`, a `std::flex_barrier` can adjust its counter after each iteration.

```cpp
void doWork(threadpool* pool){
  latch completion_latch(NUMBER_TASKS);
  for (int i = 0; i < NUMBER_TASKS; ++i){
    pool->add_task([&]{
      // perform the work
      ...
      completion_latch.count_down();
    });
  }
  // block until all tasks are done
  completion_latch.wait();
}
```
The thread running the function _doWork_ is waiting in line 11 until the `completion_latch` becomes 0. The `completion_latch` is set to NUMBER_TASKS in line 2 and decremented in line 7.

**Coroutines**

These are functions which remembers their state. When we call them again then their execution starts from the same points where we left them. Coroutines are often the means of choice to implement cooperative multitasking in operating systems, event loop, infinite lists, or pipelines.
```cpp
generator<int> getInts(int first, int last){
  for (auto i= first; i <= last; ++i){
    co_yield i;
  }
}

int main(){
  for (auto i: getInts(5, 10)){
    std::cout << i << " ";                      // 5 6 7 8 9 10
}
```

The function `getInts (line 1 - 5)` gives back a generator that returns on request a value. The expression `co_yield` serves two purposes. At first, it returns a new value and at second, it waits until a new value is requested. The range-based for-loop successively requests the values from 5 to 10.

**Transcational memory**

Transactional memory idea is based on transactions from the database theory. A transaction is an action which provides the properties Atomicity, Consistency, Isolation and Durability (ACID). Except for durability, all properties will hold for transactional memory in C++. C++ will have transactional memory in two flavours. One is called synchronised blocks and the other atomic blocks. Both have in common that they will be executed in total order and behave as they were protected by a global lock. In contrary to synchronised blocks, atomic blocks can not execute transaction-unsafe code.

Therefore, you can invoke `std::cout` in a synchronised block but not in an atomic block.

```cpp
int func() {
  static int i = 0;
  synchronized{
    std::cout << "Not interleaved \n";
    ++i;
    return i;  
  }
}

int main(){
  std::vector<std::thread> v(10);
  for(auto& t: v)
    t = std::thread([]{ for(int n = 0; n < 10; ++n) func(); });
}
```
The `synchronized` keyword in line 3 guarantees that the execution of the synchronised block (line 3 - 7) will not overlap. That means in particular that there is a single, total order between all synchronised blocks. To say it the other way around. The end of each synchronised block synchronizes-with the start of the next synchronised block.

**Task Blocks**

Task Blocks implement the fork-join paradigm.

By using `run` in a task block you can fork new tasks that will be joined at the end of the task block.

```cpp
template <typename Func>
int traverse(node& n, Func && f){
    int left = 0, right = 0;
    define_task_block(                 
        [&](task_block& tb){
            if (n.left) tb.run([&]{ left = traverse(*n.left, f); });
            if (n.right) tb.run([&]{ right = traverse(*n.right, f); });
         }
    );                                                         
    return f(n) + left + right;
}
```
_traverse_ is a function template that invokes the function _Func_ on each node of its _tree_. The expression `define_task_block` defines the task block. In this region, you have a task block tb to your disposal to start new tasks. Exactly that is happening in the left and right branch of the tree (line 6 and 7). Line 9 is the end of the task block and therefore the synchronisation point.

----

**Semaphore**

A semaphore is a data structure with a queue and a counter. Queue is for the threads to wait. `Wait` is used by a thread when it acquire a semaphore and decrement the counter. `Signal` is used when thread releases semaphore.

`C++20` supports binary semaphore. They are defined like this
```cpp
using binary_semaphore = std::counting_semaphore<1>;
```
In contrast to a `std::mutex`, a `std::counting_semaphore` is not bound to a thread. This means, that the acquire and release call of a semaphore can happen on different threads

The constructor call `std::counting_semaphore<10> sem(5)` creates a semaphore sem with a at least maximal value of 10 and a counter of 5. The call `sem.max()` returns the least maximal value.

```cpp
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::vector<int> myVec{};
std::counting_semaphore<1> prepareSignal(0);              // (1)

void prepareWork() {

    myVec.insert(myVec.end(), {0, 1, 0, 3});
    std::cout << "Sender: Data prepared."  << '\n';
    prepareSignal.release();                              // (2)
}

void completeWork() {
    std::cout << "Waiter: Waiting for data." << '\n';
    prepareSignal.acquire();                              // (3)
    myVec[2] = 2;
    std::cout << "Waiter: Complete the work." << '\n';
    for (auto i: myVec) std::cout << i << " ";
    std::cout << '\n';
}

int main() {

    std::cout << '\n';

    std::thread t1(prepareWork);
    std::thread t2(completeWork);

    t1.join();
    t2.join();

    std::cout << '\n';
}
```

#### References

[StackOverflow](https://stackoverflow.com/questions/11004273/what-is-stdpromise)

[Modernes](https://www.modernescpp.com/index.php/component/jaggyblog/semaphores-in-c-20)

https://hackernoon.com/learn-c-multi-threading-in-5-minutes-8b881c92941f

### Authors

* **The Philomath**
