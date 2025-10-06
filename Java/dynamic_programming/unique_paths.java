
/*
    Description: Unique Paths

    A robot is located at the top-left corner of an m x n grid.
    The robot can only move either down or right at any point in time.

    The robot is trying to reach the bottom-right corner of the grid.
    How many possible unique paths are there?

    Example:
        Input: m = 3, n = 7
        Output: 28
*/

public class UniquePaths {

    // -----------------------------------------------------------
    //  1. BRUTE FORCE (Recursive)
    // -----------------------------------------------------------
    // Idea:
    // From any cell (i, j), you can move either:
    //   → Right  (i, j+1)
    //   → Down   (i+1, j)
    //
    // So total paths = paths from right + paths from down.
    //
    // Base cases:
    //   - If we reach the last row or last column, there’s only 1 path.
    //
    // Time Complexity: O(2^(m+n))  (exponential)
    // Space Complexity: O(m + n)   (recursion call stack)
    public static int uniquePathsBrute(int m, int n) {
        // Base case: if we are at the bottom or right edge, only one path
        if (m == 1 || n == 1) return 1;

        // Recursive calls: go down and right
        return uniquePathsBrute(m - 1, n) + uniquePathsBrute(m, n - 1);
    }


    // -----------------------------------------------------------
    //  2. OPTIMIZED DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------
    // Idea:
    // Each cell [i][j] represents number of ways to reach that cell.
    // You can come either from the top [i-1][j] or from the left [i][j-1].
    //
    // dp[i][j] = dp[i-1][j] + dp[i][j-1]
    //
    // Base case:
    //   - First row and first column have only 1 way to reach.
    //
    // Time Complexity: O(m * n)
    // Space Complexity: O(m * n)
    public static int uniquePathsDP(int m, int n) {
        int[][] dp = new int[m][n];

        // Fill the first row and first column with 1
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int j = 0; j < n; j++) dp[0][j] = 1;

        // Fill remaining cells using the recurrence relation
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }


    // -----------------------------------------------------------
    //  3. OPTIMIZED (Space-Optimized DP)
    // -----------------------------------------------------------
    // Observation:
    // We only need the previous row to calculate the current row.
    //
    // Use a 1D array instead of 2D.
    //
    // Time Complexity: O(m * n)
    // Space Complexity: O(n)
    public static int uniquePathsOptimized(int m, int n) {
        int[] dp = new int[n];

        // Initialize first row as 1
        for (int j = 0; j < n; j++) dp[j] = 1;

        // Update dp for each subsequent row
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j - 1];
            }
        }

        return dp[n - 1];
    }


    // -----------------------------------------------------------
    //  MAIN METHOD (Test all versions)
    // -----------------------------------------------------------
    public static void main(String[] args) {
        int m = 3, n = 7;  // Example grid size

        System.out.println("Brute Force Result: " + uniquePathsBrute(m, n));
        System.out.println("DP Result: " + uniquePathsDP(m, n));
        System.out.println("Optimized Result: " + uniquePathsOptimized(m, n));
    }
}
