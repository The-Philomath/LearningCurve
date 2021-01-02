## About
It is programming with type not with values. By manipulating the types we can do the calculation at compile time itself.

Template metaprogramming is `Turing-complete`, meaning that any computation expressible by a computer program can be computed, in some form, by a template metaprogram.

Here is Fibonacci Sequence example:
```cpp
#include<iostream>

template<int n>
struct fib
{
   static int const value =  (n<0)? 0 : fib<n-1>::value + fib<n-2>::value;
};

template<>
struct fib<1>
{
   static int const value = 1;
};

template<>
struct fib<0>
{
   static int const value = 0;
};

int main()
{
   fib<5>::value;
}
```
Above code will work fine for all the `values >= 0`. But if we call it with `fib<-1>::value` compilation will go into recursive calls. Reason being when fib is instantiated with some value of n, all expressions used inside this instantiation must be compiled as well. This means that any templates that are used must also be instantiated. This is necessary even if the expression containing the template instantiation is never evaluated.

So in first pass compiler will do this
```Cpp
static int const value =  (n<0)? 0 : fib<-1-1>::value + fib<-1-2>::value;
```

This will again need to instantiate `fib<-2>` and `fib<-3>` which will leads to a recursive call.

The only way to avoid instantiation of a template inside an expression is to not compile the expression at all. This allows you to avoid instantiating the templates with incorrect arguments.

**C++14 onwards**
```cpp
template<class L, class R>
struct add {
    static constexpr auto value = L::value + R::value;
};

template<int n>
struct fibonacci {
    static const int value = std::conditional_t<(n < 0), fibonacci<0>, add<fibonacci<n-1>, fibonacci<n-2>>>::value;
};
```
or from **c++17 onwards**
```cpp
template<int n>
struct fibonacci {
    static const int value = [] {
      if constexpr (n < 0) return 0;
       else return fibonacci<n-1>::value + fibonacci<n-2>::value;
    }();
};
```
**Manipulating Types at Compile Time**

Compiler to type manipulation at compile time to support metaprogramming.
like for `std::move` compiler will modify the type
```cpp
static_cast<std::remove_reference<decltype(arg)>::type&&>(arg);
```
`std::move` takes an argument `arg`, deduces the type `decltype(arg)` from it, removes the reference `remove_reverence`, and casts it to a rvalue reference `static_cast<...>::type&&>`. In essence, this means that `std::move` returns always a `rvalue` reference type and, therefore, `move` semantic can kick it.

#### References
[Stack Overflow](https://stackoverflow.com/questions/65292785/c17-static-template-lazy-evaluation)
[modernescpp](https://www.modernescpp.com/index.php/c-core-guidelines-rules-for-template-metaprogramming)

### Authors

* **The Philomath**
