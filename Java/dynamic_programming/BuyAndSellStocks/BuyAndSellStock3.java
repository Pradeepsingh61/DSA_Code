/*
Best Time to Buy and Sell Stock III

Algorithm Description:
This algorithm finds the maximum profit from at most two buy and sell transactions. The approach uses dynamic programming with memoization, where the state is defined by the current day, whether you can buy, and the number of completed transactions. At each step, you decide to buy, sell, or skip, and recursively compute the best outcome.

Use Cases:
- Stock trading with a maximum of two transactions
- Any scenario where a limited number of transactions is allowed

Time Complexity: O(n)
- Each state (day, buy/sell, transactions done) is computed once, and there are 2*n*3 states (constant factor).

Space Complexity: O(n)
- The DP table stores results for each day, buy/sell state, and transaction count.
*/

package Java.dynamic_programming.BuyAndSellStocks;

import java.util.Arrays;

public class BuyAndSellStock3 {
    public static void main(String[] args) {
        BuyAndSellStock3 bss = new BuyAndSellStock3();
        int[] a = {3,3,5,0,0,3,1,4};
        System.out.println(bss.maxProfit(a)); // Output: 6

        // Additional test cases
        System.out.println(bss.maxProfit(new int[]{1,2,3,4,5})); // Output: 4
        System.out.println(bss.maxProfit(new int[]{7,6,4,3,1})); // Output: 0
        System.out.println(bss.maxProfit(new int[]{})); // Output: 0 (edge case: empty array)
    }

    /**
     * Recursive helper function to calculate max profit.
     * @param i   Current day index
     * @param buy 1 if we can buy, 0 if we must sell
     * @param t   Number of completed transactions
     * @param a   Prices array
     * @param dp  Memoization table
     * @return    Maximum profit from day i with given state
     */
    private int f(int i, int buy, int t, int[] a, int[][][] dp) {
        // Base case: If we've reached the end or completed 2 transactions, no more profit can be made
        if(i >= a.length || t >= 2){
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
        else{
            // Option 1: Sell at current day, increment transaction count, move to next day with buy=1
            // Option 2: Skip selling, move to next day with buy=0
            profit = Math.max(f(i+1,1,t+1,a,dp)+a[i], f(i+1,0,t,a,dp));
        }
        // Store result in dp table and return
        return dp[i][buy][t] = profit;
    }

    /**
     * Calculates the maximum profit with at most two transactions.
     * @param a Prices array
     * @return  Maximum profit
     */
    public int maxProfit(int[] a) {
        int n = a.length;
        // dp[i][buy][t]: Max profit at day i, buy/sell state, t transactions done
        int[][][] dp = new int[n][3][3];

        // Initialize dp table with -1 (uncomputed)
        for(int[][] r:dp){
            for(int[] rr:r){
                Arrays.fill(rr,-1);
            }
        }

        // Start from day 0, can buy, 0 transactions done
        return f(0,1,0,a,dp);
    }
}


