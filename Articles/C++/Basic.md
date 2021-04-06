## About
Few basic of C++

* C++ is a general purpose programming language.
* Translation unit(i.e. a .cpp file) is only translated to object code not headers.
* Linker adds initialization code used before main. That code triggers main.
* pragmas are commands given to compiler.
* _pragma once_ check for code **BELOW** it. That code will not be included twice.
* Symbols with external linkage should not define in header file. Otherwise there will be multiple definitions.
* `inline` in front of variable inform linker to discard all definition but one.
* extern with global const is used to make them externally visible.
* `ADL`-> Argument dependent lookup or Koenig lookup, is the set of rules for looking up the unqualified function names in function-call expressions, including implicit function calls to overloaded operators. These function names are looked up in the namespaces of their arguments in addition to the scopes and namespaces considered by the usual unqualified name lookup.
* Implement rule of 5 only when we have ownership semantics means we have to define a destructor to release some resources.
* return non local variables by reference.
* Name Hiding is the concept in C++ which hides the base class function in derived class if the name of function is same in both the classes even though parameters are different. It will not be an overloading.
* Always overload subscript operator in const and non const both to modify and not to modify the object.
* In C++11 Destructors are noexcept means they dont throw. If you throw from a destructor it will crash the program.
* In C++98 it will crash only if destructor is called due to stack unwinding as a result of an exception throw.
* __ declspec(nothrow)_ is visual studio specific version of nothrow
* void fun()throw(){} is execption specification and it is deprecated in modern C++
* Compiler creates jump tables for the exception handling so that during stack unwinding if the block do not capture the exception control can directly jump to block end.
* In Case of _noexcept_, no jump table is created.
* Don't store exception message in _std::string_ because exception can be raised due to new fail(Heap failure) and _std::string_ is using dynamic memory(Heap) to store the string.
* Always throw by value but catch by reference because it is possible that someone in the call stack may want to modify the exception raised and want to extra info so that the further call stack can know that it has been raised by someone else.
* integer exception can't be catch by float block but we can capture via inheritance tree.
* Aggregation and Composition are subsets of association meaning they are specific cases of association. In both aggregation and composition object of one class "owns" object of another class. But there is a subtle difference:
Aggregation implies a relationship where the child can exist independently of the parent. Example: Class (parent) and Student (child). Delete the Class and the Students still exist.
Composition implies a relationship where the child cannot exist independent of the parent. Example: House (parent) and Room (child). Rooms don't exist separate to a House.
* The Open Closed Principle (OCP): You should be able to extend a classes behavior, without modifying it.
* We can separate the defintion and declaration of templates in .cpp and .h but that's not a good practice. and the .cpp will not be a translation unit.  imagine a scenario where a template function is declared in a.h, defined in a.cpp and used in b.cpp. When a.cpp is compiled, it is not necessarily known that the upcoming compilation b.cpp will require an instance of the template
injected-class-name  -> StoryTeller - Unslander Monica
* Always use **RAII** wherever you can : RAII This is a strange name for a simple but awesome concept. Better is the name Scope Bound Resource Management (SBRM). The idea is that often you happen to allocate resources at the begin of a block, and need to release it at the exit of a block. Exiting the block can happen by normal flow control, jumping out of it, and even by an exception. To cover all these cases, the code becomes more complicated and redundant. Smart_ptr is away to implement RAII in C++.

