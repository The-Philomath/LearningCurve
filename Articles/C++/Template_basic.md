## About

Templates are used when we need a function/class algorithm that applies to different types.
Template provide the static(compile-time)polymorphism.

The process of generating type from template is called template instantiation or specialization.

```cpp
template<typename T>
class stack
{
    public:
        void push(T& data);
        T pop();
		bool isEmpty() const;
    private:
        vector<T> st;
};

stack<int> sti;
```
**Tempalte Parameter**

T is known as template parameter i.e. name after `typename` keyword.

**Template Argument**

`int` is the template argument i.e. type which is going to substitute template parameter.

**Instantiation**

This is when the compiler generates a regular class, method, or function by substituting each of the template's parameters with a concrete type.
It could be implicit or explicit.

*Implicit instantiation*

This is when the compiler decides when to generate code for our template instances. Implicit instantiation means that we have to include the template definitions in our header files so that the compiler has an access to the definitions whenever it needs to generate the instantiation code.

*Explicit instantiation*

This is when the programmer determine when the compiler should generate the code for a specific specialization. Explicit instantiation allows us to move the template implementation into the .cpp file, and so hide from the user.

**Template Specialization**

In most of the context its same as instantiation. However, the term specialization can also be used when we provide a custom implementation for a function by specifying concrete types for all the template parameters. The following is called an explicit specialization:
```cpp
template<>
void stack<int>::push(int val)
{}
```

**Partial Specialization**

This is when we provide a specialization of the template for a subset of all possible cases. In other words, we specialize one feature of the template but still allow the user to specify other features. For example, if our template accepts multiple parameters, we could partially specialize it by defining a case where we specify a concrete type for only one of the parameters. In our Stack example with a single template parameter, we could partially specialize this template to specifically handle pointers(*) to any type T. This still lets users create a stack of any type, but it also lets us write specific logic to handle the case where users create a stack of pointers. This partially specialized class declaration looks like this:
```cpp
template<typename T>
class stack<T *>
{
public:
    void push(T* val);
	T* pop();
	bool isEmpty() const;
private:
	std:vector<T*> mStack;
};
```
Another example:
```cpp
template <typename K, typename V>
class MyMap{/*...*/};

// partial specialization for string keys
template<typename V>
class MyMap<string, V> {/*...*/};
...
MyMap<int, MyClass> classes; // uses original template
MyMap<string, MyClass> classes2; // uses the partial specialization
```

#### References
[bogotobogo](https://www.bogotobogo.com/cplusplus/templates.php)

### Authors

* **The Philomath**
