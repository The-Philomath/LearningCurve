## About
A constructor which can be called without any parameter is a default constructor.
It could have the parameters with default values or could be empty.

If no user-defined constructor exists for a class A and one is needed, the compiler implicitly declares a default parameterless constructor A::A(). This constructor is an inline public member of its class. The compiler will implicitly define A::A() when the compiler uses this constructor to create an object of type A. The constructor will have no constructor initializer and a null body.

* No default constructor is created for a class that has any constant or reference type members.

A trivial default constructor is a constructor that performs no action. All data types compatible with the C language (POD types) are trivially default-constructible. For a default constructor to be trivial it must satisfy all of the following:-
* The constructor is not user-provided (i.e., is implicitly-defined or defaulted on its first declaration)
* T has no virtual member functions
* T has no virtual base classes
* T has no non-static members with default initializers.(since C++11)
* Every direct base of T has a trivial default constructor
* Every non-static member of class type has a trivial default constructor

**Delegating constructor**

Since **C++11**

If the name of the class itself appears as class-or-identifier in the member initializer list, then the list must consist of that one member initializer only; such constructor is known as the delegating constructor, and the constructor selected by the only member of the initializer list is the target constructor

In this case, the target constructor is selected by overload resolution and executed first, then the control returns to the delegating constructor and its body is executed.

Delegating constructors cannot be recursive.

A constructor calling another constructor of same class in initializer list. We can only call another constructor from one constructor in initializer list.
```cpp
//This is not a delegation constructor. code is valid even before C++11
class delConst
{
    int value {20};
    public:
    delConst(int data) : value{data}
    {

    }
    delConst()
    {
        delConst(10); // its not delegation its construction of another object
    }
};
//Delegating constructor. valid only since C++11
class delConst
{
    int value;
    public:
    delConst(int data) : value(data)
    {

    }
    delConst(): delConst(10)
    {
    }
};
```

Also note that a class can always call the constructor of parent class. Its valid before C++11 also

**why constructors can't be virtual:-**

To resolve the virtual mechanism object must be constructed beforehand. As during the object creation itself the vptr is assigned to proper vtable. So a half constructed object can't resolve the virtual call.

Although we can achieve the virtual construction behavior by using factory method.



**Output:-**

### Authors

* **The Philomath**
