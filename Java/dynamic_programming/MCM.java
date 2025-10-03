/*
 * Matrix Chain Multiplication (MCM) Algorithm
 * 
 * Description:
 * Given a sequence of matrices, the goal of Matrix Chain Multiplication is to find
 * the most efficient way to multiply these matrices together. The problem is not to
 * perform the multiplications, but to decide the order in which to multiply the matrices
 * so that the total number of scalar multiplications is minimized.
 * 
 * Approach:
 * - We use dynamic programming with a 2D dp table.
 * - dp[i][j] will store the minimum cost of multiplying matrices from i to j.
 * - For each possible length of the chain, compute the optimal cost by splitting
 *   at different positions k and taking the minimum.
 * - Final answer is stored in dp[1][n-1].
 * 
 * Time Complexity: O(n^3), where n is the number of matrices
 * Space Complexity: O(n^2) for the DP table
 */

import java.util.*;

class Solution {
    // Function to find minimum multiplication cost
    public int matrixChainOrder(int[] arr) {
        int n = arr.length;
        int[][] dp = new int[n][n];

        // dp[i][i] = 0 because a single matrix needs no multiplication
        for (int i = 1; i < n; i++) {
            dp[i][i] = 0;
        }

        // L is the chain length
        for (int L = 2; L < n; L++) {
            for (int i = 1; i < n - L + 1; i++) {
                int j = i + L - 1;
                dp[i][j] = Integer.MAX_VALUE;

                // Try all possible splits
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j];
                    dp[i][j] = Math.min(dp[i][j], cost);
                }
            }
        }

        return dp[1][n-1];
    }
}

public class MCM {
    public static void main(String[] args) {
        Solution sol = new Solution();

        // Test Case 1: Basic example
        System.out.println("Test Case 1:");
        int[] arr1 = {40, 20, 30, 10, 30};
        System.out.println("Dimensions: " + Arrays.toString(arr1));
        System.out.println("Minimum Multiplications: " + sol.matrixChainOrder(arr1));
        System.out.println();

        // Test Case 2: Another sequence
        System.out.println("Test Case 2:");
        int[] arr2 = {10, 20, 30};
        System.out.println("Dimensions: " + Arrays.toString(arr2));
        System.out.println("Minimum Multiplications: " + sol.matrixChainOrder(arr2));
        System.out.println();

        // Test Case 3: Larger sequence
        System.out.println("Test Case 3:");
        int[] arr3 = {10, 20, 30, 40, 30};
        System.out.println("Dimensions: " + Arrays.toString(arr3));
        System.out.println("Minimum Multiplications: " + sol.matrixChainOrder(arr3));
        System.out.println();

        // Test Case 4: Two matrices only
        System.out.println("Test Case 4:");
        int[] arr4 = {10, 20};
        System.out.println("Dimensions: " + Arrays.toString(arr4));
        System.out.println("Minimum Multiplications: " + sol.matrixChainOrder(arr4));
    }
}
