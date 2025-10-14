#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& matrix) {
        int maxArea = 0;
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); col++) {
                if (matrix[row][col] == 1) {
                    maxArea = max(maxArea, explore(matrix, row, col));
                }
            }
        }
        return maxArea;
    }

private:
    int explore(vector<vector<int>>& matrix, int row, int col) {
        if (matrix[row][col] == 0) return 0;

        matrix[row][col] = 0; 
        int area = 1;

        if (row - 1 >= 0) area += explore(matrix, row - 1, col);
        if (row + 1 < matrix.size()) area += explore(matrix, row + 1, col);
        if (col - 1 >= 0) area += explore(matrix, row, col - 1);
        if (col + 1 < matrix[0].size()) area += explore(matrix, row, col + 1);

        return area;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> matrix = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };

    int result = solution.maxAreaOfIsland(matrix);
    cout << "Max Area of Island: " << result << endl;

    return 0;
}
