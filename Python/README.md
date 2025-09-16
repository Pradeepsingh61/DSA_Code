# Python Implementations 🐍

Welcome to the **Python section** of our DSA repository! This directory contains clean, readable, and efficient implementations of algorithms and data structures in Python.

## 📂 Directory Structure

```
Python/
├── algorithms/                 # Algorithm Implementations
│   ├── graph_algorithms/      # Graph-based algorithms
│   ├── mathematical/          # Mathematical algorithms
│   ├── searching/             # Search algorithms
│   ├── sorting/               # Sorting algorithms
│   └── string_algorithms/     # String processing algorithms
├── data_structures/           # Data Structure Implementations
│   ├── linked_lists/         # Linked list variations
│   ├── stacks/               # Stack implementations
│   ├── graphs/               # Graph representations
│   └── trees/                # Tree structures
├── dynamic_programming/       # DP Solutions
├── game_algorithms/          # Game-related algorithms
│   ├── minimax/             # Minimax algorithm implementations
│   └── alpha_beta_pruning/  # Alpha-beta pruning
├── machine_learning/         # ML algorithms (basic implementations)
└── projects/                # Complete Python projects
    └── games/               # Game projects
```

## 🚀 Quick Start

### Python Development Setup

1. **Python Version**: Python 3.7+ recommended
2. **Virtual Environment**:
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows: venv\Scripts\activate
   ```
3. **Dependencies**: Most implementations use only standard library

### Adding New Algorithms

```python
"""
Algorithm: [Algorithm Name]
Description: [Brief description of what the algorithm does]
Time Complexity: [Big O notation]
Space Complexity: [Big O notation]
Author: [Your Name]
"""

def algorithm_name(input_data):
    """
    Brief description of the function.

    Args:
        input_data: Description of input parameter

    Returns:
        Description of return value

    Raises:
        ValueError: When input is invalid
    """
    # Implementation here
    pass


def main():
    """Test the algorithm with example cases."""
    # Test Case 1
    test_data = [1, 2, 3, 4, 5]
    result = algorithm_name(test_data)
    print(f"Result: {result}")

    # Test Case 2 - Edge case
    edge_case = []
    try:
        result = algorithm_name(edge_case)
        print(f"Edge case result: {result}")
    except ValueError as e:
        print(f"Handled edge case: {e}")


if __name__ == "__main__":
    main()
```

## 📊 Current Implementations

### Algorithms
- **Searching**: Binary Search, Linear Search, Jump Search, Interpolation Search, Exponential Search
- **Sorting**: Bubble Sort, Selection Sort, Insertion Sort, Counting Sort
- **Graph Algorithms**: Dijkstra's Algorithm
- **Mathematical**: Various mathematical computations
- **String Algorithms**: Pattern matching, string manipulation

### Data Structures
- **Linear**: Linked Lists, Stacks, implementation examples
- **Advanced**: Custom implementations of complex structures

### Game Algorithms
- **Minimax**: Decision-making for games
- **Alpha-Beta Pruning**: Game tree optimization
- **Game Projects**: Tic-tac-toe, memory games

### Projects
- **Games**: Interactive games and puzzles
- **Utilities**: Calculators, password generators
- **Algorithms**: Practical applications

## 🐍 Python-Specific Features

### Pythonic Code Style
```python
# List comprehensions
squares = [x**2 for x in range(10)]

# Generator expressions for memory efficiency
large_data = (x for x in range(1000000) if x % 2 == 0)

# Dictionary comprehensions
word_lengths = {word: len(word) for word in ['python', 'java', 'cpp']}

# Tuple unpacking
def get_min_max(arr):
    return min(arr), max(arr)

minimum, maximum = get_min_max([1, 5, 3, 9, 2])
```

### Built-in Data Structures
```python
# Lists - dynamic arrays
numbers = [1, 2, 3, 4, 5]

# Sets - for unique elements
unique_items = {1, 2, 3, 4, 5}

# Dictionaries - hash maps
student_grades = {'Alice': 95, 'Bob': 87, 'Charlie': 92}

# Tuples - immutable sequences
coordinates = (10, 20)

# Deque - double-ended queue
from collections import deque
queue = deque([1, 2, 3])
```

### Advanced Python Features
```python
# Decorators for timing algorithms
import time
from functools import wraps

