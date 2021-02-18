## About
different ways to run for looks on different objects in python

```python
for val in range(1,11):
    print(val) #prints 1...10

for val in range(1,11,2):
    print(val) # 1 3 5 7 9   

## for with string
name ="python"
for char in name[0::2]:
    print(char) # p t o

## for with list
alist = [10,20,30]
for val in alist:
    print(val) # 10 20 30

## for with tuple
atup = ("unix","linux","perl")
for item in atup:
    print(item) # unix linux perl

## for with dictionary
## read only KEY and displaying key,value both
book = {"chap1":10 ,"chap2":20}
for key in book.keys():
    print(key) # chap1 chap2
    print(book[key]) # 10 20

# we are key,value both
for key,value in book.items():
    print(key,value)    


for value in book.values():
    print(value)   
```

Some python examples for loops, if elif.
```python
data = {
"id": "0001",
"type": "donut",
"name": "Cake",
"image": {
"url": "images/0001.jpg",
"width": 200,
"height": 200
},
"thumbnail": {
"url": "images/thumbnails/0001.jpg",
"width": 32,
"height": 32
}
}

for key,value in data.items():
    if isinstance(value,str):
        print(key.ljust(20),value)
    elif isinstance(value,dict):
        for skey,svalue in value.items():
            finalkey = key + "." + skey
            print(finalkey.ljust(20),svalue)

# output will be
# id                   0001
# type                 donut
# name                 Cake
# image.url            images/0001.jpg
# image.width          200
# image.height         200
# thumbnail.url        images/thumbnails/0001.jpg
# thumbnail.width      32
# thumbnail.height     32
```

```python
z = "192.168.0."
for x in range(1,11):
    print(z+str(x))

#192.168.0.1
#.
#.
#.
#192.168.0.10
```
