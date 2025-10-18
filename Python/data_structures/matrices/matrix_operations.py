"""Matrix Operations Module

This module provides comprehensive matrix operations including:
- Matrix multiplication
- Matrix transpose
- Determinant calculation
- Sparse matrix conversion

Each function includes detailed comments, complexity analysis, and examples.
"""

def matrix_multiply(matrix_a, matrix_b):
    """Multiply two matrices using standard algorithm.
    
    Algorithm:
    - For each element (i,j) in result matrix, compute dot product
      of row i from matrix_a with column j from matrix_b
    - Time Complexity: O(n * m * p) where matrix_a is n×m and matrix_b is m×p
    - Space Complexity: O(n * p) for result matrix
    
    Args:
        matrix_a: First matrix (list of lists)
        matrix_b: Second matrix (list of lists)
    
    Returns:
        Resulting matrix from multiplication
    
    Example:
        >>> A = [[1, 2], [3, 4]]
        >>> B = [[5, 6], [7, 8]]
        >>> matrix_multiply(A, B)
        [[19, 22], [43, 50]]
    """
    if not matrix_a or not matrix_b:
        raise ValueError("Matrices cannot be empty")
    
    rows_a = len(matrix_a)
    cols_a = len(matrix_a[0])
    rows_b = len(matrix_b)
    cols_b = len(matrix_b[0])
    
    # Check if multiplication is possible
    if cols_a != rows_b:
        raise ValueError(f"Cannot multiply: columns of A ({cols_a}) != rows of B ({rows_b})")
    
    # Initialize result matrix with zeros
    result = [[0 for _ in range(cols_b)] for _ in range(rows_a)]
    
    # Perform multiplication
    for i in range(rows_a):
        for j in range(cols_b):
            # Compute dot product of row i and column j
            for k in range(cols_a):
                result[i][j] += matrix_a[i][k] * matrix_b[k][j]
    
    return result


def matrix_transpose(matrix):
    """Transpose a matrix by swapping rows and columns.
    
    Algorithm:
    - Create new matrix where element (i,j) becomes element (j,i)
    - Time Complexity: O(n * m) where matrix is n×m
    - Space Complexity: O(n * m) for transposed matrix
    
    Args:
        matrix: Input matrix (list of lists)
    
    Returns:
        Transposed matrix
    
    Example:
        >>> M = [[1, 2, 3], [4, 5, 6]]
        >>> matrix_transpose(M)
        [[1, 4], [2, 5], [3, 6]]
    """
    if not matrix:
        return []
    
    rows = len(matrix)
    cols = len(matrix[0])
    
    # Create transposed matrix
    transposed = [[matrix[i][j] for i in range(rows)] for j in range(cols)]
    
    return transposed


def calculate_determinant(matrix):
    """Calculate determinant of a square matrix using recursive cofactor expansion.
    
    Algorithm:
    - Base case: 1×1 matrix returns the single element
    - Base case: 2×2 matrix uses formula ad - bc
    - Recursive case: Expand along first row using cofactors
    - Time Complexity: O(n!) due to recursive expansion
    - Space Complexity: O(n²) for recursive call stack and submatrices
    
    Args:
        matrix: Square matrix (list of lists)
    
    Returns:
        Determinant value (float or int)
    
    Example:
        >>> M = [[4, 3], [6, 3]]
        >>> calculate_determinant(M)
        -6
        >>> M = [[1, 2, 3], [0, 1, 4], [5, 6, 0]]
        >>> calculate_determinant(M)
        1
    """
    if not matrix:
        raise ValueError("Matrix cannot be empty")
    
    n = len(matrix)
    
    # Check if matrix is square
    for row in matrix:
        if len(row) != n:
            raise ValueError("Matrix must be square")
    
    # Base case: 1x1 matrix
    if n == 1:
        return matrix[0][0]
    
    # Base case: 2x2 matrix
    if n == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]
    
    # Recursive case: cofactor expansion along first row
    determinant = 0
    for j in range(n):
        # Create minor matrix by removing row 0 and column j
        minor = [[matrix[i][k] for k in range(n) if k != j] 
                 for i in range(1, n)]
        
        # Calculate cofactor: (-1)^(0+j) * matrix[0][j] * det(minor)
        cofactor = ((-1) ** j) * matrix[0][j] * calculate_determinant(minor)
        determinant += cofactor
    
    return determinant


