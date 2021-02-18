## About
Basic operations on dictionaries

```python
# dictionary
book = {"chap1":10 ,"chap2":20 ,"chap3":30}

print(book) # {'chap1': 10, 'chap2': 20, 'chap3': 30}
# display individual key-value
print(book["chap1"]) # 10

book["chap4"] = 40
print(book) # {'chap1': 10, 'chap2': 20, 'chap3': 30, 'chap4': 40}

print(list(book.keys())) # ['chap1', 'chap2', 'chap3', 'chap4']
print(list(book.values())) # [10, 20, 30, 40]
print(book.items()) # dict_items([('chap1', 10), ('chap2', 20), ('chap3', 30), ('chap4', 40)])

if "chap6" in book:
    print(book["chap6"])

print(book.get("chap6")) # None    

# book is getting updated for newbook
newbook = {"chap8":80,"chap9":90}
book.update(newbook)
print(book)  # {'chap1': 10, 'chap2': 20, 'chap3': 30, 'chap4': 40, 'chap8': 80, 'chap9': 90}

## If any object is prefixed with ** , it becomes dictionary
## 2nd approach
output = {**book, **newbook}
print(output) # {'chap1': 10, 'chap2': 20, 'chap3': 30, 'chap4': 40, 'chap8': 80, 'chap9': 90}
```
Why `+` didn't work here to concatenate dictionaries:

By `+` means we are trying to add two dictionaries means we want to add key-value pairs or one dictionary to another one. That does not work because the keys are not hashable in a dictionary. As a general rule, only immutable objects (strings, integers, floats, frozensets, tuples of immutables) are hashable (though exceptions are possible).
