## About
A detailed overview of a static member initialization.

**static declaration**

An in-class static member is considered only as a declaration of the static member.
Usually a non-static member can be defined via the constructor call but for static member
no constructor will get called. So we have to explicitly define it outside the class.

let's take an example:
```cpp
class constructors
{
    int data;
    static int const_data; // it's a declaration
public:
};

int main()
{
    constructors obj1; // calling default constructor
    return 0;
}
```
**Output:-**

_error LNK2001: unresolved external symbol "private: static int constructors::const_data" (?const_data@constructors@@0HA)_

It's a **linker error** not a compiler error. All unresolved symbol errors are always linker errors. An unresolved symbol is the symbol in binary file for which definition is not provided.

in-class initialization will not do much good either. It pushes up the error to the compilation step.

```cpp
class constructors
{
    int data;
    static int const_data { 3 }; // in-class initialization
public:
};
```
**Output:-**

_error C2864: 'constructors::const_data': a static data member with an in-class initializer must have non-volatile const integral type_

It says `static` member should be a `non-volatile const` to get it initialized in class.

```cpp
class constructors
{
    int data;
    static const int const_data { 3 }; // in-class initialization
public:
};
```
now the value of const_data will be 3 and there is no error in it.

Remember that we can't initialize `static` member via constructor call no matter whether its a `const` or `non-const`.

**static member definition**
we have to provide definition of static member as shown below.
```cpp
class constructors
{
    int data;
    static int const_data; // it's a declaration
public:
};
int constructors::const_data = 5; // definition
```

`const` and `volatiles` are type modifiers, but `static`, `virtual` are not. The type of member should be same during declaration and definition. So if a member is declared as `const` inside class we can't define it without `const`(see below). but for static members we can do that(refer above example).
```cpp
class constructors
{
    int data;
    static const int const_data; // it's a declaration
public:
};
int constructors::const_data = 5; // definition
```
**Output:-**

_error C2373: 'const_data': redefinition; different type modifiers_

**static-const member initialization**

Once we initialize the `static const` memebr its definition is created. It could be inside the class or outside.
If we initialize at both inside and outside the class it will be an error. As we can't initialize a constant twice.

```cpp
class constructors
{
    int data;
    static const int const_data { 3 }; // compiler treat it as a definition because its a constant member.
public:
};
const int constructors::const_data = 5; // definition
```
**Output:-**

_error C2374: 'const_data': redefinition; multiple initialization_

In below code there is no error and value of const_data will be 5.
```cpp
class constructors
{
    int data;
    static const int const_data; // compiler treat it as a definition because its a constant member.
public:
};
const int constructors::const_data = 5; // definition
```

### Authors

* **The Philomath**
