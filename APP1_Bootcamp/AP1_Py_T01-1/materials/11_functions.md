# Functions

A function is a block of code that has a name, accepts arguments (input data), performs a specific task, and possibly returns a result.
Functions allow you to organize your code, make it more readable, and avoid duplication.

```python
def greeting(name):
    """A function that greets by name."""
    print(f"Hello, {name}!")


# Using the function
greeting("Anna")
```

Recursion is a concept where a function calls itself. Recursion is usually used to solve problems which can be broken down into smaller subtasks. For example, we can recursively calculate the factorial of some number n. The factorial of a number n is the product of all integers from 1 to n.

```python
def factorial(n):
    """Recursive function for calculating the factorial of a number."""
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)


# Using the function
result = factorial(5)
print(result)
```

When we use recursion, it is important to provide a base case (in this example, when n is 0 or 1), to avoid infinite function calls.

It's also important to keep in mind that the depth of recursion in Python is limited. This limit can be changed using the `setrecursionlimit()` function from the `sys` standard library, but this is only done in extreme cases, as it is completely unsafe, and use iterative algorithms whenever possible.
