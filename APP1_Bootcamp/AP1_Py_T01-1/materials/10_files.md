# Working with files

Files are the main way data is stored and transferred between programs and users.
Working with files means interacting with the file system to read data from files,
write data to files or perform other operations on files.
Python has a number of built-in functions and methods that make working with files easier.

## Main operations

### Open

You must open the file to start working with it. The `open()` function is used for that.
The function returns a file object that is used to perform read or write operations.
The second argument in the `open()` function specifies the mode of opening the file. For example, "r" means read, "w" means write, "a" means add, "b" means binary mode, and so on.

```python
file = open("example.txt", "r")  # Opening a file for reading
```

### Read

Various methods are used to read data from a file, such as `read()`, `readline()`, `readlines()` and others.

```python
content = file.read()  # Read the entire contents of a file
line = file.readline()  # Read one line from a file
lines = file.readlines()  # Read all lines of a file into a list
```

### Write

The following methods are used to write data to a file: `write()`, `writelines()` and others.

```python
file = open("example.txt", "w")  # Opening a file for writing 
file.write("Hello, World!")  # Writing a line to a file
```

### Close

Once you have finished working with the file, you should close it to free up resources.

```python
file.close()
```

It is recommended to use the context manager `with`, which automatically closes the file after the code block is finished.

```python
# The file will automatically close after exiting the 'with' block
with open("example.txt", "r") as file:
    content = file.read()
```

### Working with binary files

If you need to work with binary data, you can use the "b" mode in the `open()` function.

```python
with open("image.jpg", "rb") as binary_file:
    data = binary_file.read()
```
