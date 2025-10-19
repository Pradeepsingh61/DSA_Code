package Java.algorithms.matrix;

import java.util.*;

public class NQueens {
    static List<List<String>> res = new ArrayList<>();

    public static List<List<String>> solveNQueens(int n) {
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');
        solve(board, 0);
        return res;
    }

    static void solve(char[][] board, int row) {
        if (row == board.length) {
            List<String> temp = new ArrayList<>();
            for (char[] r : board) temp.add(new String(r));
            res.add(temp);
            return;
        }
        for (int col = 0; col < board.length; col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 'Q';
                solve(board, row + 1);
                board[row][col] = '.';
            }
        }
    }

    static boolean isSafe(char[][] board, int row, int col) {
        for (int i = 0; i < row; i++)
            if (board[i][col] == 'Q') return false;

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q') return false;

        for (int i = row - 1, j = col + 1; i >= 0 && j < board.length; i--, j++)
            if (board[i][j] == 'Q') return false;

        return true;
    }

    public static void main(String[] args) {
        List<List<String>> solutions = solveNQueens(4);
        for (List<String> s : solutions) {
            for (String row : s) System.out.println(row);
            System.out.println();
        }
    }
}
