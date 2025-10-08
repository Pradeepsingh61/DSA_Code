/*
 * Algorithm Name: Number of Islands
 * Programming Language: Java
 * Category: Matrix, Graph, Depth-First Search (DFS)
 * Difficulty Level: Medium
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water),
 * this algorithm returns the number of islands. An island is surrounded by water and is
 * formed by connecting adjacent lands horizontally or vertically.
 *
 * Time Complexity: O(m*n) - We visit each cell in the grid at most twice.
 * Space Complexity: O(m*n) - In the worst case (a grid full of land), the recursion
 * stack for DFS could go as deep as the number of cells.
 */
// package DSA_Code.Java.algorithms.matrix;

import java.util.Scanner;

public class NumberOfIslands {

    /**
     * Main function to count the number of islands.
     */
    public static int numIslands(char[][] grid) {
        if (grid == null || grid.length == 0) {
            return 0;
        }

        int m = grid.length;
        int n = grid[0].length;
        int islandCount = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find a '1', it's a new island.
                // Increment count and sink the island with DFS.
                if (grid[i][j] == '1') {
                    islandCount++;
                    dfs(grid, i, j);
                }
            }
        }
        return islandCount;
    }

    /**
     * Helper DFS function to find and "sink" all parts of an island.
     */
    private static void dfs(char[][] grid, int r, int c) {
        int m = grid.length;
        int n = grid[0].length;

        // Base cases for stopping recursion:
        // 1. Out of bounds (row or column)
        // 2. Current cell is water ('0')
        if (r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == '0') {
            return;
        }

        // Sink the current part of the island by changing it to '0'
        grid[r][c] = '0';

        // Recursively call DFS for all 4 adjacent cells
        dfs(grid, r + 1, c); // down
        dfs(grid, r - 1, c); // up
        dfs(grid, r, c + 1); // right
        dfs(grid, r, c - 1); // left
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of rows: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int n = sc.nextInt();

        char[][] grid = new char[m][n];

        System.out.println("Enter grid elements ('1' for land, '0' for water):");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = sc.next().charAt(0);
            }
        }

        System.out.println("\nOriginal Grid:");
        for (char[] row : grid) {
            for (char cell : row) {
                System.out.print(cell + " ");
            }
            System.out.println();
        }

        // Apply the algorithm
        int count = numIslands(grid);

        System.out.println("\nNumber of islands found: " + count + " 🏞️");

        sc.close();
    }
}