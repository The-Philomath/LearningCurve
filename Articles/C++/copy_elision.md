## About
Omits copy and move constructors, resulting in zero-copy pass-by-value semantics.

As per C++17 standards sometimes its mandatory for the compiler to omit the copy/move but sometimes its not.

**Mandatory elision of copy and move operations**

In a return statement, when the operand is a `prvalue`(pure rvalue means a rvalue which is not going to expire soon) of the same class type (ignoring cv-qualification) as the function return type:
```cpp
class constructors
{
    int data;
public:
    constructors()
    {
        std::cout << "default constructor"<<std::endl;
    }

    constructors(const constructors &obj)
    {
        std::cout << "copy constructor const"<<std::endl;
    }

    constructors(constructors &&obj)
    {
        std::cout << "move constructor";
    }
};

constructors func()
{
    return constructors();
}

int main()
{
    constructors obj1 = func();

    system("pause");
    return 0;
}
```

**Output:-**

_default constructor_

we can force the complier to not elide any constructor with `-fno-elide-constructors` flag. output with this flag will be.

Before **C++17**

  _default constructor  
   move constructor  
   move constructor_

Since **C++17**

  _default constructor_


#### References
[cppreference](https://en.cppreference.com/w/cpp/language/copy_elision)

### Authors

* **The Philomath**
