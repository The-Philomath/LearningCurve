## About

In Python if we talk about methods it means we are talking about member methods i.e. we are talking about methods of an object.

If we are talking about functions it means we are talking about functions common for all the objects.

**Bulitin functions**
```python
print() # print to console
input() # capture input from keyboard
range() # define a range like range(1,10) shows number from 1...9
len() # length of object
isinstance() # Returns True if a specified object is an instance of a specified object
type() # type of object
id() # Returns the id of an object
help() # Executes the built-in help system
dir() # The dir() function returns all properties and methods of the specified object, without the values.
sum() # Sums the items of an iterator
max() # returns the item with the highest value, or the item with the highest value in an iterable.
min() # returns the item with the minimum value, or the item with the minimum value in an iterable.
zip() # Returns an iterator, from two or more iterators
map() # Returns the specified iterator with the specified function applied to each item
filter() # Use a filter function to exclude items in an iterable object
```

**typecasting functions**
```python
str()
int()
list()
float()
oct()
hex()
tuple()
dict()
set()
```

----

##### User defined functions:-

By default in python everything is in main function.
```python
# Always true by default. as everything is in main.
if __name__ == "__main__":
    x = class_name()
    x.class_function("python","Perl")
```

Here is how to define a user defined function
```python
# define a display function taking two parameters, second one is a variadic parameter
def display(first,*data):
    print(first)
    print(data)

display(10)

# parameters are name bounded
def display(second,first):
    print(first) # 10
    print(second) # 20

display(first=10,second=20)

# function returning a value
def display(a,b):
    c = a + b
    return c

total = display(10,20)
print(total) #30

## function overloading in python
# default arguments
def display(a=0,b=0,c=0,d=0):
    print(a,b,c,d)

display()
display(10)

# global variables vs function variables
c = 10
def display(a, b):
    global c  # if we comment out this line then function will show and error on next line. Reason is this the line c=40, here it is considered as a declaration of a class variable. So we should tell the interpreter that this is not a class variable this is the global variable itself.
    print(a+b+c) # 60
    c=40
    print(a+b+c) # 90

display(20,30)
```
 `Lambda functions` are the single line expressions in python.
```python
# syntax
#functioname = lambda variables : expression
# lambda is the replacement of single liner function
add = lambda x : x + 5

total = add(10)
print(total) # 15

upper = lambda x : x.upper()

name = "python"
getupper = upper(name)
print(getupper) # PYTHON

# Using map to append argument of list one by one to a function
alist = ["google","oracle","microsoft"]
def append(string):
    return "http://www." + string + ".com"

print(list(map(append,alist)))

# another approach using lambda and map
alist = ["google","oracle","microsoft"]
print(list(map(lambda x :"http://www." + x + ".com" ,alist)))

alist = [1,2,3,4,5,6]
print(list(filter(lambda x:x%2, alist)))

# filtering list strings which are of length 6
alist = ["google","unix","linux","oracle"]
print(list(filter(lambda x:len(x)==6, alist)))
```
