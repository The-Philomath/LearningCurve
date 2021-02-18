## About

In python everything is an `object` instead of dataTypes

Every object contains set of methods or operations.

_There are **6** standard objects:-_

1. **number** can be decimal, integer. To convert them to octal or hex we use the casting.
```python
val = 10
```

2. **string** can be defined in single or double or triple quotes
```python
aname = 'python programming'
bname = "scala programming"
cname = """r programming"""
```

3. **list** can contain set of elements, can be group of numbers or strings or any combination. These are mutable
```python
alist = [10,20,30]
blist = [67.5,8.4]
clist = [10,56.5,"python",567.4]
```

4. **tuple** contains set of elements. can be group of numbers or strings or any combination. These are immutable

*** Elements inside tuple CANNOT be modified DIRECTLY ***
```python
atup = (10,20,40.123)
btup = (56.3,89.8)
ctup = ("unix",10,56.4)
```

5. **dictionary** contains elements in key : value pairs, like maps in C++.

Keys are always unique.

Key will either be number or string to uniquely identify.

Values can be any integer or string or list or tuple or dictionary or dictionary of dictionaries or any standard data structure

_syntax:_ object = {key:value , key:value , key:value....}
```python
book = {"chap1":10 ,"chap2":20 ,"chap3":30 ,4:6 }
```

6. **set** unorderd collection of **UNIQUE** values of same type
```python
values = {10,10,10,20,30} # set have only 3 values
```

----
**classification of objects**

_mutable objects_
* list
* dictionary
* set

_immutable objects ( unchangable )_
* string
* tuple
* number
