## About
Pimpl or Pointer to Implementation or Handle Body Idiom or Cheshire cat

**Advantages**

`Data Hiding`

When we are a library owner and wants to hide the important data and its implementation from client then we can keep the data and definition in a separate cpp file and our header can have a pointer to those implementation.

`Binary Compatibility`

We can add/modify fields to implementation file without breaking the binary compatibility with our client (which would mean crashes!). Since the binary layout of class in header file doesn't change when we add new fields to implementation class, it is safe to add new functionality to the library in minor versions updates.

`Reduce Compilation Time`

Here is an example for better understanding:-
```cpp
//Widget.h
class Widget
{
     public:
        Widget();
     private:
        std::string name;
        std::vector<double> data;
        Gadget g1;
};
```
We need to include string, vector and gadget header files in **Widget.h** file to compile our code. Suppose if gadget header file changes for some reason then all the files dependent on gadget header file needs to recompile. If a client is using **Widget.h** then client also needs to recompile that part of code.

**Implementation**

```cpp
//Widget.h
class widget
{
public:
  widget();
private:
  class impl;        //incomplete type
  std::unique_ptr<impl> pimpl;
};
//Widget.cpp
class impl
{
public:
  std::string name;
  std::vector<double> data;
  Gadget g1;
};
widget::widget():
pimpl(std::make_unique<impl>())
{
}
```
In above code we can see that **Widget.h** dependency on all three header files is gone. Now **Widget.cpp** needs to include those 3 header files for compilation.

when we will create an object of widget class it will fail.
```cpp
widget w; //Error
```
Reason is the default inline destructor provided by compiler will call code to destruct the member `std::unique_ptr<impl> pimpl`. Which in turn will call the default deleter of unique_ptr. Which will call delete. To call delete for an object, object should be a complete type but here impl is incomplete. which will fail the assertion in default deleter of unique ptr. So error is for the time when w will be destroyed not for the creation.

Compiler should find the complete type of impl before the destructor code. So we can define destructor after the definition of impl.
```cpp
//Widget.h
class widget
{
public:
  widget();
  ~widget();
  widget(widget&&);
  widget& operator=(widget&&);
private:
  class impl;
  std::unique_ptr<impl> pimpl;
};
//Widget.cpp
class impl
{
  std::string name;
  std::vector<double> data;
  Gadget g1;
};
widget::widget():
pimpl(std::make_unique<impl>())
{}
widget::~widget()= default;
widget::widget(widget &&) = default;
widget& widget::operator=(widget &&) = default;
```
If we provided destructor then compiler will not provide the move operations. So we should declare them and provide the definition in Cpp file. Defining them in header will not work. As assignment operator will delete the lhs data before assigning to rhs. This in turns will call the destructor.
For move constructor compiler will check if an exception will occur then it needs to destroy the pimpl. For that it will need a complete type of impl.

If we want to provide support for copy operations then we are supposed to define them. Default copy operations will do the shallow copy instead we needs to copy the raw pointer stored in unique_ptr.
```cpp
//Widget.h
class widget
{
public:
  ...
  widget(const widget&);
  widget& operator=(const widget&);
private:
  class impl;
  std::unique_ptr<impl> pimpl;
};
//Widget.cpp
class impl
{
  ...
};
...
widget::widget(const widget &rhs):
pimpl(std::make_unique<impl>(*rhs.pimpl))
{}
widget& widget::operator=(const widget &rhs)
{
  *pimpl = *rhs.pimpl;
  return *this;
}
```

we can use the `shared_ptr` instead of `unique_ptr`. Then there will be no problem during destruction as deleter is not part of `shared_ptr` type. But `unique_ptr` is more accurate choice as widget class has an exclusive ownership of pimpl.

If we want to use the data members of impl class in a function and don't want to make impl friend of widget then we expose a function to client but actual definition of that will be in impl class.

```Cpp
//Widget.h
class widget
{
public:
  ...
  void drawWidget();
private:
  class impl;
  std::unique_ptr<impl> pimpl;
};
//Widget.cpp
class impl
{
  ...
private:
  void drawWidget();
};
...
void widget::drawWidget()
{
  pimpl->drawWidget();
}
void impl::drawWidget()
{
  std::cout<<name;
}
```

#### References
[Stack Overflow](https://stackoverflow.com/questions/8972588/is-the-pimpl-idiom-really-used-in-practice)

### Authors

* **The Philomath**
