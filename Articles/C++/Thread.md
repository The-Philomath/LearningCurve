## About

Just basic of thread library support from c++

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
```
void foo_entry() {
   mutex_acquire(); foo(); mutex_release(); }

void foo() { ... foo(); ... }
```
----
**std::call_once** function ensures a callable is called exactly one time, in a thread safe manner.
It can be used to where we need to initialize something only once , say at the startup by any thread.
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
notify_once
wait_for
wait_until
----
get_id
joinable
native_handle
detach
