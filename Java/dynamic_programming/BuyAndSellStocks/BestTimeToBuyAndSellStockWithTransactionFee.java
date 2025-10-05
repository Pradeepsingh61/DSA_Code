/*
Best Time to Buy and Sell Stock with Transaction Fee

Algorithm Description:
This algorithm computes the maximum profit from buying and selling stocks with as many transactions as you like, but each transaction (buy+sell) incurs a fixed fee. The approach uses dynamic programming with memoization. The state is defined by the current day and whether you can buy or must sell. At each step, you decide to buy, sell (paying the fee), or skip, and recursively compute the best outcome.

Use Cases:
- Stock trading where each transaction incurs a brokerage or transaction fee
- Any scenario where actions have a fixed cost per transaction

Time Complexity: O(n)
- Each state (day, buy/sell) is computed once, and there are 2*n states.

Space Complexity: O(n)
- The DP table stores results for each day and buy/sell state.
*/

package Java.dynamic_programming.BuyAndSellStocks;

import java.util.Arrays;

public class BestTimeToBuyAndSellStockWithTransactionFee {
    public static void main(String[] args) {
        BestTimeToBuyAndSellStockWithTransactionFee bss = new BestTimeToBuyAndSellStockWithTransactionFee();
        int[] a = {1,3,2,8,4,9};
        int fee = 2;
        System.out.println(bss.maxProfit(a,fee)); // Output: 8

        // Additional test cases
        System.out.println(bss.maxProfit(new int[]{1,3,7,5,10,3}, 3)); // Output: 6
        System.out.println(bss.maxProfit(new int[]{1}, 1)); // Output: 0 (edge case: only one day)
        System.out.println(bss.maxProfit(new int[]{}, 1)); // Output: 0 (edge case: empty array)
    }

    /**
     * Recursive helper function to calculate max profit with transaction fee.
     * @param i   Current day index
     * @param buy 1 if we can buy, 0 if we must sell
     * @param fee Transaction fee per transaction
     * @param a   Prices array
     * @param dp  Memoization table
     * @return    Maximum profit from day i with given state
     */
    private int f(int i, int buy, int fee, int[] a, int[][] dp) {
        // Base case: If we've reached the end, no more profit can be made
        if(i>=a.length){
            return 0;
        }
        // Return cached result if already computed
        if(dp[i][buy] != -1){
            return dp[i][buy];
        }

        int profit = 0;
        if(buy == 1) {
            // Option 1: Buy at current day, move to next day with buy=0 (must sell next)
            // Option 2: Skip buying, move to next day with buy=1 (still can buy)
            profit = Math.max(f(i+1,0,fee,a,dp)-a[i] , f(i+1,1,fee,a,dp));
        }
        else {
            // Option 1: Sell at current day, pay fee, move to next day with buy=1 (can buy again)
            // Option 2: Skip selling, move to next day with buy=0 (still holding)
            profit = Math.max(f(i+1,1,fee,a,dp)+a[i]-fee , f(i+1,0,fee,a,dp));
        }
        // Store result in dp table and return
        return dp[i][buy] = profit;
    }

    /**
     * Calculates the maximum profit with unlimited transactions and a transaction fee.
     * @param a   Prices array
     * @param fee Transaction fee per transaction
     * @return    Maximum profit
     */
    public int maxProfit(int[] a, int fee) {
        int n = a.length;
        // dp[i][buy]: Max profit at day i, buy/sell state
        int[][] dp = new int[n+1][3];
        // Initialize dp table with -1 (uncomputed)
        for(int[] r : dp){
            Arrays.fill(r,-1);
        }
        // Start from day 0, can buy
        return f(0,1,fee,a,dp);
    }
}



