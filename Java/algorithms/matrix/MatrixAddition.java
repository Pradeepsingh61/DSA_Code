import java.util.Scanner;

public class MatrixAdd {
    public static void main(String[] args) {
        // Check if N is provided as a command line argument
        if (args.length != 1) {
            System.out.println("Please provide the value of N as a command line argument.");
            return;
        }

        int N = 0;

        // Parse the command line argument and validate it
        try {
            N = Integer.parseInt(args[0]);
            if (N <= 0) {
                System.out.println("N must be a positive integer.");
                return;
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input for N. Please enter an integer.");
            return;
        }

        int[][] matrix1 = new int[N][N];
        int[][] matrix2 = new int[N][N];

        Scanner scanner = new Scanner(System.in);

        // Read the first matrix
        System.out.println("Enter the elements of Matrix 1:");
        readMatrix(scanner, matrix1);

        // Read the second matrix
        System.out.println("Enter the elements of Matrix 2:");
        readMatrix(scanner, matrix2);

        // Perform matrix addition
        int[][] result = addMatrices(matrix1, matrix2);

        // Display the matrices and the result
        printMatrix(matrix1);
        System.out.println("+");
        printMatrix(matrix2);
        System.out.println("=");
        printMatrix(result);

        scanner.close(); // Close the scanner
    }

    // Method to read a matrix from the user
    private static void readMatrix(Scanner scanner, int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print("Enter element [" + i + "][" + j + "]: ");
                while (!scanner.hasNextInt()) {
                    System.out.println("Invalid input. Please enter an integer.");
                    scanner.next(); // Clear the invalid input
                    System.out.print("Enter element [" + i + "][" + j + "]: ");
                }
                matrix[i][j] = scanner.nextInt();
            }
        }
    }

    // Method to add two matrices
    private static int[][] addMatrices(int[][] matrix1, int[][] matrix2) {
        int N = matrix1.length;
        int[][] result = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return result;
    }

    // Method to print a matrix
    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int num : row) {
                System.out.print(num + "\t");
            }
            System.out.println();
        }
        System.out.println();
    }
}
