## About
A detailed overview of Lambda expression.

Let's take a simple lambda which is taking in argument and capturing no member(stateless) and return type is void.

    auto l = [](){};
Compiler will generate a class for this lambda and overload `opertor()`. And return us an object of that class which will be stored in l.

Lambda with an `int` return type

    auto l = []()->int{
      return 1;
    };

Lambda with variadic parameters
```cpp
int main(){
    constexpr auto l = [](auto ... val)->int{
        return (val + ...);
    };
    std::cout<<l(3,2,1);
}
```

Compiler creates a class equivalent to lambda which will looks like as shown below:-
```cpp
struct __main_lambda_0
{
    int val;
    template<typename T>
    auto /*constexpr*/ operator()(T i) const{  //passing local variable val removes constexpr
        return i + val;
    }
};
int main(){

    int val = 10;
    auto l = [val](auto i){
        return i + val;
    };
    std::cout<<typeid(l).name();
}
```
By default overloded `operator()` by compiler is `const` and it returns a `constexpr` if it can and it do the `auto` type deduction.

if we want to alter the local variable `val` then we have to use `mutable` keyword. which will simply removes the `const`

```cpp
auto l = [val](auto i) mutable {
    return i + ++val;
};
```

#### References
[C++ Weakly](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw)

### Authors
