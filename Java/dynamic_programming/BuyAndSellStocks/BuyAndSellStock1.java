/*
Best Time to Buy and Sell Stock I

Algorithm Description:
This algorithm finds the maximum profit from a single buy and sell transaction. It iterates through the price array, tracking the minimum price seen so far and the maximum profit achievable by selling at the current price. The approach is greedy and uses only constant space.

Use Cases:
- Finding the best single buy/sell opportunity in a stock price history
- Any scenario where only one transaction is allowed

Time Complexity: O(n)
- Single pass through the array.

Space Complexity: O(1)
- Only a few variables are used.
*/

package Java.dynamic_programming.BuyAndSellStocks;

class BuyAndSellStock1 {
    public static void main(String[] args) {
        BuyAndSellStock1 bss = new BuyAndSellStock1();
        int[] a = {7,1,5,3,6,4};
        System.out.println(bss.maxProfit(a)); // Output: 5

        // Additional test cases
        System.out.println(bss.maxProfit(new int[]{7,6,4,3,1})); // Output: 0 (no profit possible)
        System.out.println(bss.maxProfit(new int[]{1,2})); // Output: 1
        System.out.println(bss.maxProfit(new int[]{})); // Output: 0 (edge case: empty array)
    }

    /**
     * Calculates the maximum profit from a single buy and sell transaction.
     * @param a Prices array
     * @return  Maximum profit (0 if no profit is possible)
     */
    public int maxProfit(int[] a) {
        if (a == null || a.length == 0) return 0;
        int n = a.length;
        int profit = Integer.MIN_VALUE; // Tracks the maximum profit found so far
        int previousStock = a[0];       // Tracks the minimum price seen so far (best day to buy)

        // Iterate through each day, starting from the second day
        for(int i = 1; i < n; i++) {
            int currProfit = a[i] - previousStock; // Profit if bought at previousStock and sold today
            profit = Math.max(profit, currProfit); // Update max profit if current is better
            previousStock = Math.min(previousStock, a[i]); // Update min price if current is lower
        }
        // If profit is negative or zero, return 0 (no profit possible)
        return profit > 0 ? profit : 0;
    }
}
