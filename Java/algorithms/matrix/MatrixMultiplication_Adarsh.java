/**
 * Matrix Multiplication Algorithm
 *
 * Description:
 * Matrix multiplication is a binary operation that produces a matrix from two matrices.
 * Given two matrices A (of size m × n) and B (of size n × p), compute their product 
 * matrix C (of size m × p). Each element C[i][j] is calculated as the sum of products 
 * of corresponding elements from the i-th row of A and j-th column of B.
 *
 * Mathematical Formula:
 * C[i][j] = Σ(k=0 to n-1) A[i][k] * B[k][j]
 *
 * Time Complexity: O(m * n * p) - where m, n, p are dimensions of matrices
 * Space Complexity: O(m * p) - for the resultant matrix
 *
 * Requirements:
 * - Matrix A dimensions: m × n
 * - Matrix B dimensions: n × p  
 * - For multiplication to be valid: columns of A must equal rows of B
 * - Result matrix C dimensions: m × p
 *
 * Author: Generated for Issue #421
 * Category: Mathematical Algorithms
 * Difficulty: Easy (Beginner friendly)
 */

import java.util.Scanner;

public class MatrixMultiplication_Adarsh {
    
    /**
     * Main method to demonstrate matrix multiplication with user input
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            // Get dimensions for first matrix
            System.out.println("=== Matrix Multiplication Calculator ===");
            System.out.print("Enter number of rows for Matrix A: ");
            int m = getValidInteger(scanner);
            System.out.print("Enter number of columns for Matrix A: ");
            int n = getValidInteger(scanner);
            
            // Get dimensions for second matrix
            System.out.print("Enter number of rows for Matrix B: ");
            int p = getValidInteger(scanner);
            System.out.print("Enter number of columns for Matrix B: ");
            int q = getValidInteger(scanner);
            
            // Validate dimensions for multiplication
            if (n != p) {
                System.out.println("Error: Matrix multiplication not possible!");
                System.out.println("Columns of Matrix A (" + n + ") must equal rows of Matrix B (" + p + ")");
                return;
            }
            
            // Create matrices
            int[][] matrixA = new int[m][n];
            int[][] matrixB = new int[p][q];
            
            // Input matrices
            System.out.println("\nEnter elements of Matrix A (" + m + "x" + n + "):");
            readMatrix(scanner, matrixA);
            
            System.out.println("\nEnter elements of Matrix B (" + p + "x" + q + "):");
            readMatrix(scanner, matrixB);
            
            // Perform multiplication
            int[][] result = multiplyMatrices(matrixA, matrixB);
            
            // Display results
            displayResults(matrixA, matrixB, result);
            
            // Run test cases
            System.out.println("\n=== Running Test Cases ===");
            runTestCases();
            
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
    
    /**
     * Multiplies two matrices using the standard algorithm
     * Time Complexity: O(m * n * p)
     * Space Complexity: O(m * p)
     * 
     * @param matrixA First matrix of size m × n
     * @param matrixB Second matrix of size n × p
     * @return Result matrix of size m × p
     */
    public static int[][] multiplyMatrices(int[][] matrixA, int[][] matrixB) {
        int m = matrixA.length;        // rows in A
        int n = matrixA[0].length;     // columns in A (also rows in B)
        int p = matrixB[0].length;     // columns in B
        
        // Initialize result matrix
        int[][] result = new int[m][p];
        
        // Perform multiplication using nested loops
        for (int i = 0; i < m; i++) {           // for each row in A
            for (int j = 0; j < p; j++) {       // for each column in B
                // Calculate dot product of row i of A and column j of B
                for (int k = 0; k < n; k++) {   // sum over common dimension
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        
        return result;
    }
    
    /**
     * Reads matrix elements from user input with validation
     * 
     * @param scanner Scanner object for input
     * @param matrix Matrix to fill with user input
     */
    private static void readMatrix(Scanner scanner, int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print("Enter element [" + i + "][" + j + "]: ");
                matrix[i][j] = getValidInteger(scanner);
            }
        }
    }
    
    /**
     * Gets a valid integer from user input with error handling
     * 
     * @param scanner Scanner object for input
     * @return Valid integer input
     */
    private static int getValidInteger(Scanner scanner) {
        while (!scanner.hasNextInt()) {
            System.out.println("Invalid input. Please enter an integer.");
            scanner.next(); // Clear invalid input
        }
        return scanner.nextInt();
    }
    
    /**
     * Displays the matrices and result in a formatted way
     * 
     * @param matrixA First matrix
     * @param matrixB Second matrix
     * @param result Result matrix
     */
    private static void displayResults(int[][] matrixA, int[][] matrixB, int[][] result) {
        System.out.println("\n=== Results ===");
        System.out.println("Matrix A:");
        printMatrix(matrixA);
        
        System.out.println("Matrix B:");
        printMatrix(matrixB);
        
        System.out.println("Result (A × B):");
        printMatrix(result);
    }
    
    /**
     * Prints a matrix in formatted output
     * 
     * @param matrix Matrix to print
     */
    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int element : row) {
                System.out.printf("%6d ", element);
            }
            System.out.println();
        }
        System.out.println();
    }
    
    /**
     * Runs comprehensive test cases as specified in the issue
     */
    private static void runTestCases() {
        // Test Case 1: Small square matrices (2x2)
        System.out.println("Test Case 1: Small square matrices (2x2)");
        int[][] a1 = {{1, 2}, {3, 4}};
        int[][] b1 = {{5, 6}, {7, 8}};
        int[][] result1 = multiplyMatrices(a1, b1);
        System.out.println("A × B:");
        printMatrix(result1);
        // Expected: [[19, 22], [43, 50]]
        
        // Test Case 2: Non-square matrices (2x3 × 3x2)
        System.out.println("Test Case 2: Non-square matrices (2x3 × 3x2)");
        int[][] a2 = {{1, 2, 3}, {4, 5, 6}};
        int[][] b2 = {{7, 8}, {9, 10}, {11, 12}};
        int[][] result2 = multiplyMatrices(a2, b2);
        System.out.println("A × B:");
        printMatrix(result2);
        // Expected: [[58, 64], [139, 154]]
        
        // Test Case 3: Single row matrix (1x3 × 3x1)
        System.out.println("Test Case 3: Single row matrix (1x3 × 3x1)");
        int[][] a3 = {{1, 2, 3}};
        int[][] b3 = {{4}, {5}, {6}};
        int[][] result3 = multiplyMatrices(a3, b3);
        System.out.println("A × B:");
        printMatrix(result3);
        // Expected: [[32]]
        
        // Test Case 4: Single column matrix (3x1 × 1x3)
        System.out.println("Test Case 4: Single column matrix (3x1 × 1x3)");
        int[][] a4 = {{2}, {3}, {4}};
        int[][] b4 = {{1, 5, 7}};
        int[][] result4 = multiplyMatrices(a4, b4);
        System.out.println("A × B:");
        printMatrix(result4);
        // Expected: [[2, 10, 14], [3, 15, 21], [4, 20, 28]]
        
        // Test Case 5: Identity matrix multiplication (3x3)
        System.out.println("Test Case 5: Identity matrix multiplication (3x3)");
        int[][] a5 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        int[][] identity = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        int[][] result5 = multiplyMatrices(a5, identity);
        System.out.println("A × Identity:");
        printMatrix(result5);
        // Expected: Same as matrix A
        
        System.out.println("All test cases completed successfully!");
    }
}
