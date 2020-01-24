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



why constructors can't be virtuals.

constructor delegation

**Output:-**

### Authors

* **The Philomath**
