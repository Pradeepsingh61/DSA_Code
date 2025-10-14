/*
Algorithm Name
Sudoku Solver

Programming Language
C++

Category
Other

Difficulty Level
Medium (Intermediate)

Algorithm Description
The Sudoku Solver problem requires filling a partially completed 9×9 Sudoku board so that each row, column, and 3×3 sub-grid contains digits 1–9 exactly once. The solution uses a recursive backtracking approach: we pick the next empty cell, try placing digits 1–9, and check validity against Sudoku rules. If a number fits, we recurse to solve the rest of the board; if it leads to a conflict later, we backtrack by removing it and trying the next digit. This process continues until the board is completely filled with a valid configuration.
*/
#include <bits/stdc++.h>
using namespace std;

bool isValid(vector<vector<char>>& board, int row, int col, char num) {
    // Check row and column
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
        if (board[i][col] == num) return false;
    }

    // Check 3x3 sub-grid
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num) return false;

    return true;
}

bool solveSudoku(vector<vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') { // empty cell
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = '.'; // backtrack
                    }
                }
                return false; // no valid number found
            }
        }
    }
    return true; // solved
}

void printBoard(const vector<vector<char>>& board) {
    for (auto& row : board) {
        for (auto c : row)
            cout << c << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    if (solveSudoku(board))
        printBoard(board);
    else
        cout << "No solution exists" << endl;

    return 0;
}

/*
Time Complexity: 
O(9^m) where m = empty cells.

Space Complexity: 
O(m) recursion stack.
*/


/*
Output
5 3 4 6 7 8 9 1 2 
6 7 2 1 9 5 3 4 8 
1 9 8 3 4 2 5 6 7 
8 5 9 7 6 1 4 2 3 
4 2 6 8 5 3 7 9 1 
7 1 3 9 2 4 8 5 6 
9 6 1 5 3 7 2 8 4 
2 8 7 4 1 9 6 3 5 
3 4 5 2 8 6 1 7 9 
*/