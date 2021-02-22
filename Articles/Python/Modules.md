## About

Python supports a number of Module or libraries.

**builtin library**

builtin libraries will be installed with the python which are generally used. Python has inbuilt database sqlite3 database  ( library sqlite3)

**third party library**

Depending on the requirement( Database(oracle,sybase,mongodb,mysql,) , networking , cloud(AWS azure gcp oci alibaba) , ML , DA , Image processing)
developer has to install the third party library from www.pypi.org OR pip tool OR easy_install tool

**Examples**

_builtin libraries_

        os            : os.listdir() os.remove()
        sys           : system config information
        urllib.request: working with http
        math          : mathematical operations
        random        : random numbers
        calendar
        smtplib       : sending mails
        ftplib        : ftp'ng the file
        telnetlib     :
        logging       : logging all the events
        shutil        : copy,move,rmtree ....
        filecmp       : comparing directories
        zipfile       : create/extract the zip files
        rarfile       : create/extract the tar files
        tarfile       : create/extract the tarfiles
        getpass       : shadowing the password
        json          : reading/writing json files
        csv           : reading/writing csv files
        xml        
        sysconfig     : system configuration
        collections   : working with dictionaries
        argparse      : passing args from command line
        optparse      : passing args from command line
        time          : working with date and time
        datetime      : working with date and time
        cryptography  : encrypting and decrypting the passwords
        heapq         : performing array operations
        gzip          : reading gunzip files
        re            : validating the strings
        ipadresss     : validting ip address
        platform      : display platform information
        pathlib       : creating temp files
        threading     : for performing multi threading
        multiprocessing:
        subprocess    : invoking the system commands ( linux or dos commands)


_frequently used third party libraries_

> database related

        pymysql   :
        cx_Oracle
        pymongo
        pymssql


> web frameworks ( developing web applications)

        django
        flask
        bottom

> analytics/machine learning

        numpy
        scipy
        pandas
        seaborn
        plotly
        ggplot
        matplotlib   : visualizing data .. bar graph.. pie graph
        scikit-learn :  machine learning algorithms

>image processing

        pillow
        opencv

>APIs ( REST API) ( web services )

        requests

>excel programming

        openpyxl    : reading/write excel files
        xlsxwriter  : writing to excel file
        pyexcel
        xlrd
        python-docx : working with ms-word

>networking

        paramiko   :  interacting with remote servers
        netmiko    :  connecting to router/switch
        pyping     :  ping any host or ip address

>web scrapping

        beautifulsoup
        scrapy

#### How to import a library
```python
import os
filesize = os.path.getsize(filename)


## 1st approach
import math
print(math.floor(3.4))
print(math.ceil(3.4))


## 2nd approach
import math as m
print(m.log(2))
print(m.tan(2))


## 3rd approach
from math import floor,tan,log,sin
print(floor(3.4))


##4rd approach
from math import *
print(floor(3.4))
print(log(3))
```
