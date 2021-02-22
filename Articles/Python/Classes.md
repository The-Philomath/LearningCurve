## About

Basics of object oriented implementations in python.

In python there is a difference in class variable and instance variable. Class variables are like the `static` variables in `C++` and instance variables are like a normal member variable.

**Class variable:**

A variable that is shared by all instances of a class. Class variables are defined within a class but outside any of the class's methods. Class variables are not used as frequently as instance variables are.

**Instance variable:**
A variable that is defined inside a method and belongs only to the current instance of a class.

----
**Operator Overloading**
```python
class Marks:
    def __init__(self,marks,subject):
        print("Inside constructor ( __init__) ")
        self.marks = marks
        self.subject = subject

    def __str__(self):
        print("Inside constructor (  __str__) ")
        return 'Total marks %d obtained in %s ' %(self.marks,self.subject)

    def __add__(self,other):
        print("Inside constructor ( __add__) ")
        return Marks(self.marks + other.marks,self.subject + ',' +  other.subject)

m1 = Marks(80,"Maths")
m2 = Marks(85,"Science")
m3 = Marks(75,"English")
m4 = Marks(83,"French")
m5 = Marks(82,"Geography")

print( m1 + m2 + m3 + m4 + m5 )
```
----
**Data hiding**

Variables with `__` are `private` and `_` are `protected`.

All the members defined with public can be accessible anywhere in the program

Member defined with private(__) can be accessible only inside the class

Any member defined with protected(_) can be accessed in other classes as well
```python
class Person(object):
    # A class variable
    __secretCount = 0
    def getDetails(self):
        print("Calling person details method")
        self.__secretCount +=1
        print(self._Person__secretCount)

person1 = Person()
person1.getDetails()
person1.getDetails()
```
----
**inheritance**
```python
#every class is inherited from object class but its not mandatory to mention object here
class Person(object):
    ## constructor in python
    def __init__(self,name):
        print("Calling person constructor")
        # instance variable
        self.name = name

    def getDetails(self):
        print("Calling Person Details method")
        return self.name

    ## destructor in python. will be called at garbage collection i.e. when object is no more in use.
    def __del__(self):
        class_name = self.__class__.__name__
        print(class_name,"destroyed")

class Student(Person):
    def __init__(self,name,branch,year):
        print("Calling student constructor")
        Person.__init__(self,name)
        self.branch = branch
        self.year = year

    def getDetails(self):
        print("Calling student constructor")
        return "%s studies %s and in %s year." %(self.name,self.branch,self.year)

class Teacher(Person):
    def __init__(self,name,papers):
        print("Calling teacher constructor")
        Person.__init__(self,name)
        self.papers = papers

    def getDetails(self):
        print("Calling Teacher Details method")
        return "%s teaches %s " % ( self.name ,','.join(self.papers))

person1 = Person('Tyler')
print(person1.getDetails())
student1 = Student('Ryan','computer science',2013)

#getDetails calls overridden method
print(student1.getDetails())
teacher1 =  Teacher('Giridhar',['C','C++'])

# getDetails calls overridden method
print(teacher1.getDetails())
```

We can import any other class with name of file like:-
```python
import file_name
print(file_name.__name__)
```

Using `Pass`

The pass statement is used as a placeholder for future code.

When the pass statement is executed, nothing happens, but you avoid getting an error when empty code is not allowed.

Empty code is not allowed in loops, function definitions, class definitions, or in if statements.
```python
class Robot:
    pass

x = Robot()
y = Robot()

x.name = "Marvin"
x.build_year = "1979"

y.name = "Caliban"
y.build_year = "1993"

print(x.name) # Marvin
print(y.build_year) # 1993
```
