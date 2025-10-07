import java.util.Arrays;

public class Knapsack {

    /**
     * Solves the 0/1 Knapsack problem using Dynamic Programming (Tabulation).
     *
     * @param weights   An array of weights of the items.
     * @param values    An array of values of the items.
     * @param capacity  The maximum weight capacity of the knapsack.
     * @param n         The number of items.
     * @return The maximum value that can be put in the knapsack.
     */
    public int solveKnapsack(int[] weights, int[] values, int capacity) {
        int n = weights.length;
        
        // dp[i][w] will be the maximum value that can be obtained
        // using the first 'i' items with a knapsack capacity of 'w'.
        // We use n+1 and capacity+1 to make indexing easier (1-based).
        int[][] dp = new int[n + 1][capacity + 1];

        // Build table dp[][] in a bottom-up manner.
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= capacity; w++) {
                // Base case: If there are no items (i=0) or the capacity is 0 (w=0),
                // the value is 0.
                if (i == 0 || w == 0) {
                    dp[i][w] = 0;
                } 
                // If the weight of the i-th item is less than or equal to the current capacity 'w'
                else if (weights[i - 1] <= w) {
                    // We have two choices:
                    // 1. Include the i-th item: value is values[i-1] + value from remaining capacity.
                    // 2. Exclude the i-th item: value is the same as with i-1 items.
                    // We take the maximum of these two choices.
                    // Note: weights[i-1] and values[i-1] correspond to the i-th item.
                    dp[i][w] = Math.max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]], // Include item
                        dp[i - 1][w]                                  // Exclude item
                    );
                } 
                // If the weight of the i-th item is more than the current capacity 'w',
                // we cannot include it. So the value is the same as with i-1 items.
                else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        
        // The final answer is in the bottom-right corner of the table.
        return dp[n][capacity];
    }

    public static void main(String[] args) {
        Knapsack ks = new Knapsack();
        
        int[] values = {60, 100, 120};
        int[] weights = {10, 20, 30};
        int capacity = 50;
        
        int maxValue = ks.solveKnapsack(weights, values, capacity);
        
        System.out.println("Items available:");
        System.out.println("Values: " + Arrays.toString(values));
        System.out.println("Weights: " + Arrays.toString(weights));
        System.out.println("Knapsack Capacity: " + capacity);
        System.out.println("Maximum value that can be obtained is: " + maxValue);
        
        // Expected output for this example is 220.
        // This is achieved by taking the items with weight 20 (value 100) and 30 (value 120).
        // Total weight = 20 + 30 = 50.
        // Total value = 100 + 120 = 220.
    }
}