## About

Scoped enums or enum class members(enumerators) are visible only inside the enum class. let's take a look at them.

Whereas the c++98 style enums are known as Unscoped enums.
Here is an example:-
```cpp
enum Number{
    one,
    two,
    three
};

int main()
{
    if(one == 0)
    {
        std::cout<<"its one";
    }
    return 0;
}
```
**Output:-**

_its one_

Two things are clear from above example:-
* **one** which is *enum Number*'s type is leaking everywhere just like its in a global namespace.
* we can compare an enum to an integer. enums behaves like integer here but they are not integer.
  Actually there underlying type is not defined.

Let's change enum to enum class
```cpp
enum class Number{
    one,
    two,
    three
};

int main()
{
    if(one == 0)
    {
        std::cout<<"its one";
    }
    return 0;
}
```
**Output:-**

_error: 'one' was not declared in this scope; did you mean 'Number::one'?_

We can see that we can't use one directly as its bound to the Number's scope.
If we change the **one** to **Number::one** this error will be gone. But still there is one more error.
We are comparing a Number to an integer which is not allowed without a cast.

```cpp
if(Number::one == 0)
{
    std::cout<<"its one";
}
```
**Output:-**

_error: no match for 'operator==' (operand types are 'Number' and 'int')_

we can solve this error either by a *static_cast* of **0** or something like we did in below example:-
```cpp
Number n = Number::one;
if(Number::one == n)
{
    std::cout<<"its one";
}
```

**Underlying type of scoped enums are integer**

Yes its integer by default. Due to this we can forward_declare them. If we want to we can change the underlying type.

unscoped enums
```cpp
enum Number;
```
**Output:-**

_error: use of enum 'Number' without previous declaration_

with scoped enums its fine to declare like
```cpp
enum class Number;
```

we can change the underlying type like:-
```cpp
enum class Number: std::uint32_t{};
```

unscoped enums can also be forward_declare if we define the type. like below code is a valid code:-
```cpp
enum Number: std::uint32_t;
```

### Authors

* **The Philomath**
