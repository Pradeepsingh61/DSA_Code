"""
Algorithm: Sudoku Solver
Description: Solves a 9x9 Sudoku puzzle using backtracking
Time Complexity: O(9^(n*n)) where n=9, exponential in worst case
Space Complexity: O(n*n) for recursion stack
Author: DSA Code Repository
Date: 2025-10-02
"""

def is_valid(board, row, col, num):
    """
    Check if placing num at (row, col) is valid in Sudoku rules.
    
    Args:
        board: 9x9 Sudoku grid
        row: Row index (0-8)
        col: Column index (0-8)
        num: Number to place (1-9)
        
    Returns:
        bool: True if placement is valid, False otherwise
    """
    # Check row
    for x in range(9):
        if board[row][x] == num:
            return False
    
    # Check column
    for x in range(9):
        if board[x][col] == num:
            return False
    
    # Check 3x3 box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if board[i + start_row][j + start_col] == num:
                return False
    
    return True

def solve_sudoku(board):
    """
    Solve Sudoku puzzle using backtracking.
    
    Args:
        board: 9x9 list of lists, 0 represents empty cells
        
    Returns:
        bool: True if solution exists, False otherwise
        
    Examples:
        >>> board = [[5,3,0,0,7,0,0,0,0],
        ...          [6,0,0,1,9,5,0,0,0],
        ...          [0,9,8,0,0,0,0,6,0],
        ...          [8,0,0,0,6,0,0,0,3],
        ...          [4,0,0,8,0,3,0,0,1],
        ...          [7,0,0,0,2,0,0,0,6],
        ...          [0,6,0,0,0,0,2,8,0],
        ...          [0,0,0,4,1,9,0,0,5],
        ...          [0,0,0,0,8,0,0,7,9]]
        >>> solve_sudoku(board)
        True
    """
    # Find empty cell
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                # Try numbers 1-9
                for num in range(1, 10):
                    if is_valid(board, i, j, num):
                        # Make choice
                        board[i][j] = num
                        
                        # Recursive call
                        if solve_sudoku(board):
                            return True
                        
                        # Backtrack
                        board[i][j] = 0
                
                return False
    
    return True  # All cells filled

def print_board(board):
    """Print Sudoku board in a formatted way."""
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("- - - - - - - - - - - -")
        
        for j in range(9):
            if j % 3 == 0 and j != 0:
                print(" | ", end="")
            
            if j == 8:
                print(board[i][j])
            else:
                print(str(board[i][j]) + " ", end="")

def main():
    """Test the Sudoku solver with example puzzles."""
    print("Sudoku Solver using Backtracking")
    print("=" * 40)
    
    # Test case 1: Easy puzzle
    board = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9]
    ]
    
    print("Original Sudoku puzzle:")
    print_board(board)
    print()
    
    if solve_sudoku(board):
        print("Solved Sudoku puzzle:")
        print_board(board)
    else:
        print("No solution exists for this Sudoku puzzle!")
    
    print("\n" + "=" * 40)
    
    # Test case 2: Empty board
    empty_board = [[0 for _ in range(9)] for _ in range(9)]
    print("Solving empty Sudoku board...")
    
    if solve_sudoku(empty_board):
        print("Solution for empty board:")
        print_board(empty_board)
    else:
        print("No solution found!")

if __name__ == "__main__":
    main()