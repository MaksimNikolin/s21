# Simple data types

The Python language has a few simple data types: numbers, strings, and Boolean values.

## Numbers

In Python, you can work with integers (`int`) and floating point numbers (`float`). 
Numbers are used to perform mathematical operations and store quantitative information.

```python
a = 15  # integer
b = 4.2  # floating point number
```

## Strings

Strings (`str`) are a sequence of numbers characters enclosed in quotes. They are used to store textual information and can be changeable or non-changeable.

```python
# Single quotes
my_string = 'Hello, world!'

# Double quotes
another_string = "It's a different string."

# Triple quotes (for multiline strings)
multiline_string = ''It's
a multiline
string.'''
```

Strings can be concatenated - `my_string + another_string`, and you can access the characters of a string
by indices - `my_string[0]` (you can use slices - `my_string[1:4]`).

**String formatting**

String formatting allows you to insert variable values at specific places in a string or create strings with a specific format, making code more readable and flexible.

- Format() method

```python
name = 'Alice'
age = 30
sentence = 'My name is {}, and I am {} years old.'.format(name, age)
print(sentence)  Output: My name is Alice, and I am 30 years old.
```

- f-strings (available from Python version 3.6 and higher)

```python
name = 'Bob'
age = 25
sentence = f'My name is {name}, and I am {age} years old.'
print(sentence)  # Output: My name is Bob, and I am 25 years old.
```

**Basic methods for working with strings**

- len(): Returns the length of the string, i.e. the number of characters in the string.

```python
my_string = "Example string"
length = len(my_string)
print(length)  # Output: 14
```

- lower() and upper(): Convert all characters in a string to lower or upper case.

```python
my_string = "Example String"
lower_case = my_string.lower()
upper_case = my_string.upper()
print(lower_case)  # Output: "example string"
print(upper_case)  # Output: "EXAMPLE STRING"
```

- strip(): emoves whitespace characters at the beginning and end of a string.

```python
my_string = "   Spaces at the beginning and end   "
stripped_string = my_string.strip()
print(stripped_string)  # Output: "Spaces at the beginning and end"
```

- replace(): Replaces a substring with another substring.

```python
my_string = "Character replacement"
new_string = my_string.replace("а", "о")
print(new_string)  # Output: "Chorocter replocement"
```

- find() and index(): Search for a substring in the string and return the index of the first occurrence. find() returns -1 if no substring is found, and index() raises an exception.

```python
my_string = "Substring search"
index1 = my_string.find("substring")
index2 = my_string.index("substring")
print(index1)  # Output: 6
print(index2)  # Output: 6
```

- split(): Splits a string into substrings by the specified delimiter and returns a list.

```python
my_string = "Splitting a string into words"
words = my_string.split()
print(words)  # Output: ['Splitting', 'a', 'string', 'into', 'words']
```

- join(): Combines elements of a string list into a single string using the specified delimiter.

```python
words = ['Splitting', 'a', 'string', 'into', 'words']
my_string = ' '.join(words)
print(my_string)  # Output: "Splitting a string into words"
```

## Boolean values

Boolean values (`bool`) are logical values `True` and `False`. They are used to perform logical operations and make decisions in the program.

### Basic Boolean operations

- Conjunction (AND)

Returns `True` if both operands are True`. Otherwise, returns `False`.

```python
x = True
y = False

result = x and y
print(result)  # Output: False
```

- Disjunction (OR)

Returns True if at least one of the operands is True. If both operands are False, returns False.


```python
x = True
y = False

result = x or y
print(result)  # Output: True
```

- Negation (NOT)

Inverts the boolean value of the operand. If an operand is True, then not will make it False, and vice versa.

```python
x = True

result = not x
print(result)  # Output: False
```

These operations can be combined to create more complex logical expressions.

```python
a = True
b = False
c = True

result = (a and b) or (not c)
print(result)  # Output: False
```

Boolean values are also often used in conditional statements (e.g., `if`, `else`, `elif`) to make decisions depending on the fulfillment of certain conditions.

```python
x = 10

if x > 5 and x < 15:   # in this case, you could have written 5 < x < 15 (chained expression)
    print("x ranges from 6 to 14.")
else:
    print("x is not ranged from 6 to 14.")
```
