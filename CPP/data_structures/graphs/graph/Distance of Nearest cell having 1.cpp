#include <bits/stdc++.h>
using namespace std;

/*
Algorithm: BFS-based Distance of Nearest 1 in a Binary Grid

Given a binary matrix 'grid', we want to calculate, for each cell, 
the distance to the nearest cell containing 1. 

Steps:
1. Initialize a 'distance' matrix of same size as grid to store results.
2. Initialize a 'visited' matrix to track which cells have been processed.
3. Use a queue to perform multi-source BFS:
   - Push all cells containing 1 into the queue with distance 0.
4. Perform BFS:
   - For each cell, explore its 4 neighbors (up, down, left, right).
   - If a neighbor is valid and unvisited, mark it visited and push it into the queue with incremented distance.
5. Continue until all reachable cells are processed.
6. Return the 'distance' matrix.

Time Complexity: O(N*M), where N = number of rows, M = number of columns
  - Each cell is processed at most once.

Space Complexity: O(N*M)
  - For 'visited' and 'distance' matrices + queue storage
*/

class Solution 
{
public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // Distance matrix to store minimum distance to nearest 1
        vector<vector<int>> distance(rows, vector<int>(cols, 0));

        // Visited matrix to track processed cells
        vector<vector<int>> visited(rows, vector<int>(cols, 0));

        // Queue to perform BFS, stores {{row, col}, distance_from_1}
        queue<pair<pair<int,int>, int>> bfsQueue;

        // Step 1: Initialize BFS with all cells containing 1
        for(int r = 0; r < rows; r++) 
        {
            for(int c = 0; c < cols; c++) 
            {
                if(grid[r][c] == 1) 
                {
                    bfsQueue.push({{r, c}, 0}); // Push coordinates with distance 0
                    visited[r][c] = 1;          // Mark as visited
                }
            }
        }

        // Direction vectors for 4 neighbors: up, right, down, left
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        // Step 2: BFS traversal
        while(!bfsQueue.empty()) 
        {
            int currentRow = bfsQueue.front().first.first;
            int currentCol = bfsQueue.front().first.second;
            int currentDistance = bfsQueue.front().second;
            bfsQueue.pop();

            distance[currentRow][currentCol] = currentDistance;

            // Explore 4 neighbors
            for(int i = 0; i < 4; i++) 
            {
                int neighborRow = currentRow + dRow[i];
                int neighborCol = currentCol + dCol[i];

                // Check if neighbor is inside grid and unvisited
                if(neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols
                   && visited[neighborRow][neighborCol] == 0) 
                {
                    visited[neighborRow][neighborCol] = 1;
                    bfsQueue.push({{neighborRow, neighborCol}, currentDistance + 1});
                }
            }
        }

        return distance; // Return final distance matrix
    }
};

// Driver code to test the Solution class
int main() 
{
    Solution sol;

    vector<vector<int>> grid = {
        {0, 0, 1},
        {0, 1, 0},
        {0, 0, 0}
    };

    vector<vector<int>> result = sol.nearest(grid);

    cout << "Distance matrix:\n";
    for(auto &row : result) 
    {
        for(auto &val : row) 
            cout << val << " ";
        cout << "\n";
    }

    return 0;
}
