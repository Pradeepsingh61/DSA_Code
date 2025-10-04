/*
File path (suggested): algorithms/matrix/SearchIn2DMatrix.java
(If you want to use a package, uncomment the package line below and place the file accordingly)
*/
// package algorithms.matrix;

/**
 * Algorithm Name : Search in 2D Matrix (LeetCode 74 style)
 * Programming Language: Java
 * Category: Matrix / Binary Search
 * Difficulty Level: Medium
 *
 * Problem Statement:
 * You are given an m x n matrix where each row is sorted in ascending order 
 * from left to right, and the first integer of each row is greater than the 
 * last integer of the previous row. Given an integer target, return true 
 * if target is in the matrix or false otherwise.
 *
 * Example:
 * Input: 
 * matrix = [
 *   [1, 3, 5, 7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 60]
 * ], target = 3
 * Output: true
 *
 * Approach:
 * - Treat the 2D matrix as a flattened 1D sorted array of size (m * n).
 * - Perform standard binary search on indices [0, m*n - 1].
 * - Convert 1D mid index into (row, col) using:
 *      row = mid / n
 *      col = mid % n
 * - Compare matrix[row][col] with target and adjust search space.
 *
 * Time Complexity:
 * - O(log(m * n)) where m = number of rows, n = number of columns.
 *   (Since binary search on m*n elements)
 *
 * Space Complexity:
 * - O(1), as no extra space is used apart from variables.
 */
public class SearchIn2DMatrix {

    /**
     * Searches for the target value in the given 2D matrix.
     */
    public boolean searchMatrix(int[][] matrix, int target) {
        // Edge case: empty matrix
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return false;
        }

        int m = matrix.length;       // number of rows
        int n = matrix[0].length;    // number of columns

        int low = 0, high = m * n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int value = matrix[mid / n][mid % n]; // map mid -> (row, col)

            if (value == target) {
                return true;
            } else if (value < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

    /** Driver code to test the implementation */
    public static void main(String[] args) {
        SearchIn2DMatrix solver = new SearchIn2DMatrix();

        int[][] matrix = {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60}
        };

        // Test cases
        System.out.println(solver.searchMatrix(matrix, 3));   // true
        System.out.println(solver.searchMatrix(matrix, 13));  // false
        System.out.println(solver.searchMatrix(matrix, 60));  // true
    }
}
