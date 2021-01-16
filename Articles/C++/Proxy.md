## About

A proxy is a class that provides a modified interface to another class.

Proxy classes can be visible or invisible. Visible proxy examples are `unique_ptr` and `shared_ptr`. Invisible proxy example is `std::vector<bool>::reference`. In a general rule invisible proxies don't play well with `auto`. So we should avoid using `auto` for invisible proxies.

Suppose we want to define a class which can only accept binary numbers i.e. 1 and 0.
```cpp
class bitArray
{
  int _bits[10];
public:
  int &operator[](int index)
  {
    return _bits[index];
  }
};
```

But how can we compare the value which we want to assign at _index_ ? How can we make sure that only binary numbers can be assigned to _bitArray_ ?

Answer is in returning object of another class which will do the comparison work for bitArray. That another class is knows as **proxy** class.
```cpp
class proxy
{
  int *lvaluePtr;
public:
  proxy(int &lvalue):lvaluePtr(&lvalue){}

  int operator =(const int rvalue)
  {
    if(rvalue ==1 || rvalue ==0)
    {
      *lvaluePtr = rvalue;
    }
    else
    {
      throw "not a binary number";
    }
    return *lvaluePtr;
  }
};
class bitArray
{
  int _bits[10];
public:
  proxy& operator[](int index)
  {
    return proxy(_bits[index]);
  }
};


int main()
{
  bitArray b;
  try
  {
    b[0] = 1; //fine
    b[1] = 10; //exception thrown
  }
  catch (const char *message)
  {
    std::cout<<message;
  }
  return 0;
}
```

The _proxy_ class now does our checking for a binary digit and we make the _bitArray_'s `operator[]` return an instance of the proxy which has limited access to the _bitArray_'s internals.

suppose a function is returning a bool vector.
then the auto type deduction will not deduce the return type as bool in this case :-
```cpp
auto val = fn()[3]; //calling fn which will return a bool vector. accessing 4th element of vector.
```
type of _val_ is not necessarily be `bool`. as the proxy class will return a `std::vector<bool>::reference` object.

If we want to use the auto then solution is to use the _explicit typed initializer idiom_. i.e.
```cpp
auto val = static_cast<bool>(fn()[3]);
```
Now type of _val_ is `bool`.

#### References
[stackoverflow](https://stackoverflow.com/questions/994488/what-is-proxy-class-in-c)

### Authors

* **The Philomath**
