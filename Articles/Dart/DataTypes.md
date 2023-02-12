**Data Types**
- int
- bool
- double
- String
- dynamic

**dynamic** type variables can be reassiged to a different type after the initial assignment.

Like initially we can assign a string and later an integer to it.

Unlike others it will be defined at runtime. Others will be defined at compile time.

**String**

* String can be defined in single or double quotes.
* Put `r` in front of string to define a raw string. Special chracters will be treated as normal string and they will not be evaluated.
* can define multi line strings with three single or three double quotes.

**Type Conversion**
* To convert string to integer or double use `parse` function.
> var one = int.parse('1');
* To convert integer to string use `toString` function.
> String oneToString = 1.toString();
* To convert double to string use `toStringsFixed` function.
> String oneToString = 3.14159.toStringAsFixed(2); // output is 3.14

* Type of a variable can be checked with `varName.runtimeType`.
* If no value is asigned to  variable it contains `null` object.

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
