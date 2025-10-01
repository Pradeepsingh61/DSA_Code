#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Algorithm: N-Queens Problem using Backtracking
=====================================================

The N-Queens problem is to place N queens on an N×N chessboard
such that no two queens attack each other. A queen can attack
horizontally, vertically, and diagonally.

Approach:
1. Place queens one column at a time (from left to right).
2. For each column, try placing a queen in every row:
   - Check if the position is safe (no conflict in row, upper-left diagonal, lower-left diagonal).
   - If safe, place the queen and recursively attempt to place the rest.
   - If placing the queen leads to no solution, backtrack (remove the queen and try next row).
3. Stop when all queens are successfully placed.

=====================================================
Time Complexity:
- For each column, we try placing a queen in N rows.
- At each step, we perform an O(N) check for safety (row + 2 diagonals).
- Worst-case time complexity: O(N!) (factorial growth).
- More precisely: O(N * N!) due to the safety check overhead.

Space Complexity:
- O(N^2) for the chessboard representation.
- O(N) recursive call stack (depth = number of columns).
=====================================================
*/

// Function to print the solution board
void printSolution(vector<vector<int>>& board) {
    int n = board.size();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 1)
                cout << "Q ";  // Queen placed
            else
                cout << ". ";  // Empty cell
        }
        cout << "\n";
    }
}

// Check if it's safe to place a queen at board[row][col]
bool isSafe(vector<vector<int>>& board, int row, int col) {
    int n = board.size();

    // Check row on the left
    for (int j = 0; j < col; j++)
        if (board[row][j] == 1)
            return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // Check lower-left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    return true; // Safe to place queen
}

// Recursive utility function to solve N-Queens
bool solveNQUtil(vector<vector<int>>& board, int col) {
    int n = board.size();

    // Base case: all queens are placed
    if (col >= n)
        return true;

    // Try placing queen in each row of current column
    for (int row = 0; row < n; row++) {
        if (isSafe(board, row, col)) {
            // Place queen
            board[row][col] = 1;

            // Recur to place rest of the queens
            if (solveNQUtil(board, col + 1))
                return true;

            // Backtrack: remove queen
            board[row][col] = 0;
        }
    }

    // No valid placement in this column
    return false;
}

// Solve N-Queens problem
bool solveNQ(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (!solveNQUtil(board, 0)) {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(board);
    return true;
}

// Driver code
int main() {
    int n = 4;
    solveNQ(n);
    return 0;
}

