## About

Basic operations on tuples are

```python
atup = (10,20,30,40)
print("Tuple elements are", atup) # Tuple elements are (10, 20, 30, 40)

# As tuples are immutable so we need to convert them to list to modify them
# converting to list
alist = list(atup)
alist.append(50)
alist[0] = 1000
# recoverting back to tuple
atup = tuple(alist)
print(atup) # (1000, 20, 30, 40, 50)
```

Tuple supports only two operations `index` and `count`

index will return the index of element we are searching. Count will return the number of occurrences of that element.
