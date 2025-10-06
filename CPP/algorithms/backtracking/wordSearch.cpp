#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
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
    bool backtrack(vector<vector<char>>& board, string& word, int r, int c, int idx) {
        // If full word matched
        if (idx == word.size()) return true;

        // Check boundaries & mismatch
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[idx]) {
            return false;
        }

        // Mark current cell as visited
        char temp = board[r][c];
        board[r][c] = '#';

        // Explore all 4 directions
        bool found = backtrack(board, word, r+1, c, idx+1) ||
                     backtrack(board, word, r-1, c, idx+1) ||
                     backtrack(board, word, r, c+1, idx+1) ||
                     backtrack(board, word, r, c-1, idx+1);

        // Restore cell (backtracking)
        board[r][c] = temp;

        return found;
    }
};

int main() {
    Solution sol;

    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    cout << boolalpha;  // prints true/false instead of 1/0

    cout << sol.exist(board, "ABCCED") << endl; // true
    cout << sol.exist(board, "SEE") << endl;    // true
    cout << sol.exist(board, "ABCB") << endl;   // false

    return 0;
}
