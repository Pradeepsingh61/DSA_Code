/*
 * Algorithm Name: Search a 2D Matrix
 * Programming Language: Java
 * Category: Matrix, Binary Search
 * Difficulty Level: Medium
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Efficiently searches for a value in an m x n matrix where each row is sorted
 * left to right, and the first element of each row is greater than the last
 * element of the previous row. This implementation uses binary search.
 *
 * Time Complexity: O(log(m*n))
 * Space Complexity: O(1)
 */
// package DSA_Code.Java.algorithms.matrix;

import java.util.Scanner;
import java.util.Arrays;

public class Search2DMatrix {

    public static boolean searchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return false;
        }

        int m = matrix.length;
        int n = matrix[0].length;

        int left = 0;
        int right = m * n - 1; // Treat the matrix as a flattened 1D array

        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Convert the 1D mid-point back to 2D coordinates
            int midRow = mid / n;
            int midCol = mid % n;
            int midValue = matrix[midRow][midCol];

            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of rows: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int n = sc.nextInt();

        int[][] matrix = new int[m][n];

        System.out.println("Enter sorted matrix elements:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sc.nextInt();
            }
        }
        
        System.out.print("\nEnter the target value to search for: ");
        int target = sc.nextInt();

        System.out.println("\nOriginal Matrix:");
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }

        // Apply the algorithm
        boolean found = searchMatrix(matrix, target);

        if (found) {
            System.out.println("\nTarget " + target + " was found in the matrix. ✅");
        } else {
            System.out.println("\nTarget " + target + " was not found in the matrix. ❌");
        }

        sc.close();
    }
}