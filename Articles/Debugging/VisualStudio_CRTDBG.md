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

This shows that memory block (normal block) number **73** address **0x006260F8** had allocated a memory of **4 bytes**.
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

There is one shortcoming of this method.
We need to re-run the program with memory block number to get the location of allocated memory block.

To overcome this we can set up the checkpoints in our functions and narrow down to the point where memory was allocated. We can keep these checkpoints in our debug build which will give us extra info about the possible leak of memory.

-----
```cpp
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC

int main()
{
    // store crt memory state and calculate the difference
    _CrtMemState begin, end, diff;
    _CrtMemCheckpoint(&begin);

    int *p = new int(3);

    _CrtMemCheckpoint(&end);

    // if there is a difference in memory state means there is a leak
    if (_CrtMemDifference(&diff, &begin, &end) == 1)
    {
        // dump memory statistics
        _CrtMemDumpStatistics(&diff);
        std::cout << "mem leak at " << __func__ << std::endl;
        std::cout << __FILE__<< std::endl;
    }

    system("pause");
    return 0;
}
```
-----

**Sample Output:-**

  _0 bytes in 0 Free Blocks.  
   4 bytes in 1 Normal Blocks.  
   0 bytes in 0 CRT Blocks.  
   0 bytes in 0 Ignore Blocks.  
   0 bytes in 0 Client Blocks.  
   Largest number used: 0 bytes.  
   Total allocations: 4 bytes._

**Console Output:-**

  _mem leak at main  
   c:\users\ThePhilomath\documents\visual studio 2015\projects\test\test\main.cpp_

There is one shortcoming of this method that we have to but the checks in every suspected function beforehand.


We can further improve this by creating a Macro based approach and instead of adding all  crt checkpoints in every function we can simply include Macro to all the functions.

-----
Helper.h
```cpp
#pragma once
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC

class CrtStateChecker
{
    const char *pfName;
    const char *pfuncName;
    _CrtMemState beg, end, diff;
public:
    CrtStateChecker(const char *file, const char *function)
    {
        pfName = file;
        pfuncName = function;
        _CrtMemCheckpoint(&beg);
    }
    ~CrtStateChecker()
    {
        _CrtMemCheckpoint(&end);
        if (_CrtMemDifference(&diff, &beg, &end) == 1)
        {
            _CrtMemDumpStatistics(&diff);
            std::cout << "mem leak at" << std::endl << pfuncName;
            std::cout << std::endl << pfName << std::endl;
        }
    }
};

#define CRT_CHECKPOINT CrtStateChecker obj(__FILE__, __FUNCSIG__)
```

Main.cpp

```cpp
#include "DebugHelper.h"

char* process()
{
    CRT_CHECKPOINT;
    char* buff = new(_NORMAL_BLOCK, __FILE__, __LINE__) char(5);
    return buff;
}

int main()
{
    process();

    system("pause");
    return 0;
}
```

This way we only need to add **CRT_CHECKPOINT** macro in every suspected funcion.


-----
Helper.h
```cpp
#pragma once
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC

class CrtStateChecker
{
    const char *pfName;
    const char *pfuncName;
    _CrtMemState beg, end, diff;
public:
    CrtStateChecker(const char *file, const char *function)
    {
        pfName = file;
        pfuncName = function;
        _CrtMemCheckpoint(&beg);
    }
    ~CrtStateChecker()
    {
        _CrtMemCheckpoint(&end);
        if (_CrtMemDifference(&diff, &beg, &end) == 1)
        {
            _CrtMemDumpStatistics(&diff);
            std::cout << "mem leak at" << std::endl << pfuncName;
            std::cout << std::endl << pfName << std::endl;
        }
    }
};

#define CRT_CHECKPOINT CrtStateChecker obj(__FILE__, __FUNCSIG__)
```

Main.cpp

```cpp
#include "DebugHelper.h"

char* process()
{
    CRT_CHECKPOINT;
    char* buff = new(_NORMAL_BLOCK, __FILE__, __LINE__) char(5);
    return buff;
}

int main()
{
    process();

    system("pause");
    return 0;
}
```
-----

This way we only need to add **CRT_CHECKPOINT** macro in every suspected funcion.

### Authors

* **The Philomath**