def to_sparse_matrix(matrix, threshold=0):
    """Convert dense matrix to sparse representation (COO format).
    
    Algorithm:
    - Scan all matrix elements
    - Store only non-zero elements (or above threshold) with their positions
    - COO format: list of (row, col, value) tuples
    - Time Complexity: O(n * m) where matrix is n×m
    - Space Complexity: O(k) where k is number of non-zero elements
    
    Args:
        matrix: Dense matrix (list of lists)
        threshold: Values above this are considered non-zero (default: 0)
    
    Returns:
        Dictionary with 'shape' and 'data' (list of (row, col, value) tuples)
    
    Example:
        >>> M = [[1, 0, 0], [0, 5, 0], [0, 0, 9]]
        >>> to_sparse_matrix(M)
        {'shape': (3, 3), 'data': [(0, 0, 1), (1, 1, 5), (2, 2, 9)]}
    """
    if not matrix:
        return {'shape': (0, 0), 'data': []}
    
    rows = len(matrix)
    cols = len(matrix[0]) if matrix[0] else 0
    
    # Store non-zero elements
    sparse_data = []
    for i in range(rows):
        for j in range(len(matrix[i])):
            if matrix[i][j] > threshold:
                sparse_data.append((i, j, matrix[i][j]))
    
    return {
        'shape': (rows, cols),
        'data': sparse_data
    }


def from_sparse_matrix(sparse_dict):
    """Convert sparse matrix representation back to dense matrix.
    
    Algorithm:
    - Initialize matrix with zeros
    - Fill in values from sparse data
    - Time Complexity: O(n * m + k) where k is number of non-zero elements
    - Space Complexity: O(n * m) for dense matrix
    
    Args:
        sparse_dict: Dictionary with 'shape' and 'data' keys
    
    Returns:
        Dense matrix (list of lists)
    
    Example:
        >>> sparse = {'shape': (2, 3), 'data': [(0, 0, 5), (1, 2, 7)]}
        >>> from_sparse_matrix(sparse)
        [[5, 0, 0], [0, 0, 7]]
    """
    rows, cols = sparse_dict['shape']
    
    # Initialize matrix with zeros
    matrix = [[0 for _ in range(cols)] for _ in range(rows)]
    
    # Fill in non-zero values
    for row, col, value in sparse_dict['data']:
        matrix[row][col] = value
    
    return matrix


if __name__ == "__main__":
    # Example usage and testing
    print("Matrix Operations Examples\n" + "="*50)
    
    # Example 1: Matrix Multiplication
    print("\n1. Matrix Multiplication:")
    A = [[1, 2], [3, 4]]
    B = [[5, 6], [7, 8]]
    print(f"A = {A}")
    print(f"B = {B}")
    result = matrix_multiply(A, B)
    print(f"A × B = {result}")
    
    # Example 2: Matrix Transpose
    print("\n2. Matrix Transpose:")
    M = [[1, 2, 3], [4, 5, 6]]
    print(f"Original: {M}")
    print(f"Transposed: {matrix_transpose(M)}")
    
    # Example 3: Determinant Calculation
    print("\n3. Determinant Calculation:")
    M2 = [[4, 3], [6, 3]]
    print(f"Matrix: {M2}")
    print(f"Determinant: {calculate_determinant(M2)}")
    
    M3 = [[1, 2, 3], [0, 1, 4], [5, 6, 0]]
    print(f"\nMatrix: {M3}")
    print(f"Determinant: {calculate_determinant(M3)}")
    
    # Example 4: Sparse Matrix Conversion
    print("\n4. Sparse Matrix Conversion:")
    dense = [[1, 0, 0, 0], [0, 5, 0, 0], [0, 0, 9, 0], [0, 0, 0, 0]]
    print(f"Dense matrix: {dense}")
    sparse = to_sparse_matrix(dense)
    print(f"Sparse representation: {sparse}")
    print(f"Converted back: {from_sparse_matrix(sparse)}")
    
    print("\n" + "="*50)
