### About

`std::move` doesn't move and `std::forward` doesn't forward anything. So what do they do. Let's find out.

----

Before going into details of `std::move` and `std::forward` we need to understand a few things.

A C++ expression, in addition to a type also has a value category. Traditionally the main value categories were **lvalue** and **rvalue** with a rough meaning that if it could stand on the left side of an assignment it’s a **lvalue**, otherwise it’s a **rvalue**.

If you can take the address of an expression, the expression is an **lvalue**.

If the type of an expression is an **lvalue reference** (e.g., `T&` or `const T&`, etc.), that expression is an **lvalue**.
Otherwise, the expression is an **rvalue**.  Conceptually (and typically also in fact), **rvalues** correspond to temporary objects, such as those returned from functions or created through implicit type conversions. Most literal values (e.g., 10 and 5.3) are also **rvalues**.

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

**Universal References**
```cpp
Widget&& var1 = someWidget;      // here, “&&” means rvalue reference

auto&& var2 = var1;              // here, “&&” does not mean rvalue reference

template<typename T>
void f(std::vector<T>&& param);  // here, “&&” means rvalue reference

template<typename T>
void f(T&& param);               // here, “&&”does not mean rvalue reference
```
The essence of the issue is that `&&` in a type declaration sometimes means **rvalue reference**, but sometimes it means either **rvalue reference** or **lvalue reference**.

references declared with `&&` that may be either **lvalue references** or **rvalue references** may bind to anything.  Such unusually flexible references deserve their own name. We can call them **universal references** or **forwarding references**.

If a variable or parameter is declared to have type `T&&` for some deduced type `T`, that variable or parameter is a **universal reference**.

In practice, almost all universal references are parameters to function templates. Because the type deduction rules for auto-declared variables are essentially the same as for templates, it’s also possible to have auto-declared **universal references**.

If the expression initializing a **universal reference** is an **lvalue**, the universal reference becomes an **lvalue reference**.
If the expression initializing the **universal reference** is an **rvalue**, the universal reference becomes an **rvalue reference**.

```cpp
Widget&& var1 = someWidget;
auto&& var2 = var1;
```
You can take the address of var1, so var1 is an **lvalue**.  var2’s type declaration of `auto&&` makes it a **universal reference**, and because it’s being initialized with var1 (an **lvalue**), var2 becomes an **lvalue reference**.  A casual reading of the source code could lead you to believe that var2 was an **rvalue reference**; the `&&` in its declaration certainly suggests that conclusion.  But because it is a **universal reference** being initialized with an **lvalue**, var2 becomes an **lvalue reference**.

Remember that `&&` indicates a **universal reference** only where type deduction takes place.  Where there’s no type deduction, there’s no **universal reference**.  In such cases, `&&` in type declarations always means **rvalue reference**.

I stated that the form of the reference declaration must be `T&&` in order for the reference to be universal. That’s an important caveat.  Look again at this declaration from the beginning of this article:

```cpp
template<typename T>
void f(std::vector<T>&& param);     // “&&” means rvalue reference
```
Even the simple addition of a `const` qualifier is enough to disable the interpretation of `&&` as a **universal reference**:
```cpp
template<typename T>
void f(const T&& param);               // “&&” means rvalue reference
```

----

**Template type deduction** and **univesal references**

Sometimes you can see `T&&` in a function template declaration where T is a template parameter, yet there’s still no type deduction.  Consider this `push_back` function in `std::vector`
```cpp
template <class T, class Allocator = allocator<T> >
class vector {
public:
    ...
    void push_back(T&& x);       // fully specified parameter type ⇒ no type deduction;
    ...                          // && ≡ rvalue reference
};
```
Here, `T` is a template parameter, and `push_back` takes a `T&&`, yet the parameter is not a **universal reference**!  How can that be?

The answer becomes apparent if we look at how `push_back` would be declared outside the class. I’m going to pretend that `std::vector`’s Allocator parameter doesn’t exist, because it’s irrelevant to the discussion, and it just clutters up the code.  With that in mind, here’s the declaration for this version of `std::vector::push_back`:
```cpp
template <class T>
void vector<T>::push_back(T&& x);
```
`push_back` can’t exist without the class `std::vector<T>` that contains it.  But if we have a class `std::vector<T>`, we already know what `T` is, so there’s no need to deduce it.

