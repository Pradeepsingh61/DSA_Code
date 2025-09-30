#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Algorithm: Flood Fill (DFS)
=====================================================

Problem:
Given an image represented as a 2D grid, start from a pixel (sr, sc),
and change the color of all connected pixels having the same initial
color to a new color. Connectivity is 4-directional (up, right, down, left).

Approach (DFS):
1. Store the initial color of the starting pixel.
2. Use DFS to explore all 4-directionally connected pixels.
3. If a pixel has the same initial color and is not already filled with
   the new color, recolor it and recursively continue.
4. Return the modified image.

=====================================================
Time Complexity:
- Each pixel is visited at most once.
- For each pixel, we check 4 neighbors.
- Overall: O(N * M), where N = number of rows, M = number of columns.

Space Complexity:
- Recursive DFS stack: O(N * M) in the worst case (all pixels same color).
- Output image (copy): O(N * M).
=====================================================
*/

class Solution {
private:
    // Depth-First Search helper function
    void dfs(int row, int col, vector<vector<int>>& result,
             vector<vector<int>>& image, int newColor,
             int delRow[], int delCol[], int initialColor) {

        // Recolor the current pixel
        result[row][col] = newColor; 

        int n = image.size();
        int m = image[0].size(); 

        // Explore 4 neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = row + delRow[i]; 
            int newCol = col + delCol[i]; 

            // Check valid coordinates
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m) {
                // Check if the neighbor has the same initial color and is not recolored yet
                if (image[newRow][newCol] == initialColor && result[newRow][newCol] != newColor) {
                    dfs(newRow, newCol, result, image, newColor, delRow, delCol, initialColor); 
                }
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        // Get the initial color of the starting pixel
        int initialColor = image[sr][sc]; 

        // Copy of the original image to store result
        vector<vector<int>> result = image; 

        // Direction arrays for up, right, down, left
        int delRow[] = {-1, 0, +1, 0};
        int delCol[] = {0, +1, 0, -1}; 

        // Call DFS from the starting pixel
        dfs(sr, sc, result, image, newColor, delRow, delCol, initialColor); 

        return result; 
    }
};

// Driver code
int main() {
    vector<vector<int>> image {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    int sr = 1, sc = 1, newColor = 2;   // starting point (1,1) with new color 2

    Solution obj;
    vector<vector<int>> result = obj.floodFill(image, sr, sc, newColor);

    // Print output image
    for (auto row : result) {
        for (auto pixel : row)
            cout << pixel << " ";
        cout << "\n";
    }

    return 0;
}
