class Solution {
    public void solveSudoku(char[][] board) {
        backtrack(board); // Start backtracking from the first cell
    }

    // Backtracking function to fill empty cells
    private boolean backtrack(char[][] board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '.') { // Found an empty cell
                    for (char num = '1'; num <= '9'; num++) {
                        if (isValid(board, row, col, num)) { // Check if number is valid
                            board[row][col] = num; // Place number

                            if (backtrack(board)) return true; // Continue solving recursively
                            board[row][col] = '.'; // Backtrack if dead-end
                        }
                    }
                    return false; // No valid number, trigger backtracking
                }
            }
        }
        return true; // All cells filled, Sudoku solved
    }

    // Check if placing 'c' at board[row][col] is valid
    private boolean isValid(char[][] board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == c) return false;
            // Check column
            if (board[i][col] == c) return false;
            // Check 3x3 sub-box
            int subRow = 3 * (row / 3) + i / 3;
            int subCol = 3 * (col / 3) + i % 3;
            if (board[subRow][subCol] == c) return false;
        }
        return true;
    }
}

/*
Algorithm Description:
1. Traverse the board to find an empty cell (denoted by '.').
2. Try placing digits '1' to '9' in the empty cell.
3. For each number, check if it is valid in current row, column, and 3x3 sub-box.
4. If valid, place the number and recursively attempt to solve the rest of the board.
5. If a dead-end is reached, backtrack by resetting the cell to '.'.
6. Repeat until all cells are filled correctly, yielding the solved Sudoku.

Complexity Analysis:
- Time Complexity: O(9^m), where m = number of empty cells (each empty cell can have up to 9 options).
- Space Complexity: O(1) extra space (board modified in-place). Recursion stack can go up to O(m).
*/