def timer(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(f"{func.__name__} took {end - start:.4f} seconds")
        return result
    return wrapper

@timer
def bubble_sort(arr):
    # Implementation
    pass

# Context managers for resource handling
class AlgorithmProfiler:
    def __enter__(self):
        self.start_time = time.time()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print(f"Algorithm completed in {time.time() - self.start_time:.4f}s")

# Usage
with AlgorithmProfiler():
    result = some_algorithm(data)
```

## 🔥 Popular Algorithms to Implement

### High Priority
- [ ] Quick Sort with different pivot strategies
- [ ] Merge Sort (bottom-up and top-down)
- [ ] Heap Sort using heapq module
- [ ] A* Search Algorithm
- [ ] Breadth-First Search (BFS)
- [ ] Depth-First Search (DFS)

### Medium Priority
- [ ] Dynamic Programming classics:
  - [ ] Longest Common Subsequence
  - [ ] Coin Change Problem
  - [ ] 0/1 Knapsack (already partially implemented)
  - [ ] Edit Distance
- [ ] Graph Algorithms:
  - [ ] Kruskal's MST
  - [ ] Prim's MST
  - [ ] Topological Sort

### Python-Specific Implementations
- [ ] Generators for memory-efficient algorithms
- [ ] Asyncio-based concurrent algorithms
- [ ] NumPy-accelerated numerical algorithms
- [ ] Pandas-based data processing algorithms

## 💡 Best Practices

### Code Style (PEP 8)
```python
# Function names: snake_case
def binary_search(arr, target):
    pass

# Class names: PascalCase
class BinarySearchTree:
    pass

# Constants: UPPER_SNAKE_CASE
MAX_HEAP_SIZE = 1000

# Variable names: snake_case
student_count = 50
```

### Error Handling
```python
def safe_division(a, b):
    """Safely divide two numbers."""
    try:
        if b == 0:
            raise ValueError("Division by zero is not allowed")
        return a / b
    except TypeError:
        raise TypeError("Both arguments must be numbers")
    except Exception as e:
        print(f"Unexpected error: {e}")
        raise
```

### Documentation
```python
def dijkstra_algorithm(graph, start_node):
    """
    Implement Dijkstra's shortest path algorithm.

    Args:
        graph (dict): Adjacency list representation of the graph
                     {node: [(neighbor, weight), ...], ...}
        start_node: Starting node for the algorithm

    Returns:
        dict: Shortest distances from start_node to all other nodes
              {node: distance, ...}

    Raises:
        ValueError: If start_node is not in the graph
        TypeError: If graph is not properly formatted

    Example:
        >>> graph = {'A': [('B', 1), ('C', 4)], 'B': [('C', 2)], 'C': []}
        >>> dijkstra_algorithm(graph, 'A')
        {'A': 0, 'B': 1, 'C': 3}
    """
    pass
```

### Testing
```python
import unittest

class TestSortingAlgorithms(unittest.TestCase):
    def setUp(self):
        self.test_arrays = [
            [64, 34, 25, 12, 22, 11, 90],
            [1],
            [],
            [5, 5, 5, 5],
            list(range(100, 0, -1))  # Reverse sorted
        ]

    def test_bubble_sort(self):
        for arr in self.test_arrays:
            with self.subTest(arr=arr):
                sorted_arr = bubble_sort(arr.copy())
                self.assertEqual(sorted_arr, sorted(arr))

if __name__ == '__main__':
    unittest.main()
```

## 🌟 Featured Python Implementations

### Clean Algorithm Examples
- **Recursive Solutions**: Clean and readable recursive implementations
- **Generator-Based**: Memory-efficient algorithms using generators
- **Object-Oriented**: Proper class hierarchies for data structures

### Python Libraries Integration
```python
# Using collections module
from collections import defaultdict, Counter, deque

# Using heapq for priority queues
import heapq

# Using itertools for combinatorial algorithms
import itertools

# Using functools for optimization
from functools import lru_cache, reduce
```

## 🎯 Contribution Guidelines

### Code Quality Checklist
- [ ] Follows PEP 8 style guidelines
- [ ] Includes comprehensive docstrings
- [ ] Has proper error handling
- [ ] Includes test cases in `main()` function
- [ ] Uses type hints where appropriate
- [ ] Is memory and time efficient

### Python-Specific Guidelines
1. **Use built-ins**: Leverage Python's rich standard library
2. **List comprehensions**: Prefer them over explicit loops when readable
3. **Generators**: Use for large datasets to save memory
4. **Context managers**: For resource management
5. **Exception handling**: Be specific about exception types

### Performance Considerations
```python
# Use appropriate data structures
# Good: O(1) lookup
valid_items = {'apple', 'banana', 'orange'}
if item in valid_items:
    process(item)

# Avoid: O(n) lookup
valid_items = ['apple', 'banana', 'orange']
if item in valid_items:  # This is O(n)
    process(item)

# Use generators for large datasets
def fibonacci_generator():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

# Memory-efficient processing
def process_large_file(filename):
    with open(filename) as file:
        for line in file:  # Processes one line at a time
            yield process_line(line)
```

Happy Pythonic Coding! 🐍🚀

---
**Note**: Focus on writing clean, readable, and efficient Python code that showcases the language's strengths and follows Python idioms.