/*
 * Algorithm Name
Matrix Multiplication

Programming Language
Java

Category
Algorithms / Matrix Operations

Difficulty Level
Easy to Medium

* Algorithm Description : 

1. Problem it solves:
-> Computes the product of two matrices A (m x n) and B (n x p), resulting in matrix C (m x p).

2. Approach / Idea:
-> Use three nested loops:
   - Outer loop for rows of A
   - Middle loop for columns of B
   - Inner loop to compute sum of products of corresponding elements
-> Store the results in a new matrix C.

3. Complexity:
Time: O(m * n * p) where m = rows of A, n = columns of A / rows of B, p = columns of B
Space: O(m * p) for storing the result matrix

* Author: Revant Singh
*/
package DSA_Code.Java.algorithms.matrix;
import java.util.Scanner;

public class MatrixMultiplication {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input dimensions of first matrix
        System.out.print("Enter number of rows for matrix A: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns for matrix A: ");
        int n = sc.nextInt();

        // Input dimensions of second matrix
        System.out.print("Enter number of columns for matrix B: ");
        int p = sc.nextInt();

        int[][] A = new int[m][n];
        int[][] B = new int[n][p];

        // Input matrix A
        System.out.println("Enter elements of matrix A:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = sc.nextInt();
            }
        }

        // Input matrix B
        System.out.println("Enter elements of matrix B:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                B[i][j] = sc.nextInt();
            }
        }

        // Multiply matrices
        int[][] C = multiplyMatrices(A, B, m, n, p);

        // Display result
        System.out.println("Resultant Matrix C (A x B):");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                System.out.print(C[i][j] + " ");
            }
            System.out.println();
        }

        sc.close();
    }

    // Function to multiply matrices
    static int[][] multiplyMatrices(int[][] A, int[][] B, int m, int n, int p) {
        int[][] C = new int[m][p];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }
}
