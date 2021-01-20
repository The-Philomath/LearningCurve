## About

`Substitution failure is not an error` (**SFINAE**) refers to a situation in `C++` where an invalid substitution of template parameters is not in itself an error. David Vandevoorde first introduced the acronym **SFINAE** to describe related programming techniques.

Compile can reject the code that would not compile for a given type.

When the compiler tries to compile a function call (simplified):

How the compiler resolve overloaded function calls. An oversimplified version to understand **SFINAE** will look like this:
* Perform a name lookup
* For function templates the template argument values are deduced from the types of the actual arguments passed into the function.
     * All occurrences of the template parameter (in the return type and parameters types) are substituted with those deduced types.
     * When this process leads to invalid type the particular function is removed from the overload resolution set. (**SFINAE**)
* At the end, we have a list of viable functions that can be used for the specific call. If this set is empty, then the compilation fails. If more than one function is chosen, we have an ambiguity. In general, the candidate function, whose parameters match the arguments most closely is the one that is called.

----
**Usages of _SFINAE_**

Wherever we want to a particular function or specialization for a particular type we can use the **SFINAE**

Examples:
* Call a function when `T` has a given method (like call `toString()` if `T` has `toString` method)
* Disallow narrowing or wrong conversions from wrapper types. For example, this is used to prevent `std::variant` from deducing the wrong types.
* Specialize a function for all kind of type traits that we have (is_integral, is_array, is_class, is_pointer, etc… more traits here)

----
How can we write the useful **SFINAE** ?

**std::enable_if**

It's a set to tools that internally use **SFINAE** . They allow to include or exclude overloads from possible function templates or class template specialization.

```cpp
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
foo(T t) {
  std::cout << "foo<arithmetic T>\n";
  return t;
}
```
This function ‘works’ for all the types, that are arithmetic (int, long, float…). If you pass other types (for instance MyClass), it will fail to instantiate

since `C++14`
```cpp
// C++17:
template <class T>
typename std::enable_if_t<std::is_arithmetic_v<T>, T> // << shorter!
foo(T t) {
  std::cout << "foo<arithmetic T>\n";
  return t;
}
```

Another use of **SFINAE** is in expressions like:-
```cpp
template <class T> auto f(T t1, T t2) -> decltype(t1 + t2);
```
the expression of `t1+t2` needs to be checked. It will work for two `int`'s, but not for `int` and `std::vector`.

----
**Alternative to SFINAE**

* **Tag Dispatching**: To call the proper function based upon parameter type we can define a core function and then we choose the proper function using compile time condition or tag.
```cpp
    template <typename T>
    int get_int_value_impl(T t, std::true_type) {
        return static_cast<int>(t+0.5f);
    }

    template <typename T>
    int get_int_value_impl(T t, std::false_type) {
        return static_cast<int>(t);
    }

    template <typename T>
    int get_int_value(T t) {
        return get_int_value_impl(t, std::is_floating_point<T>{});
    }
```

Here `std:: true_type` and `std:: false_type`are types or tags. Although they are equivalent to `true` and `false` but they are types. When you call _get_int_value_ the compiler will then check the value of `std::is_floating_point` and then call the matching *_impl* function.

* **Compile Time if - Since C++17** : allows us to check the condition at compile time - without the need to write complex templated code!
```cpp
template <typename T>
int get_int_value(T t) {
     if constexpr (std::is_floating_point_v<T>) {
         return static_cast<int>(t+0.5f);
     }
     else {
         return static_cast<int>(t);
     }
}
```
* **Concepts - Since C++20** : With Concepts, we will be able to add constraints on the template parameters and get better compiler warnings.

```cpp
// define a concept:
template <class T>
concept SignedIntegral = std::is_integral_v<T> && std::is_signed_v<T>;

// use:
template <SignedIntegral T>
void signedIntsOnly(T val) { }
```
In the code above we first create a concept that describes types that are signed and integral. Please notice that we can use existing type traits. Later, we use it to define a template function that supports only types that match the concept. Here we don’t use typename T, but we can refer to the name of a concept.

----
Another example how to use **SFINAE**

**SFINAE** to check the boolean condition:
```cpp
template<int I> void div(char(*)[I % 2 == 0] = 0) {
    /* this is taken when I is even */
}

template<int I> void div(char(*)[I % 2 == 1] = 0) {
    /* this is taken when I is odd */
}
```
It can be quite useful. For example, to check whether an initializer list collected using operator comma is no longer than a fixed size.

```cpp
    template<int N>
    struct Vector {
        template<int M>
        Vector(MyInitList<M> const& i, char( * )[M <= N] = 0) { /* ... */ }
    }
```

The list is only accepted when M is smaller than N, which means that the initializer list has not too many elements.

The syntax `char(*)[C]` means: Pointer to an array with element type `char` and size `C`. If `C` is false (0 here), then we get the invalid type `char(*)[0]`, pointer to a zero sized array: **SFINAE** makes it so that the template will be ignored then.


#### References
[Bartek's](https://www.bfilipek.com/2016/02/notes-on-c-sfinae.html)

[stackOverflow](https://stackoverflow.com/questions/982808/c-sfinae-examples/989518#989518)

### Authors

* **The Philomath**
