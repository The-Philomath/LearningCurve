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
    Class<std::string> a = std::string("abc"); // copy-initialization
    Class<std::string> b = "abc";    // error , copy-initialization
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
Class<std::string> b("abc");    // direct-initialization
```

Now there will be only one conversion and that will be

From  _const char *_ to _std::string_

Further we can also use uniform-initialization in place of both the initialization specified in main
```cpp
Class<std::string> a{ std::string("abc") }; // uniform-initialization
Class<std::string> b{ "abc" };    // uniform-initialization
```

We can look uniform-initialization and direct-initialization as
two statements which different kind of intentions. There are two kinds of notions of object initialization:
1) Take all these items and pour them into this object I'm initializing. // uniform-initialization
2) Construct this object using these arguments I provided as a guide. //direct-initialization

#### Benefits of uniform-initialization :-

**Minimizes Redundant Typenames**

Consider the following:
```cpp
vec3 GetValue()
{
  return vec3(x, y, z);
}
```
Why do I need to type vec3 twice? Is there a point to that? The compiler knows good and well what the function returns. Why can't I just say, "call the constructor of what I return with these values and return it?" With uniform initialization, I can:
```cpp
vec3 GetValue()
{
  return {x, y, z};
}
```
Everything works.

Even better is for function arguments. Consider this:
```cpp
void DoSomething(const std::string &str);

DoSomething("A string.");
```
That works without having to type a typename, because _std::string_ knows how to build itself from a _const char*_ implicitly. That's great. But what if that string came from, say RapidXML. Or a Lua string. That is, let's say I actually know the length of the string up front. The _std::string_ constructor that takes a _const char*_ will have to take the length of the string if I just pass a _const char*._

There is an overload that takes a length explicitly though. But to use it, I'd have to do this: ``` DoSomething(std::string(strValue, strLen)).``` Why have the extra typename in there? The compiler knows what the type is. Just like with _auto_, we can avoid having extra typenames:
```cpp
DoSomething({strValue, strLen});
```

But it sometimes mislead when it looks like initialization as pouring into a constructor but it is not like that. e.g. a constructor call:-
```cpp
class Stairs
{
    std::vector<float> stepHeights;

public:
    Stairs(float initHeight, int numSteps, float stepHeight)
    {
        float height = initHeight;

        for (int i = 0; i < numSteps; ++i)
        {
            stepHeights.push_back(height);
            height += stepHeight;
        }
    }
};
```

```Stairs s (2.5, 10, 0.5);```
It's a bad thing that the new standard allows people to initialize Stairs like this:
```Stairs s {2, 4, 6};```

#### Never Get The Most Vexing Parse

```cpp
class Bar;

void Func()
{
  int foo(Bar());
}
```
What is foo? If you answered "a variable", you're wrong. It's actually the prototype of a function that takes as its parameter a function that returns a Bar, and the foo function's return value is an int.

This is called C++'s "Most Vexing Parse".

Uniform initialization cannot be interpreted as a function prototype:
```cpp
class Bar;

void Func()
{
  int foo{Bar{}};
}
```
_Bar{}_ always creates a temporary. _int foo{...}_ always creates a variable.
#### Reasons Not To
The only real power you give up is narrowing. You cannot initialize a smaller value with a larger one with uniform initialization.
```cpp
int val{5.2};
```
That will not compile. You can do that with old-fashioned initialization, but not uniform initialization.

This was done in part to make initializer lists actually work. Otherwise, there would be a lot of ambiguous cases with regard to the types of initializer lists.

There is one other reason not to:
```cpp
std::vector<int> v{100};
```
What does this do? It could create a ```vector<int>``` with one hundred default-constructed items. Or it could create a ```vector<int>``` with 1 item who's value is 100. Both are theoretically possible.

In actuality, it does the latter.

Why? Initializer lists use the same syntax as uniform initialization. So there have to be some rules to explain what to do in the case of ambiguity. The rule is pretty simple: if the compiler can use an initializer list constructor with a brace-initialized list, then it will. Since ```vector<int>``` has an initializer list constructor that takes ```initializer_list<int>```, and {100} could be a valid ```initializer_list<int>```, it therefore must be.

In order to get the sizing constructor, you must use () instead of {}

[StackOverflow]: (https://softwareengineering.stackexchange.com/questions/133688/is-c11-uniform-initialization-a-replacement-for-the-old-style-syntax/133690#133690)

### Authors

* **The Philomath**
