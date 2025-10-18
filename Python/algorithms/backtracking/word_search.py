"""
Algorithm: Word Search in Grid
Description: Search for words in a 2D character grid using backtracking
Time Complexity: O(N * M * 4^L) where N*M is grid size, L is word length
Space Complexity: O(L) for recursion stack where L is word length
Author: DSA Code Repository
Date: 2025-10-02
"""

def exist(board, word):
    """
    Search for a word in 2D character grid.
    
    Args:
        board: 2D list of characters
        word: String to search for
        
    Returns:
        bool: True if word exists in the grid, False otherwise
        
    Examples:
        >>> board = [['A','B','C','E'],
        ...          ['S','F','C','S'],
        ...          ['A','D','E','E']]
        >>> exist(board, "ABCCED")
        True
        >>> exist(board, "SEE")
        True
        >>> exist(board, "ABCB")
        False
    """
    if not board or not board[0] or not word:
        return False
    
    rows, cols = len(board), len(board[0])
    
    def backtrack(row, col, index):
        """
        Backtracking helper function.
        
        Args:
            row: Current row position
            col: Current column position
            index: Current index in the word
            
        Returns:
            bool: True if word can be formed from this position
        """
        # Base case: found the complete word
        if index == len(word):
            return True
        
        # Check boundaries and character match
        if (row < 0 or row >= rows or col < 0 or col >= cols or 
            board[row][col] != word[index]):
            return False
        
        # Mark current cell as visited
        temp = board[row][col]
        board[row][col] = '#'  # Use # as visited marker
        
        # Explore all 4 directions
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
        found = any(backtrack(row + dx, col + dy, index + 1) 
                   for dx, dy in directions)
        
        # Backtrack: restore the cell
        board[row][col] = temp
        
        return found
    
    # Try starting from each cell
    for i in range(rows):
        for j in range(cols):
            if backtrack(i, j, 0):
                return True
    
    return False

def find_all_words(board, words):
    """
    Find all words from a list that exist in the grid.
    
    Args:
        board: 2D character grid
        words: List of words to search for
        
    Returns:
        list: List of words found in the grid
    """
    found_words = []
    
    for word in words:
        # Create a copy of board for each word search
        board_copy = [row[:] for row in board]
        if exist(board_copy, word):
            found_words.append(word)
    
    return found_words

def find_word_path(board, word):
    """
    Find the path of a word in the grid (returns coordinates).
    
    Args:
        board: 2D character grid
        word: Word to find
        
    Returns:
        list: List of (row, col) coordinates forming the word path, or None if not found
    """
    if not board or not board[0] or not word:
        return None
    
    rows, cols = len(board), len(board[0])
    
    def backtrack_with_path(row, col, index, path):
        """Backtracking with path tracking."""
        if index == len(word):
            return path[:]
        
        if (row < 0 or row >= rows or col < 0 or col >= cols or 
            board[row][col] != word[index] or (row, col) in path):
            return None
        
        # Add current position to path
        path.append((row, col))
        
        # Explore all 4 directions
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        for dx, dy in directions:
            result = backtrack_with_path(row + dx, col + dy, index + 1, path)
            if result:
                return result
        
        # Backtrack: remove current position from path
        path.pop()
        return None
    
    # Try starting from each cell
    for i in range(rows):
        for j in range(cols):
            if board[i][j] == word[0]:
                path = backtrack_with_path(i, j, 0, [])
                if path:
                    return path
    
    return None

def count_word_occurrences(board, word):
    """
    Count how many times a word appears in the grid (different paths).
    
    Args:
        board: 2D character grid
        word: Word to count
        
    Returns:
        int: Number of different ways the word can be formed
    """
    if not board or not board[0] or not word:
        return 0
    
    rows, cols = len(board), len(board[0])
    count = 0
    
    def backtrack_count(row, col, index, visited):
        """Backtracking to count all possible paths."""
        nonlocal count
        
        if index == len(word):
            count += 1
            return
        
        if (row < 0 or row >= rows or col < 0 or col >= cols or 
            board[row][col] != word[index] or (row, col) in visited):
            return
        
        # Mark as visited
        visited.add((row, col))
        
        # Explore all 4 directions
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        for dx, dy in directions:
            backtrack_count(row + dx, col + dy, index + 1, visited)
        
        # Backtrack
        visited.remove((row, col))
    
    # Try starting from each cell
    for i in range(rows):
        for j in range(cols):
            if board[i][j] == word[0]:
                backtrack_count(i, j, 0, set())
    
    return count

def print_board_with_path(board, path, word):
    """Print board highlighting the path of the word."""
    if not path:
        print("No path found!")
        return
    
    rows, cols = len(board), len(board[0])
    display_board = [['.' for _ in range(cols)] for _ in range(rows)]
    
    # Mark the path
    for i, (row, col) in enumerate(path):
        display_board[row][col] = word[i]
    
    print(f"\nPath for word '{word}':")
    for i, row in enumerate(display_board):
        for j, cell in enumerate(row):
            if (i, j) in path:
                print(f"[{cell}]", end=" ")
            else:
                print(f" {board[i][j]} ", end=" ")
        print()
    
    print(f"Path coordinates: {path}")

def main():
    """Test the word search algorithm with various examples."""
    print("Word Search in Grid using Backtracking")
    print("=" * 45)
    
    # Test case 1: Basic word search
    board1 = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    
    print("Test Case 1: Basic Word Search")
    print("Board:")
    for row in board1:
        print("  ".join(row))
    
    test_words = ["ABCCED", "SEE", "ABCB", "SFCS"]
    
    for word in test_words:
        # Make a copy since exist() modifies the board
        board_copy = [row[:] for row in board1]
        found = exist(board_copy, word)
        print(f"Word '{word}': {'Found' if found else 'Not Found'}")
        
        if found:
            path = find_word_path(board1, word)
            print_board_with_path(board1, path, word)
    
    # Test case 2: Multiple word search
    print("\n" + "="*45)
    print("Test Case 2: Multiple Words Search")
    
    word_list = ["ABCCED", "SEE", "ABCB", "AS", "SF", "DEED"]
    found_words = find_all_words(board1, word_list)
    
    print(f"Words to search: {word_list}")
    print(f"Words found: {found_words}")
    
    # Test case 3: Count occurrences
    print("\n" + "="*45)
    print("Test Case 3: Count Word Occurrences")
    
    board2 = [
        ['A', 'A', 'A'],
        ['A', 'A', 'A'],
        ['A', 'A', 'A']
    ]
    
    print("Board (all A's):")
    for row in board2:
        print("  ".join(row))
    
    word = "AAA"
    count = count_word_occurrences(board2, word)
    print(f"Number of ways to form '{word}': {count}")
    
    # Test case 4: Complex grid
    print("\n" + "="*45)
    print("Test Case 4: Complex Grid")
    
    board3 = [
        ['C', 'A', 'T', 'S'],
        ['R', 'A', 'T', 'E'],
        ['D', 'O', 'G', 'S'],
        ['F', 'I', 'S', 'H']
    ]
    
    print("Animal Grid:")
    for row in board3:
        print("  ".join(row))
    
    animals = ["CAT", "DOG", "FISH", "RAT", "CATS", "DOGS", "RATE"]
    found_animals = find_all_words(board3, animals)
    
    print(f"Animal words found: {found_animals}")
    
    # Show paths for found animals
    for animal in found_animals[:3]:  # Show first 3 to avoid clutter
        path = find_word_path(board3, animal)
        print_board_with_path(board3, path, animal)

if __name__ == "__main__":
    main()