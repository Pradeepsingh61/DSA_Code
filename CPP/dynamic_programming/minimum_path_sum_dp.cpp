// The "Minimum Path Sum" problem is a classic dynamic programming exercise. The goal is to find a path with the smallest sum of numbers from the top-left to the bottom-right corner of a grid. You can only move either down or right at any point. 

#include <vector>
#include <algorithm> // For std::min
#include <iostream>  // For input/output

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (n == 0) return 0;

        // Create a DP table to store minimum path sums
        std::vector<std::vector<int>> dp(m, std::vector<int>(n));

        // Base case: The first cell's minimum path sum is its own value
        dp[0][0] = grid[0][0];

        // Fill the first row
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // Fill the first column
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Fill the rest of the DP table
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        // The minimum path sum to the bottom-right corner
        return dp[m - 1][n - 1];
    }
};

int main() {
    Solution sol;

    // Test Case 1
    std::vector<std::vector<int>> grid1 = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    std::cout << "Minimum Path Sum for grid1: " << sol.minPathSum(grid1) << std::endl; // Expected: 7

    // Test Case 2
    std::vector<std::vector<int>> grid2 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::cout << "Minimum Path Sum for grid2: " << sol.minPathSum(grid2) << std::endl; // Expected: 12

    // Test Case 3 (Edge case: single cell)
    std::vector<std::vector<int>> grid3 = {
        {7}
    };
    std::cout << "Minimum Path Sum for grid3: " << sol.minPathSum(grid3) << std::endl; // Expected: 7

    // Test Case 4 (Edge case: empty grid)
    std::vector<std::vector<int>> grid4 = {};
    std::cout << "Minimum Path Sum for grid4: " << sol.minPathSum(grid4) << std::endl; // Expected: 0

    return 0;
}