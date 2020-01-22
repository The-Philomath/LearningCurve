## About
Return value optimization(RVO) is nothing but a type of copy elision. It eliminates unnecessary copying/moving of objects.

Two type of RVO :-

**Named RVO**

If a function returns a class type by value and the return statement's expression is the name of a non-volatile object with automatic storage duration (which isn't a function parameter), then the copy/move that would be performed by a non-optimising compiler can be omitted. If so, the returned value is constructed directly in the storage to which the function's return value would otherwise be moved or copied.

**RVO**

If the function returns a nameless temporary object that would be moved or copied into the destination by a naive compiler, the copy or move can be omitted

```cpp
ABC fun123()  
{ ABC obj; return obj; }  

ABC xyz123()  
{  return ABC(); }  

int main()  
{   
    ABC obj1(fun123());//NRVO  
    ABC obj2(xyz123());//RVO  
    ABC xyz = "Stack Overflow";//RVO  

    return 0;
}
```

Its mandatory in few cases for the compiler to optimize the return values and omit them. see [copy elision](./copy_elision.md) for more info.
### Authors

* **The Philomath**
