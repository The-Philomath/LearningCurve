Apart from basic operators dart provides **Null Aware Operator**

* ?.
* ??
* ??=

```dart
if(num != null)
{
  data = num.member;
}

//is  equivalent to
data = num?.member;
```

```dart
if(num != null)
{
  data = num.member;
}
else
{
  data = 'defaultVal';
}

//is  equivalent to
data = num?.member ?? 'defaultVal';
```

```dart
if(num == null)
{
  num = Num();
}

//is  equivalent to
data = num ??= Num();
```

**Type test operator**
* is

```dart
if(x is int)
{
  ...
}
```

#### References
[youtube](https://www.youtube.com/watch?v=Ej_Pcr4uC2Q)

### Authors

* **The Philomath**
