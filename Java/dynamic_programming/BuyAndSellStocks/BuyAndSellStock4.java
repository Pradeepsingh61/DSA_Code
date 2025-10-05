/*
Best Time to Buy and Sell Stock IV

Algorithm Description:
This algorithm finds the maximum profit from at most k buy and sell transactions. The approach uses dynamic programming with memoization, where the state is defined by the current day, whether you can buy, and the number of transactions remaining. At each step, you decide to buy, sell, or skip, and recursively compute the best outcome.

Use Cases:
- Stock trading with a maximum of k transactions
- Any scenario where a limited number of transactions is allowed

Time Complexity: O(n*k)
- Each state (day, buy/sell, transactions left) is computed once, and there are 2*n*k states.

Space Complexity: O(n*k)
- The DP table stores results for each day, buy/sell state, and transaction count.
*/

package Java.dynamic_programming.BuyAndSellStocks;

import java.util.Arrays;

public class BuyAndSellStock4 {
    public static void main(String[] args) {
        BuyAndSellStock4 bss = new BuyAndSellStock4();
        int[] a = {2,4,1};
        int k = 2;
        System.out.println(bss.maxProfit(k, a)); // Output: 2

        // Additional test cases
        System.out.println(bss.maxProfit(2, new int[]{3,2,6,5,0,3})); // Output: 7
        System.out.println(bss.maxProfit(0, new int[]{1,2,3,4,5})); // Output: 0 (no transactions allowed)
        System.out.println(bss.maxProfit(100, new int[]{1,2,3,4,5})); // Output: 4 (unlimited transactions)
        System.out.println(bss.maxProfit(2, new int[]{})); // Output: 0 (edge case: empty array)
    }

    /**
     * Recursive helper function to calculate max profit.
     * @param i   Current day index
     * @param buy 1 if we can buy, 0 if we must sell
     * @param t   Number of transactions remaining
     * @param a   Prices array
     * @param dp  Memoization table
     * @return    Maximum profit from day i with given state
     */
    private int f(int i, int buy, int t, int[] a, int[][][] dp) {
        // Base case: If we've reached the end or have no transactions left, no more profit can be made
        if(i == a.length || t == 0){
            return 0;
        }
        // Return cached result if already computed
        if(dp[i][buy][t] != -1){
            return dp[i][buy][t];
        }

        int profit = 0;
        if(buy == 1) {
            // Option 1: Buy at current day, move to next day with buy=0 (must sell next)
            // Option 2: Skip buying, move to next day with buy=1
            profit = Math.max(f(i+1,0,t,a,dp)-a[i], f(i+1,1,t,a,dp));
        }  
        else {
            // Option 1: Sell at current day, decrement transaction count, move to next day with buy=1
            // Option 2: Skip selling, move to next day with buy=0
            profit = Math.max(f(i+1,1,t-1,a,dp)+a[i], f(i+1,0,t,a,dp));
        }
        // Store result in dp table and return
        return dp[i][buy][t] = profit;
    }

    /**
     * Calculates the maximum profit with at most k transactions.
     * @param k Maximum number of transactions allowed
     * @param a Prices array
     * @return  Maximum profit
     */
    public int maxProfit(int k, int[] a) {
        int n = a.length;
        // dp[i][buy][t]: Max profit at day i, buy/sell state, t transactions remaining
        int[][][] dp = new int[n+1][3][k+1];

        // Initialize dp table with -1 (uncomputed)
        for(int[][] r:dp){
            for(int[] rr: r){
                Arrays.fill(rr,-1);
            }
        }

        // Start from day 0, can buy, k transactions remaining
        return f(0,1,k,a,dp);
    }
}


