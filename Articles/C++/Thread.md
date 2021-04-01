## About

Basics of thread library support in `C++``

```cpp
std::mutex mut;
void function(int i)
{
  std::lock_guard<std::mutex> lg(mut); //A lock guard is an object that manages a mutex object by keeping it always locked.
                                       //Mutex will automatically get released at end of current scope.
  std::cout<<i;
}
std::thread t(function, i) // create a thread and pass i as argument to it.
t.join(); //join t to main thread
```

instead of `std::lock_guard` we can also use `mut.lock()` and `mut.unlock()` to control when mutex should get locked and when to unlock.
`std::unique_lock<std::mutex> ul(mut);` its similar to `lock_guard`

A `lock_guard` always holds a lock from its construction to its destruction. A `unique_lock` can be created without immediately locking, can unlock at any point in its existence, and can transfer ownership of the lock from one instance to another.

So you always use `lock_guard`, unless you need the capabilities of `unique_lock`. A `condition_variable` needs a `unique_lock`.

We can lock multiple `mutexes` simultaneously. that will prevent the deadlock like:- `std::lock(mut1, mut2);`

----
**Try_lock**

`mut.lock()` is a blocking call. For a non blocking call use `try_lock()` Read comments below.

```cpp
std::mutex foo,bar;

void task_a () {
  foo.lock();
  std::cout << "task a\n";
  bar.lock();     // if task_a will not be able to lock bar then it will not release foo lock also.
  // ...
  foo.unlock();
  bar.unlock();
}

void task_b () {
  int x = try_lock(bar,foo); // non-blocking if either of locking request fails then it will release any locks which was acquired
  if (x==-1) {   // on success return -1 on failure return the first number of lock which it didn't get
    std::cout << "task b\n";
    // ...
    bar.unlock();
    foo.unlock();
  }
  else {
    std::cout << "[task b failed: mutex " << (x?"foo":"bar") << " locked]\n";
  }
}

int main ()
{
  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}
```
----
**recursive_mutex**

When we have function that calls it recursively, and you want to get synchronized access to it:
```cpp
void foo() {
   ... mutex_acquire();
   ... foo();
   ... mutex_release();
}
```
without a recursive mutex you would have to create an "entry point" function first, and this becomes cumbersome when you have a set of functions that are mutually recursive. Without recursive mutex:
```cpp
void foo_entry() {
   mutex_acquire();
   foo();
   mutex_release(); }

void foo() { ... foo(); ... }
```

----

**std::call_once** function ensures a callable is called exactly one time, in a thread safe manner.

It can be used where we need to initialize something only once , say at the startup by any thread. When multiple threads wants to call the initialization only the first one will succeed.

----

**condition_variable**

A condition variable is an object able to block the calling thread until notified to resume. It uses a `unique_lock` (over a mutex) to lock the thread when one of its wait functions is called. The thread remains blocked until woken up by another thread that calls a notification function on the same condition_variable object.

```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready) cv.wait(lck);
  // ...
  std::cout << "thread " << id << '\n';
}

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_id,i);

  std::cout << "10 threads ready to race...\n";
  go();                       // go!

  for (auto& th : threads) th.join();

  return 0;
}
```

**notify_all** notify all the waiting threads. Unblocks all waiting threads.

**notify_one** unblocks one of the waiting threads.

**wait** blocks the current thread until the condition variable is woken up. Some other thread notifies to unblock the thread.

**wait_for** blocks the current thread until the condition variable is woken up or after the specified timeout duration.
```cpp
cv.wait_for(lk, idx*100ms, []{return i == 1;}); //lk is unique_lock
```

**wait_until** blocks the current thread until the condition variable is woken up or until specified time point has been reached

----

**sleep_for** to make the current thread sleep for a time period `std::this_thread::sleep_for(120ms);`

**get_id** return thread id of current thread. `std::thread::id this_id = std::this_thread::get_id();`. To get the id of any thread `t1` we can use `t1.get_id()`.

**joinable** Checks if the std::thread object identifies an active thread of execution. A thread that has finished executing code, but has not yet been joined is still considered an active thread of execution and is therefore joinable.

**native_handle** Accesses the native handle of *this.

The meaning and the type of the result of this function is implementation-defined. On a POSIX system, this may be a value of type `pthread_cond_t*`. On a Windows system, this may be a `PCONDITION_VARIABLE`.

**detach** Separates the thread of execution from the thread object, allowing execution to continue independently. Any allocated resources will be freed once the thread exits. After calling detach *this no longer owns any thread.

**hardware_concurrency** returns numbers of concurrent threads supported by the implementation. The value should be considered as a hint.

**jthread** these are similar to the `std::thread`. If a `std::thread` is still joinable, `std::terminate` is called in its destructor. A thread `thr` is joinable if neither `thr.join()` nor `thr.detach()` was called. `std::jthread` fixes this; it joins on destruction by default (hence the name: "joining thread"). It also supports a mechanism to ask a thread to halt execution, though there is no enforcement of this (aka: you can't make another thread stop executing).

----

**Semaphore**

binary or counting semaphore can be created since `c++20`. Internally binary semaphore is declared like:-
```cpp
binary_semaphore = std::counting_semaphore<1>;
```
To increment the counter we have to use the `release` function and to decrement the counter we have to use the `acquire` function. `max` function gives the maximum possible value of the internal counter. In case of binary semaphore its 2.

----

**Data Race vs Race condition**

Data races can occur when two or thread accessing to same memory. mutual exclusion or mutex is used to avoid it.

Race conditions are flow in timing or ordering of a program's execution that causes incorrect behavior. We can use sleep statements to modify timing and execution order .

Race conditions are a type of _Heisenbug_ -> a software bug that disappear why you try to debug it. Mutexes can't avoid race conditions. We need a barrier for that.

**Barrier** prevents a group of threads from proceeding until enough threads have reached the barrier.

A **latch(value)** is initialized with count value. Latch one or more threads to wait until a set of operation completes. wait() for the latch count value to reach zero. count_down() will decrement the count value.

**Barrier** releases when certain number of threads are waiting.

**Latches** releases when count value reaches to zero.

**ideal parallelism** or the parallelism which we can achieve is work/span

**Thread Pool** Create and maintains a collection of worker threads. Reuses existing threads to execute tasks

**Future** is a placeholder for result which is initially unknown but will be available in future. Its the mechanism to provide the result of asynchronous operation. The one who is providing the result is full-filling a **Promise**.

**Weak Scaling**:- variable number of processors with fixed problem size per processor. Accomplish more work at same time.

**Strong Scaling**:- variable number of processors with fixed total problem size. Accomplish same work in less time.

To calculate the speedup a parallel program can achieve we use **Amdhal's law**
    p is Portion of program that is parallelizable
    S is speedup of the parallelized portion
    Overall speedup = 1/(1-p)+(P/S)

To **Design** a parallel system we should consider these stages

* **Partitioning** :- Domain or functional decomposition

* **Communication** :- point to point communication.  Synchronous or asynchronous, sync are blocking communication as all tasks wait until entire communication cycle complete. Latency, throughput, bandwidth

* **Agglomeration** :- Combine tasks and replicate data/computation to increase efficiency. Granularity = computation/communication fine grained parallelism. large number of small tasks. Coarse grained. Don't hardcore number of processors as they can change in future.

* **Mapping**:- minimize total execution time. Place tasks on different processors that can execute concurrently. Places tasks that can communicate frequently on the same processor.

#### References
[cppreference](https://en.cppreference.com/w/cpp)

### Authors

* **The Philomath**