An example will help.  If I write
```cpp
Widget makeWidget();             // factory function for Widget
std::vector<Widget> vw;
...
Widget w;
vw.push_back(makeWidget());      // create Widget from factory, add it to vw
```
my use of `push_back` will cause the compiler to instantiate that function for the class `std::vector<Widget>`. The declaration for that `push_back` looks like this:
```cpp
void std::vector<Widget>::push_back(Widget&& x);
```
See?  Once we know that the class is `std::vector<Widget>`, the type of `push_back`’s parameter is fully determined:  it’s `Widget&&`.  There’s no role here for type deduction.

Contrast that with `std::vector`’s `emplace_back`, which is declared like this:
```cpp
template <class T, class Allocator = allocator<T> >
class vector {
public:
    ...
    template <class... Args>
    void emplace_back(Args&&... args); // deduced parameter types ⇒ type deduction;
    ...                                // && ≡ universal references
};
```
Don’t let the fact that `emplace_back` takes a variable number of arguments (as indicated by the ellipses in the declarations for **Args** and **args**) distract you from the fact that a type for each of those arguments must be deduced.  The function template parameter Args is independent of the class template parameter `T`, so even if we know that the class is, say, `std::vector<Widget>`, that doesn’t tell us the type(s) taken by `emplace_back`.  The out-of-class declaration for `emplace_back` for `std::vector<Widget>` makes that clear (I’m continuing to ignore the existence of the Allocator parameter):
```cpp
template<class... Args>
void std::vector<Widget>::emplace_back(Args&&... args);
```
Clearly, knowing that the class is `std::vector<Widget>` doesn’t eliminate the need for the compiler to deduce the type(s) passed to `emplace_back`.  As a result, `std::vector::emplace_back`’s parameters are universal references, unlike the parameter to the version of `std::vector::push_back` we examined, which is an **rvalue reference**.

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

A final point is worth bearing in mind: the lvalueness or rvalueness of an expression is independent of its type. Consider the type `int`.  There are **lvalues** of type `int` (e.g., variables declared to be ints), and there are **rvalues** of type `int` (e.g., literals like 10).  It’s the same for user-defined types like Widget. A Widget object can be an **lvalue** (e.g., a Widget variable) or an **rvalue** (e.g., an object returned from a Widget-creating factory function). The type of an expression does not tell you whether it is an **lvalue** or an **rvalue**.
Because the lvalueness or rvalueness of an expression is independent of its type, it’s possible to have **lvalues** whose type is **rvalue reference**, and it’s also possible to have **rvalues** of the type **rvalue reference**:
```cpp
Widget makeWidget();                       // factory function for Widget

Widget&& var1 = makeWidget()               // var1 is an lvalue, but
                                           // its type is rvalue reference (to Widget)

Widget var2 = static_cast<Widget&&>(var1); // the cast expression yields an rvalue, but
                                           // its type is rvalue reference  (to Widget)
```
The conventional way to turn **lvalues** (such as var1) into **rvalues** is to use `std::move` on them, so var2 could be defined like this:
```cpp
Widget var2 = std::move(var1);             // equivalent to above
```
I initially showed the code with `static_cast` only to make explicit that the type of the expression was an **rvalue** reference (Widget&&).

f it’s bound to an **rvalue** and we want to take advantage of the rvalueness of what it’s bound to, we have to convert rhs back into an rvalue. If it’s bound to an **lvalue**, of course, we don’t want to treat it like an **rvalue**.  This ambiguity regarding the lvalueness and rvalueness of what a universal reference is bound to is the motivation for std::forward:  to take a universal reference **lvalue** and convert it into an **rvalue** only if the expression it’s bound to is an **rvalue**.
```cpp
void f(int& && param);           // initial instantiation of f with lvalue
```
Because of the reference-to-reference, this instantiated code is prima facie invalid, but the source code– “f(x)” – is completely reasonable.  To avoid rejecting it, `C++11` performs “reference collapsing” when references to references arise in contexts such as template instantiation.

There are only two reference-collapsing rules:

An **rvalue reference** to an **rvalue reference** becomes (“collapses into”) an **rvalue reference**.
All other references to references (i.e., all combinations involving an **lvalue reference**) collapse into an **lvalue reference**.
```cpp
Widget w1, w2;

auto&& v1 = w1;                  // v1 is an auto-based universal reference being
                                 // initialized with an lvalue, so v1 becomes an
                                 // lvalue reference referring to w1.

decltype(w1)&& v2 = w2;          // v2 is a decltype-based universal reference, and
                                 // decltype(w1) is Widget, so v2 becomes an rvalue reference.
                                 // w2 is an lvalue, and it’s not legal to initialize an
                                 // rvalue reference with an lvalue, so
                                 // this code does not compile.
```

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
