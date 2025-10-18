/*
Best Time to Buy and Sell Stock with Cooldown

Algorithm Description:
This algorithm finds the maximum profit from buying and selling stocks with as many transactions as you like, but with a cooldown of one day after each sale. You cannot buy a stock on the day immediately after selling it. The approach uses dynamic programming with memoization to avoid redundant calculations. The state is defined by the current day and whether you can buy or must sell. At each step, you decide to buy, sell, or skip, and recursively compute the best outcome.

Use Cases:
- Stock trading with cooldown restrictions (e.g., to avoid rapid trading penalties)
- Any scenario where actions are limited by a cooldown period

Time Complexity: O(n)
- Each state (day, buy/sell) is computed once, and there are 2*n states.

Space Complexity: O(n)
- The DP table stores results for each day and buy/sell state.
*/

package Java.dynamic_programming.BuyAndSellStocks;

import java.util.Arrays;

public class BestTimeToBuyAndSellStockWithCooldown {
    public static void main(String[] args) {
        BestTimeToBuyAndSellStockWithCooldown bss = new BestTimeToBuyAndSellStockWithCooldown();
        int[] a = {1,2,3,0,2};
        System.out.println(bss.maxProfit(a)); // Output: 3

        // Additional test cases
        System.out.println(bss.maxProfit(new int[]{1})); // Output: 0 (edge case: only one day)
        System.out.println(bss.maxProfit(new int[]{2,1,4})); // Output: 3
        System.out.println(bss.maxProfit(new int[]{})); // Output: 0 (edge case: empty array)
    }

    /**
     * Recursive helper function to calculate max profit with cooldown.
     * @param i   Current day index
     * @param buy 1 if we can buy, 0 if we must sell
     * @param a   Prices array
     * @param dp  Memoization table
     * @return    Maximum profit from day i with given state
     */
    private int f(int i, int buy, int[] a, int[][] dp) {
        // Base case: If we've reached the end, no more profit can be made
        if(i >= a.length){
            return 0;
        }
        // Return cached result if already computed
        if(dp[i][buy] != -1){
            return dp[i][buy];
        }
        int profit = 0;
        if(buy == 1){
            // Option 1: Buy at current day, move to next day with buy=0 (must sell next)
            // Option 2: Skip buying, move to next day with buy=1 (still can buy)
            profit = Math.max(f(i+1,0,a,dp)-a[i], f(i+1,1,a,dp));
        }
        else{
            // Option 1: Sell at current day, move to day after next (cooldown), can buy again
            // Option 2: Skip selling, move to next day with buy=0 (still holding)
            profit = Math.max(f(i+2, 1, a, dp) + a[i], f(i+1,0,a,dp));
        }
        // Store result in dp table and return
        return dp[i][buy] = profit;
    }

    /**
     * Calculates the maximum profit with cooldown after selling.
     * @param a Prices array
     * @return  Maximum profit
     */
    public int maxProfit(int[] a) {
        int n = a.length;
        // dp[i][buy]: Max profit at day i, buy/sell state
        int[][] dp = new int[n+1][3];

        // Initialize dp table with -1 (uncomputed)
        for(int[] r: dp) {
            Arrays.fill(r,-1);
        }

        // Start from day 0, can buy
        return f(0,1,a,dp);
    }
}


