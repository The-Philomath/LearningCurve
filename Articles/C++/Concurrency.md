## About
Basics of concurrency.

* `Concurrency` is a single system which can perform multiple tasks in parallel instead of running them in a sequence one after the other.

* `Task switching` is used to give the illusion of running tasks in parallel but actually there are all running in a sequence. At a time OS can run only one task on a single core machine. To give the illusion of concurrent execution, OS switches between the active and waiting tasks. It is also known as the context switch as OS switches the context of processes.

* `Hardware concurrency` is the number of processors of cores on a single processor. It is the actual number of tasks which the machine can run in parallel instead of giving an illusion of concurrent execution. `Hardware thread` is the measure of hardware concurrency.

* Concurrency can be achieved by multiprocessing and multithreading. Both have their own advantage and disadvantage.

* `Multiprocessing` disadvantage is that the IPC is complicated to setup and slow and it will take a lot of resources for each process.OS devote resource to maintain each process. OS takes measures so that processes don't override each other's address space. Advantage is that extra protecting by OS helps to easily maintain concurrency. Multiple processes can be run over a network on different machines.

* `Multithreading` advantage is that the multiple threads shared address space, so less resources consumed. The shared address space and lack of protection of data between threads makes the overhead associated with using multiple threads much smaller than that from using multiple processes, because the operating system has less bookkeeping to do. Disadvantage is that the application programmer must ensure that the view of data seen by each thread is consistent whenever it’s accessed.

* `Parallelism` is taking advantage of the available hardware to increase the performance of bulk data processing, whereas people talk about concurrency when their primary concern is separation of concerns, or responsiveness. But its quite vague and most of the times their definition overlaps.

* There can only be one out of two **Reasons** to use concurrency
   1. Separation of concern
   2. Performance

 all other reasons boils down to only these two reasons.

* Concurrency for Performance can be used in two ways: Task parallelism and data parallelism

* Algorithms to achieve data parallelism are readily susceptible to parallelism are frequently called embarrassingly parallel.

* **Disadvantage of concurrency**:
    * Concurrent code is hard to understand. Intellectual cost and maintenance cost is there. Such codes are prone to bugs.
    * The performance gain might not be as large as expected; there’s an inherent overhead associated with launching a thread, because the OS has to allocate the associated kernel resources and stack space and then add the new thread to the scheduler, all of which takes time.
    * Address space exhaust, each thread requires its own stack.
    * Task switch, may be creating the thread itself take more time than the work the thread will do.
    * Resources are limited. limited resource may cause other applications go slow.

* `Abstraction penalty` is the implementation costs associated with using any high-level facilities, compared to using the underlying low-level facilities directly.

* The types in the C++ Thread Library may offer a `native_handle()` member function that allows the underlying implementation to be directly manipulated using a platform-specific API. After getting native_handle and performing operations on this are platform dependent, so it will be an unportable code, so one must consider before using native_handle directly.

* Every thread has to have an initial function. This function is used as the starting point for thread.

* `Hyper-threading` exposes multiple logical cores for a single physical CPU core. In simple terms, hyper-threading makes context-switching more efficient for each CPU core.

#### References

* Concurrency In action

### Authors

* **The Philomath**
