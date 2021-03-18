How to sort an array of size of more than the size of RAM? Or Sort a million 32 bit integers using only 2MB of RAM

The concept used to sort these types of problems is known as external sorting - divide and conquer.

A million integers will take a size of 32 * 10^6 bits ~ 4 * 10^6 bytes ~ 4 MB . So we need to sort 4MB of integers using 2 MB of RAM.

**Steps:-**

1. read half the list into 2MB ram and sort using quicksort (quicksort uses logn space - however 0.5m integers is less than 2MB (2000kb v 2048kb) so this should be okay).
2. write sorted data to disk
3. repeat for next chunk
4. merging results: we need an output buffer. lets say this is 1MB. then we read 512KB from each of your chunks into input buffers. we then perform a 2-way merge of the data. when an input buffer becomes empty we can pull in the remainder of the chunk.
5. when the output buffer is full we write this to disk.
6. when the process completes we are left with 2x 1MB files sorted in the correct order.

notes:

- when choosing an input buffer size, the smaller we make it the more I/O operations we will need to perform which would significantly slow down our sorting. a smaller output buffer would also do the same. we would rather a smaller output buffer as multi-threading would allow sorting to continue while writing to disk.
- we could use an additional thread to load next chunk from disk when input buffer drops below half size.
- HDD mirror raid would increase sequential read and write speed to disk as well as HDD speed
- compression of input would also reduce I/O
- we choose quicksort over mergesort as mergesort requires O(n) space. quicksort therefore reduces the number of merge operations.
