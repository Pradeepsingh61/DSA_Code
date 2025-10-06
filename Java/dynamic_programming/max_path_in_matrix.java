
/*
    Description: Maximum Path in Matrix

    From any cell in the first row, move to either:
        → directly below
        → diagonally left below
        → diagonally right below
    Collect values along the path. Find maximum sum path to the last row.
*/

public class max_path_in_matrix {

    // -----------------------------------------------------------
    //  1. BRUTE FORCE (Recursive)
    // -----------------------------------------------------------
    // Idea:
    // For each cell, try all 3 possible moves in the next row.
    // Return maximum path sum recursively.
    //
    // Time Complexity: O(3^(m*n)) — exponential
    // Space Complexity: O(m) — recursion stack
    public static int maxPathBrute(int[][] matrix, int i, int j) {
        int m = matrix.length;
        int n = matrix[0].length;

        // Out of bounds
        if (j < 0 || j >= n) return Integer.MIN_VALUE;

        // Base case: last row
        if (i == m - 1) return matrix[i][j];

        // Move to 3 possible directions
        int down = maxPathBrute(matrix, i + 1, j);
        int downLeft = maxPathBrute(matrix, i + 1, j - 1);
        int downRight = maxPathBrute(matrix, i + 1, j + 1);

        return matrix[i][j] + Math.max(down, Math.max(downLeft, downRight));
    }

    // Wrapper for brute force
    public static int maxPathBrute(int[][] matrix) {
        int maxSum = Integer.MIN_VALUE;
        for (int j = 0; j < matrix[0].length; j++) {
            maxSum = Math.max(maxSum, maxPathBrute(matrix, 0, j));
        }
        return maxSum;
    }

    // -----------------------------------------------------------
    //  2. DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------
    // Idea:
    // dp[i][j] = maximum sum to reach cell (i,j)
    // dp[i][j] = matrix[i][j] + max(dp[i-1][j], dp[i-1][j-1], dp[i-1][j+1])
    //
    // Time Complexity: O(m*n)
    // Space Complexity: O(m*n)
    public static int maxPathDP(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;

        int[][] dp = new int[m][n];

        // Copy first row
        for (int j = 0; j < n; j++) dp[0][j] = matrix[0][j];

        // Fill DP table
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int up = dp[i - 1][j];
                int upLeft = (j > 0) ? dp[i - 1][j - 1] : Integer.MIN_VALUE;
                int upRight = (j < n - 1) ? dp[i - 1][j + 1] : Integer.MIN_VALUE;

                dp[i][j] = matrix[i][j] + Math.max(up, Math.max(upLeft, upRight));
            }
        }

        // Max in last row
        int maxSum = Integer.MIN_VALUE;
        for (int j = 0; j < n; j++) {
            maxSum = Math.max(maxSum, dp[m - 1][j]);
        }

        return maxSum;
    }

    // -----------------------------------------------------------
    //  3. SPACE-OPTIMIZED DP
    // -----------------------------------------------------------
    // Only previous row is needed at any time
    // Time Complexity: O(m*n)
    // Space Complexity: O(n)
    public static int maxPathOptimized(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;

        int[] prev = new int[n];
        System.arraycopy(matrix[0], 0, prev, 0, n);

        for (int i = 1; i < m; i++) {
            int[] curr = new int[n];
            for (int j = 0; j < n; j++) {
                int up = prev[j];
                int upLeft = (j > 0) ? prev[j - 1] : Integer.MIN_VALUE;
                int upRight = (j < n - 1) ? prev[j + 1] : Integer.MIN_VALUE;

                curr[j] = matrix[i][j] + Math.max(up, Math.max(upLeft, upRight));
            }
            prev = curr;
        }

        int maxSum = Integer.MIN_VALUE;
        for (int val : prev) maxSum = Math.max(maxSum, val);

        return maxSum;
    }

    // -----------------------------------------------------------
    //  MAIN METHOD (Test all versions)
    // -----------------------------------------------------------
    public static void main(String[] args) {
        int[][] matrix = {
            {10, 10, 2, 0, 20, 4},
            {1, 0, 0, 30, 2, 5},
            {0, 10, 4, 0, 2, 0},
            {1, 0, 2, 20, 0, 4}
        };

        System.out.println("Brute Force Result: " + maxPathBrute(matrix));
        System.out.println("DP Result: " + maxPathDP(matrix));
        System.out.println("Optimized Result: " + maxPathOptimized(matrix));
    }
}
