public class Knapsack {

    /**
     * Solves the 0/1 Knapsack problem using Dynamic Programming.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * The 0/1 Knapsack problem is an optimization problem where we are given a set of items,
     * each with a specific weight and value. The goal is to determine which items to include
     * in a collection (a "knapsack") so that the total weight is less than or equal to a
     * given capacity and the total value is maximized. Each item can either be taken
     * completely or not at all (the "0/1" property).
     *
     * DYNAMIC PROGRAMMING APPROACH:
     * We can solve this using a 2D DP table, let's call it `dp`.
     *
     * State Definition:
     * `dp[i][w]` will store the maximum value that can be achieved using the first `i` items
     * with a knapsack of capacity `w`.
     *
     * Recurrence Relation:
     * For each item `i` (from 1 to n) and for each capacity `w` (from 1 to W):
     * We have two choices for the i-th item (which corresponds to `values[i-1]` and `weights[i-1]`):
     *
     * 1. DO NOT include the i-th item:
     * If we don't include the current item, the maximum value is simply the maximum value
     * we could get with the previous `i-1` items and the same capacity `w`.
     * Value = `dp[i-1][w]`
     *
     * 2. INCLUDE the i-th item:
     * We can only include the i-th item if its weight (`weights[i-1]`) is less than or
     * equal to the current capacity `w`. If we include it, the value is the value of the
     * current item (`values[i-1]`) plus the maximum value we could get with the
     * remaining capacity (`w - weights[i-1]`) using the previous `i-1` items.
     * Value = `values[i-1] + dp[i-1][w - weights[i-1]]`
     *
     * We take the maximum of these two choices to fill `dp[i][w]`.
     *
     * Base Cases:
     * If there are 0 items (`i=0`) or the capacity is 0 (`w=0`), the maximum value is 0.
     * Our DP table of size (n+1)x(W+1) is initialized to 0, which automatically handles these cases.
     * The final answer is the value stored in `dp[n][W]`.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Time Complexity: O(N * W)
     * where N is the number of items and W is the capacity of the knapsack.
     * This is because we are filling a 2D table of size (N+1) x (W+1) using
     * two nested loops.
     *
     * Space Complexity: O(N * W)
     * This is the space required to store the 2D DP table.
     * (Note: This can be optimized to O(W) space, but the O(N*W) approach is
     * clearer for understanding the core DP concept).
     *
     * @param W The maximum capacity of the knapsack.
     * @param weights An array containing the weights of the items.
     * @param values An array containing the values of the items.
     * @param n The number of items.
     * @return The maximum value that can be put in the knapsack.
     */
    public int solveKnapsack(int W, int[] weights, int[] values, int n) {
        // Step 1: Create the DP table.
        // The table will have n+1 rows (for 0 to n items) and W+1 columns (for capacity 0 to W).
        // It's automatically initialized with 0s, which covers our base cases.
        int[][] dp = new int[n + 1][W + 1];

        // Step 2: Fill the DP table using a bottom-up approach.
        // Iterate through each item from 1 to n.
        for (int i = 1; i <= n; i++) {
            // Iterate through each possible capacity from 1 to W.
            for (int w = 1; w <= W; w++) {
                // The current item's weight and value. Note the i-1 index because
                // the arrays are 0-indexed while our DP table logic is 1-indexed.
                int currentWeight = weights[i-1];
                int currentValue = values[i-1];

                // Step 3: Apply the recurrence relation.
                
                // Case 1: The current item's weight is more than the current capacity 'w'.
                // In this case, we cannot include the item. The maximum value is the same
                // as the maximum value obtained with the previous i-1 items.
                if (currentWeight > w) {
                    dp[i][w] = dp[i-1][w];
                } else {
                    // Case 2: The current item can be included.
                    // We have two choices:
                    //   a) Don't include the item: Value is dp[i-1][w].
                    //   b) Include the item: Value is the item's value + the max value for the
                    //      remaining capacity with previous items (dp[i-1][w - currentWeight]).
                    // We take the maximum of these two choices.
                    int valueWithoutCurrent = dp[i-1][w];
                    int valueWithCurrent = currentValue + dp[i-1][w - currentWeight];
                    
                    dp[i][w] = Math.max(valueWithoutCurrent, valueWithCurrent);
                }
            }
        }

        // Step 4: Return the final answer.
        // The value in the bottom-right cell of the table represents the maximum value
        // achievable with n items and a knapsack of capacity W.
        return dp[n][W];
    }

    public static void main(String[] args) {
        Knapsack ks = new Knapsack();
        
        int[] values = {60, 100, 120};
        int[] weights = {10, 20, 30};
        int W = 50; // Knapsack capacity
        int n = values.length;
        
        int maxValue = ks.solveKnapsack(W, weights, values, n);
        
        System.out.println("Items:");
        for (int i = 0; i < n; i++) {
            System.out.println("- Value: " + values[i] + ", Weight: " + weights[i]);
        }
        System.out.println("Knapsack Capacity: " + W);
        System.out.println("Maximum value in Knapsack = " + maxValue); // Expected output: 220
    }
}