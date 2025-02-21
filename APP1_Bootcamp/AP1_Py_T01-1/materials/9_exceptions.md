# Exception handling

Exception handling is a mechanism for handling errors and unusual situations in a program.
When an error occurs during code execution, Python creates an exception object and tries to find the appropriate exception handling block.

```python
try:
    x = int(input("Enter a number: "))
    result = 10 / x
except ValueError as e:
    print(f"Error: Not a number. {e}.")
except ZeroDivisionError:
    print("Error: Division by zero.")
else:
    print(f"Result: {result}")
finally:
    print("End of program.")
```

**Main elements**

- try: This block holds the code where an exception can occur.
- except: Here you specify the type of exception you want to catch. If an exception of this type occurs, control is passed to the appropriate except block.
- as e: The variable e is used to store information about the exception, which provides additional information about the error that occurred.
- else: This block is executed if no exceptions occurred in the try block.
- finally: The code in this block is always executed, regardless of whether an exception has occurred or not. This is where code is usually placed for finalizing actions such as closing files or network connections.
