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
- reading using fobj.readlines()
- reading using fobj.read()
- reading using csv library       ( used for processing )
- reading using pandas library    ( used in data analytics )
