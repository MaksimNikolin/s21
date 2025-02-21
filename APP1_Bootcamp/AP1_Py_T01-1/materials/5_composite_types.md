# Composite data types

In Python, composite data types provide the ability to store and manage large amounts of information. You can group related data into one variable and make the code more organized and easy to work with.

## A list

One of the most popular composite data types in Python is the `list`.

The list is an ordered collection of items that can contain objects of different data types.

You can add, delete, and modify list items, as well as perform various operations such as sorting and searching.

### List creation

You can create lists using square brackets or the function `list()`.

```python
my_list = [1, 2, 3]
another_list = list((4, 5, 6))  # any iterated object can be passed to the list() function: list, tuple, map, str, etc.
```

### Indexing and slicing

List items can be retrieved by index or by performing slices. Indexing starts at 0.

```python
my_list = [1, 2, 3, 4, 5]
print(my_list[0])  # Output: 1
print(my_list[1:3])  # Output: (2, 3)
```

### The length of a list

You can find out the length of a list using the `len()` function.

```python
my_tuple = (1, 2, 3)
print(len(my_tuple))  # Output: 3
```

### Concatenation and repetition

Lists can be joined using the `+` operator and repeated using the `*` operator.

```python
list1 = [1, 2, 3]
list2 = [4, 5, 6]
concatenated_list = list1 + list2  # Output: [1, 2, 3, 4, 5, 6]
repeated_list = list1 * 3  # Output: [1, 2, 3, 1, 2, 3, 1, 2, 3]
```

### Basic methods for working with lists

#### append()

Adds an item to the end of a list.

```python
my_list = [1, 2, 3]
my_list.append(4)
# Result: [1, 2, 3, 4]
```

#### extend()

Expands a list by adding items of another list to the end.

```python
my_list = [1, 2, 3]
another_list = [4, 5, 6]
my_list.extend(another_list)
# Result: [1, 2, 3, 4, 5, 6]
```

#### insert()

Insert an item at the specified position in a list.

```python
my_list = [1, 2, 3]
my_list.insert(1, 5)  # Insert 5 to position 1
# Result: [1, 5, 2, 3]
```

#### remove()

Removes the first occurrence of an item from the list.

```python
my_list = [1, 2, 3, 2]
my_list.remove(2)
# Result: [1, 3, 2]
```

#### pop()

Deletes an item by index and returns its value. If no index is specified, the last item is deleted.

```python
my_list = [1, 2, 3]
value = my_list.pop(1)  # Delete the item with 1 (2) index and store its value in the value variable.
# Result my_list: [1, 3]
# Result value: 2
```

#### index()

Returns the index of the first occurrence of the specified item in the list.

```python
my_list = [1, 2, 3, 2]
index = my_list.index(2)
# Result: index = 1
```

#### count()

Returns the number of occurrences of the specified item in the list.

```python
my_list = [1, 2, 3, 2]
count = my_list.count(2)
# Result: count = 2
```

#### sort()

Sorts the list in ascending order (or by specific criteria, if specified).

```python
my_list = [3, 1, 4, 2]
my_list.sort()
# Result: [1, 2, 3, 4]
```

## Tuples

Another composite data type(`tuple`).

A tuple is similar to a list, but it is unchangeable, meaning that its items cannot be changed after creation. 
Tuples are often used to represent unchangeable data sets, such as point coordinates or date and time.

### Tuples creation

You can create tuples using round brackets or the function `tuple()`.

```python
my_tuple = (1, 2, 3)
another_tuple = tuple([4, 5, 6])
```

### Indexing and slicing

As in lists, tuple items can be retrieved by index or by performing slicing. Indexing starts at 0.

```python
my_tuple = (1, 2, 3, 4, 5)
print(my_tuple[0])  # Output: 1
print(my_tuple[1:3])  # Output: (2, 3)
```

### Tuple length

You can find out the length of a tuple using the `len()` function.

```python
my_tuple = (1, 2, 3)
print(len(my_tuple))  # Output: 3
```

### Concatenation and repetition

Tuples can be joined using the `+` operator and repeated using the `*` operator.

```python
tuple1 = (1, 2, 3)
tuple2 = (4, 5, 6)
concatenated_tuple = tuple1 + tuple2  # Output: (1, 2, 3, 4, 5, 6)
repeated_tuple = tuple1 * 3  # Output: (1, 2, 3, 1, 2, 3, 1, 2, 3)
```

Tuples have all the methods of lists that don't modify them. For example, `count()`, `find()`, `index()` and others.

## Dictionaries

A `dictionary` is another powerful composite data type in Python.

It is a collection of key-value pairs. Dictionaries allow you to quickly find values by key and manipulate data in a more structured format.


### Dictionary creation

You can create dictionaries using curly brackets or the function `dict()`. An empty dictionary can only be created using the second method, since empty curly brackets create an empty set.

```python
my_dict = {"apple": 2, "banana": 4, "orange": 6}
```

### Adding an item

```python
my_dict["grape"] = 3
```

### Retrieving value by key

```python
print(my_dict["apple"])  # Output: 2
```

### Checking for a key in the dictionary

```python
print("pear" in my_dict)  # Output: False
```

### Deleting an item by key

```python
del my_dict["banana"]
```

### Retrieving all keys or dictionary values

```python
keys = my_dict.keys()
values = my_dict.values()
```

### Retrieving all key-value pairs of the dictionary

```python
items = my_dict.items()
```

### Updating a dictionary with another dictionary

```python
new_dict = {"kiwi": 5, "grapefruit": 8}
my_dict.update(new_dict)
```

### Enumeration of dictionary elements

```python
for key, value in my_dict.items():
    print(key, value)
```

### Clearing the dictionary

```python
my_dict.clear()
```

## Sets

There are sets in Python, which are unordered collections of unique items.

Sets are useful for removing duplicates and performing operations on sets, such as union, intersection, and difference.

### Sets creation

You can create sets using curly brackets or the function `set()`.

```python
my_set = {1, 2, 3, 4, 5}  # creating a set using curly brackets 
```

### Adding an item in a set

```python
my_set.add(6)  # adding item 6 to the set
```

### Removing an item from a set

```python
my_set.remove(3)  # removing item 3 from the set
```

### Checking the availability of an item in a set

```python
if 4 in my_set:
    print("Item 4 is in the set")
```

### Union of two sets

```python
my_set2 = {5, 6, 7, 8, 9}
union_set = my_set.union(my_set2)  # set union

```

### Intersection of two sets

```python
intersection_set = my_set.intersection(my_set2)  # set intersection
```

### Difference of two sets

```python
difference_set = my_set.difference(my_set2)  # set difference
```

### Subset check

```python
if my_set.issubset(my_set2):
    print("The set my_set is a subset of my_set2")
```

### Disjoint sets check

```python
if my_set.isdisjoint(my_set2):
    print("The sets my_set and my_set2 have no items in common")
```
