## About

Basic operations on sets

```python
aset = {10,10,10,20,30,30,30}
bset = {30,30,40,40,50}
cset = {20,30,40,50,60}
print(aset) # {10, 20, 30}
print(aset.union(bset)) # {50, 20, 40, 10, 30}
print(aset.intersection(bset).intersection(cset)) # {30}
print(aset.difference(bset)) # {10, 20}
print(aset.issubset(bset)) # false

alist = [10,10,20,30,40,50]
aset = set(alist)
print(aset) # {40, 10, 50, 20, 30}  check here no ordering in output

```
