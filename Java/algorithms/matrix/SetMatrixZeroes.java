/*
 * Algorithm Name: Set Matrix Zeroes
 * Programming Language: Java
 * Category: Matrix
 * Difficulty Level: Medium
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Given an m x n matrix, if an element is 0, set its entire row and column to 0.
 * This implementation does it in-place using O(1) extra space.
 *
 * Time Complexity: O(m*n)
 * Space Complexity: O(1)
 */
// package DSA_Code.Java.algorithms.matrix;

import java.util.Scanner;

public class SetMatrixZeroes {

    public static void setZeroes(int[][] matrix) {
        if (matrix == null || matrix.length == 0) {
            return;
        }

        int m = matrix.length;
        int n = matrix[0].length;

        boolean isFirstRowZero = false;
        boolean isFirstColZero = false;

        // 1. Check if the first column has any zeroes
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                isFirstColZero = true;
                break;
            }
        }

        // 2. Check if the first row has any zeroes
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                isFirstRowZero = true;
                break;
            }
        }

        // 3. Use the first row and column as markers for the rest of the matrix
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 4. Set elements to zero based on the markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 5. Set the first row to zero if needed
        if (isFirstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // 6. Set the first column to zero if needed
        if (isFirstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }

    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of rows: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int n = sc.nextInt();

        int[][] matrix = new int[m][n];

        System.out.println("Enter matrix elements:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sc.nextInt();
            }
        }

        System.out.println("\nOriginal Matrix:");
        printMatrix(matrix);

        // Apply the algorithm
        setZeroes(matrix);

        System.out.println("\nMatrix after setting zeroes:");
        printMatrix(matrix);

        sc.close();
    }
}