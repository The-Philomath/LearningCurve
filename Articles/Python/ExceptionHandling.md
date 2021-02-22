## About

Handling the exceptions in the runtime is known as exception handling.

**Types of Errors**
- syntax error
- semantic error or runtime error or logical errors


_Exception handling keywords:_

    try     ( Code for which we need to handle exception goes into try block)
    except  ( mention the type of exception we want to capture)
    else    ( optional, if exception didn't hit then the else block will execute)
    finally ( optional, will always be called whether exception hit or not )
    raise   ( to raise the exceptions forcefully)

```python
import csv
import sys
try:
    with open("realestate1111.csv","r") as fobj:
        csvreader = csv.reader(fobj)
        for line in csvreader:
            print(line[0])
            print(line[1])
            print("-------")

except FileNotFoundError as err:
    print("Error : File not found")
    print("system generated error:",err)
except IndexError as error:
    print("system generated error:",error)
# capture multiple exceptions
except (ValueError,ZeroDivisionError) as err:
    print(err)
# All exceptions are inherited from Exception class
except Exception as err:
    print("system generated error:",err)  
    print(sys.exc_info())
```
