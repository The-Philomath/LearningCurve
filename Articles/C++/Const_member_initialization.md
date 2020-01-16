## About
A detailed overview of a constant member initialization.

**const member must be initialized**

initialization can be in class initialization or in the parameterized list of the constructor.

As soon as compiler sees a constant member it deletes the default constructor. This way compiler enforce us to do the initialization of constant member

let's take an example:
```cpp
class constructors
{
    int data;
    const int const_data; // Compiler deletes default constructor
public:

};

int main()
{
    constructors obj1; // calling default constructor
    return 0;
}
```
**Output:-**

_error C2280: 'constructors::constructors(void)': attempting to reference a deleted function_

If we provide a default constructor but don't initialize the constant member then compiler will give us an error saying const-qualified type must be initialized.

```cpp
class constructors
{
    int data;
    const int const_data; // Compiler deletes default constructor
public:
    constructors() // user defined default constructor
    {}
};
```
**Output:-**
_error C2789: 'constructors::const_data': an object of const-qualified type must be initialized_

**in-class initialization**

No compilation error. Default construction will work.
Now compiler will provide the default constructor if there will be no user defined default constructor.
```cpp
class constructors
{
    int data;
    const int const_data{ 2 }; // Compiler don't deletes default constructor as we are initializing const here
public:
    constructors() // optional user defined default constructor
    {}
};
```
This was **illegal** before C++11. A non static constant member can't be initialized like this. We have to make the variable static as well or we can use the constructor parameter list as initialization.

**mem-initializer-list**
```cpp
class constructors
{
    int data;
    const int const_data; // Compiler deletes default constructor
public:
    constructors(int d) : const_data(d)
    {}
};

int main()
{
    constructors obj1(1); // calling parameterized constructor to initialized const member.
    return 0;
}
```

if we provide both types of initialization then also only one definition is provided by compiler.

Instead of resulting in multiple definitions for the linker to sort out, it will results in one definition, and the compiler has to sort it out.

If a member is initialized by both an in-class initializer and a constructor, only the constructor's initialization is done (it "overrides" the default).

```cpp
class constructors
{
    int data;
    const int const_data { 3 }; // Compiler don't deletes default constructor
public:
    constructors(int d) : const_data(d) // default constructor hides
    {}
};
```
making in-class initialization as legal in C++11 doesn't mean that member will be initialized without a constructor call.

In other words, the initialization is still tied with constructor, just the notation is different.

If the constructor is called, the values are initialized with in-class initialization if present or the constructor can override that with own initialization. The path of initialization is essentially the same, that is, via the constructor.


### Authors

* **The Philomath**
