## About
A copy constructor of class T is a non-template constructor whose first parameter is T&‍, const T&‍, volatile T&‍, or const volatile T&‍, and either there are no other parameters, or the rest of the parameters all have default values.

Default copy constructors are **inline** and **constexpr**.

A class can have multiple copy constructors, e.g. both T::T(const T&) and T::T(T&)

If we declare a move constructor in a class then compiler will not generate the copy constructor and copy assignment operator.

Here is an example:-
```cpp
class Base
{
  public:
  Base()
  {
    std::cout<<"default constructor\n";
  }

  Base(Base &&)
  {
    std::cout<<"move constructor\n";
  }

  virtual ~Base()
  {
    std::cout<<"Base destructor\n";
  }
};
```
Here is the output from cppinsights.io
```cpp
class Base
{

  public:
  inline Base()
  {
    std::operator<<(std::cout, "default constructor\n");
  }

  inline Base(Base &&)
  {
    std::operator<<(std::cout, "move constructor\n");
  }

  inline virtual ~Base() noexcept
  {
    std::operator<<(std::cout, "Base destructor\n");
  }

  // inline constexpr Base(const Base &) = delete;
  // inline Base & operator=(const Base &) = delete;
};
```

But if we declare the copy constructor. Compiler will provide the default copy assignment operator.

Since C++11 if we are defining any of copy constructor or copy assignment operator or destructor and not defining other two then compiler can warn you and its a deprecated behavior. It means it can be removed all together somewhere in future. So we should always follow rule of 3/5 even if we do not want to define any of 5 function we should declare them with a **default** keyword. Either define all 5 or define none.

**Output:-**

### Authors

* **The Philomath**
