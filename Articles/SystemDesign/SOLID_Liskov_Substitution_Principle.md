`LSV : Liskov Substitution Principle:`  Substitutability is a principle in object-oriented programming stating that, in a computer program, if S is a subtype of T, then objects of type T may be replaced with objects of type S. If it looks like a duck, quacks like a duck but need batteries. then you probably have the wrong abstraction.

Functions that use pointers or references to base classes must be able to use objects of derived classes without knowing it.

```cpp
//Bad design
class Bird{
    public:
       void fly(){}
};

class Duck: public Bird
{};

```

The duck can fly because it is a bird, but what about this:
```cpp
class Ostrich: public Bird
{};
```
Ostrich is a bird, but it can't fly, Ostrich class is a subtype of class Bird, but it shouldn't be able to use the fly method, that means we are breaking the LSP principle.
```cpp
//Good design
class Bird{}
class FlyingBirds: public Bird{
   public void fly(){}
};
class Duck: public: FlyingBirds
{};
class Ostrich: public Bird
{};
```
