### About

`std::move` doesn't move and `std::forward` doesn't forward anything. So what do they do. Let's find out.

----
Before going into details of `std::move` and `std::forward` we need to understand a few things.

A C++ expression, in addition to a type also has a value category. Traditionally the main value categories were **lvalue** and **rvalue** with a rough meaning that if it could stand on the left side of an assignment it’s a **lvalue**, otherwise it’s a **rvalue**.

With the advent of **C++11**, additional value categories have been identified and organized in a systematic way based on the observation that there are two important properties of an expression: has identity (i.e. ‘can we get its address’) and can be moved from

But when used inside the function body, a parameter of function, whether it's a **lvalue reference** or **rvalue reference**, is an **lvalue** itself i.e. it has a name like any other variable.

```cpp
// parameter is rvalue reference
void fn(X && x)
{
  // but here expression x has an lvalue value category
  // can use std::move to convert it to an xvalue
}

struct X {};

// overloads
void fn(X &) { std::cout<< "X &\n"; }
void fn(const X &) { std::cout<< "const X &\n"; }
void fn(const X &&) { std::cout<< "const X &&\n"; }

int main()
{
  X a;
  fn(a);
  // lvalue selects fn(X &)
  // fallbacks on fn(const X &)

  const X b;
  fn(b);
  // const lvalue requires fn(const X &)

  fn(X());
  // rvalue selects fn(X &&)
  // and then on fn(const X &)

  fn(std::move(b));
}
```

**Output:-**

    _X &_
    _const X &_
    _X &&_
    _const X &&_

----

Once we have an expression of a value category, we can convert it to an expression of a different value category. If we have a **rvalue** we can assign it to a variable, or take a reference, hence becoming a **lvalue**. If we have a **lvalue** we can return it from a function, so we get a **rvalue**.

But one important rule is that: one can covert from a **lvalue** to a **rvalue** (to an **xvalue** more precisely) by using `static_cast<X &&>` without creating temporaries.

----

**std::move** possible implementation of `std::move` in library would be

```cpp
template<typename T> struct remove_reference { typedef T type; };
template<typename T> struct remove_reference<T&> { typedef T type; };
template<typename T> struct remove_reference<T&&> { typedef T type; };

template<typename T>
constexpr typename remove_reference<T>::type && move(T && arg) noexcept
{
  return static_cast<typename remove_reference<T>::type &&>(arg);
}
```

In conclusion `std::move` does not move, all it does is to return a **rvalue** so that the function that actually moves, eventually receiving a **rvalue reference**, is selected by the compiler

----

**std::forward**

The idiomatic use of `std::forward` is inside a templated function with an argument declared as a forwarding reference, where the argument is now **lvalue**, used to retrieve the original value category, that it was called with, and pass it on further down the call chain (perfect forwarding).

```cpp
struct Y
{
  Y(){}
  Y(const Y &){ std::cout << "Copy constructor\n"; }
  Y(Y &&){ std::cout << "Move constructor\n"; }
};

struct X
{
  template<typename A, typename B>
  X(A && a, B && b) :
    // retrieve the original value category from constructor call
    // and pass on to member variables
    a_{ std::forward<A>(a) },
    b_{ std::forward<B>(b) }
  {
  }

  Y a_;
  Y b_;
};

template<typename A, typename B>
X factory(A && a, B && b)
{
  // retrieve the original value category from the factory call
  // and pass on to X constructor
  return X(std::forward<A>(a), std::forward<B>(b));
}

int main()
{
  Y y;
  X two = factory(y, Y());
  // the first argument is a lvalue, eventually a_ will have the
  // copy constructor called
  // the second argument is an rvalue, eventually b_ will have the
  // move constructor called
}
```

**Output:-**

    _Copy constructor_
    _Move constructor_

possible implementation of `std::forward`

```cpp
template<typename T> struct is_lvalue_reference { static constexpr bool value = false; };
template<typename T> struct is_lvalue_reference<T&> { static constexpr bool value = true; };

template<typename T>
constexpr T&& forward(typename remove_reference<T>::type & arg) noexcept
{
  return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(typename remove_reference<T>::type && arg) noexcept
{
  static_assert(!is_lvalue_reference<T>::value, "invalid rvalue to lvalue conversion");
  return static_cast<T&&>(arg);
}
```

#### References
[bajamircea](http://bajamircea.github.io/coding/cpp/2016/04/07/move-forward.html)

### Authors

* **The Philomath**
