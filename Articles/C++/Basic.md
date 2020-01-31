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
* __declspec(nothrow)_ is visual studio specific version of nothrow
* void fun()throw(){} is execption specification and it is deprecated in modern C++
* Compiler creates jump tables for the exception handling so that during stack unwinding if the block do not capture the exception control can directly jump to block end.
* In Case of _noexcept_, no jump table is created.
* Don't store exception message in _std::string_ because exception can be raised due to new fail(Heap failure) and _std::string_ is using dynamic memory(Heap) to store the string.
* Always throw by value but catch by reference because it is possible that someone in the call stack may want to modify the exception raised and want to extra info so that the further call stack can know that it has been raised by someone else.
* integer exception can't be catch by float block but we can capture via inheritance tree.
* `dependency inversion principle` -> High level modules should not depend upon low level modules. Both should depend upon abstractions.
The Dependency Inversion Principle is basically a way of adding plugs and sockets to your code. It allows you to create your high level modules (the computer) independent of the low level modules (the mouse). The low level modules can be created later, and are easily replaceable. Plugs can be base classes with virtual methods; templating; possibly preprocessor function macros. The plug is essentially an abstract interface. All implementations/subclasses adhere to the Liskov Substitution Principle. This is because the implementations/subclasses will be used via the abstract interface, not the concrete class interface. The "sockets" are any functions or classes that use a "plug".
The Open Closed Principle (OCP): You should be able to extend a classes behavior, without modifying it.
* We can separate the defintion and declaration of templates in .cpp and .h but that's not a good practice. and the .cpp will not be a translation unit.  imagine a scenario where a template function is declared in a.h, defined in a.cpp and used in b.cpp. When a.cpp is compiled, it is not necessarily known that the upcoming compilation b.cpp will require an instance of the template
injected-class-name  -> StoryTeller - Unslander Monica
* Always use **RAII** whereever you can

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
