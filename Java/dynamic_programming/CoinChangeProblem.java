import java.util.Arrays;
import java.util.Scanner;

public class CoinChangeProblem {

    /**
     * Finds the minimum number of coins to make a given amount using Dynamic Programming.
     *
     * @param coins  An array of available coin denominations.
     * @param amount The target amount to make change for.
     * @return The minimum number of coins required, or -1 if impossible.
     */
    static int findMinCoins(int[] coins, int amount) {
        // Create a DP array to store the minimum number of coins for each amount.
        // The size is amount + 1 to handle amounts from 0 to amount.
        int[] dp = new int[amount + 1];

        // A value larger than any possible answer. amount + 1 is a safe choice
        // to represent infinity, as the max number of coins can't exceed the amount
        // (if a 1-unit coin is available).
        int infinity = amount + 1;

        // Initialize the DP array with the "infinity" value.
        Arrays.fill(dp, infinity);

        // Base case: 0 coins are needed to make an amount of 0.
        dp[0] = 0;

        // Build the DP table from the bottom up.
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                // If the current coin can be used to make up amount 'i'.
                if (coin <= i) {
                    // Update the minimum coins required for amount 'i'.
                    // The choice is either to not use this coin (keep dp[i])
                    // or to use this coin (1 + dp[i - coin]).
                    dp[i] = Math.min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        // If dp[amount] is still our "infinity" value, it means the amount cannot be made.
        // Otherwise, it holds the minimum number of coins.
        return dp[amount] > amount ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of coin denominations: ");
        int n = scanner.nextInt();

        int[] coins = new int[n];
        System.out.println("Enter the coin denominations:");
        for (int i = 0; i < n; i++) {
            System.out.print("Coin " + (i + 1) + ": ");
            coins[i] = scanner.nextInt();
        }

        System.out.print("\nEnter the target amount: ");
        int amount = scanner.nextInt();

        int minCoins = findMinCoins(coins, amount);

        if (minCoins == -1) {
            System.out.println("\nIt is not possible to make the amount " + amount + " with the given coins.");
        } else {
            System.out.println("\nMinimum number of coins required to make " + amount + " is: " + minCoins);
        }

        scanner.close();
    }
}