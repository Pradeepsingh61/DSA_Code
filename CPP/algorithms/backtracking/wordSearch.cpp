#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Word Search (Backtracking Algorithm)

📌 Description:
Given an m x n grid of characters (board) and a string (word),
determine if the word exists in the grid. 
The word can be constructed from letters of sequentially adjacent cells,
where adjacent cells are horizontally or vertically neighboring. 
The same cell cannot be used more than once.

💡 Approach:
- Start DFS (backtracking) from every cell in the grid.
- At each step, check if the current character matches.
- Move in 4 directions: up, down, left, right.
- Mark visited cells temporarily to avoid reuse, then restore (backtracking).
- If all characters are matched, return true.

📊 Complexity Analysis:
- Time Complexity: O(M * N * 4^L)
    - M = number of rows, N = number of columns
    - L = length of the word
    - For each cell, we explore up to 4 directions recursively for each character in the word.
- Space Complexity: O(L)
    - Recursion depth is at most L (length of the word).
    - Extra space for recursion stack, in addition to the input board.

🎯 Applications:
- Puzzle solving (crossword, word search games).
- Pathfinding with constraints.
- General grid-based search problems.
*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
        // Try starting from every cell
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // Recursive backtracking function
    bool backtrack(vector<vector<char>>& board, string& word, int r, int c, int idx) {
        // ✅ Base case: full word matched
        if (idx == word.size()) return true;

        // ❌ Invalid index or mismatch
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[idx]) {
            return false;
        }

        // Mark current cell as visited
        char temp = board[r][c];
        board[r][c] = '#';

        // Explore all 4 possible directions
        bool found = backtrack(board, word, r+1, c, idx+1) ||
                     backtrack(board, word, r-1, c, idx+1) ||
                     backtrack(board, word, r, c+1, idx+1) ||
                     backtrack(board, word, r, c-1, idx+1);

        // Restore cell after backtracking
        board[r][c] = temp;

        return found;
    }
};

// ------------------ Test Cases ------------------
int main() {
    Solution sol;

    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    cout << boolalpha;  // print true/false instead of 1/0

    // ✅ Test cases
    cout << sol.exist(board, "ABCCED") << endl; // true
    cout << sol.exist(board, "SEE") << endl;    // true
    cout << sol.exist(board, "ABCB") << endl;   // false

    // ⚡ Edge case: single letter
    vector<vector<char>> board2 = {{'A'}};
    cout << sol.exist(board2, "A") << endl;     // true
    cout << sol.exist(board2, "B") << endl;     // false

    return 0;
}
