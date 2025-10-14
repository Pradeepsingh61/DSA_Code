/*
 * Algorithm Name: Word Search
 * Programming Language: Java
 * Category: Matrix, Backtracking, Depth-First Search (DFS)
 * Difficulty Level: Hard
 *
 * Author: Ojasvi Bakshi
 *
 * Algorithm Description:
 * Given an m x n grid of characters and a string "word", this algorithm returns true
 * if the word exists in the grid. The word can be constructed from letters of sequentially
 * adjacent cells, where "adjacent" cells are horizontally or vertically neighboring.
 * The same letter cell may not be used more than once.
 *
 * Time Complexity: O(N * 3^L), where N is the number of cells and L is the length
 * of the word. For each cell, we branch out, but we don't go back, so there are 3 choices.
 * Space Complexity: O(L) for the recursion stack depth.
 */
package DSA_Code.Java.algorithms.matrix;

import java.util.Scanner;

public class WordSearch {

    public static boolean exist(char[][] board, String word) {
        if (board == null || board.length == 0 || word == null || word.length() == 0) {
            return false;
        }

        int m = board.length;
        int n = board[0].length;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Start the search only if the first character matches
                if (board[i][j] == word.charAt(0)) {
                    if (search(board, word, i, j, 0)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    private static boolean search(char[][] board, String word, int r, int c, int index) {
        // Base Case 1: Success - we've found all characters in the word
        if (index == word.length()) {
            return true;
        }

        // Base Case 2: Failure - out of bounds or character mismatch
        if (r < 0 || c < 0 || r >= board.length || c >= board[0].length || board[r][c] != word.charAt(index)) {
            return false;
        }

        // Mark the current cell as visited to avoid reusing it
        char temp = board[r][c];
        board[r][c] = '#';

        // Explore neighbors (up, down, left, right)
        boolean found = search(board, word, r + 1, c, index + 1) ||
                        search(board, word, r - 1, c, index + 1) ||
                        search(board, word, r, c + 1, index + 1) ||
                        search(board, word, r, c - 1, index + 1);

        // Backtrack: un-mark the cell, restoring it for other paths
        board[r][c] = temp;

        return found;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of rows: ");
        int m = sc.nextInt();
        System.out.print("Enter number of columns: ");
        int n = sc.nextInt();

        char[][] board = new char[m][n];

        System.out.println("Enter grid characters:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = sc.next().charAt(0);
            }
        }
        
        System.out.print("\nEnter the word to search for: ");
        String word = sc.next();

        System.out.println("\nOriginal Grid:");
        for (char[] row : board) {
            for (char cell : row) {
                System.out.print(cell + " ");
            }
            System.out.println();
        }

        // Apply the algorithm
        boolean found = exist(board, word);

        if (found) {
            System.out.println("\nThe word \"" + word + "\" was found in the grid. ✅");
        } else {
            System.out.println("\nThe word \"" + word + "\" was not found in the grid. ❌");
        }

        sc.close();
    }
}