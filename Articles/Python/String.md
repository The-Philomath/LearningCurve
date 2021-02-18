## About
Brief introduction on strings in python

Strings are **immutable** in python. we can't modify them.

let's understand different methods in python for strings.
```python
name ="python programming"
aname = 'unix'
bname = "unix shell scripting"

print(name,aname,bname)  # python programming unix unix shell scripting
### different substring operations on string
# string[start_index:stop_index:step]   
print(name) # python programming
print(name[0]) # p
print(name[1]) # y
print(name[0:4]) # pyth
print(name[3:6]) # hon
print(name[2:]) # thon programming
print(name[:5]) # pytho
print(name[:])  # print everything i.e. python programming
print(name[::]) # python programming
print(name[0:17:2]) # pto rgamn
print(name[1:17:2]) # yhnpormi
print(name[-1]) # g
print(name[-2]) # n
print(name[-4:-2]) # mi
print(name[::-1]) # gnimmargorp nohtyp
```
```python
print("unix","language") # comma , is a separator here but in output we will have space as a separator. By default print will insert a newline after each print.
```

_String formating_
```python
query = "I love {1} and {0}" # {} is a placeholder, by default its value start from 0 in a format string but we can change the order like here we did
print(query.format("python", "scala")) # I love scala and python
```
----
Here are some string functions or methods and there usages:-
```python
name ="python programming"

print(name.capitalize()) # first letter will be capitalized. Python programming
print(name.lower()) # convert string to lowercase. python programming
print(name.upper()) # convert string to uppercase. PYTHON PROGRAMMING
print(name.swapcase()) # toggle the casing. PYTHON PROGRAMMING

print(name.center(40)) # create a space of 40 and insert string in middle of that.            python programming           
print(name.center(30,"*")) # create a space of 30, insert string in middle of that and insert "*" in the remaining space. ******python programming******
print(name) # python programming
print(name.replace("python", "ruby")) # find first argument in string and replace with second argument. ruby programming
print(name) # python programming
print(name.isupper()) # All is functions return bool values. check is the string uppercase. False
print(name.islower()) # is string lower case. True
print(name.split(" ")) # split with space as delimiter. ['python', 'programming']
output = name.split(" ") # store the returned value in a variable
print(output) # ['python', 'programming']

aname = " python   "
print(len(aname)) # print length of string. 10
bname = aname.strip()  # remove whitespace at both ends
print(len(bname)) # 6

print(name.encode(encoding='utf-8')) # binary encoded string. can use `utf-16' or other encodings. b'python programming'
```

We can concatenate strings with + operator like this:
```python
first = "python"
second = "programming"

output = first + " " + second
print(output) #python programming
```
