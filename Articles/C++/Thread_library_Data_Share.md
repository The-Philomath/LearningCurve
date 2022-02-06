## About
Thread library support in C++.

> If all shared data is read-only, there’s no problem, because the data read by one thread is unaffected by whether or not another thread is reading the same data.

So the problem is sharing the modify-able data between threads.

**Invariants** are the statements that holds true for a data structure. The invariants are often broken during an update on a data structure. Invariant should hold after the update is complete. If a thread accesses the data structure while another one is updating it then the broken invariant can cause an issue, its known as **Race condition**. It a type of **data race**.

So a Race condition is anything where outcome depends upon the relative order of execution of two or more threads.

#### Ways to avoid race conditions

* using synchronisation mechanism

* lock-free programming

* transactions

**Transaction** are data-modification are stored in transaction logs and later committed in a single step. If the commit can’t proceed because the data structure has been modified by another thread, the transaction is restarted. This is termed **software transactional memory (STM)**.

#### Mutex

`lock()` is used to acquire the mutex. `unlock()` to release a mutex.

`lock_guard` will release the mutex at the end of scope.
```cpp
std::mutex mut;
std::lock_guard<std::mutex> lg(mutex);

std::lock_guard lg(mutex); //C++17 class template argument deduction

std::scoped_lock sl(mutex); //C++17 unlike lock_guard it can acquire locks on multiple mutexes at once. Its variadic.
```
> Don’t pass pointers and references to protected data outside the scope of the lock, whether by returning them from a function, storing them in externally visible memory, or passing them as arguments to user-supplied functions.

**Deadlock** is quite opposite to race condition, rather than two threads racing to be first, each one is waiting for the other, so neither makes any progress.

Always lock mutexes in the same order to avoid the deadlock.

Attempting to acquire a lock on `std::mutex` when you already hold it is *undefined behavior*.

`std::recursive_mutex` allows multiple locks by same thread.

If we try to acquire multiple locks using `std::lock` and while acquiring second lock it throws an exception, then first lock will get released. `std::lock` provides all-or-nothing semantics with regard to locking the supplied mutexes

The `std::adopt_lock` parameter to `std::lock_guard` can be supplied in addition to the mutex to indicate to the `std::lock_guard` objects that the mutexes are already locked, and they should adopt the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor.

#### Guidelines to avoid deadlock
* Don't acquire another lock if you already acquired one. If you need to acquire multiple locks then do that in a single `std::lock` call.

* Avoid calling user defined code while you have a lock. As the user supplied code may acquire a lock and that may lead to deadlock scenario.

* Acquire multiple locks in same order in every thread.

* Define a lock hierarchy: idea is to divide the application into layers. and identify all the mutexes that can be acquired in that layer. if code already have a lock from lower layer, then it will not allow to acquire the lock of higher layer.

> We can use user defined mutex classes in `std::lock_guard<>` but that class must satisfy the mutex concept for that it needs to implement the three functions i.e. `lock()` `unlock()` and `try_lock()`.

**try_lock()** if the lock on the mutex is held by another thread, it returns **false** rather than waiting until the calling thread can acquire the lock on the mutex.

**thread_local** declare a variable which has a separate copy for each thread.

Instead of mutexes, `std::call_once()` can be used to handle the scenario of initialisation only once when multiple threads are trying to execute the initialisation code.

 A **reader-writer mutex**, allows two different kinds of usage: exclusive access by a single “writer” thread or shared, and concurrent access by multiple “reader” threads. `std::shared_mutex` and `std::shared_timed_mutex` are those types of mutexes.

 With `std::mutex`, it’s an error for a thread to try to lock a mutex it already owns, and attempting to do so will result in **undefined behavior**. If a thread wants to do that then we should use `std::recursive_mutex`.

#### References

* Concurrency In action

### Authors

* **The Philomath**
