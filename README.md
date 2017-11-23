# staff-management-system
it stores the employee data 

this system prompts the user to choose an action from the menu 

-insert information about an employee into database

or delete an employee from database or edit information about an employee

....................................................................................

MYSQL,database management system is used,it allows you to create tables to store data ana manage the relational databases.

the database that i use, contain two tables

employee table:id,name,birth year,address

jobsalary table:id_emp(foreign key),jobtitle,salary

......................................................

the source code is exist in the file called main1.cpp

the main parts in the code:

>>class employee

contains functions like....>

-insert :

for record information about any new employee .

-list :

list the id and the name of all employees.

-search:

search for an employee via their id number

-Delete:

delete rows from two tables

employee table(id,name,birth year,address)

jobsalary table(id_emp(foreign key),jobtitle,salary)

>>class JobSalary

contains functions like...>

-insert_job:

insert the job title and salary of an employee and the id of each employee

note: you must enter the name of employee that is recorded in employee table to record the job and salary in the jobsalary table

-update:

update the job title and salary of an employee
