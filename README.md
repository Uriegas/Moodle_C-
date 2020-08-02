# Moodle Replica

This is a simple moodle replica written in C++ using the ANSI C library and other self created functions.   

In brief the user can create calculated questions for an end-user, mostly an student, this calculated questions have some settings like error tolerance, range of possible answer, etcetera.    

**A calculated question is a questions which input can be set by the user a.k.a. professor and the result is programmed by the user, which results in personalized questions for the end-user a.k.a. student.**

An example of a calculated question is: 
What is the result of x in 10x-20 = 0.  

Note that the result depends in the factors, this is 10, 20 and 0.  
So the professor will set this in the program as follows:  

**What is the result of x in {a}x -{b} = {c}.**

The values a, b, c have a range which is going to be set by the user and an error tolerance. The correct answer has to be set by a formula that the program is going to use, in this case the formula is:
({c}+{b})/{a}   

Then the range could be between 1 and 100; which tells the program that the possible values of a, b and c are going to be in this range, and by the formula this is going to evaluate to the result of x that the student should answer, but if he or she fails and the answer is between the error tolerance then the answer would be correct.  

## BUILDING
Build from source using cmake.  
It is required cmake, make and gnu gcc.  

Install as follows:  
1. **mkdir build**
2. **cd build**
3. **cmake ..**

These is going to create an executable in the build directory.  
This has only been proven in Ubuntu 18.04.4.  
Please do a little research on installing CMake projects before installing in another operating system.  

## TODO
1. Implement the formula input function on the Input class
2. Implement the 3 question functions
3. Implement the examen generator

## NOTES
testing.sh is file in the main directory that is going to build from source and open the executable automatically. It only works on Linux.  

This program make use of the lexer and parser functions in the following [repository](https://github.com/Uriegas/Lexer-Parser-in-Cpp) is better to prove the code before using the functions, it has not been fully tested yet.  

## FOR DEVELOPERS   
### Question Modularitation
There are 3 types of questions:  
1. Simple Calculated Question
2. Normal Calculated Question
3. Multiple Calculated Question

For a better performance the questions can be subdivided with 3 functions:  
1. `question_edit()`
2. `dataset_properties()`
3. `dataset_editing()`

This is the main format for every calculated question eachone with their specific specs.  

### Dataset
For storing the datasets configuration we only use the following container:   
```c++
    template <class T, class Compare = less<T>, class Alloc = allocator<T>>
    class set;
```
defined in the std namespace from the STL library.  

### Randomness
For generating random numbers we use a simple density probabilty function.  
1. Uniform. It means that every item has the same probability of ocurrance.
2. Logarithmic Unifor. The random items instantiation tends to minor values.

### Save Configuration
After creating the exam is necessary to store the configuration to a file, so that it can be used by other program that read it and applies the exam to the student.    
For this another program should be created or at least implement such a program in the current one.