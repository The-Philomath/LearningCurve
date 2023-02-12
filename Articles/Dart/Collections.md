Three built-in collection types in dart
* List
* Set
* Map

**List or Array**

```dart
var nums = [1,2,3];
for(var n in nums)
{
  print(n);
}
//equivalent forEach
nums.forEach( (n) => print(n) );
```
* `List<int>` static type list means we can't assign anything else except int to it.

* To make the values of a List constant.
> var names = const ['Philo', 'Math'];

We can't change the value at 0 and 1 indexes in above list.

```dart
List<String> names = ['Philo', 'Math'];
var aliasNames = names;
var copyNames = [...names];
```

**Set**

* unique collections of items
> var names = {'Philo', 'Math'};

* empty curly braces defines a map. to define set define the type Like
> var names = <String>{}; // same as below
> Set<String> names = {};

**Map**
* Key value pairs
> var names = {
>    'n1': 'Philo',
>    'n2': 'Math'
>};
* define and assign later
> var names = Map();

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
