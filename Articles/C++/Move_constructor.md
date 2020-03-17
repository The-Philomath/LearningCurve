## About
A move constructor of class T is a non-template constructor whose first parameter is T&&, const T&&, volatile T&&, or const volatile T&&, and either there are no other parameters, or the rest of the parameters all have default values.

When the initializer is a prvalue, the move constructor call is often optimized out (until C++17)never made (since C++17), refer copy elision.

If we declare a destructor or a copy assignment operator or a copy constructor compiler will to provide the default move constructor or move assignment operator. If we try to move the object using std::move() it will call the copy constructor in that case (reasoning is provided below).

```cpp
class Base
{
  public:
  Base()
  {
    std::cout<<"default constructor\n";
  }

  Base(const Base &)
  {
    std::cout<<"copy constructor\n";
  }

  virtual ~Base()
  {
    std::cout<<"Base destructor\n";
  }
};

int main(){
    Base b;
    Base b2(std::move(func())); // will call copy constructor.
    return 0;
}
```

Also if we define the move constructor compiler will not provide the move assignment operator and vice versa.
Reason is that if we are defining a move operation then compiler thinks that move operation shouldn't be same as of the default. Because user want to behave that in some other way. So compiler will not provide the other move function.

**Output:-**

### Authors

* **The Philomath**
