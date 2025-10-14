/*
 * Algorithm Name: Diagonal Traversal (Zig-Zag)
 * Programming Language: Java
 * Category: Matrix
 * Difficulty Level: Medium
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Given an m x n matrix, return all elements of the matrix in diagonal order.
 * The traversal moves in a zig-zag pattern: up-right, then down-left, and so on.
 *
 * Time Complexity: O(m*n) - Each element is visited exactly once.
 * Space Complexity: O(m*n) - To store the resulting array. O(1) if printing directly.
 */

import java.util.Scanner;
import java.util.Arrays;

public class DiagonalTraversal {

    public static int[] findDiagonalOrder(int[][] matrix) {
        if (matrix == null || matrix.length == 0) {
            return new int[0];
        }

        int m = matrix.length;
        int n = matrix[0].length;
        int[] result = new int[m * n];
        int index = 0;
        
        // There are a total of (m + n - 1) diagonals
        for (int d = 0; d < m + n - 1; d++) {
            // d is the sum of row + col
            
            if (d % 2 == 0) { // Even diagonals: Traverse up-right
                // Find the starting head of the diagonal
                int row = (d < m) ? d : m - 1;
                int col = d - row;

                while (row >= 0 && col < n) {
                    result[index++] = matrix[row][col];
                    row--;
                    col++;
                }
            } else { // Odd diagonals: Traverse down-left
                // Find the starting head of the diagonal
                int col = (d < n) ? d : n - 1;
                int row = d - col;
                
                while (col >= 0 && row < m) {
                    result[index++] = matrix[row][col];
                    col--;
                    row++;
                }
            }
        }
        return result;
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
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }

        // Apply the algorithm
        int[] diagonalOrder = findDiagonalOrder(matrix);

        System.out.println("\nMatrix in Diagonal Traversal Order:");
        System.out.println(Arrays.toString(diagonalOrder));

        sc.close();
    }
}