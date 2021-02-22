# About

Brief overview of file handling in python

- working with flat files (  csv log conf txt  .... )
- working with third party files ( xlsx docx pdf mp4 pptx .... )

**Flat Files**

Different modes to open a file:

    r : read
    w : write
    a : append

Ways to open a file:
```python
fobj = open("filename.txt","a")
```

Way to close a file:
```python
fobj.close()
```

##### Approach to open the file
```python
fobj = open("info.txt","w")
fobj.write("python programming\n")
fobj.close()
```

#### context manager
if the line starts with the keyword 'with' it is called as context manager

file will be closed automatically when it moves out of context/indentation
```python
with open("infonew.txt","w") as fobj:
    fobj.write("unix shell scripting\n")
```
##### if the file has to be created in different path ....
```python
fobj = open("D:\\trainings\\info.txt","w")
fobj.write("python programming\n")
fobj.close()
```

Different read operations for a file

- reading the file line by line   ( used for processing )
- reading using `fobj.readlines()`  ( output will be in list )
- reading using `fobj.read()`       ( output will be in string format)
- reading using csv library       ( used for processing )
- reading using pandas library    ( used in data analytics )

Examples to read a file.
```python
## reading the file line by line
# fobj acts as file object or file handler or cursor
with open("languages.txt") as fobj:
    for line in fobj:
        # remove whitespaces if any
        line = line.strip()
        output = line.split(":")
        print(output[0])



## using readlines()
with open("languages.txt") as fobj:
    print(fobj.readlines())


## using readlines()
with open("languages.txt") as fobj:
    print(fobj.read())


import csv
with open("languages.csv") as fobj:
    #converting file object to csv object
    csvreader = csv.reader(fobj,delimiter=':')
    #print(csv.reader(fobj,delimiter=':'))
    for line in csvreader:
        print(line)
```
