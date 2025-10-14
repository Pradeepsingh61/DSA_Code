/*
 * Algorithm: Sudoku Solver using Recursion + Backtracking
 * Description: Recursively fills empty cells with valid numbers and backtracks when a conflict occurs.
 * Time Complexity: O(9^m) where m is the number of empty cells
 * Space Complexity: O(m) for recursion stack, where m is the number of empty cells
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Solves a Sudoku puzzle using recursion and backtracking using modern C++
 * @param board 9x9 Sudoku board to solve
 */


bool sudoku_solver(vector<vector<char>> &board, vector<vector<bool>> &rowFreq, vector<vector<bool>> &colFreq, vector<vector<bool>> &boxFreq) {
    int i, j, k;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(board[i][j] == '.') {
                for(k = 0; k < 9; k++) {
                    int box = (i / 3) * 3 + (j / 3);
                    if(!rowFreq[i][k] && !colFreq[j][k] && !boxFreq[box][k]) {
                        board[i][j] = char(k + '1');
                        rowFreq[i][k] = true;
                        colFreq[j][k] = true;
                        boxFreq[box][k] = true;
                        if(sudoku_solver(board, rowFreq, colFreq, boxFreq)) {
                            return true;
                        }
                        board[i][j] = '.';
                        rowFreq[i][k] = false;
                        colFreq[j][k] = false;
                        boxFreq[box][k] = false;
                    }
                }
                return false;
            }
        }
    }
    return true;  
}


void solve_sudoku(vector<vector<char>>& board) {
    vector<vector<bool>> rowFreq(9, vector<bool>(9, false));
    vector<vector<bool>> colFreq(9, vector<bool>(9, false));
    vector<vector<bool>> boxFreq(9, vector<bool>(9, false));

    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(board[i][j] != '.') {
                int digit = board[i][j] - '0';
                rowFreq[i][digit - 1] = true;
                colFreq[j][digit - 1] = true;
                int box = (i / 3) * 3 + (j / 3);
                boxFreq[box][digit - 1] = true;
            }
        }
    }

    sudoku_solver(board, rowFreq, colFreq, boxFreq);

}


// Test function with modern C++ features
void test_sudoku_solver() {

    // Testcase: Normal Sudoku board
    vector<vector<char>> board1 = {
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

    vector<vector<char>> expected1 = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };

    solve_sudoku(board1);
    cout << "Test Case 1: " << (board1 == expected1 ? "Passed" : "Failed") << endl;

    //Testcase: Already solved sudoku board
    vector<vector<char>> board2 = expected1;
    vector<vector<char>> expected2 = expected1;

    solve_sudoku(board2);
    cout << "Test Case 2: " << (board2 == expected2 ? "Passed" : "Failed") << endl;

    //Testcase: Minimal solved board
    vector<vector<char>> board3(9, vector<char>(9, '.'));
    board3[0][0] = '1';
    solve_sudoku(board3);
    
    bool fullyFilled = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board3[i][j] == '.') {
                fullyFilled = false;
                break;
            }
        }
        if (!fullyFilled) {
            break;
        }
    }

    cout << "Test Case 3: " << (fullyFilled ? "Passed" : "Failed") << endl;
}


int main() {

    test_sudoku_solver();

    return 0;
}