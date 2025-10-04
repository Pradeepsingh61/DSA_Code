package DSA_Code.Java.dynamic_programming;
/*
File path (suggested): algorithms/dynamic_programming/MinPathSum.java
(If you want to use a package, uncomment the package line below and place the file accordingly)
*/
// package algorithms.dynamic_programming;



/**
 * Algorithm Name : Minimum Path Sum in a Grid
 * Programming Language: Java
 * Category: Dynamic Programming
 * Difficulty Level: Medium
 *
 * Problem Statement:
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right
 * which minimizes the sum of all numbers along its path. You can only move either down or right at any point in time.
 *
 * Requirements:
 * - Input: 2D integer array 'grid'
 * - Output: Minimum path sum from top-left to bottom-right
 *
 * Complexities:
 * - Time Complexity: O(n * m) — we fill each cell once
 * - Space Complexity: O(n * m) — for dp array (can be optimized to O(m) for a rolling array)
 */
import java.util.Arrays;
public class MinPathSum {

    /**
     * Returns the minimum path sum from top-left to bottom-right in the given grid.
     */
    public int minPathSum(int[][] grid) {
        if (grid == null || grid.length == 0 || grid[0].length == 0) return 0;

        int n = grid.length;
        int m = grid[0].length;
        int[][] dp = new int[n][m];

        // Initialize starting point
        dp[0][0] = grid[0][0];

        // Fill first column
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Fill first row
        for (int j = 1; j < m; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // Fill the rest of dp array
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[n - 1][m - 1];
    }

    /** Utility function to print a 2D grid — useful for debugging */
    private static void printGrid(int[][] grid) {
        for (int[] row : grid) {
            System.out.println(Arrays.toString(row));
        }
    }

    /** Sample test cases */
    public static void main(String[] args) {
        MinPathSum solution = new MinPathSum();

        int[][] grid1 = {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
        };
        System.out.println("Minimum Path Sum (grid1): " + solution.minPathSum(grid1)); // Output: 7

        int[][] grid2 = {
            {1, 2, 5},
            {3, 2, 1}
        };
        System.out.println("Minimum Path Sum (grid2): " + solution.minPathSum(grid2)); // Output: 6
    }
}
