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

if we want to alter the local variable `val` and pass it by value then we have to use `mutable` keyword. which will simply removes the `const`

or we can pass by reference in the capture list.

```cpp
auto l = [val](auto i) mutable {
    return i + ++val;
};
```

Since **C++14** we can put expressions in capture list.

Fibonacci series using lambda. Each time calling of this function will return next number of series.
```cpp
auto l = [i = 0, j = 1]() mutable{   // A statefull lambda. carrying its own states
        i = std::exchange(j, j+i);
        return i;
    };
```

similarly we can put a `unique_ptr` in capture list and then lambda will become non copy able.
```cpp
auto l = [i = 0, p = std::make_unique<int>(2)]() mutable{   // A statefull lambda. carrying its own states
        return ++i;
    };

//auto l2 = l; //gives error
```

Interacting statefull Lambda
```cpp
auto l = [i = 0, j = 1]() mutable{
        struct Results{
           int &a;
           int &b;

           Results(int& i, int& j):a(i),b(j){}
           operator int(){
               return a;
           }
           Results next()
           {
               a = std::exchange(b, b+a);
               return *this;
           }
        };

        return Results(i,j).next();
    };
```
l().b = 10;


#### References
[C++ Weakly](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw)

### Authors
