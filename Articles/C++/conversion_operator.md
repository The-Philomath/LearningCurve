## About
conversion operator/function enables implicit conversion or explicit conversion from a class type to another type.

It's behavior is opposite to [Conversion constructor](Conversion_constructor.md). When such member function is declared in class `Test`, it performs conversion from `Test` to `conversion-type-id`:

Conversion function is declared like a `non-static member function` or `member function template` with no parameters, no explicit return type, and with the name of the form:

* Declares a user-defined conversion function that participates in all implicit and explicit conversions
```
operator conversion-type-id
```
* Declares a user-defined conversion function that participates in direct-initialization and explicit conversions only.
```
explicit operator conversion-type-id	(since C++11)
```

Here is an example:

In below code; on `std::cout << func();` First the implicit default constructor will get called. which will return an object of `constructors` type. As there is no `operator<<` is overloaded for `constructors` class so the second best option for compiler to perform a conversion. so `operator int()` will get called and it will return an integer.

```cpp
class constructors
{
    int data;
public:
    constructors()
    {
       std::cout<< "default constructor" <<std::endl;
    }
    operator int()
    {
        std::cout << "conversion operator get called" <<std::endl;
        return data;
    }
};

constructors func()
{
    return{};
}
int main()
{
    std::cout << func(); // valid
    int data = func();  // valid
    int data2 = static_cast<int>(func()); //valid
    return 0;
}
```
**Output:-**

_default constructor  
 conversion operator get called  
 -8589939464_

**using auto**

 The placeholder `auto` can be used in `conversion-type-id`, indicating a deduced return type:

 **since C++14**
 ```cpp
 operator int(); // OK
 operator auto() -> short;  // error: trailing return type not part of syntax
 operator auto() const { return 10; } // OK: deduced return type
```

we can define the operator as explicit to not allow implicit conversions.
```
explicit operator int();
```
now from the previous example
```
int data = func();  // its invalid
int data2 = static_cast<int>(func()); //valid
```

Note that conversion functions are never used to convert to the same class type or to a base class type except, in some cases, through virtual dispatch

```cpp
struct Derived;
struct Base {
    virtual operator Derived() = 0;
};
struct Derived : Base
{
    operator Derived() override { return Derived(); }
};

int main()
{
    Derived obj;
    Derived obj2 = obj; // does not call Derived::operator Derived()
    Base& br = obj;
    Derived obj3 = br; // calls Derived::operator Derived() through virtual dispatch
}
```

**Conversion to reference**

In the conditional operator, conversion to a reference type is possible, if the type converted to is an lvalue.
```cpp
struct B { };
struct A {
  operator B&() { static B b; return b; }
};

int main() { B b; 0 ? b : A(); } // called!
```
Another conversion to reference is when you bind a reference, directly
```cpp
struct B { };
struct A {
  operator B&() { static B b; return b; }
};

B &b = A(); // called!
```
**Conversion to function pointers**

You may have a conversion function to a function pointer or reference, and when a call is made, then it might be used.
```cpp
typedef void (*fPtr)(int);

void foo(int a);
struct test {
  operator fPtr() { return foo; }
};

int main() {
  test t; t(10); // called!
}
```
This thing can actually become quite useful sometimes.

**Conversion to non class types**

The implicit conversions that happen always and everywhere can use user defined conversions too. You may define a conversion function that returns a `boolean` value
```cpp
struct test {
  operator bool() { return true; }
};

int main() {
  test t;
  if(t) { ... }
}
```
(The conversion to `bool` in this case can be made safer by the safe-bool idiom, to forbid conversions to other integer types.) The conversions are triggered anywhere where a built-in operator expects a certain type. Conversions may get into the way, though.
```cpp
struct test {
  void operator[](unsigned int) { }
  operator char *() { static char c; return &c; }
};

int main() {
  test t; t[0]; // ambiguous
}
```
```
// (t).operator[] (unsigned int) : member
// operator[](T *, std::ptrdiff_t) : built-in
```
The call can be ambiguous, because for the member, the second parameter needs a conversion, and for the built-in operator, the first needs a user defined conversion. The other two parameters match perfectly respectively. The call can be non-ambiguous in some cases (`ptrdiff_t `needs be different from `int` then).

**Conversion function template**

Templates allow some nice things, but better be very cautious about them. The following makes a type convertible to any pointer type (member pointers aren't seen as "pointer types").
```cpp
struct test {
  template<typename T>
  operator T*() { return 0; }
};

void *pv = test();
bool *pb = test();
```
### Authors

* **The Philomath**
