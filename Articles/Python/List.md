# About

some basic operations which can be applied on lists are

```python
alist = [10,20,30,40,50,56,2,4,65,6]

print(alist[0:3]) # [10, 20, 30]
print(alist[::-1]) # [6, 65, 4, 2, 56, 50, 40, 30, 20, 10]
print(alist[::2]) # [10, 30, 50, 2, 65]

# append() : one object will be added at the end of the list
alist.append(900)
print("After appending:",alist) # After appending: [10, 20, 30, 40, 50, 56, 2, 4, 65, 6, 900]

# extend() : adding an iterable
alist.extend([34,23,12])
print("After extending:", alist) # After extending: [10, 20, 30, 40, 50, 56, 2, 4, 65, 6, 900, 34, 23, 12]

# list.insert(where to insert , what to insert)
alist.insert(0,100)
print("After inserting:", alist) # After inserting: [100, 10, 20, 30, 40, 50, 56, 2, 4, 65, 6, 900, 34, 23, 12]

alist.pop()   # last value will be removed
print("After pop", alist) # After pop [100, 10, 20, 30, 40, 50, 56, 2, 4, 65, 6, 900, 34, 23]

returnedvalue = alist.pop(0)
print("After pop", alist) # After pop [10, 20, 30, 40, 50, 56, 2, 4, 65, 6, 900, 34, 23]
print(returnedvalue) # 100

getcount = alist.count(10)
print(getcount) # 1

if 400 in alist:
    alist.remove(400)
    print("After removing:",alist)

alist.reverse()
print("After reversing:", alist) # After reversing: [23, 34, 900, 6, 65, 4, 2, 56, 50, 40, 30, 20, 10]

alist.sort()
print("After sorting:",alist) # After sorting: [2, 4, 6, 10, 20, 23, 30, 34, 40, 50, 56, 65, 900]
```
