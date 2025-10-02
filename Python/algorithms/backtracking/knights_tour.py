"""
Algorithm: Knight's Tour
Description: Find a sequence of moves for a knight to visit every square on a chessboard exactly once
Time Complexity: O(8^(n^2)) in worst case, exponential
Space Complexity: O(n^2) for the board and recursion stack
Author: DSA Code Repository
Date: 2025-10-02
"""

def is_safe(x, y, board, n):
    """
    Check if the knight can move to position (x, y).
    
    Args:
        x: Row coordinate
        y: Column coordinate
        board: Current state of the chessboard
        n: Size of the board (n x n)
        
    Returns:
        bool: True if move is valid, False otherwise
    """
    return (x >= 0 and x < n and y >= 0 and y < n and board[x][y] == -1)

def print_solution(board, n):
    """Print the knight's tour solution."""
    print("\nKnight's Tour Solution:")
    for i in range(n):
        for j in range(n):
            print(f"{board[i][j]:3d}", end=" ")
        print()

def solve_knights_tour_util(x, y, move_count, board, x_moves, y_moves, n):
    """
    Utility function to solve Knight's Tour using backtracking.
    
    Args:
        x: Current row position
        y: Current column position
        move_count: Number of moves made so far
        board: Current board state
        x_moves: Possible x-direction moves for knight
        y_moves: Possible y-direction moves for knight
        n: Board size
        
    Returns:
        bool: True if solution found, False otherwise
    """
    # Base case: if all squares are visited
    if move_count == n * n:
        return True
    
    # Try all 8 possible moves for knight
    for i in range(8):
        next_x = x + x_moves[i]
        next_y = y + y_moves[i]
        
        if is_safe(next_x, next_y, board, n):
            # Make the move
            board[next_x][next_y] = move_count
            
            # Recursive call for next move
            if solve_knights_tour_util(next_x, next_y, move_count + 1, 
                                     board, x_moves, y_moves, n):
                return True
            
            # Backtrack: undo the move
            board[next_x][next_y] = -1
    
    return False

def solve_knights_tour(n, start_x=0, start_y=0):
    """
    Solve the Knight's Tour problem.
    
    Args:
        n: Size of the chessboard (n x n)
        start_x: Starting row position (default: 0)
        start_y: Starting column position (default: 0)
        
    Returns:
        list: Solution board if found, None otherwise
        
    Examples:
        >>> board = solve_knights_tour(8)
        >>> print("Solution found!" if board else "No solution exists!")
    """
    # Initialize the board with -1 (unvisited)
    board = [[-1 for _ in range(n)] for _ in range(n)]
    
    # Define possible moves for a knight
    # Knight moves in L-shape: 2 squares in one direction, 1 in perpendicular
    x_moves = [2, 1, -1, -2, -2, -1, 1, 2]
    y_moves = [1, 2, 2, 1, -1, -2, -2, -1]
    
    # Starting position
    board[start_x][start_y] = 0
    
    # Solve using backtracking
    if solve_knights_tour_util(start_x, start_y, 1, board, x_moves, y_moves, n):
        return board
    else:
        return None

def count_onward_moves(x, y, board, x_moves, y_moves, n):
    """
    Count the number of valid moves from position (x, y).
    Used for Warnsdorff's heuristic optimization.
    """
    count = 0
    for i in range(8):
        next_x = x + x_moves[i]
        next_y = y + y_moves[i]
        if is_safe(next_x, next_y, board, n):
            count += 1
    return count

def solve_knights_tour_optimized(n, start_x=0, start_y=0):
    """
    Solve Knight's Tour using Warnsdorff's heuristic for better performance.
    Always move to the square from which the knight will have the fewest onward moves.
    
    Args:
        n: Size of the chessboard
        start_x: Starting row
        start_y: Starting column
        
    Returns:
        list: Solution board if found, None otherwise
    """
    board = [[-1 for _ in range(n)] for _ in range(n)]
    x_moves = [2, 1, -1, -2, -2, -1, 1, 2]
    y_moves = [1, 2, 2, 1, -1, -2, -2, -1]
    
    # Start position
    board[start_x][start_y] = 0
    x, y = start_x, start_y
    
    # Make n*n-1 moves
    for move_count in range(1, n * n):
        # Find the best next move using Warnsdorff's heuristic
        min_onward_moves = 9  # Maximum possible is 8
        next_x = next_y = -1
        
        for i in range(8):
            new_x = x + x_moves[i]
            new_y = y + y_moves[i]
            
            if is_safe(new_x, new_y, board, n):
                onward_moves = count_onward_moves(new_x, new_y, board, x_moves, y_moves, n)
                if onward_moves < min_onward_moves:
                    min_onward_moves = onward_moves
                    next_x, next_y = new_x, new_y
        
        if next_x == -1:  # No valid move found
            return None
        
        # Make the move
        board[next_x][next_y] = move_count
        x, y = next_x, next_y
    
    return board

def find_all_tours(n, max_tours=5):
    """
    Find multiple Knight's Tour solutions.
    
    Args:
        n: Board size
        max_tours: Maximum number of tours to find
        
    Returns:
        list: List of solution boards
    """
    tours = []
    
    # Try different starting positions
    for start_x in range(min(n, 3)):  # Limit starting positions for efficiency
        for start_y in range(min(n, 3)):
            if len(tours) >= max_tours:
                break
            
            tour = solve_knights_tour_optimized(n, start_x, start_y)
            if tour:
                tours.append((tour, start_x, start_y))
        
        if len(tours) >= max_tours:
            break
    
    return tours

def main():
    """Test the Knight's Tour algorithm with different board sizes."""
    print("Knight's Tour Problem using Backtracking")
    print("=" * 50)
    
    # Test case 1: Small board (5x5)
    print("Test Case 1: 5x5 board")
    print("-" * 25)
    
    board5 = solve_knights_tour_optimized(5)
    if board5:
        print("Solution found for 5x5 board:")
        print_solution(board5, 5)
    else:
        print("No solution exists for 5x5 board!")
    
    # Test case 2: Standard chessboard (8x8)
    print("\n\nTest Case 2: 8x8 chessboard")
    print("-" * 30)
    
    print("Solving 8x8 board (this may take a moment)...")
    board8 = solve_knights_tour_optimized(8)
    if board8:
        print("Solution found for 8x8 board:")
        print_solution(board8, 8)
        
        # Verify solution
        visited = set()
        valid = True
        for i in range(8):
            for j in range(8):
                if board8[i][j] in visited or board8[i][j] < 0 or board8[i][j] >= 64:
                    valid = False
                    break
                visited.add(board8[i][j])
            if not valid:
                break
        
        print(f"\nSolution verification: {'Valid' if valid and len(visited) == 64 else 'Invalid'}")
    else:
        print("No solution found for 8x8 board!")
    
    # Test case 3: Multiple tours for smaller board
    print("\n\nTest Case 3: Multiple tours for 6x6 board")
    print("-" * 40)
    
    tours = find_all_tours(6, max_tours=3)
    print(f"Found {len(tours)} different tours:")
    
    for i, (tour, start_x, start_y) in enumerate(tours):
        print(f"\nTour {i + 1} (starting from ({start_x}, {start_y})):")
        print_solution(tour, 6)
    
    # Test case 4: Impossible case
    print("\n\nTest Case 4: 3x3 board (impossible)")
    print("-" * 35)
    
    board3 = solve_knights_tour(3)
    if board3:
        print("Solution found for 3x3 board:")
        print_solution(board3, 3)
    else:
        print("No solution exists for 3x3 board (as expected - impossible!)")

if __name__ == "__main__":
    main()