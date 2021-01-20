## About

Variadic templates should be used when we need a number of arguments of different verities.

Here is a definition of a template taking variable number of arguments.
```cpp
#include <utility>

struct MyType{
    MyType(int, double, bool){};
};

template <typename T, typename ... Args>
T createT(Args&& ... args){
    return T(std::forward<Args>(args) ... );
}

int main(){

    int lvalue{2020};

    int uniqZero = createT<int>();                       
    auto uniqEleven = createT<int>(2011);                
    auto uniqTwenty = createT<int>(lvalue);              
    auto uniqType = createT<MyType>(lvalue, 3.14, true);

}
```
The three dots stand for a ellipse. By using them Args, or args becomes a parameter pack. To be more precise, `Args` is a **template parameter pack** and `args` is a **function parameter pack**. You can only apply two operations to a parameter pack: you can pack or unpack it. If the ellipse is left of `Args` the parameter pack is **packed**; if the ellipse is right of `Args` the parameter pack is **unpacked**. In case of the expression `std::forward<Args>(args)...` this means the expression is unpacked until the parameter pack is consumed and a comma is just place between the unpacked components. This was all.

`std::make_unique` can be defined like this
```cpp
template <typename T, typename ... Args>
std::unique_ptr<T> make_unique(Args&& ... args){
    return std::unique_ptr<T>(new T(std::forward<Args>(args) ... ));
}
```

similarly we can define a type safe `printf` like this
```cpp
void myPrintf(const char* format){                           
    std::cout << format;
}

template<typename T, typename ... Args>
void myPrintf(const char* format, T value, Args ... args){   
    for ( ; *format != '\0'; format++ ) {                    
        if ( *format == '%' ) {                               
           std::cout << value;
           myPrintf(format + 1, args ... );                  
           return;
        }
        std::cout << *format;                                
    }
}
```

#### References
[modernescpp](https://www.modernescpp.com/index.php/c-core-guidelines-rules-for-variadic-templates)

### Authors

* **The Philomath**
