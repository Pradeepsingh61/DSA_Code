/*
 * Algorithm Name: Valid Sudoku
 * Programming Language: Java
 * Category: Matrix, Hashing
 * Difficulty Level: Medium
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Determines if a 9x9 Sudoku board is valid. The validation checks for uniqueness
 * of digits (1-9) in each row, each column, and each of the nine 3x3 sub-grids.
 * Empty cells are represented by '.'.
 *
 * Time Complexity: O(N^2), where N=9. We iterate through the 9x9 board a constant number of times.
 * Space Complexity: O(N), where N=9. The space is used for the HashSet.
 */
package DSA_Code.Java.algorithms.matrix;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class ValidSudoku {

    public static boolean isValidSudoku(char[][] board) {
        // Check 1: Validate each row
        for (int i = 0; i < 9; i++) {
            Set<Character> rowSet = new HashSet<>();
            for (int j = 0; j < 9; j++) {
                char cell = board[i][j];
                if (cell != '.') {
                    if (rowSet.contains(cell)) {
                        return false; // Duplicate found
                    }
                    rowSet.add(cell);
                }
            }
        }

        // Check 2: Validate each column
        for (int j = 0; j < 9; j++) {
            Set<Character> colSet = new HashSet<>();
            for (int i = 0; i < 9; i++) {
                char cell = board[i][j];
                if (cell != '.') {
                    if (colSet.contains(cell)) {
                        return false; // Duplicate found
                    }
                    colSet.add(cell);
                }
            }
        }

        // Check 3: Validate each 3x3 sub-box
        for (int boxRow = 0; boxRow < 9; boxRow += 3) {
            for (int boxCol = 0; boxCol < 9; boxCol += 3) {
                Set<Character> boxSet = new HashSet<>();
                for (int i = boxRow; i < boxRow + 3; i++) {
                    for (int j = boxCol; j < boxCol + 3; j++) {
                        char cell = board[i][j];
                        if (cell != '.') {
                            if (boxSet.contains(cell)) {
                                return false; // Duplicate found
                            }
                            boxSet.add(cell);
                        }
                    }
                }
            }
        }
        
        return true; // All checks passed
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[][] board = new char[9][9];

        System.out.println("Enter the 9x9 Sudoku board (use '.' for empty cells):");
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = sc.next().charAt(0);
            }
        }

        System.out.println("\nSudoku Board:");
        for (char[] row : board) {
            for (char cell : row) {
                System.out.print(cell + " ");
            }
            System.out.println();
        }

        boolean isValid = isValidSudoku(board);

        if (isValid) {
            System.out.println("\nThis Sudoku board is valid. ✅");
        } else {
            System.out.println("\nThis Sudoku board is invalid. ❌");
        }

        sc.close();
    }
}