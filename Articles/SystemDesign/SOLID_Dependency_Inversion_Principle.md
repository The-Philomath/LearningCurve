**Dependency Inversion Principle** is to define the best possible way to define dependency between different objects. It is based on 2 core ideas:-

1. High level modules should not depend upon low level modules. Both of them should depend upon abstractions.
2. Abstractions should not depend on details. Details should depend on Abstractions.

Here abstraction means we should not depend on the concrete type instead of that we should use the abstraction. Like if the implementation detail of class is using a vector and we are traversing that vector in another class then the another class depends on the implementation details of first class. The first class may change the underlying implementation to something else and then it will break the another class code. We should not have this type of dependency.

The **DIP** is basically a way of adding plugs and sockets to your code. It allows you to create your high level modules (the computer) independent of the low level modules (the mouse). The low level modules can be created later, and are easily replaceable. Plugs can be base classes with virtual methods; templating; possibly preprocessor function macros. The plug is essentially an abstract interface. All implementations/subclasses adhere to the Liskov Substitution Principle. This is because the implementations/subclasses will be used via the abstract interface, not the concrete class interface. The "sockets" are any functions or classes that use a "plug".

```cpp
enum class Relationship{
  parent,
  child,
  sibling
};

struct Person{
  string name;
};

struct Relationships  // Low-lvel as it provide functionality for data storage
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }
};

struct Research // High-level
{
  Research(Relationships& relationships)
  {
    auto & relations = relationships.relations;  // depends on internals of low level module. Breaks DIP
    for(auto && [first, rel, second]: relations)
    {
      if(first.name == "A" && rel == Relationship::parent)
      {
        std::cout<<"A is parent of "<< second.name;
      }
    }
  }
};
int main()
{
  Person parent{"A"};
  Person child1{"B"}, child2{"C"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research r(relationships);
  return 0;
}
```
If vector will changes to the map in future then it will break the code in high level module. So instead of having direct dependency we should use the abstracton.

```cpp
enum class Relationship{
  parent,
  child,
  sibling
};

struct Person{
  string name;
};

struct RelationshipBrowser{
   virtual vector<Parent> find_all_children_of(const string& name) = 0;  
};

struct Relationships: RelationshipBrowser // Low-level as it provide functionality for data storage
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string& name) override
  {
    vector<Person> result;

    for(auto && [f, rel, s]: relations)
    {
      if(d.name == name && rel == Relationship::parent)
      {
        result.push_back(s);
      }
    }

    return result;
  }
};

struct Research // High-level
{
  Research(RelationshipBrowser& browser)
  {
    for(auto& child: browser.find_all_children_of("A"))
    {
      std::cout<<"A has a child "<<child.name;
    }
  }
};
int main()
{
  Person parent{"A"};
  Person child1{"B"}, child2{"C"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research r(relationships);
  return 0;
}
```
----
**Dependency Injection**

To use this technique, we need classes that fulfill four basic roles. These are:

1. The **service** you want to use.
2. The **client** that uses the service.
3. An **interface** that’s used by the client and implemented by the service.
4. The **injector** which creates a service instance and injects it into the client.

First 3 are already provided by **DIP** service is Relationship, client is Research, interface is RelationshipBrowser.

It allows us to standardize and centralize the way objects are constructed in our application by supplying (injecting) an external dependency into a software component rather than creating an dependency within.

There are three ways a component (object or function) can get a hold of its dependencies:

* The component can create the dependency, typically using the new operator.
* The component can look up the dependency, by referring to a global variable.
* The component can have the dependency passed to it where it is needed.

The first two options of creating or looking up dependencies are not optimal because they hard code the dependency to the component. This makes it difficult, if not impossible, to modify the dependencies. This is especially problematic in tests, where it is often desirable to provide mock dependencies for test isolation.

The third option is the most viable, since it removes the responsibility of locating the dependency from the component. The dependency is simply handed to the component.

Ways to inject dependency:

1. **Setter Injection** Adding a setter method that accepts the dependency is one way of injection point into a class.
2. **Constructor Injection** (the most popular way of injection) The most common way to inject dependencies is via a class's constructor. To do this, we need to add an argument to the constructor signature to accept the dependency.
3. **Property Injection** Just setting public fields of the class directly.

**DI** using Constructor Injection:-
```cpp
#include <iostream>

class GasolineSource {
public:
    virtual void FuelUp() = 0;
    virtual ~GasolineSource() = default;
};

class GasStation : public GasolineSource {
public:
    virtual void FuelUp() {
        std::cout << "Pumping gas at gas station" << std::endl;
    }
};

class FuelCan : public GasolineSource {
public:
    virtual void FuelUp() {
        std::cout << "Pumping gas from fuel can" << std::endl;
    }
};

class Car {
    GasolineSource *gasolineService = nullptr;
public:
    // The dependency for a source of gasoline is passed in
    // through constructor injection
    // as opposed to hard-coded into the class definition.
    Car(GasolineSource *service)
    : gasolineService(service) {
        // If the dependency was not defined, throw an exception.
        if(gasolineService == nullptr){
            throw std::invalid_argument("service must not be null");
        }
    }
    void getGasoline() {
        std::cout << "Car needs more gasoline!" << std::endl;
        // Abstract away the dependency implementation with polymorphism.
        gasolineService->FuelUp();
    }
};
```
