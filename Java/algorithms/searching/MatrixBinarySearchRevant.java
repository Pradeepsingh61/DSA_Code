

/*
File path (suggested): algorithms/searching/MatrixBinarySearchRevant.java
*/
// package algorithms.searching;


/**
 * Algorithm Name: Search in 2D Matrix
 * Programming Language: Java
 * Class Name: MatrixBinarySearchRevant
 * Category: Searching
 * Difficulty Level: Medium
 *
 * Problem Statement:
 * Given a 2D matrix where each row is sorted and the first element of each row
 * is greater than the last element of the previous row, implement binary search
 * to determine if a target value exists in the matrix.
 *
 * Requirements:
 * - Input: 2D integer array 'matrix', integer 'target'
 * - Output: true if target exists in matrix, false otherwise
 *
 * Time Complexity: O(log(m * n)) where m = number of rows, n = number of columns
 * Space Complexity: O(1)
 */

package algorithms.searching;
import java.util.Arrays;
public class MatrixBinarySearchRevant {

    /**
     * Searches for target in 2D matrix using binary search.
     */
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return false; // Handle empty matrix
        }

        int m = matrix.length;
        int n = matrix[0].length;

        int low = 0;
        int high = m * n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int midValue = matrix[mid / n][mid % n];

            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

    /**
     * Sample test cases to validate the implementation.
     */
    public static void main(String[] args) {
        MatrixBinarySearchRevant searcher = new MatrixBinarySearchRevant();

        int[][] matrix1 = {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
        };
        System.out.println("Searching 3: " + searcher.searchMatrix(matrix1, 3)); // true
        System.out.println("Searching 13: " + searcher.searchMatrix(matrix1, 13)); // false

        int[][] matrix2 = {
            {1}
        };
        System.out.println("Searching 1: " + searcher.searchMatrix(matrix2, 1)); // true
        System.out.println("Searching 2: " + searcher.searchMatrix(matrix2, 2)); // false
    }
}

