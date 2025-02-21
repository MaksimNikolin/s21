# Complex data structures

Python allows you to create complex data structures by inserting compound data structures into each other, obtaining, for example, lists of lists, lists of tuples, dictionaries of dictionaries, etc.

```python
# Matrix as a list of lists
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

# The json format as a dictionary of dictionaries
users = {
    'user1': {
        'name': 'Alice',
        'age': 25,
        'email': 'alice@example.com'
    },
    'user2': {
        'name': 'Bob',
        'age': 30,
        'email': 'bob@example.com'
    }
}
```

The `typing` module in Python provides tools to support annotation of data types.
It allows you to declare complex data types such as lists of certain objects, dictionaries with certain keys and values, tuples of different types, etc.
This helps improve the readability of the code and makes it easier to maintain.

Python also offers other complex data structures, such as, `collections` (namedtuple, defaultdict, Counter and others).
They provide different ways of storing and arranging data depending on your specific needs. It is important to choose data structures depending on the task, considering data access requirements, speed of operations and other characteristics.
Python provides a wide range of tools for working with data, making it a convenient and flexible programming language.
