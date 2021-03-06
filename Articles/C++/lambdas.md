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
----
**Interacting with statefull Lambda**

We can use the states of a lambda outside the lambda.
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

// we can call lambda and access the member variable of local class
  l().b = 10;  // setting member variable to 10
```
----
**Inheriting lambda**

Just like any other class we can inherit lambdas. One of the use of it is as it provides the access to the call operator.

```cpp
template<typename t1, typename t2>
struct combine: t1,t2
{
    combine(t1 l1,t2 l2):t1(std::move(l1)),t2(std::move(l2)){}
    using t1::operator();
    using t2::operator();
};

int main(){
    auto l1 = [](){ return 1;};
    auto l2 = [](int a){return 1+a;};
    combine c = combine(l1,l2);
    cout<<c(4);

    return 0;
}
```
----
**Lambda to function pointer conversion**

For conversion it must be a non capturing lambda because capturing lambdas have states.

It is quite useful for passing lambdas to a **C** API.

```cpp
std::vector<std::function<int (int,int)>> vfunc;

vfunc.emplace_back([](int i, int j){return i+j;});
vfunc.emplace_back([](int i, int j){return i*j;});

//we can also define our vector like:-
std::vector<int ( * ) (int, int)> vfunv;
```
another example. `set` with unique member variables.
```cpp
struct coordinates
{
    int x;
    int y;
};

int main(){

    using fptr = bool (*)(const coordinates &,const coordinates &);
    std::set<coordinates, fptr> s{[](const coordinates &first, const coordinates &second){
        return ((first.x != second.x) && (first.y != second.y));
        }};

    s.insert(coordinates{3,4});
    s.insert(coordinates{3,4});
    std::cout<<s.size();
    for(auto i: s)
    {
        std::cout<<i.x<<" "<<i.y;
    }

    return 0;
}
```
----
**memory management using lambda**

lambdas can be used with smart_ptr as a custom deleter
```cpp
int main(){
    auto deleter = [](FILE* f){
        fclose(f);
    };

    auto file = std::unique_ptr<FILE, decltype(deleter)> (fopen("file.txt","w"), deleter);    
}
```
----
**Higher Order functions**

Functions which returns another functions are known as higher order functions.
```cpp
template<typename f1, typename f2>
auto f1f2(f1 &&func1, f2 &&func2)
{
    return [func1 = std::forward<f1>(func1), func2 = std::forward<f2>(func2)](){
        return func1(func2());
    };
}

int bigFunc(int);
int biggerFunc();

int main(const int argc, const char *[]){
    auto ret = f1f2(bigFunc,biggerFunc);
    if(argc > 2)
    {
        return ret();
    }
}
```
----
**C++17 variadic using**
```cpp

template<typename ... B>
struct combine : B...
{
    template<typename ... T>
    combine(T && ... t) : B(std::forward<T>(t))...
    {
    }

    using B::operator()...;
};

//typ deduction guide
template<typename ... T>
combine(T...) -> combine<std::decay_t<T>...>;

int main(){
    const auto l1 = [](){ return 1;};
    const auto l2 = [](int a){return 1+a;};
    combine c(l1,l2, [](const double d){return d;});
    std::cout<<c(4);

    return 0;
}
```
same can be written using aggregate initialization using **C++17**. where we can also initilize base classes using initializer list
```cpp
template<typename ... B>
struct combine : B ...
{
   using B::operator()...;
};

//typ deduction guide
template<typename ... T>
combine(T...) -> combine<T...>;

int main(){
    const auto l1 = [](){ return 1;};
    const auto l2 = [](int a){return 1+a;};
    combine c{l1,l2, [](const double d){return d;}};  // aggregate initialization
    std::cout<<c(4);

    return 0;
}
```

**Lambdas within fold expressions**

We can use lambdas within fold expression. A fold expression is an expression within paranthesis i.e. ()
```cpp
template<typename ... T>
auto func(T ... var)
{
    return ([var](){return var + 1;}() + ...); // creating lambda and calling it inside the fold expression
}

int main()
{
    std::cout<<func(1,2,3,4,5);
    return 0;
}
```

`std::function` can be used where we uses function pointers. But `std::funciton` is more than a function pointer. we can store any callable object:
* functions
* lambda expressions
* bind expressions (internally implemented as functors)
* functors

#### References
[C++ Weakly](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw)

### Authors

* **The Philomath**
