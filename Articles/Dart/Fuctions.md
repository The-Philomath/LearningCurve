* Each function is object of class Function.
* forEach is higher Order function as it takes another function as parameter.

**Arrow function**
* shortut to define a function.
```dart
dynamic sum(var num1, var num2)
{
  return num1 + num2;
}
// is equivalent to
dynamic sum(var num1, var num2) => num1 + num2;
```
* positional parameter and named parameter.
```dart
//previous example shows positional parameter. Here is named parameter
sum(num2: 2, num1: 3); //function call
dynamic sum({var num1, var num2}) => num1 + num2;
```
* by default named parameter are optional
* We can mix both positonal and named parameter
> dynamic sum(var num1, {var num2}) => num1 + (num2 ?? 0);
* To make positonal parameter optional use angular brackets
> dynamic sum(var num1, [var num2]) => num1 + (num2 ?? 0);

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
