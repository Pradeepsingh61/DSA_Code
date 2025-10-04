/*
 * Algorithm Name: Matrix Transpose
 * Programming Language: Java
 * Category: Matrix
 * Difficulty Level: Easy
 *
 * Author: Revant Singh
 *
 * Algorithm Description:
 * Transpose a given m x n matrix. Flip the matrix over its diagonal.
 *
 * Time Complexity: O(m*n)
 * Space Complexity: O(m*n)
 */
package DSA_Code.Java.algorithms.matrix;
import java.util.Scanner;

public class MatrixTranspose {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of rows: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int n = sc.nextInt();

        int[][] matrix = new int[m][n];
        int[][] transpose = new int[n][m];

        System.out.println("Enter matrix elements:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sc.nextInt();
            }
        }

        // Transpose logic
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                transpose[j][i] = matrix[i][j];
            }
        }

        System.out.println("Transposed Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(transpose[i][j] + " ");
            }
            System.out.println();
        }

        sc.close();
    }
}
