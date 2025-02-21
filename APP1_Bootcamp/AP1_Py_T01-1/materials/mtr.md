# Topics

1. Program entry point, program structure
2. Program compilation/interpretation
3. Language control structures ( sequential, branching, repetition)
4. Simple data types
5. Composite data types
6. Input/Output (stdin-stdout)
7. Memory management, garbage collector
8. Complex data structures
9. Exception handling
10. Working with files
11. Functions

# Methodological guidelines for tasks
## Scalar product

The scalar product is a mathematical operation applied to two vectors in three-dimensional space (or more generally n-dimensional space) and returns a scalar quantity.

For two vectors `a = [a1, a2, ..., an]` and `b = [b1, b2, ..., bn]`,
scalar product is calculated as follows:
`a * b = a1 * b1 + a2 * b2 + ... + an * bn`.
This number is the sum of the products of the corresponding components of the vectors.

## Palindrome

A palindrome is a number that reads from left to right and right to left equally.
Thus, in order to determine whether a number is a palindrome or not, it is necessary to make sure that the digits at the beginning and at the end of the number, which are at the same distance from the middle, coincide. Preliminarily, it is necessary to get the digits of the number. You could cast the number to a string and use indices to get the digits, but it is more efficient to generate a list of digits using integer division operations in the loop.

## Figures

To find figures in a matrix, we suggest writing an algorithm that, in the process of traversing the matrix by rows or columns, for any unit encountered on the path, will start a recursive traversal of all units adjacent to it. In doing so, of course, the encountered units must be replaced by zeros in order to count each one only once. There are various ways to determine whether a figure is a circle or a square.
One option is to count the number of units during the traversal, and save the index of the leftmost, rightmost, bottom and top units encountered, so that you can compare the expected area of the square (maximum width of the area * maximum height of the area) with the number of units found.


## Pascal's triangle

Pascal's triangle is a number triangle in which each number is equal to the sum of the two numbers above it. The top row of the triangle contains the number 1, and each successive number in the triangle is calculated as the sum of the two numbers above it in the previous row.

```
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
```

## String to number conversion

In order to convert a string into a real number, we suggest writing an algorithm that will process the input string character by character and gather all the necessary information about the number. Then use it to get the number itself. Alternatively, you can store in a boolean variable whether the number is positive, and in a list - the digits of the final number. Record the number of digits after the dot in a separate variable, and then reconstruct the number by multiplying each digit by 10 to the desired degree, then divide by 10 according to the number of digits after the dot and multiply by -1 if a negative number was entered.

## Movies

It is convenient to work with the json format using the `json` module, which has the `loads()` function to get information from the json string as a `dict` dictionary, and the antonymous `dumps()` function to convert the `dict` dictionary into a json string. If a string that does not match the json format is passed to the `loads()` function, a `JSONDecodeError` exception will be generated. You should foresee this situation by catching a possible exception. It is also possible to catch an error in the input data related to the absence of necessary fields in the dictionary. This can be done using the `get()` method, passing a default value to it, or catching a possible `KeyError` exception. The algorithm to join two sorted lists into a single sorted list must go through the data once. In other words, if you concatenate two lists and then sort them, the correct list will be obtained, but this algorithm is not the most efficient, so it is not recommended for use.

## A robot

The robot can go either down or to the right from each square of the field, so the number of possible trajectories from start to finish is very large. Hence, an algorithm that tries all possible robot trajectories to find the most successful one will be extremely slow, so it is not recommended for use. Instead, we suggest a different algorithm based on the ideas of dynamic programming. The dynamic programming method is used to optimize problems that can be broken down into smaller subtasks. At the same time, the solutions of small subtasks can be saved and used to solve the larger task. In this case, since the robot can enter any square only from the top or from the left, it is logical to choose the most advantageous of these two options. This will be the small subtask, which is solved by simply choosing between the two options. And then, starting from the top left square, you can be sure for each square following it on the right and below that the robot has already been able to get into it in the most convenient way. That is, we solve the same minor subtask for each subsequent square. So, reaching the bottom right corner of the field, we will get the largest number of coins, which could be collected in the best case. This means that a larger task is solved. In this case, you will not have to go through all the routes of the robot.

## Different numbers

To count the amount of different numbers entered, you will have to save them to determine each time whether such a number has been encountered yet. Using a list to save encountered numbers is not the most efficient way, because for each new number you have to check if it is already in the list, and this operation involves going through all the items in the list. But you can use a set. The operation of checking whether a number belongs to a set is much faster than the same operation for a list. An alternative option is to use a dictionary. In this case, the operation under discussion is also fast, but it requires a bit more memory.

## The derivative at a point

The derivative of a polynomial is calculated as the sum of the derivatives of each of its terms. For example, the derivative of `x` of the polynomial `5 * x**2 + 1.2 * x - 3` will be the sum of the derivatives of `5 * x**2`, `1.2 * x` and `-3`. The derivative of each summand of the `a * x**n` can be found by the formula `a * n * x**(n - 1)`. The derivative of the constant is zero. So for the given polynomial we get the derivative `10 * x + 1.2`. And you can calculate the derivative of the polynomial at a point by substituting the given value of `x` into the obtained expression. The derivative at the point `3.0` would then be `10 * 3 + 1.2 = 31.2`. The algorithm for calculating the derivative can immediately find and accumulate the total sum of the derivative summands while reading the data.

## Machines

It is convenient to use `dict` dictionaries to divide machines by year of manufacture (store separately machines of different years, since the two machines needed must necessarily be of the same year of manufacture). Moreover, it is also convenient to store information about machines in the dictionary. If the key is the machine's operating time, you can check if there is another machine in the dictionary that has the required time in combination with the data. And since we need to minimize the cost, we can leave the minimum cost of the machine for each time of operation in such a dictionary, then the sum will be minimal in the end. Thus, for each year in the dictionary we will get a different answer and it remains to choose the minimum one.
