"""
Algorithm: Rat in a Maze
Description: Find path from source to destination in a maze using backtracking
Time Complexity: O(2^(n^2)) in worst case
Space Complexity: O(n^2) for recursion stack and solution matrix
Author: DSA Code Repository
Date: 2025-10-02
"""

def is_safe(maze, x, y, n):
    """
    Check if (x, y) is a valid cell to move in the maze.
    
    Args:
        maze: 2D matrix representing the maze
        x: Row coordinate
        y: Column coordinate  
        n: Size of the maze (n x n)
        
    Returns:
        bool: True if cell is safe to move, False otherwise
    """
    return (x >= 0 and x < n and y >= 0 and y < n and maze[x][y] == 1)

def solve_maze_util(maze, x, y, solution, n):
    """
    Utility function to solve maze using backtracking.
    
    Args:
        maze: Input maze matrix
        x: Current row position
        y: Current column position
        solution: Solution matrix to track path
        n: Size of maze
        
    Returns:
        bool: True if path exists, False otherwise
    """
    # Base case: reached destination
    if x == n - 1 and y == n - 1 and maze[x][y] == 1:
        solution[x][y] = 1
        return True
    
    # Check if current cell is valid
    if is_safe(maze, x, y, n):
        # Check if current cell is already part of solution
        if solution[x][y] == 1:
            return False
        
        # Mark current cell as part of solution
        solution[x][y] = 1
        
        # Move right
        if solve_maze_util(maze, x, y + 1, solution, n):
            return True
        
        # Move down
        if solve_maze_util(maze, x + 1, y, solution, n):
            return True
        
        # Move left
        if solve_maze_util(maze, x, y - 1, solution, n):
            return True
        
        # Move up
        if solve_maze_util(maze, x - 1, y, solution, n):
            return True
        
        # Backtrack: unmark current cell
        solution[x][y] = 0
        return False
    
    return False

def solve_maze(maze):
    """
    Solve rat in a maze problem.
    
    Args:
        maze: 2D list where 1 represents open path and 0 represents blocked
        
    Returns:
        list: Solution matrix showing the path, or None if no solution
        
    Examples:
        >>> maze = [[1, 0, 0, 0],
        ...         [1, 1, 0, 1],
        ...         [0, 1, 0, 0],
        ...         [1, 1, 1, 1]]
        >>> solution = solve_maze(maze)
        >>> print(solution)
        [[1, 0, 0, 0], [1, 1, 0, 0], [0, 1, 0, 0], [0, 1, 1, 1]]
    """
    n = len(maze)
    solution = [[0 for _ in range(n)] for _ in range(n)]
    
    if solve_maze_util(maze, 0, 0, solution, n):
        return solution
    else:
        return None

def print_maze(maze, title="Maze"):
    """Print maze in a formatted way."""
    print(f"\n{title}:")
    for row in maze:
        print("  ".join(str(cell) for cell in row))
    print()

def solve_maze_all_paths(maze, x, y, solution, n, all_solutions):
    """
    Find all possible paths in the maze.
    
    Args:
        maze: Input maze matrix
        x: Current row position
        y: Current column position
        solution: Current solution matrix
        n: Size of maze
        all_solutions: List to store all found solutions
    """
    # Base case: reached destination
    if x == n - 1 and y == n - 1 and maze[x][y] == 1:
        solution[x][y] = 1
        # Add copy of current solution
        all_solutions.append([row[:] for row in solution])
        solution[x][y] = 0  # Backtrack for other paths
        return
    
    # Check if current cell is valid
    if is_safe(maze, x, y, n) and solution[x][y] == 0:
        # Mark current cell as part of solution
        solution[x][y] = 1
        
        # Try all four directions
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
        for dx, dy in directions:
            solve_maze_all_paths(maze, x + dx, y + dy, solution, n, all_solutions)
        
        # Backtrack
        solution[x][y] = 0

def find_all_paths(maze):
    """
    Find all possible paths from source to destination.
    
    Args:
        maze: 2D maze matrix
        
    Returns:
        list: List of all solution matrices
    """
    n = len(maze)
    solution = [[0 for _ in range(n)] for _ in range(n)]
    all_solutions = []
    
    solve_maze_all_paths(maze, 0, 0, solution, n, all_solutions)
    return all_solutions

def main():
    """Test the rat in a maze algorithm with example mazes."""
    print("Rat in a Maze using Backtracking")
    print("=" * 40)
    
    # Test case 1: Simple maze
    maze1 = [
        [1, 0, 0, 0],
        [1, 1, 0, 1],
        [0, 1, 0, 0],
        [1, 1, 1, 1]
    ]
    
    print("Test Case 1:")
    print_maze(maze1, "Original Maze (1=path, 0=wall)")
    
    solution = solve_maze(maze1)
    if solution:
        print_maze(solution, "Solution Path (1=path taken)")
    else:
        print("No solution exists!")
    
    # Test case 2: More complex maze
    maze2 = [
        [1, 1, 0, 0, 1],
        [0, 1, 1, 0, 1],
        [0, 0, 1, 0, 1],
        [0, 0, 1, 1, 1],
        [1, 0, 0, 0, 1]
    ]
    
    print("\nTest Case 2:")
    print_maze(maze2, "Complex Maze")
    
    solution2 = solve_maze(maze2)
    if solution2:
        print_maze(solution2, "Solution Path")
    else:
        print("No solution exists!")
    
    # Test case 3: Find all paths
    print("\nTest Case 3: Finding all possible paths")
    simple_maze = [
        [1, 1, 1],
        [1, 1, 1],
        [1, 1, 1]
    ]
    
    print_maze(simple_maze, "Simple 3x3 Maze")
    all_paths = find_all_paths(simple_maze)
    
    print(f"Found {len(all_paths)} different paths:")
    for i, path in enumerate(all_paths):
        print(f"\nPath {i + 1}:")
        print_maze(path, f"Solution {i + 1}")
    
    # Test case 4: No solution maze
    print("\nTest Case 4: Maze with no solution")
    no_solution_maze = [
        [1, 0, 0],
        [0, 0, 0],
        [0, 0, 1]
    ]
    
    print_maze(no_solution_maze, "No Solution Maze")
    solution3 = solve_maze(no_solution_maze)
    if solution3:
        print_maze(solution3, "Solution Path")
    else:
        print("No solution exists for this maze!")

if __name__ == "__main__":
    main()