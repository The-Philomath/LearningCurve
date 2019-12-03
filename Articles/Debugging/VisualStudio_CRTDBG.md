## About
This article is an overview of using debugging in Visual studio using CRT(C Run-Time) library APIs. Make sure that code is compiled in debug mode

------
```cpp
#include <stdlib.h>
#include <crtdbg.h>

// When the _CRTDBG_MAP_ALLOC flag is defined in the debug version of an application,
// the base version of the heap functions are directly mapped to their debug versions.
// The flag is used in Crtdbg.h to do the mapping. This flag is only available when the _DEBUG flag has been defined in the application.
// Note: Define it after header file inclusion otherwise application debugging will be very slow as the mapping will also be enabled in header file.
#define _CRTDBG_MAP_ALLOC

int main()
{
    // Turn on debug allocation | Leak Check at program Exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int *p = new int(3);

    // Dumps all the memory blocks in the debug heap when a memory leak has occurred
    _CrtDumpMemoryLeaks();

    return 0;
}
```
------

**Sample Output:-** 

  _Detected memory leaks!  
   Dumping objects ->  
   {73} normal block at 0x006260F8, 4 bytes long.  
    Data: <    > 03 00 00 00  
   Object dump complete._

This shows that memory block number **73** address **0x006260F8** had allocated a memory of **4 bytes**.
**03** is stored at first byte as my system is little endian.
This memory got leaked.

But it is not pointing out to the exact location where memory was allocated and which was not freed.

To find out exact location we will put a break point on block number **73** which is not freed.

------
```cpp
{
    _CrtSetBreakAlloc(73);
    // Turn on debug allocation | Leak Check at program Exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

break ==>   int *p = new int(3);

    // Dumps all the memory blocks in the debug heap when a memory leak has occurred
    _CrtDumpMemoryLeaks();
}
```
------

Code will hit the break point and we can figure out which memory was not freed.

### Authors

* **The Philomath**
