# Project 01 - Python_Bootcamp  

Summary: In this project, you will learn about the main functions of the **Python** language .

## Contents
 1. [Chapter I](#chapter-i)   
     - [Rules](#rules)   
 2. [Chapter II](#chapter-ii)  
     - [General information](#general-information)  
 3. [Chapter III](#chapter-iii)      
     - [Task 0. Project creation](#task-0-project-creation)  
     - [Task 1. Scalar product](#task-1-scalar-product)  
     - [Task 2. Palindrome](#task-2-palindrome)  
     - [Task 3. Figures](#task-3-figures)  
     - [Task 4. Pascal's triangle](#task-4-pascal's-triangle)  
     - [Task 5. String to number conversion](#task-5-string-to-number-conversion)  
     - [Task 6. Movies](#task-6-movies)  
     - [Task 7. A robot](#task-7-a-robot)
     - [Task 8. Different numbers](#task-8-different-numbers) 
     - [Task 9. The derivative at a point](#task-9-the-derivative-at-a-point)  
     - [Task 10. Machines](#task-10-machines)   



## Chapter I
## Rules

1. All along the way you may feel a sense of uncertainty and a severe lack of information: that's okay. Don't forget that the information in the repository and Google is always with you. So are your peers and Rocket.Chat. Communicate. Search. Rely on common sense. Don't be afraid to make mistakes.
2. Be careful about the sources of information. Check. Think. Analyze. Compare. 
3. Read the tasks thoroughly. Reread it several times.  
4. Read the examples carefully. There may be something in them that is not explicitly stated in the task itself.
5. You may find inconsistencies, when something new in the terms of the task or examples conflicts with something you already know. If you come across such an inconsistency, try to figure it out. If you can’t, write the question in open questions and find out in the process of work. Do not leave open questions unresolved.  
6. If a task seems confusing or impossible to complete — it only seems that way. Try to decompose it. Most likely, some parts will become clear.  
7. There will be various tasks. Those marked with an c (\\\*) are for the more meticulous students. These tasks are more difficult and are not mandatory. But if you do them, you will gain additional experience and knowledge.
8. Don't try to fool the system and those around you. You will be fooling yourself first.
9. You got a question? Ask your neighbor on the right.  If that doesn't help, ask your neighbor on the left.
10. If you use help, you should always understand why and how.  Otherwise, the help will not make sense.
11. Always push only to the develop branch! The master branch will be ignored. Work in the src directory.
12. There should be no files in your directory other than those specified in the tasks.

## Chapter II
## General information

**Python** is a high-level, interpreted programming language that has a simple and readable syntax.

In the late 1980s, Guido van Rossum of the Dutch National Research Institute for Mathematics and Computer Science GWI proposed the idea of creating a new programming language.

At the time, Guido was involved in the development of the ABC language as a basis for studying programming. The ABC project eventually failed and Guido moved on to programming other projects involving the Amoeba operating system as a key theme (which connects computers in a network and gives users the illusion of interacting with a single system).

In 1989, the Amoeba system lacked a scripting language, so Guido van Rossum planned a mini project: he was going to write a programming language based on the ABC developments. The first prototype consisted of a simple virtual machine, a parser, and a runtime environment. CWI developers liked the Python prototype, and many of them got involved right away: they started using the language for internal projects and helped refine the code.

In February 1991, Guido published the source code for Python version 0.9.0 in the newsgroup. This initial release had modules borrowed from Modula-3. Van Rossum described the module as "one of the main elements in Python programming".

Python 1.0 was released in January 1994. The last version released by Van Rossum while working at the Center for Mathematics and Informatics (CWI) was Python 1.2.

On June 29, 1994, the forum published an article that addressed the Python community's dependence on Guido van Rossum's solutions - the author shared that large companies are afraid of using technologies that are tied to one person.

The article was written by Michael McLay of the US National Institute of Standards and Technology (NIST). He recruited Guido to work with him, and this led to the creation of the Python Software Foundation in 1995 — a non-profit organization that was to be responsible for the protection and development of the Python language. This organization got several leaders, and Guido van Rossum was given the mock title of Benevolent Dictator For Life.

Since then, Python has become very popular with developers who are attracted to its clean syntax and reputation for productivity. The second version of Python appeared in 2000, and the third version in 2008. Since late 2020, the official Python community has only supported the third version.

**Python's main advantages**:

1. Сode readability: Python syntax is designed to make code easy to read and understand. It helps to develop programs quickly and simplifies code maintenance.
2. Interpretability: Python is an interpreted language, which means that the code is executed line by line by an interpreter rather than compiled into machine code. This makes development and testing easier.
3. Multitasking: Python supports both synchronous and asynchronous programming. This allows us to efficiently solve a variety of tasks, including processing large amounts of data, creating web applications, and solving scientific problems.
4. A large community: Python has an active developer community, which contributes to an extensive library of modules and frameworks. This makes Python a powerful tool for a variety of tasks.
5. Wide use: Python is used in various fields such as web development (FastAPI, Django, Flask), data analysis and machine learning (NumPy, Pandas, TensorFlow, PyTorch), task automation, scientific research, game creation, and more.
6. Portability: Python is a cross-platform language, which allows programs to run on different operating systems without changes to the source code.
7. Object-oriented programming: Python supports object-oriented programming (OOP), which makes code easier to organize and more modular.

### Topics to study:

- Program entry point, program structure: In Python, the entry point into a program usually starts with the `main()` function or by executing code at the top level of the file.
- Program compilation/interpretation: Python is an interpreted language, code is executed line by line by the interpreter.
- Control structures (sequential, branching, repetition): Python also has conditional statements (if-elif-else), loops (for, while) to control program execution.
- Simple data types: Python has data types such as numbers (integers, floating point numbers), strings, and boolean values.
- Composite data types: Lists, tuples, dictionaries, and sets are the main composite data types in Python.
- Input/Output (stdin-stdout): Python has features to handle data input and output via standard streams:  (`input()` and `print()`.
- Memory management, garbage collector: Python automatically manages memory and has a garbage collector that keeps track of unused objects and frees memory.
- Complex data structures: Python includes high-level data structures such as lists of lists, dictionaries of dictionaries, modules for creating templates (e.g., the` typing` module for supporting typing), and others.
- Exception handling: Python provides mechanisms for handling exceptions using keywords `try`, `except`, `finally`, `else`. This allows programmers to handle and manage errors in the code.
- Working with files: Python has rich tools for working with files. You can open, read, write and close files using built-in functions and methods.
- Functions: You can create custom functions in Python using the `def` keyword. This allows for better code organization as well as the implementation of recursive algorithms.
- Object-oriented programming: Python supports object-oriented programming: You can create classes and objects, define methods and attributes, and use inheritance and polymorphism.

## Chapter III

**Pay attention!** Each task must be prepared as an individual project. For example, `T01/src/exercise0`, `T01/src/exercise1`, ... , `T01/src/exerciseN-1`, where *N* is a number of tasks. If you need the previous task for the next one, simply copy the previous project to the directory of the next one and continue development in it.

## Task 0. Creating a Project

For development in the Python language, you will need to install the appropriate interpreter. You can download it from the official site. You will then be able to use the command line and/or various integrated development environments (IDEs) to work on your projects. 
A project in this case is a set of files with the extension `.py` , which contain Python code. They are run with the python command `filename.py` (or `python3`) individually or imported into some common file, often called `main.py`. The process of creating a project in PyCharm is quite simple - you will need to select the Python interpreter, as well as the path for storing and the name of the project. It is also possible to create a virtual environment, which is usually convenient to use for large projects with many different dependencies (libraries, frameworks). The solutions to the following tasks need to be organized as separate files: `task1.py`, `task2.py`, ... I.e the solution of each task must be in an individual file. Run these files also separately.

## Task 1. Scalar product

Calculate the scalar product of two vectors in three dimensional space. Use standard input stream and standard output stream for data input and output, respectively. Do not check the correctness of the input data.

- Input: Real numbers, coordinates of two vectors on two lines respectively.
- Output: Real number, scalar product of given vectors.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>1.0 2.0 3.0<br>4.0 5.0 6.0</td>
        <td>32.0</td>
    </tr>
</table>

## Task 2. Palindrome

Determine whether the number is a palindrome or not. Use standard input stream and standard output stream for data input and output, respectively. Do not use strings. Negative numbers are not considered palindromes. Do not check the correctness of the input data.

- Input: Integer.
- Output: True if this number is a palindrome. False if this number is not a palindrome.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>1143411</td>
        <td>True</td>
    </tr>
</table>

## Task 3. Figures

Process a square matrix of zeros and ones, count the number of "squares" and "circles" in it. There are no other figures in the matrix. The figures cannot be beyond the boundaries of the matrix. There is an empty space between any two figures. Identified figures contain more than one unit. Use the input.txt file to enter data. Use the standard output stream to output data. Do not check the correctness of the input data.

- Input: The rows of a square matrix, each containing zeros/units separated by a space.
- Output: Two natural numbers separated by a space are the number of "squares" and the number of "circles" in the matrix, respectively.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>0 0 0 0 0 0 0 0 1 0<br>0 1 1 1 0 0 0 1 1 1<br>0 1 1 1 0 0 0 0 1 0<br>
        0 1 1 1 0 0 0 0 0 0<br>0 0 0 0 0 0 0 0 0 0<br>0 1 1 0 0 1 1 0 0 0<br>
        0 1 1 0 1 1 1 1 0 0<br>0 0 0 0 1 1 1 1 0 0<br>1 1 0 0 0 1 1 0 0 0<br>1 1 0 0 0 0 0 0 0 0</td>
        <td>3 2</td>
    </tr>
</table>

## Task 4. Pascal's triangle

Output N first rows of Pascal's triangle by the given number N of rows. Use standard input stream and standard output stream for data input and output, respectively. Check the correctness of the input data.

- Input: Integer, number of rows.
- Output: Integer numbers, Pascal's triangle.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>5</td>
        <td>1<br>1 1<br>1 2 1<br>1 3 3 1<br>1 4 6 4 1</td>
    </tr>
    <tr>
        <td>f</td>
        <td>Natural number was expected</td>
    </tr>

</table>

## Task 5. String to number conversion

Convert a string to a real number as if it were processed by the `float()` function . It, as well as any similar functions, should not be used in the implementation. Multiply the resulting real number by 2. Print the result with three digits after the dot. Use standard input stream and standard output stream for data input and output, respectively. Check the correctness of the input data.

- Input: A string
- Output: A real number if the input is correct. An error message if the input is incorrect.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>-14.97</td>
        <td>-29.940</td>
    </tr>
</table>

### Task 6. Movies

Join two lists of movies sorted by the `year` field so that the resulting list remains sorted. The input data is in json format. Output the joined list also in json format. Use the input.txt text file to enter data. Use the standard output stream to output data. Check the correctness of the input data.

- Input: Two sorted lists of movies in json format.
- Output: The joined sorted list in json format if the input is correct. An error message if the input is incorrect.

### Input

```json
{
  "list1": [
    {
      "title": "Titanic",
      "year": 1998
    },
    {
      "title": "Taxi 2",
      "year": 2000
    },
    {
      "title": "Avatar",
      "year": 2009
    }
  ],
  "list2": [
    {
      "title": "Terminator",
      "year": 1984
    },
    {
      "title": "Home Alone",
      "year": 1993
    },
    {
      "title": "Spider-Man",
      "year": 2002
    }
  ]
}
```
### Output

```json
{
  "list0": [
    {
      "title": "Terminator",
      "year": 1984
    },
    {
      "title": "Home Alone",
      "year": 1993
    },
    {
      "title": "Titanic",
      "year": 1998
    },
    {
      "title": "Taxi 2",
      "year": 2000
    },
    {
      "title": "Spider-Man",
      "year": 2002
    },
    {
      "title": "Avatar",
      "year": 2009
    }
  ]
}
```

## Task 7. A robot

The robot is able to move down or to the right one square of the field. The field is rectangular and filled with numbers - the number of coins in each square of the field. The robot collects coins from each square it walked on. It is initially located in the top left square, so it collects the coins located there anyway. The robot's task is to collect as many coins as possible on the way to the bottom right square of the field, so it always moves along the most successful route. Determine from the given field how many coins the robot will collect. Use standard input stream and standard output stream for data input and output, respectively. Do not check the correctness of the input data.

- Input: Two natural numbers, the number of rows N and the number of columns M of a field, respectively. N rows, each containing M non-negative numbers, the number of coins in each square of the field.
- Output: A non-negative number, the total number of coins the robot will collect.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>3 4<br>3 0 2 1<br>6 4 8 5<br>3 3 6 0</td>
        <td>27</td>
    </tr>
</table>

## Task 8. Different numbers

Count the number of different numbers entered. Use standard input stream and standard output stream for data input and output, respectively. Do not check the correctness of the input data.

- Input: Natural number, the number of numbers is N. N lines, each containing an integer.
- Output: A natural number, the number of different numbers entered.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>10<br>5<br>3<br>7<br>3<br>6<br>3<br>5<br>2<br>9<br>4</td>
        <td>7</td>
    </tr>
</table>

## Task 9. The derivative at a point

Calculate the derivative of a given polynomial at a given point. Print the result with three digits after the dot. Use standard input stream and standard output stream for data input and output, respectively. Do not check the correctness of the input data.

- Input: The natural and real numbers, the highest degree of the polynomial N and the point at which you want to find the derivative, respectively. N lines, the i-th line contains a real number, the coefficient at x in degree i (indexing from one).
- Output: The real number, the derivative of a polynomial at a point.

Polynomial: `5 * x**2 + 1.2 * x - 3` \
Derivative: `10 * x + 1.2` \
Derivative at a point`3.0`: `30 + 1.2 = 31.2`

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>2 3.0<br>5<br>1.2<br>-3</td>
        <td>31.200</td>
    </tr>
</table>

## Task 10. Machines

The machine has certain year of manufacture, cost and running time. You need to select two such machines that will take turns and spend a certain amount of time. At the same time, the cost of the machines should be minimal and the year of manufacture should be the same. Output the total cost of the selected machines. It is guaranteed that there is a single solution. Use standard input stream and standard output stream for data input and output, respectively. Check the correctness of the input data.

- Input: Two natural numbers separated by a space, the number of available machines N and the required total running time, respectively. N lines, each containing three natural numbers separated by a space, the year of manufacture, the cost and the running time of the machine, respectively.
- Output: A real number if the input is correct. An error message if the input is incorrect.

<table>
    <tr>
        <th>Input</th>
        <th>Output</th>
    </tr>
    <tr>
        <td>5 48<br>2023 100 14<br>2020 18 347<br>2023 10000000 34<br>2023 1000 34<br>2022 10 34</td>
        <td>1100</td>
    </tr>
</table>

💡 [Click here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to give us feedback on this project**. It's anonymous and will help our team make your learning process better.
