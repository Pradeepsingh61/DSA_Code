#include <vector>
#include <queue>
#include <algorithm>

/*
 * @brief Trapping Rain Water II
 *
 * @description
 * This algorithm calculates the volume of water that can be trapped in a 2D height map.
 * The approach uses a Breadth-First Search (BFS) starting from the outer boundary cells of the grid.
 * A min-heap (priority queue) is used to always process the cell with the minimum height from the current boundary.
 *
 * We initialize the heap with all border cells. Then, we extract the cell with the minimum height and explore its
 * unvisited neighbors. If a neighbor is lower than the current cell's height (which acts as a boundary wall),
 * it can trap water. The amount of trapped water is the difference between the wall's height and the neighbor's height.
 * The neighbor is then added to the heap, with its effective height for the new boundary being the maximum of its
 * own height and the current wall's height. This process continues until the heap is empty.
 *
 * @complexity
 * Time complexity: O(m * n * log(m * n)), where m and n are the dimensions of the height map.
 * In the worst case, every cell is pushed onto and popped from the min-heap once. Each heap operation
 * takes O(log(k)) time, where k is the number of elements in the heap (at most m*n).
 *
 * Space complexity: O(m * n).
 * The space is dominated by the priority queue and the visited matrix, both of which can store up to m*n elements
 * in the worst case.
 */
class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) {
            return 0;
        }

        int numRows = heightMap.size();
        int numCols = heightMap[0].size();
        
        // A visited matrix to keep track of cells we have processed
        std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));
        
        // A min-heap to store boundary cells, prioritized by height. Structure: {height, row, col}
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> minHeap;

        // Initialize the min-heap with all border cells
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1) {
                    minHeap.push({heightMap[i][j], i, j});
                    visited[i][j] = true;
                }
            }
        }

        int trappedWater = 0;
        // Directions for 4-way BFS (up, down, left, right)
        std::vector<std::vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Process cells from the lowest boundary wall inwards
        while (!minHeap.empty()) {
            std::vector<int> currentCell = minHeap.top();
            minHeap.pop();
            
            int height = currentCell[0];
            int row = currentCell[1];
            int col = currentCell[2];

            // Explore neighbors
            for (const auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];

                // Check if the neighbor is within bounds and not visited
                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {
                    // Mark neighbor as visited
                    visited[newRow][newCol] = true;
                    
                    // Calculate trapped water based on the current boundary height
                    trappedWater += std::max(0, height - heightMap[newRow][newCol]);
                    
                    // Add the new cell to the boundary. The new wall height is the max of the current wall
                    // and the neighbor's own height, ensuring water can't spill over.
                    minHeap.push({std::max(height, heightMap[newRow][newCol]), newRow, newCol});
                }
            }
        }
        
        return trappedWater;
    }
};