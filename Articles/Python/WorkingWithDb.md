## About

How tot work with databases using Python

**Basics of SQL:**

displaying all the existing databases
```
show databases ;
```
creating database
```
create database aristocrat;
```
access your database
```
use aristocrat;
```
displaying all tables
```
show tables;
```
creating table
```
create table realestate( street varchar(100) , city varchar(100) );
desc realestate;
```
inserting records
```
insert into realestate values('101 MG Road','Delhi');
insert into realestate values('GT Road','Hyderabad');
select * from realestate;
```

Working with python using `pymysql` library
```python
#step1: establish the connection
#step2: prepare query
#step3: executing query
#step4: fetch the output
#step5  close the connection

import pymysql

try:
    db = pymysql.connect(host='localhost',port=3306,user='root',password='password@123',database='aristocrat')
    #print(db)
    #step2 : create cursor
    cursor = db.cursor()   
    query = "select * from realestate"   
    #step3: execute the query
    cursor.execute(query)

    #step4 : fetch the output
    for record in cursor.fetchall():
        print("Street:",record[0])
        print("City  :",record[1])
        print("--------")

    #step5 : close the connection
    db.close()
except pymysql.OperationalError as err:
    print("Invalid credentials")
except pymysql.IntegrityError as err:
    print(err)
except (pymysql.DatabaseError,pymysql.ProgrammingError) as err:
    print(err)
except TypeError as err:
    print(err)
except Exception as err:
    print(err)
```
reading from csv and writing to db
```python
import pymysql
import csv

try:
    db = pymysql.connect(host='localhost',port=3306,user='root',password='password@123',database='aristocrat')
    #print(db)
    #step2 : create cursor
    cursor = db.cursor()   
    with open("realestate.csv","r") as fobj:
        reader = csv.reader(fobj)
        for line in reader:   
            query = "insert into aristocrat.realestate values('{}','{}')".format(line[0],line[1])               
            #step3: execute the query
            cursor.execute(query)  
    db.commit()
    #step5 : close the connection


    db.close()
except Exception as err:
    print(err)
```
