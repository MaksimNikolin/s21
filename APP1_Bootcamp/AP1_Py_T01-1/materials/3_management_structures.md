# Control structures (sequential, branching, repetition)

Control structures (sequential, branching, repetition) are the basic building blocks for creating programs.
Using them allows developers to efficiently manage the flow of program execution and create complex and functional applications.

## Sequence

This is a basic control structure in which instructions are executed sequentially, one after the other, from top to bottom.

```python
# An example of a sequence
print("Step 1")
print("Step 2")
print("Step 3")
```

## Branching (conditional statements)

This structure allows certain instructions to be executed only under certain conditions.
Python uses the `if` statement , as well as `elif` (else if) and `else`.

```python
# An example of branching
x = 10

if x > 0:
    print("x positive")
elif x == 0:
    print("x equal 0")
else:
    print("x negative")
```

With Python 3.10, a new structure was introduced to control the flow of program execution - `match case`.
It is designed for more convenient and readable condition handling when you want to compare the value of a variable with several possible values at once.

```python
def check_number(x):
    match x:
        case 0:
            print("This is zero")
        case 1 | 2:
            print("This is one or two")
        case 3 | 4 | 5:
            print("This is three, four, five")
        case _:
            print("Other value")


check_number(3)
```

In the above example, `match case` checks the value of the variable `x` against various conditions.
The `|` is used to combine multiple values into a single `case`.
The `_` is a wildcard (заполнителем) and corresponds to any value.
This structure makes the code clearer and avoids bulky if-elif-else chains.
`match case` improves code readability and maintainability.

## Repetition (loops)

These structures allow the same block of code to be executed multiple times.
There are two basic types of loops in Python: `for` and `while`.

### For

The for loop is used to iterate through a sequence (such as a list, tuple, string, or range of numbers)
and execute specific instructions for each element in the sequence.

```python
# Iteartion through a list
fruits = ["apple", "banana", "pear"]
for fruit in fruits:
    print(fruit)

# Iteration through a range of numbers
for i in range(5):
    print(i)
```

### While

The while loop is executed as long as the condition is true. It is appropriate when the number of iterations is not known in advance.

```python
count = 0
while count < 5:
    print(count)
    count += 1
```
