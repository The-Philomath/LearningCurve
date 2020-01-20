## About
Functors or function objects are the objects of a class which has overloaded function call operator i.e. `()`. Objects of Functor can behave like a function call.

Functor call is not a function call. Unlike functions functors do have states. And we can use functors as callable, wherever we need to pass a callable like in the comparators.

Function objects are another example of the power of generic programming and the concept of pure abstraction. We could say that anything that behaves like a function is a function.

Here is an example:-
```cpp
class constructors
{
    int data;
public:
    void operator ()(int temp)
    {
      std::cout << "function call operator";
      //some calculation on temp
    }
};
int main()
{
  constructors obj;
  obj(10); //operator() get called
}
```
**Output:-**

_function call operator_

As per "The C++ Standard Library" by Nicolai M. Josuttis.
>Function objects are usually faster than ordinary functions.
The concept of templates usually allows better optimization because more details are defined at compile time. Thus, passing function objects instead of ordinary functions often results in better performance.

STL refines functor concepts as follows:

* A **generator** is a functor that can be called with no argument.
* A **unary function** is a functor that can be called with one argument.
* A **binary function** is a functor that can be called with two arguments.

A special auxiliary function for algorithm is a **predicate**. **Predicates** are functions that return a `Boolean` value (or something that can be implicitly converted to `bool`). In other words, a **predicate** class is a **functor** class whose `operator()` function is a **predicate**, i.e., its `operator()` returns `true` or `false`.

**Predicates** are widely used in the STL. The comparison functions for the standard associative containers are **predicates**, and **predicate** functions are commonly passed as parameters to algorithms like `find_if`. Depending on their purpose, predicates are `unary` or `binary`.

A unary function that returns a bool value is a **predicate**.
A binary function that returns a bool value is a **binary predicate**.

**Predefined Functions Objects**
A typical example of predefined function object in STL is `set`. It sorts element in increasing order because by default it's using less(<) sorting criteria. So, when we do:

    set<int> mySet;
internal code looks like this:

    set<int, less<int> > mySet;
So, we want to store our elements in decreasing order in a `set`, we do:

    set<int, greater<int> > mySet;
In the example below, the `negate<int>()`` creates a function object from the predefined template class negate. It simply returns the negated `int` element.

The second `transform()` algorithm combines the elements from two vector containers by using `multiplies<int>()` operation. Then it writes the results into the 3rd vector container.

### Authors

* **The Philomath**
