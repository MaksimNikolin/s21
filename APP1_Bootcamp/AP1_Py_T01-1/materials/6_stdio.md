# Input/Output (stdin-stdout)

Standard I/O streams are usually denoted as stdin (standard input) and stdout (standard output). 
These streams are abstractions through which the program interacts with the outside world, reading data from the console (or other sources) and writing execution results to the console (or other places).

## Stdin

Stdin is the stream where the program receives input from the user or from another source. 
In Python, data from stdin can be read using the `input()` function. 
It waits for input from the user and returns it as a string.

```python 
name = input("Enter your name: ") 
```

## Stdout

Stdout is the stream where the program sends the results of its work. In Python, the `print()` function outputs data.
It takes one or more arguments and outputs them, adding a sep (default space) delimiter after each argument, and an end (default line break) at the end.

```python 
print("This message will be output to the stdout.") 
```

```python
# An example program that reads a number from stdin, multiplies it by 2 and outputs the result to stdout
input_number = input("Enter a number: ")
try:
    input_number = float(input_number)
    result = input_number * 2
    print("Result of multiplication by 2:", result)
except ValueError:
    print("Error: Enter the valid number.")
```