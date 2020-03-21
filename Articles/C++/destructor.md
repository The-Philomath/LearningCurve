## About
Destructor are used to destroy the object. They are called automatically when object goes out of scope or when `delete` get called.

Destructors can't be overloaded. As we can't provide any parameter to destructor. Because it doesn't make sense. Most of the times destructor get called automatically.

By default destructors are always **inline** and **noexcept**. Not only destructors all those functions which helps in releasing memory are noexcept (delete, delete[]) until unless it is explicitly declared as it(or its Base classes) will raise an exception.

**Section §12.4 of C++0x draft n3290** has this to say about destructors:

**Destructors**

>A special declarator syntax using an optional function-speciﬁer (7.1.2) followed by ˜ followed by the destructor’s class name followed by an empty parameter list is used to declare the destructor in a class deﬁnition.

(emphasis added)

So no, destructors do not take parameters. (The 2003 standard has the exact wording of the above paragraph.)

We should always make destructors as `virtual` if we are going to get the support of runtime inheritance in our class.

Let's take an example:-
```cpp
#include<iostream>

class Base
{
   public:
   Base()
   {
       std::cout<<"Base constructor"<<std::endl;
   }
   virtual void display()
   {
       std::cout<<"Base class";
   }
   ~Base()
   {
       std::cout<<"Base destructor"<<std::endl;
   }
};
class Derived:public Base
{
   public:
   Derived()
   {
       std::cout<<"Derived constructor"<<std::endl;
   }
   void display()
   {
       std::cout<<"Derived class"<<std::endl;
   }
   ~Derived()
   {
       std::cout<<"Derived destructor"<<std::endl;
   }
};

int main()
{
    Base *obj1 = new Derived;

    obj1->display();
    delete obj1;
    system("pause");
    return 0;
}
```

**Output:-**

 _Base constructor  
  Derived constructor  
  Derived class  
  Base destructor_

From the above example its clear that if there is some resource allocation in Derived constructor then that will not get freed as derived's destructor is not get called. To call the derived's destructor destructor of base class should be virtual.

    virtual ~Base();

**Output:-**

_Base constructor  
 Derived constructor  
 Derived class  
 Derived destructor  
 Base destructor_

We can declare destructors as pure virtual if we don't want to make any other method of class as pure virtual but still want to make the class as abstract.

Note that if we declare any other method as pure virtual then derived class must have to override that otherwise that will also be abstract. But if declare destructor as pure virtual then only base class will be abstract.

>The destructor is the only method that even if it is pure virtual has to have an **implementation** in order to instantiate derived classes.

Destructor of derived class will always be virtual if base class has a virtual destructor.

### Authors

* **The Philomath**
