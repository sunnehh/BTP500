## Due: November 25, 2022

### This assignment is worth 12% of your final grade.

### Late penalties

* up to 1 week late - 10%
* 10% per day there after to a maximum of 50%

## Assignment Completion

In order to for this assignment to be considered completed you must submit:

* a completed analysis of functions listed for (part A)
* a successful test run for part C (green check for part C in actions tab)

Note: Assignment completion is the minimum requirements for your assignment.  It does not mean you will receive full marks.


## Assignment Objectives:

In this assignment, you will:

* Complete an analysis of multiple related functions for a class
* Implement hash tables
* Observe effects of various implementations on performance

## Repository Setup

* [Repo Creation for 1 person](https://github.com/seneca-btp500-f22/btp500-f22/blob/main/assignments/individual-repo-creation.md)
* [Repo Creation for teams of 2](https://github.com/seneca-btp500-f22/btp500-f22/blob/main/assignments/group-repo-creation.md)

For this assignment you can choose to work entirely on your own or with one partner.  The choice is entirely yours and it will have no effect on your mark for this assignment.  Any mark received will be given to every member of your team.  You do not have to keep your team beyond one assignment (so if you find you are not working well with your partner, you don't have to stay with them for the entire course).

No matter which option you choose, you need to set up a repository for your assignment, even if you are working by yourself. You cannot just use your lab repository. The starter files and tester will be in the repo you create.

If you are working with a partner, we would like you to work such that for each item, if one person did the writing (the author), the other person would verify and check the work (the checker).   The authoring of the work should be split approximately equally.  Work needs to be split so that each person authors parts of the programming and non-programming components.  In other words, each person needs to write some code and do some analysis/reflection.

## Restrictions

**No STL containers classes(such as vector, lists, etc.) or library functions(such as sort) may be used for this assignment. Please ask if you aren't sure when using any part of the Standard Library.**

## Overview

The Table class is a templated abstract base class.  That is, it describes the functionalities of a Table but does not implement any part of it.  It is up to classes derived from the Table to implement the Table itself.  This section describes the interfaces (ie the operations) of a Table.  The specifics of the implementation (ie is it a hash table or a sorted array? what collision resolution method is used etc.) is all done in the derived classes.

The records for this table consists of key-value pairs.  The key is a c++ string.  The value can be any data type (T) that supports the following:

* assignment (=)
* instantiation without arguments (you can declare variables of type T, the value of which is undefined)

In the description below the word Record refer to a key-value pair.  The way you store it (whether you make a template struct called Record with a data member for key and value, or you store them separately in parallel structures is entirely up to you).

Here are the operations on Table:

```c++
Table();
``` 
Initializes a Table to an empty table

***

```c++
bool insert(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the function does nothing and returns false.  Otherwise the new key-value pair is added to the table and true is returned.   When out of space, the function will grow the array.

***

```c++
bool modify(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the record's value is replaced by the value passed to this function.  If no record exists with a matching key, function does nothing and returns false.


***

```c++
bool find(const string& key,TYPE& value );
```
This function is passed a key and a reference for passing back a found value.  If your table contains a record with a matching key, the function returns true, and passes back the value from the record.  If it does not find a record with a matching key, function returns false.

***

```c++
bool remove(const string& key);
```

This function is passed a key.   If your table contains a record with a matching key, the record (both the key and the value) is removed from the table

***

```c++
int numRecords() const
```

This function returns the number of records in the table.

***

```c++
bool isEmpty() const
```

This function returns the number of records in the table.

***

```c++
size_t capacity() const
```
This function returns capacity of the table.

***

```c++
double loadFactor() const
```
This function returns the load factor of the table. (number of records divided by capacity of table)

***

Aside from the above functions, all tables must have proper destructors, copy constructors/assignment operators, move constructor/operator that allow for resources to be properly managed.

## Part A: Analysis (9 marks)

The SimpleTable class (found in table.h) implements a table using a Sorted array of records.  That is all records are sorted by their keys.  the "smallest" key is at element 0, and the keys get larger as you progress along the array.  

The table's implementation can be found in the table.h file.   Determine the run time of the following functions/situations as they are currently implemented, where n is the total number of records in the current table. In cases such as the the copy constructor or assignment operator where there is a SimpleTable as argument (the rhs), base on your analysis with the assumption that rhs will have the same number of records as the current object.

* numRecords()
* insert() - if item does not exist
* modify - if item does exist 
* find() - if item is not there
* remove() - if item is there
* copy constructor
* move constructor
* move assignment operator
* destructor


## Part B: Suggestions (6 marks)

Suggest 3 improvements you could make to the code that will improve its efficiency. State which function(s) would be improved by the suggested improvement.  Write up your suggestion into a2.md.   This is not a coding question.  You do not need to implement your suggestion.  A clear description of what you want to do is good enough.

**Which improvements counts and which do not**:
* You can't change the underlying data structure.  For example, "make it a hash table" would make it something different so that won't count.  Fundamentally it must use a sorted array as the underlying data structure
* A process only counts once: "Do a selection sort instead of what is written in the copy constructor" and "Do this selection sort instead of what is written in the assignment operator" is just one suggestion not two. (note this suggestion is silly, and just used as an example)

## Part C Implementation(20 marks)


A hash table organizes the records as an array, where records are placed according to a hash value that you get from a hash function.  Please use the hash function from the C++ STL.  You can find more info about how to do it here:

[[http://en.cppreference.com/w/cpp/utility/hash]]

Here is a simple example of how to use the hash function with string keys:
```cpp
#include <iostream>
#include <string>
//you need to include functional to use hash functions
#include <functional>
const int cap = 100;
int main(void){
    //this is just a string... any string can be a key
    std::string key = "this is my key";

    //declare an hash function object.  hashFunction is a variable but it is also a function
    std::hash<std::string> hashFunction;
 
    //you can now call hashFunction and it will return an unsigned whole number
    size_t hash = hashFunction(key);
    std::cout << "hash(key): " << hash << std::endl;
    
    //if you need to change it so that it is a proper index for a table with capacity of cap
    size_t idx = hash % cap;
    std::cout <<"hashindex = hash(key) %% cap"<< idx << std::endl;
}
```

You will implement two hash tables for this assignment.  One will use linear probing for collision resolution, the other will use chaining.  

### LPTable 


LPTable is a hash table that uses linear probing as the collision resolution method.  

The constructor for the LPTable accepts one argument
```
LPTable(size_t capacity, double maxLoadFactor=0.7);
```

**capacity** is the capacity (number of elements for the array) of the table.
**maxLoadFactor** is defaulted to 0.7 (70%).  When inserting, if adding a new record causes the load factor to exceed the maxLoadFactor, function will grow the array.

***

```c++
bool insert(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the function does nothing and returns false.  Otherwise the new key-value pair is added to the table and true is returned. When inserting, if adding a new record causes the load factor to exceed the maxLoadFactor, function will grow the array.  (each time the table is grown, the capacity is doubled)  

***

```c++
bool modify(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the record's value is replaced by the value passed to this function.  If no record exists with a matching key, function does nothing and returns false.


***

```c++
bool find(const string& key,TYPE& value );
```
This function is passed a key and a reference for passing back a found value.  If your table contains a record with a matching key, the function returns true, and passes back the value from the record.  If it does not find a record with a matching key, function returns false.

***

```c++
bool remove(const string& key);
```

This function is passed a key.   If your table contains a record with a matching key, the record (both the key and the value) is removed from the table

***

```c++
int numRecords() const
```

This function returns the number of records in the table.

***

```c++
bool isEmpty() const
```

This function returns the number of records in the table.

***
```c++
size_t capacity() const
```
This function returns capacity of the table.

***

```c++
double loadFactor() const
```
This function returns the load factor of the table. (number of records divided by capacity of table)

***

**Aside from the above functions, all tables must have proper destructors, copy constructors/assignment operators, move constructor/operator that allow for resources to be properly managed.**


### Chaining Table

ChainingTable is a hash table that uses chaining as the collision resolution method.  

It is recommended that you use your assignment 1 linked list to help you in this part of the assignment.  To do so, set up a struct for to combine your key-value pairs into a single object.  Then  add ==, !=, and < comparison operators to compare these according to its key

The constructor for the ChainingTable accepts one argument
```
ChainingTable(size_t capacity, double maxLoadFactor=1.0);
```

**capacity** is the capacity (number of elements for the array) of the table.
**maxLoadFactor** is defaulted to 1.0 (100%). 

***

```c++
bool insert(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the function does nothing and returns false.  Otherwise the new key-value pair is added to the table and true is returned. When inserting, if adding a new record causes the load factor to exceed the maxLoadFactor, function will grow the array.  (each time the table is grown, the capacity is doubled)  

***

```c++
bool modify(const string& key, const TYPE& value);
```  
This function is passed a key-value pair.   If your table already has a record with a matching key, the record's value is replaced by the value passed to this function.  If no record exists with a matching key, function does nothing and returns false.


***

```c++
bool find(const string& key,TYPE& value );
```
This function is passed a key and a reference for passing back a found value.  If your table contains a record with a matching key, the function returns true, and passes back the value from the record.  If it does not find a record with a matching key, function returns false.

***

```c++
bool remove(const string& key);
```

This function is passed a key.   If your table contains a record with a matching key, the record (both the key and the value) is removed from the table

***

```c++
int numRecords() const
```

This function returns the number of records in the table.

***

```c++
bool isEmpty() const
```

This function returns the number of records in the table.

***
```c++
size_t capacity() const
```
This function returns capacity of the table.

***

```c++
double loadFactor() const
```
This function returns the load factor of the table. (number of records divided by capacity of table)

***

**Aside from the above functions, all tables must have proper destructors, copy constructors/assignment operators, move constructor/operator that allow for resources to be properly managed.**

### Files needed for testing
```
table.h
timer.cpp
timer.h
a2tester.cpp
dictionary.txt
```

## Part D: Comparing performance (5 marks)

In this part of the assignment you will conduct an experiment that compares the performance of the find() function for the two tables.  This part of the assignment is more open ended and there will be choices that are left up to you.

What we want to know is the following:

1. How fast is search() function at the same load factor?
2. Does the load factor determine which table performs better?

### Design an experiment

Design how you will perform your experiment. In your repository you will find a file called experiment.cpp.  It shows you how to use the Timer class.  You will need to alter this file to answer the questions above.  

* Submit the experiment.cpp file. 

### Discussion

In a a2.md in your repo:

* Describe your experiment.  
     * how does your experiment program work?  
     * At what load factor(s) did you measure performance?
     * What did you search for?  was every item in table or did you search for things that were not in table also?

* Create at least 1 graph that show your results of your experiment.  Make sure you can see the graphs in your page.  A link is not good enough.
* Write a summary paragraph that answers the two questions above.


## Submission:

In order to for this assignment to be considered completed you must submit:
* the analysis for part A (placed in the a2.md)
* a successful test run for part C (green check for part C in actions tab)

Part B and D are not required for completion but failure to complete them will result in a grade of 0 for that portion of the assignment

Please make sure you follow the steps listed below fully


### Submit a test verification


In order for this assignment to be considered completed, you must submit:
* a successful pull request (or push) of your table.h 
* your code via github in the main branch



### Submit your analysis, improvements and experiments

* For parts A, B and D (graphs and discussion), Provide all answers/graphs/discussion in a2.md amd place the updated file into your main branch
* For part D, complete a successful pull request or push of experiment.cpp file into your repo


### Resubmissions

* With the test verification there is very rarely a need to have you resubmit your program.  However, if there are many errors in your program or it misses the point entirely (like making use the STL or not writing a hash table), you may be asked to resubmit your work.  Any work that is resubmitted, will receive a 50% penalty

## Grading Breaking

#### Part A (analysis)

There are 9 functions/scenarios you are asked to analyze for part A and it is worth 9 marks.  The rubric for grading analysis is as follows:

 Criteria | Level 0 | Level 1 | Level 2 | Level 3 | Level 4 |
|---|---|---|---|---|---|
| Analysis | No analysis completed | Little to no explanation in analysis... arrives at final result as if by magic  | Lacks a significant component to analysis has one or more major errors or miscalculation within the analysis | Has minor errors or some minor missing steps in analysis  | Clearly laid out analysis with correct flow that shows how all mathematical expressions are obtained.  Clear and consistent usage of mathematical symbols.  Complete and clear count of operations |

Each function is judged independently.

#### Part B (Improvements)

You get two marks for each improvement suggestion that isn't saying the same thing... so if you suggest doing one thing and that results in 3 function being faster, that isn't 3 different suggestions.  that is just one suggestion.  Make sure you have 3 distinct suggestions for improvements.  Improvements also cannot fundamentally change the data structure (it must stay a sorted array)

#### Part C (Implementation)

* Documentation - 20%
* Coding Style - 10%
* Memory Management - 20%
* Efficiency - 25%
* Completion and correctness of functions/functionality - 25% - Some aspects of some functions may not be tested for.  Sometimes this is because it simply isn't possible (like destructors for example).  Thus, I reserve the right to read your program and take off marks for anything that does not work to spec.

| Criteria | Level 0 | Level 1 | Level 2 | Level 3 | Level 4 |
|---|---|---|---|---|---|
| **Documentation - 20%** |Almost no documentation of any type |only a few functions got documented and documentation tends to be code description as opposed to code intention. | many function documentation missing or severe lack of details for function description or documentation is done only at code level (within the code) and not as an overall intention|a few functions documentation missing. or function description comments lack some detail Over documentation.  documenting every line of code is not a good... let the code speak | For all functions state what parameters are (and any limitations, what return value is, what it does. |
| **Code Styling - 10%** | more than 10 cases of inconsistent or bad styling | 5 to 10 cases of inconsistent  or bad styling | 3 to 5 cases of inconsistent or bad styling or  less than 3 casses of inconsistent or bad styling with creation of non-specified public member functions | 2 or less cases of inconsistent  or bad styling or creation of non-specified public member functions | Consistency is key. same variable name styling (camel case pref), same data member styling, same curly bracket positioning, correct and consistent indentation, good variable names | 
| **Memory Management - 20%** | 4 or more instance of serious lack of memory deallocation , or only deallocating part of structure | 3 instance of serious lack of memory deallocation , or only deallocating part of structure | 2 instance of serious lack of memory deallocation , or only deallocating part of structure |a few small memory leaks, forgetting to delete a node here and there OR 1 instance of serious lack of memory deallocation , or only deallocating part of structure | no memory leaks|
|**Correctness and Completeness of Code - 25%** | 4 significant error or 2 or more signifiicant error with missing code for 1 function | 3 significant error or 1 signifiicant error with missing code for 1 function | 2 significant error or missing the code for 1 function | 1 significant error | all functions completed and correct |
| **Efficiency - 25%** | 4 or more instance of inefficiency | 3 instance of inefficiency | 2 instance of inefficiency| 1 instance of inefficiency | Function is as efficient as possible |


#### Part D (Data Analysis)

Your marks is based on the following:

* degree to which your experiments can answer the questions
* clear and correct graphs to show your results
* appropriate discussion of your experiment and results

