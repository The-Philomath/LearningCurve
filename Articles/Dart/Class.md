* **Default constructor**: constructor with name same as class name
```dart
class Person
{
  String name;
  Person(String name)
  {
    this.name = name;
  }
  // equivalent constructor
  Person(this.name);
}
```

* **Named constructor**:
```dart
class Person
{
  String name;
  Person(this.name);
  Person.guest(){
    name = 'guest';
  }
}
//can be called as
var perObj = Person.guest();
```

* outside of class `final` and `const` works similarly.
* `final` can be assigned only once in constructor. can't be reassiged.
* `const` is compile time constant.
* using `extend` keyword we can inherit a class.
* `@override` annotations are used to get compile time warning if we are not actually overriding base class function.
* Getter and setter
```dart
num get right => left + width;
set right(num value) => left = value - width;
```

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
