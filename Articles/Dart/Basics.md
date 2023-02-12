Basics of Dart language

#### Setup

Can write and test the code on https://dartpad.dev/
Or if building a Cross platform App then install Visual Studio Code and Flutter and Dart extensions.

To run the dart program from terminal
> dart playground.dart

---
**Hello world**
```dart
main() {
  print("Hello World!!")
}
```
As the return type is not mentioned in above program, by default functions have return type as **void**.

* Dart is Static type programming language
* Its compiled programming language
* Dart core support is in dart:core package.
* Dart core package is by default included. We can also include it but that will be rdundent.
> import 'dart:core';
* To take input from user use io library
> import 'dart:io';
* Everything is an object in Dart. Even **null** type is object. main is also an object which is a subtype of the function class.

```dart
stdout.writeln('Enter you Name');
String name = stdin.readLineSync();
print('Your Name is $name');
```

Dart supports two types of compilation
* **AOT**: Ahead Of Time compilation
* **JIT**: Just in Time compilation

When we deploy application then dart runs AOT with optimization.

For local testing or production it runs JIT.

Variable can be defined like
```
var firstName = 'Name' // type of firstName is decided by the type of value assigned to the variable. Also known as type inference
String sirName = 'Name' // can only assign String
```

* Comments can be added as In-Line(//), multi-Line(/* */) or documentation(///).

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
