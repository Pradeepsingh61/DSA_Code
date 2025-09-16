# Python Algorithms 🐍⚡

This directory contains various algorithm implementations in Python, organized by category for easy navigation and learning.

## 📂 Directory Structure

```
algorithms/
├── arrays/              # Array manipulation algorithms
├── backtracking/        # Backtracking algorithms
├── graph_algorithms/    # Graph traversal and algorithms
├── mathematical/        # Mathematical and numerical algorithms
├── searching/          # Search algorithms
├── sorting/            # Sorting algorithms
└── string_algorithms/  # String processing algorithms
```

## 🔍 Searching Algorithms

Located in `searching/`

- **Binary Search** (`binary_search.py`) - O(log n) search in sorted arrays
- **Linear Search** (`linear_search.py`) - O(n) sequential search
- **Jump Search** (`jump_search.py`) - O(√n) search algorithm
- **Interpolation Search** (`interpolation_search.py`) - Better than binary for uniformly distributed data
- **Exponential Search** (`exponential_search.py`) - For unbounded/infinite arrays

## 📊 Sorting Algorithms

Located in `sorting/`

- **Bubble Sort** (`bubble_sort.py`) - O(n²) simple comparison sort
- **Selection Sort** (`selection_sort.py`) - O(n²) selection-based sort
- **Insertion Sort** (`insertion_sort.py`) - O(n²) insertion-based sort
- **Counting Sort** (`counting_sort.py`) - O(n+k) non-comparison sort
- **Merge Two Sorted Arrays** (`merge_two_sorted_arrays.py`) - Merge operation for merge sort

## 🎯 Array Algorithms

Located in `arrays/`

- **Three Sum** (`three_sum.py`) - Find three numbers that sum to target
- **Two Sum** (`pair_with_given_sum_two_sum.py`) - Find pair that sums to target
- **Container With Most Water** (`container_with_most_water.py`) - Maximum area problem
- **Spiral Matrix** (`spiral_matrix.py`) - Traverse matrix in spiral order
- **Longest Subarray** (`longest_subarray_with_maximum_bitwise_and.py`) - Bitwise operations

## 🌐 Graph Algorithms

Located in `graph_algorithms/`

- **Dijkstra's Algorithm** (`dijkstra_algorithm.py`) - Shortest path algorithm

## 🔢 Mathematical Algorithms

Located in `mathematical/`

- **Karatsuba Algorithm** (`karatsuba_algorithm.py`) - Fast multiplication algorithm

## 🔄 Backtracking Algorithms

Located in `backtracking/`

- **N-Queen Problem** (`n_queen_problem.py`) - Classic backtracking problem

## 📝 String Algorithms

Located in `string_algorithms/`

- **Palindrome Check** (`check_if_string_is_palindrome.py`) - Check if string is palindrome
- **Kth Bit in Nth String** (`find_kth_bit_in_nth_string.py`) - Binary string manipulation
- **String Sequence** (`find_sequence_of_strings_on_screen.py`) - String sequence finding

## 🚀 Usage Examples

### Binary Search Example
```python
from searching.binary_search import binary_search

arr = [1, 3, 5, 7, 9, 11, 13]
target = 7
result = binary_search(arr, target)
print(f"Element {target} found at index: {result}")
```

### Bubble Sort Example
```python
from sorting.bubble_sort import bubble_sort

unsorted_list = [64, 34, 25, 12, 22, 11, 90]
sorted_list = bubble_sort(unsorted_list.copy())
print(f"Sorted array: {sorted_list}")
```

## 🎯 Contributing Guidelines

When adding new algorithms to this directory:

### File Naming
- Use `snake_case` for file names
- Include algorithm name clearly
- Add `.py` extension

### Code Structure
```python
"""
Algorithm: [Name]
Description: [Brief description]
Time Complexity: O(?)
Space Complexity: O(?)
"""

def algorithm_name(input_params):
    """
    Brief description of the function.

    Args:
        input_params: Description

    Returns:
        return_value: Description

    Examples:
        >>> algorithm_name([1, 2, 3])
        result
    """
    # Implementation here
    pass

def main():
    """Test the algorithm with examples."""
    # Test cases here
    pass

if __name__ == "__main__":
    main()
```

### Documentation
- Include time and space complexity
- Add clear docstrings
- Provide usage examples
- Include test cases in main()

## 📚 Algorithm Categories

### By Time Complexity
- **O(1)**: Constant time algorithms
- **O(log n)**: Logarithmic algorithms (Binary Search)
- **O(n)**: Linear algorithms (Linear Search)
- **O(n log n)**: Linearithmic algorithms (Merge Sort, Quick Sort)
- **O(n²)**: Quadratic algorithms (Bubble Sort, Selection Sort)

### By Problem Type
- **Search Problems**: Finding elements in data structures
- **Sort Problems**: Arranging elements in order
- **Array Problems**: Manipulating array data structures
- **Graph Problems**: Working with graph data structures
- **String Problems**: Text processing and manipulation

## 🏆 Recommended Learning Path

1. **Start with**: Linear Search, Binary Search
2. **Move to**: Bubble Sort, Selection Sort, Insertion Sort
3. **Progress to**: Array algorithms (Two Sum, Three Sum)
4. **Advanced**: Graph algorithms, Mathematical algorithms
5. **Expert**: Backtracking algorithms, Complex string algorithms

Happy Algorithm Learning! 🐍🚀