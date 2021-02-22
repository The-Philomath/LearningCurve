## About

Few examples of working with different python libraries

**Working with json**
```python
import json

with open('employee.json') as fobj:
    # convert into json object
    data = json.load(fobj)
    for key,value in data.items():
        if isinstance(value,list):
            for item in value:

                for skey,svalue in item.items():
                    print(skey.ljust(15),svalue)
```

**Working with web scrapping**
```python
import requests
import bs4
from bs4 import BeautifulSoup


response = requests.get("https://www.google.com/")

if response.status_code== 200 :

    soup = BeautifulSoup(response.text, 'html.parser')
    for link in soup.find_all('a'):
        print(link.get('href'))

    #print(soup.get_text())
```

**Datetime and time**
```python
import datetime

print(datetime.datetime.now())

print(datetime.date.today())

import time
print(time.time())
```
**openpyxl and csv**
```python
from openpyxl import Workbook
wb = Workbook()

# grab the active worksheet
ws = wb.active

# Data can be assigned directly to cells
ws['A1'] = 42

# Rows can also be appended
ws.append([1, 2, 3])

# Python types will automatically be converted
import datetime
ws['A2'] = datetime.datetime.now()

# Save the file
wb.save("sample.xlsx")
```
convert xlsx to csv
```python
# importe required libraries
import openpyxl
import csv

  # open given workbook  
# and store in excel object  
excel = openpyxl.load_workbook("19_Feb_2021.xlsx")

# select the active sheet
sheet = excel.active

# writer object is created
col = csv.writer(open("realestate_new.csv", 'w',  newline=""))

# writing the data in csv file
for r in sheet.rows:
    # row by row write  
    # operation is perform
    col.writerow([cell.value for cell in r])
```