* Either move ctor or move assignment operator disables generation of copy ctor/assignment.
* Don't include header file use forward declaration instead.
* `lock_gurad` will lock the undelying mutex and unlock it at the end of scope.
* `decltype` keyword is not scope sensitive.
* We must have to define templates in .h But specialized versions have to define in .cpp with prototype in .h
* Function object or Functor is a function that has some state.
* No public and private specifiers mentioned in a struct then its a **POD** type.
* Call to function object is faster than a function pointer.
* Avoid storing pointers inside containers because it may lead to memory leak during deletion.
* to unmangle use -> _undname < < mangled string > >_
* _std::sort()_ function require random access iterators so list can't use it.
* `erase remove idiom`-> First use remove/remove_if to remove the elements. This will shift whole array/vector to front. then erase all the elements in one go.
* Never use hand written loop with container always use algorithms because they are much efficeint and fast. require less typing. No matter what you do it is very rare that you will be able to write a much efficient algorithms.
* `iterator adaptors`-> _std::inserter_ is a convenience function template that constructs a _std::insert_iterator_ (an iterator adaptor)for the container c and its iterator i with the type deduced from the type of the argument.
* _std::insert_iterator_ is a LegacyOutputIterator that inserts elements into a container for which it was constructed, at the position pointed to by the supplied iterator. The container's insert() member function is called whenever the iterator (whether dereferenced or not) is assigned to. Incrementing the _std::insert_iterator_ is a no-op
_std::set<int>_ target;
* _std::copy(source.begin(), source.end(), inserter<std::set<int>>(target, target.begin()))_ // iterator adaptors
* `emplace vs insert fns like push_back`-> insertion functions take objects to be inserted while emplace functions take constructor argument for the object to be inserted. Due to which insert functions creates a temporary object and copy that(move construct) to target container. But emplace don't create temporaries.
* We can rely on vector, dequeue and strings for construction and no to do the assignment instead. Prefer to use emplace to these containers.
* Don't use emplace for the containers which can store duplicates and we are going to store the duplicates in future. Because for such containers emplace also creates the temporaries to find the duplicates and it creates it more often than inserts.
* don't use emplace functions if you are adding the resource managing objects(smart pointers) to a container it may lead to memory leak on exception during `new` call.
* `Braced initialization` prevent narrowing conversion i.e. _int b{2.0};_ will throw an error whereas _int b(2.0);_ will not throw.
* `Braced initialization` is immune to `c++ most vexing parse`(anything that can be parsed as a declaration must be interpreted as one) i.e. _Widget w();_ its a function declaration. What if the client want to create an object _w_ by calling default constructor. It is possible with only braced initialization i.e. _widget w{};_ will call the default constructor.
* An example where the choice between parentheses and braces can make a significant difference is creating a _std::vector< numeric type >_ with two arguments.
* Call using braced initialization strongly prefer the constructor overloads taking `std::intializer_lists` even if an exact matching constructor is available. If compiler can convert the argument to initializer list params it will prefer the initializer list.
* Avoid 0 and NULL use _nullptr_. Avoid overloading on integral and pointer types. _nullptr_ is not integral type is of _std::nullptr_t_ type and that is defined as type of _nullptr_. Its a circular definition. _nullptr_ is a pointer of one type, its pointer of all types.
* If _f(int)_ and _f(void *)_ are present and we call it with 0 or NULL it will always call _f(int)_ but if we call it with _nullptr_ it will call _f(void *)_ .
* If base class pointer pointing to a function which is not available in base class then it will generate error over there. It's a compilation error. Memory of `Vtable` and `VPTR` gets allocated inside the process address space.
* even if a pointer/reference of base class pointing to an object on stack then also the function called with that pointer/reference will need a virtual base class method to resolve the overrided function call.
* Remember virtual mechanism(runtime polymorphism) of resolving the function depend on the type of memory to which pointer/reference pointing to. Whereas compile time function call resolution depend on the time of pointer itself.
* Runtime polymorphism do not depend on how the object to which pointer/reference pointing to get the memory. It can be an object on stack or an object on heap.
* If the object is on stack and object gets its memory on compile time then why is it called runtime polymorphism? Here runtime means the function call happens with that pointer/reference will be resolved at runtime. At compile time compiler will see that the calling function is a virtual function so compiler will decide to leave the resolution of that call at runtime and insert code like. Call vptr_in_the_object(pointing to base of VTABLE) + offset(to function actual address in VTABLE).
* Why can't compiler resolve the call at compile time if the object has already been created and vptr has been assigned? Because at function call statement i.e. `ptr->fn()` compiler don't know what type of object `ptr` is pointing to. Is it pointing to base or a derived object.
* For abstract classes compiler does allocate a slot in the `vtable` for the pure virtual function but does not assign an address to it. This leaves the `vtable` incomplete which requires the derived classes to implement the function and complete the `vtable`. Some implementations do simply place a _NULL_ pointer in the `vtable` entry; other implementations place a pointer to a dummy method that does something similar to an assertion.
* Why emplace_back uses parameter pack instead of one argument? "emplace" means "construct in place". So it needs the arguments for the constructor. The argument to constructor can be any. all the arguments are forwarded to the constructor director like: `std​::​forward<​Args​>(​args)...`.
* Calling virtual functions from a constructor or destructor is dangerous and should be avoided whenever possible. All C++ implementations should call the version of the function defined at the level of the hierarchy in the current constructor and no further. In a constructor, the virtual call mechanism is disabled because overriding from derived classes hasn’t yet happened. Objects are constructed from the base up, “base before derived”. Destruction is done “derived class before base class”, so virtual functions behave as in constructors: Only the local definitions are used – and no calls are made to overriding functions to avoid touching the (now destroyed) derived class part of the object.
* In `C` When initializing an object of static or thread-local storage duration, every expression in the initializer must be a constant expression or string literal. Static variables are initialized prior to program startup. While in `C++` static local variables are initialized the first time control passes through their declaration. So they can point to a non constant variable also.
*  When would the following code be false.
```cpp
bool result  = (floatValue == floatValue);
```
When `floatValue == NaN` //not a number like (0/0)
* Pure virtual may have a body, although it is illegal to include it at the point of declaration. This means that to have a body the pure virtual function must be defined outside the class. Note that even if it has a body, the function must still be overridden by any concrete classes derived from Abstract. They would just have an option to call Abstract::pure_virtual() explicitly if they need to
* dynamic_cast will return NULL on a bad cast if you are casting a pointer; it will throw std::bad_cast when casting references. It is a compile-time error to attempt to cast objects with dynamic_cast (eg, with dynamic_cast<Derived>(base))
* Vector of `bool` doesn't store `bool`s. It's basically a bitfield.
```cpp
vector<bool> vb(20,true);
auto b = vb[10]; //type of auto not necessarily be bool. From cppinsight its std::_bitreference
bool *pb = &b; //error, cannot convert 'std::_Bit_reference*' to 'bool*' in initialization
```
* Perfect forwarding allows you to preserve an argument’s value category (lvalue/rvalue) and const/volatile modifiers.
* West `const` is the worst `const` east `const` is the best const. East `const` refers to putting `const`, by habit, to the right (east) of the thing you want `const`. West `const` is the habit of putting `const` to the left.

In west const style, `const T` when `T` is `char*` is `char*const`. Surprising. (T is template parameter)
In east const style, `T const` when `T` is `char*` is `char*const`. Not surprising at all.
* keywords we can use anywhere but identifies can only be used at certian specific places. We can define a variable with the identifier name.
identifiers: final, override, import, module
* If it is a reverse_iterator and we want to erase at that location then we should use either

```cpp
stackObj.erase( std::next(it).base() );
```
Or
```cpp
std::advance(it, 1);
stackObj.erase( it.base() );
```
* Covariant return types(overloaded functions using base and derived types) works only with pointers and references not with objects or smart pointers.
* when the `new` operator is used to allocate memory and the handling function is unable to do so, a `bad_alloc` exception is thrown. But when `nothrow` is used as argument for `new`, it returns a `nullptr` instead.
* There are three ways in C++ to initialize variables in a thread safe way. 1. Constant expressions 2. The function `std::call_once` in combination with the flag `std::once_flag` 3. Static variables with block scope
