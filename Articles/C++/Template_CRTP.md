## About

**CRTP** or Curiously Recurring Template Pattern is a way of implementing polymorphic code at compile time, similar to what we get using virtual inheritance. Also known as Static polymorphism.

In short, CRTP is when a `class A` has a `Base` class which is a template specialization for the `class A` itself.
```cpp
Template<typename T>
class Base
{
};

class A: public Base<A>
{
};
```

CRTP is based on lazy-evaluation means a function will not get instantiated until it is not needed.
Here is an example:-
```cpp
#include <iostream>

template<class T>
struct Lazy{
    void func() { std::cout << "func" << std::endl;}
    void func2(); // not defined
};

int main(){   
  Lazy<int> lazy;
  lazy.func();    
}
```

Even though we have not defined `func2()` compiler/linker will never give an error this. Reason is that we are not using it or calling it.
That is exactly the property that the CRTP uses because the definition of a method of class templates is only needed if called.

```cpp
#include <iostream>

template <typename T>
class Base
{
   public:
        void display()
        {
            static_cast<T*>(this)->print();
        }
        void print()
        {
            std::cout<<"In Base"<<std::endl;
        }
};

class Derived1: public Base<Derived1>
{
    public:
        void print()
        {
            std::cout<<"In Derived1"<<std::endl;
        }
};

class Derived2: public Base<Derived2>
{
    public:
        void print()
        {
            std::cout<<"In Derived2"<<std::endl;
        }
};

template<typename T>
void display(Base<T>* b)
{
    b->display();
}

int main() {
    Derived1 d1;
    Derived2 d2;
    display(&d1);
    display(&d2);
}
```

So the compiler delayed the instantiation of base template or specialization until we actually calls the `b->display()`.
Here is what compiler generated code looks like:

```cpp
/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Base<Derived1>
{

  public:
  inline void display()
  {
    static_cast<Derived1 *>(this)->print();
  }

  inline void print();

  // inline constexpr Base() noexcept = default;
};

#endif

/* First instantiated from: insights.cpp:26 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Base<Derived2>
{

  public:
  inline void display()
  {
    static_cast<Derived2 *>(this)->print();
  }

  inline void print();

  // inline constexpr Base() noexcept = default;
};

#endif


class Derived1 : public Base<Derived1>
{

  public:
  inline void print()
  {
    std::operator<<(std::cout, "In Derived1").operator<<(std::endl);
  }

  // inline constexpr Derived1() noexcept = default;
};

class Derived2 : public Base<Derived2>
{

  public:
  inline void print()
  {
    std::operator<<(std::cout, "In Derived2").operator<<(std::endl);
  }

  // inline constexpr Derived2() noexcept = default;
};

template<typename T>
void display(Base<T>* b)
{
    b->display();
}

/* First instantiated from: insights.cpp:44 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void display<Derived1>(Base<Derived1> * b)
{
  b->display();
}
#endif

/* First instantiated from: insights.cpp:45 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void display<Derived2>(Base<Derived2> * b)
{
  b->display();
}
#endif

int main()
{
  Derived1 d1 = Derived1();
  Derived2 d2 = Derived2();
  display(static_cast<Base<Derived1> *>(&d1));
  display(static_cast<Base<Derived2> *>(&d2));
}
```

**Output:-**

    In Derived1
    In Derived2

----

**Usages**

Imagine we want to provide only operator `<` for our classes but automatically get operator `==` for them!

```cpp
template<class Derived>
class Equality
{
};

template <class Derived>
bool operator == (Equality<Derived> const& op1, Equality<Derived> const & op2)
{
    Derived const& d1 = static_cast<Derived const&>(op1);//you assume this works     
    //because you know that the dynamic type will actually be your template parameter.
    //wonderful, isn't it?
    Derived const& d2 = static_cast<Derived const&>(op2);
    return !(d1 < d2) && !(d2 < d1);//assuming derived has operator <
}
// We can use it like this
struct Apple:public Equality<Apple>
{
    int size;
};

bool operator < (Apple const & a1, Apple const& a2)
{
    return a1.size < a2.size;
}

int main()
{
    Apple a1;
    Apple a2;

    a1.size = 10;
    a2.size = 10;
    if(a1 == a2) //the compiler won't complain!
    {
    }
}
```

We don't need to provide `==` operator for `Apple`.

This could seem that you would write less if you just wrote operator `==` for Apple, but imagine that the Equality template would provide not only `==` but `>`, `>=`, `<=` etc. And you could use these definitions for multiple classes, reusing the code!

Another usage is `std::enable_shared_from_this` from `C++11`:

    A class T can inherit from enable_­shared_­from_­this<T> to inherit the shared_­from_­this member functions that obtain a shared_­ptr instance pointing to *this.

That is, inheriting from `std::enable_shared_from_this` makes it possible to get a shared (or weak) pointer to your instance without access to it (e.g. from a member function where you only know about *this).

It's useful when you need to give a `std::shared_ptr` but you only have access to `*this`:

```cpp
struct Node;

void process_node(const std::shared_ptr<Node> &);

struct Node : std::enable_shared_from_this<Node> // CRTP
{
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;

    void add_child(std::shared_ptr<Node> child)
    {
        process_node(shared_from_this()); // Shouldn't pass `this` directly.
        child->parent = weak_from_this(); // Ditto.
        children.push_back(std::move(child));
    }
};
```

The reason you can't just pass `this` directly instead of `shared_from_this()` is that it would break the ownership mechanism:

```cpp
struct S
{
    std::shared_ptr<S> get_shared() { return std::shared_ptr<S>(this); }
};

// Both shared_ptr think they're the only owner of S.
// This invokes UB (double-free).
std::shared_ptr<S> s1 = std::make_shared<S>();
std::shared_ptr<S> s2 = s1->get_shared();
assert(s2.use_count() == 1);
```

#### References
[Stack Overflow](https://stackoverflow.com/questions/4173254/what-is-the-curiously-recurring-template-pattern-crtp)

[Modernescpp](https://www.modernescpp.com/index.php/c-is-still-lazy)

### Authors

* **The Philomath**
