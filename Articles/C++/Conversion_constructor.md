## About
conversion constructor `implicitly` convert one data type to the other data type.

**C++03: §12.3.1**

> A constructor declared without the _function-specifier_ `explicit` that can be called with a single parameter specifies a conversion from the type of its first parameter to the type of its class. Such a constructor is called a converting constructor.

**C++11: §12.3.1**

>A constructor declared without the _function-specifier_ `explicit` specifies a conversion from the types of its parameters to the type of its class. Such a constructor is called a converting constructor.

So as per C++11 standard its not necessary that the constructor should be a single argument constructor.

In below code an `int` is converted to `constructor` type.

```cpp
class constructors
{
    int data;
public:
    constructors(int d):data(d)
    {
        std::cout << "single argument constructor get called" << std::endl;
    }
};

void func(constructors obj)
{ // do something with obj
}

int main()
{
    func(3);
    return 0;
}
```
**Output:-**

_single argument constructor get called_

Compiler always go for the exact match if an exact match constructor is provided.

In the below example we are calling the `func` with a character so a character version of constructor will get called.
```cpp
class constructors
{
    int data;
public:
    constructors(int d):data(d)
    {
        std::cout << "single argument constructor get called" << std::endl;
    }
    constructors(char c)
    {
        std::cout << "char single argument constructor get called";
    }
};

int main()
{
    func('a');
    return 0;
}
```
**Output:-**

_char single argument constructor get called_

Making the `char` constructor as explicit prevent compiler from calling the `char` constructor implicity. Compiler will still try to do the implicit conversion by calling constructor with `int` argument.
```cpp
class constructors
{
    int data;
public:
    constructors(int d):data(d)
    {
        std::cout << "single argument constructor get called" << std::endl;
    }
    explicit constructors(char c)
    {
        std::cout << "char single argument constructor get called";
    }
};

int main()
{
    func('a');
    return 0;
}
```
**Output:-**

_single argument constructor get called_

Why are constructors with more than a single parameter considered to be converting constructors in **C++11**? That is because the new standard provides us with some handy syntax for passing arguments and returning values using `braced-init-lists`. Consider the following example:
```cpp
constructors func(constructors f)
{
  return {1.0f, 5};
}
```
The ability to specify the return value as a `braced-init-list` is considered to be a conversion. This uses the converting constructor for `constructors` that takes a `float` and an `int`. In addition, we can call this function by doing `bar({2.5f, 10})`. This is also a conversion. Since they are conversions, it makes sense for the constructors they use to be converting constructors.

It is important to note, therefore, that making the constructor of `constructors` which takes a `float` and an `int` have the `explicit` function specifier would stop the above code from compiling.

same way constructors with no arguments considered as converting constructors in **C++11**
```cpp
constructors func()
{
    return{};
}
```
It will return an object created using a default constructor which should be implicitly callable.
### Authors

* **The Philomath**
