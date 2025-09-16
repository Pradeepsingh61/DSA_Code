# Python Data Structures 🐍🏗️

This directory contains implementations of fundamental data structures in Python, showcasing both built-in Python capabilities and custom implementations.

## 📂 Directory Structure

```
data_structures/
├── linked_lists/    # Linked list implementations and operations
├── matrices/        # Matrix operations and algorithms
├── stacks/         # Stack implementations and applications
└── trees/          # Tree structures and algorithms
```

## 🔗 Linked Lists

Located in `linked_lists/`

### Current Implementations
- **Reverse Linked List** (`reverse_a_linked_list.py`) - Reverse a singly linked list

### Common Operations to Implement
- [ ] Singly Linked List basic operations
- [ ] Doubly Linked List implementation
- [ ] Circular Linked List
- [ ] Merge two sorted linked lists
- [ ] Find middle element
- [ ] Detect cycle in linked list
- [ ] Remove duplicates

## 📚 Stacks

Located in `stacks/`

### Current Implementations
- **Delete Middle Element** (`delete_middle_element_of_stack.py`) - Remove middle element from stack
- **Stack using Queues** (`implement_stack_using_queues.py`) - Implement stack using queue operations

### Stack Applications
- Expression evaluation
- Parentheses matching
- Undo operations
- Function call management
- Browser history

### Python Stack Examples
```python
# Using list as stack (built-in)
stack = []
stack.append(1)    # push
stack.append(2)    # push
top = stack.pop()  # pop

# Using collections.deque (more efficient)
from collections import deque
stack = deque()
stack.append(1)    # push
top = stack.pop()  # pop
```

## 🌳 Trees

Located in `trees/`

### Current Implementations
- **Maximum Depth of Binary Tree** (`find_maximum_depth_of_binary_tree.py`) - Find height of binary tree

### Tree Types to Implement
- [ ] Binary Tree basic operations
- [ ] Binary Search Tree (BST)
- [ ] AVL Tree (self-balancing)
- [ ] Red-Black Tree
- [ ] Heap (Min/Max)
- [ ] Trie (Prefix Tree)
- [ ] Segment Tree
- [ ] Fenwick Tree (Binary Indexed Tree)

### Common Tree Operations
```python
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Tree traversals
def inorder(root):
    if root:
        inorder(root.left)
        print(root.val)
        inorder(root.right)

def preorder(root):
    if root:
        print(root.val)
        preorder(root.left)
        preorder(root.right)

def postorder(root):
    if root:
        postorder(root.left)
        postorder(root.right)
        print(root.val)
```

## 🔢 Matrices

Located in `matrices/`

### Operations to Implement
- [ ] Matrix multiplication
- [ ] Matrix transpose
- [ ] Determinant calculation
- [ ] Matrix rotation
- [ ] Spiral traversal
- [ ] Search in sorted matrix
- [ ] Sparse matrix operations

### Python Matrix Examples
```python
# Using lists
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

# Using NumPy (if available)
import numpy as np
matrix = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
```

## 🎯 Implementation Guidelines

### Custom Data Structure Template
```python
class DataStructureName:
    def __init__(self):
        """Initialize the data structure."""
        pass

    def insert(self, value):
        """Insert a value into the data structure."""
        pass

    def delete(self, value):
        """Delete a value from the data structure."""
        pass

    def search(self, value):
        """Search for a value in the data structure."""
        pass

    def display(self):
        """Display the contents of the data structure."""
        pass

    def is_empty(self):
        """Check if the data structure is empty."""
        pass

    def size(self):
        """Return the size of the data structure."""
        pass
```

## 🚀 Python-Specific Features

### Built-in Data Structures
```python
# List (dynamic array)
my_list = [1, 2, 3, 4, 5]

# Tuple (immutable sequence)
my_tuple = (1, 2, 3, 4, 5)

# Set (unique elements)
my_set = {1, 2, 3, 4, 5}

# Dictionary (key-value pairs)
my_dict = {'a': 1, 'b': 2, 'c': 3}

# Deque (double-ended queue)
from collections import deque
my_deque = deque([1, 2, 3, 4, 5])
```

### Collections Module
```python
from collections import (
    defaultdict,  # Dictionary with default values
    Counter,      # Count occurrences
    OrderedDict,  # Ordered dictionary
    namedtuple,   # Named tuple
    deque         # Double-ended queue
)

# Example usage
counter = Counter(['a', 'b', 'a', 'c', 'b', 'a'])
# Counter({'a': 3, 'b': 2, 'c': 1})

default_dict = defaultdict(list)
default_dict['key'].append('value')  # No KeyError
```

## 🔥 Priority Data Structures to Implement

### High Priority
1. **Binary Search Tree** - Foundation for many tree operations
2. **Hash Table** - Custom hash table with collision handling
3. **Queue using Stacks** - Complement to existing stack using queues
4. **Min/Max Heap** - Priority queue implementation
5. **Doubly Linked List** - More flexible linked list

### Medium Priority
1. **Trie** - For string operations and autocomplete
2. **Graph** - Adjacency list and matrix representations
3. **Circular Queue** - Space-efficient queue
4. **Stack with Min** - Stack that tracks minimum element
5. **LRU Cache** - Least Recently Used cache

### Advanced
1. **Red-Black Tree** - Self-balancing BST
2. **B-Tree** - For database systems
3. **Segment Tree** - Range query data structure
4. **Union-Find** - Disjoint set data structure

## 🎓 Learning Resources

### Complexity Analysis
- **Time Complexity**: How execution time grows with input size
- **Space Complexity**: How memory usage grows with input size

### Common Complexities
- **O(1)**: Constant - Array access, hash table operations
- **O(log n)**: Logarithmic - Binary search, balanced tree operations
- **O(n)**: Linear - Linear search, tree traversal
- **O(n log n)**: Linearithmic - Efficient sorting algorithms
- **O(n²)**: Quadratic - Nested loops, simple sorting algorithms

## 🏆 Best Practices

### Code Quality
1. **Clear naming**: Use descriptive variable and method names
2. **Documentation**: Include docstrings and comments
3. **Error handling**: Handle edge cases and invalid inputs
4. **Testing**: Include comprehensive test cases

### Python Idioms
```python
# Use list comprehensions
squares = [x**2 for x in range(10)]

# Use enumerate for index and value
for i, value in enumerate(my_list):
    print(f"Index {i}: {value}")

# Use zip for parallel iteration
for name, age in zip(names, ages):
    print(f"{name} is {age} years old")

# Use generators for memory efficiency
def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b
```

Happy Data Structure Implementation! 🐍🏗️🚀