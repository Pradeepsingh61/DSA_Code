# Sparse Matrix Operations in C++

This program implements various operations on sparse matrices using C++. A sparse matrix is a matrix that contains mostly zero elements, making it memory-efficient to store only the non-zero elements.

## Features

- **Addition**: Add two sparse matrices of the same dimensions
- **Subtraction**: Subtract one sparse matrix from another
- **Multiplication**: Matrix multiplication following standard rules
- **Element-wise Division**: Divide corresponding elements (not standard matrix division)
- **Transpose**: Get the transpose of a sparse matrix

## Data Structure

The program uses a triplet representation where each non-zero element is stored as:
- Row index
- Column index  
- Value

## How to Compile and Run

```bash
g++ -o sparse_matrix_operations sparse_matrix_operations.cpp
./sparse_matrix_operations
```

## Usage Examples

### Example 1: Matrix Addition
```
Matrix A (3x3):
1  0  2
0  0  0
3  0  4

Matrix B (3x3):  
0  5  0
6  0  7
0  8  0

Result A + B:
1  5  2
6  0  7
3  8  4
```

### Example 2: Matrix Multiplication
```
Matrix A (2x3):
1  0  2
0  3  0

Matrix B (3x2):
4  0
0  5
6  0

Result A × B:
16  0
0  15
```

### Input Format

When prompted, enter:
1. Number of rows
2. Number of columns  
3. Number of non-zero elements
4. For each non-zero element: row_index column_index value

**Note**: Indices are 0-based (start from 0)

### Example Input Session
```
Enter number of rows: 3
Enter number of columns: 3
Enter number of non-zero elements: 4
Element 1: 0 0 1
Element 2: 0 2 2  
Element 3: 2 0 3
Element 4: 2 2 4
```

## Operations Details

### Addition and Subtraction
- Matrices must have the same dimensions
- Corresponding elements are added/subtracted
- Result maintains sparse representation

### Multiplication  
- First matrix columns must equal second matrix rows
- Standard matrix multiplication algorithm
- Efficiently handles sparse matrices

### Element-wise Division
- Matrices must have same dimensions
- Divides corresponding non-zero elements
- Warns about division by zero

### Transpose
- Swaps rows and columns
- Dimensions change from m×n to n×m

## Memory Efficiency

The sparse matrix representation is memory efficient:
- Only stores non-zero elements
- Space complexity: O(number of non-zero elements)
- Ideal for matrices with many zeros

## Time Complexity

- **Addition/Subtraction**: O(m + n) where m, n are non-zero elements in each matrix
- **Multiplication**: O(m × n) where m, n are non-zero elements in each matrix  
- **Transpose**: O(k) where k is number of non-zero elements

## Error Handling

The program includes error handling for:
- Invalid matrix dimensions for operations
- Division by zero
- Invalid array indices
- Memory allocation issues

## Limitations

- Element-wise division is not standard matrix division
- Integer arithmetic only (can be extended to floating-point)
- No matrix inversion or other advanced operations

## Future Enhancements

Possible improvements:
- Support for floating-point numbers
- Matrix determinant calculation
- Matrix inversion for invertible matrices
- File I/O for large matrices
- Optimized algorithms for very large sparse matrices