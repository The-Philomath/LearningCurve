## About
Omits copy and move constructors, resulting in zero-copy pass-by-value semantics.

As per C++17 standards sometimes its mandatory for the compiler to omit the copy/move but sometimes its not.

**Mandatory elision of copy and move operations**

* In a return statement, when the operand is a `prvalue`(pure rvalue means a rvalue which is not going to expire soon) of the same class type (ignoring cv-qualification) as the function return type:

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

If we make move constructor inaccessible(mark private or delete them) in above code and compile without the `-fno-elide-constructors` flag, compiler before **C++17** version will give us error. Even though it will do the optimization but compiler rules makes it mandatory to provide the move constructor. Here is the output after making it private:

**Output:-**

  _In function 'constructors func()':  
   error: 'constructors::constructors(constructors&&)' is private within this context  
   return constructors();  
   note: declared private here  
   constructors(constructors &&obj)  
   In function 'int main()':  
   error: 'constructors::constructors(constructors&&)' is private within this context  
   constructors obj1 = func();  
   note: declared private here  
   constructors(constructors &&obj)_

But compiler since **C++17** will not give any error.

* In the initialization of an object, when the initializer expression is a prvalue of the same class type (ignoring cv-qualification) as the variable type:

        constructors obj1 = constructors(constructors(func())); // only one call to default constructor of T, to initialize x

**Non-mandatory elision of copy and move operations**

* In the return statement. Check [Named Return value optimization](./Return_value_optimization.md)
* Return value optimization (Before **C++17**). After **C++17** its Mandatory.
* In a throw-expression, when the operand is the name of a non-volatile object with automatic storage duration, which isn't a function parameter or a catch clause parameter, and whose scope does not extend past the innermost try-block (if there is a try-block).
* In a catch clause, when the argument is of the same type (ignoring cv-qualification) as the exception object thrown, the copy of the exception object is omitted and the body of the catch clause accesses the exception object directly, as if caught by reference (there cannot be a move from the exception object because it is always an lvalue).

exception is thrown and caught by value
 ```cpp
 struct Thing{
  Thing();
  Thing(const Thing&);
};

void foo() {
  Thing c;
  throw c;
}

int main() {
  try {
    foo();
  }
  catch(Thing c) {  
  }             
}
```
* In coroutines, copy/move of the parameter into coroutine state may be elided where this does not change the behavior of the program other than by omitting the calls to the parameter's constructor and destructor.

In constant expression and constant initialization, return value optimization (RVO) is guaranteed, however, named return value optimization (NRVO) is forbidden:
```cpp
struct A {
    void *p;
    constexpr A(): p(this) {}
};

constexpr A g()
{
    A a;
    return a;
}

constexpr A a;          // a.p points to a
// constexpr A b = g(); // error: b.p would be dangling and would point to a temporary
                        // with automatic storage duration
```

Common limitations of copy elision are:

* multiple return points
* conditional initialization

#### References
[cppreference](https://en.cppreference.com/w/cpp/language/copy_elision)

### Authors

* **The Philomath**
