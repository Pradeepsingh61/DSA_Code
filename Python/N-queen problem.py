# Function to check if placement is safe
def is_safe(board, curr_row, curr_col):
    for i in range(len(board)):
        placed_row = board[i]
        placed_col = i + 1
        
        # Check diagonals
        if abs(placed_row - curr_row) == \
           abs(placed_col - curr_col):
            return False # Not safe
    return True # Safe to place

# Recursive utility to solve N-Queens
def nqueen_util(col, n, board, result, visited):
  
    # If all queens placed, add to result
    if col > n:
        result.append(board.copy())
        return
      
    # Try each row in column
    for row in range(1, n+1):
      
        # If row not used
        if not visited[row]:
          
            # Check safety
            if is_safe(board, row, col):
              
                # Mark row
                visited[row] = True
                
                # Place queen
                board.append(row)
                
                # Recur for next column
                nqueen_util(col+1, n, board, result, visited)
                
                # Backtrack
                board.pop()
                visited[row] = False

# Main N-Queen solver
def nqueen(n):
    result = []
    board = []
    visited = [False] * (n +1)
    nqueen_util(1, n, board, result, visited)
    return result

# Main function
if __name__ == "__main__":
    n = 4
    result = nqueen(n)
    for res in result:
        print("[", end="")
        for i in range(len(res)):
            print(res[i], end="")
            if i != len(res)-1:
                print(", ", end="")
        print("]")
