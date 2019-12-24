## About
What is copy-initialization, direct-initialization, uniform initialization etc. Understanding the issues with them and solutions.

```cpp
#include <string>
#include <iostream>

template <typename Type>
struct Class
{
    Type data;
    Class(Type data) : data(data) { }
};

int main()
{
    Class<std::string> a = std::string("abc"); // copy initialization
    Class<std::string> b = "abc";    // error , copy initialization
    std::cout << a.data << std::endl;
    return 0;
}
```

There is an error in above and the reason is that we are performing copy-initialization.
in copy-initialization we are performing two conversions:-
1. From  _const char *_ to _std::string_
2. Fom _std::string_ to _Class<std::string>_

But at max only one conversion is allowed.

We can use direct-initialization in place of copy-initialization to solve this problems.
```cpp
Class<std::string> b("abc");
```

Now there will be only one conversion and that will be
From  _const char *_ to _std::string_

Further we can also use uniform-initialization inplace of both the initliaztion specified in main
```cpp
Class<std::string> a{ std::string("abc") }; // uniform initialization
Class<std::string> b{ "abc" };    // uniform initialization
```

### Authors

* **The Philomath**
