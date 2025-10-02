/**
 * Comprehensive Coin Change Problem Implementation
 * 
 * The Coin Change problem is a classic dynamic programming problem that involves
 * finding the minimum number of coins needed to make a given amount, or counting
 * the number of ways to make change for a given amount using given coin denominations.
 * 
 * Problem Variants Implemented:
 * 1. Minimum Coins Problem - Find minimum number of coins to make amount
 * 2. Coin Change Ways - Count number of ways to make amount
 * 3. Coin Change with Coin Tracking - Return actual coins used
 * 4. Unbounded vs Bounded Coin Change variations
 * 
 * Approaches:
 * - Dynamic Programming (Bottom-up)
 * - Memoization (Top-down)
 * - Space Optimized DP
 * - Recursive (for comparison)
 * 
 * Time Complexity: O(n * amount) where n is number of coin types
 * Space Complexity: O(amount) for optimized version, O(n * amount) for 2D approach
 * 
 * @author DSA_Code Repository
 * @version 1.0
 * @since Hacktoberfest 2025
 */

import java.util.*;

public class CoinChange {
    
    // ==================== MINIMUM COINS PROBLEM ====================
    
    /**
     * Find minimum number of coins needed to make the given amount
     * Dynamic Programming Approach (Bottom-up)
     * 
     * Time Complexity: O(n * amount)
     * Space Complexity: O(amount)
     * 
     * @param coins array of available coin denominations
     * @param amount target amount to make
     * @return minimum number of coins needed, -1 if impossible
     */
    public static int coinChangeMinCoins(int[] coins, int amount) {
        if (amount == 0) return 0;
        if (coins == null || coins.length == 0) return -1;
        
        // dp[i] represents minimum coins needed to make amount i
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1); // Initialize with impossible value
        dp[0] = 0; // Base case: 0 coins needed for amount 0
        
        // For each amount from 1 to target amount
        for (int i = 1; i <= amount; i++) {
            // Try each coin denomination
            for (int coin : coins) {
                if (coin <= i) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
    
    /**
     * Find minimum coins with memoization (Top-down approach)
     * 
     * Time Complexity: O(n * amount)
     * Space Complexity: O(amount) for recursion stack + memoization
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     * @return minimum coins needed
     */
    public static int coinChangeMinCoinsMemo(int[] coins, int amount) {
        if (amount == 0) return 0;
        if (coins == null || coins.length == 0) return -1;
        
        Integer[] memo = new Integer[amount + 1];
        int result = coinChangeHelper(coins, amount, memo);
        return result == Integer.MAX_VALUE ? -1 : result;
    }
    
    private static int coinChangeHelper(int[] coins, int amount, Integer[] memo) {
        if (amount == 0) return 0;
        if (amount < 0) return Integer.MAX_VALUE;
        if (memo[amount] != null) return memo[amount];
        
        int minCoins = Integer.MAX_VALUE;
        for (int coin : coins) {
            int result = coinChangeHelper(coins, amount - coin, memo);
            if (result != Integer.MAX_VALUE) {
                minCoins = Math.min(minCoins, result + 1);
            }
        }
        
        memo[amount] = minCoins;
        return minCoins;
    }
    
    /**
     * Find minimum coins and return the actual coins used
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     * @return list of coins used to make the amount
     */
    public static List<Integer> coinChangeWithCoins(int[] coins, int amount) {
        if (amount == 0) return new ArrayList<>();
        if (coins == null || coins.length == 0) return null;
        
        int[] dp = new int[amount + 1];
        int[] parent = new int[amount + 1]; // Track which coin was used
        Arrays.fill(dp, amount + 1);
        Arrays.fill(parent, -1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    parent[i] = coin;
                }
            }
        }
        
        if (dp[amount] > amount) return null; // Impossible to make amount
        
        // Reconstruct the coins used
        List<Integer> result = new ArrayList<>();
        int current = amount;
        while (current > 0) {
            int coin = parent[current];
            result.add(coin);
            current -= coin;
        }
        
        return result;
    }
    
    // ==================== COIN CHANGE WAYS PROBLEM ====================
    
    /**
     * Count number of ways to make the given amount using given coins
     * Each coin can be used unlimited times
     * 
     * Time Complexity: O(n * amount)
     * Space Complexity: O(amount)
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     * @return number of ways to make the amount
     */
    public static int coinChangeWays(int[] coins, int amount) {
        if (amount == 0) return 1;
        if (coins == null || coins.length == 0) return 0;
        
        int[] dp = new int[amount + 1];
        dp[0] = 1; // One way to make 0: use no coins
        
        // For each coin type
        for (int coin : coins) {
            // Update dp array for all amounts that can use this coin
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        
        return dp[amount];
    }
    
    /**
     * Count ways using 2D DP approach (shows the thought process)
     * 
     * Time Complexity: O(n * amount)
     * Space Complexity: O(n * amount)
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     * @return number of ways to make the amount
     */
    public static int coinChangeWays2D(int[] coins, int amount) {
        if (amount == 0) return 1;
        if (coins == null || coins.length == 0) return 0;
        
        int n = coins.length;
        int[][] dp = new int[n + 1][amount + 1];
        
        // Base case: one way to make amount 0 (use no coins)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= amount; j++) {
                // Don't use current coin
                dp[i][j] = dp[i - 1][j];
                
                // Use current coin (if possible)
                if (coins[i - 1] <= j) {
                    dp[i][j] += dp[i][j - coins[i - 1]];
                }
            }
        }
        
        return dp[n][amount];
    }
    
    // ==================== BOUNDED COIN CHANGE ====================
    
    /**
     * Coin change with limited quantity of each coin type
     * 
     * @param coins array of coin denominations
     * @param quantities array of quantities for each coin type
     * @param amount target amount
     * @return minimum coins needed
     */
    public static int boundedCoinChange(int[] coins, int[] quantities, int amount) {
        if (amount == 0) return 0;
        if (coins == null || coins.length == 0) return -1;
        
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;
        
        for (int i = 0; i < coins.length; i++) {
            int coin = coins[i];
            int qty = quantities[i];
            
            // For each quantity of this coin type
            for (int k = 1; k <= qty; k++) {
                // Update dp array in reverse order to avoid using same coin multiple times
                for (int j = amount; j >= coin; j--) {
                    if (dp[j - coin] != amount + 1) {
                        dp[j] = Math.min(dp[j], dp[j - coin] + 1);
                    }
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
    
    // ==================== UTILITY METHODS ====================
    
    /**
     * Validate input parameters
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     * @return true if valid, false otherwise
     */
    public static boolean isValidInput(int[] coins, int amount) {
        if (amount < 0) {
            System.out.println("❌ Error: Amount cannot be negative");
            return false;
        }
        
        if (coins == null || coins.length == 0) {
            System.out.println("❌ Error: Coins array cannot be null or empty");
            return false;
        }
        
        for (int coin : coins) {
            if (coin <= 0) {
                System.out.println("❌ Error: All coin denominations must be positive");
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * Print array in a formatted way
     * 
     * @param arr array to print
     * @param name name of the array
     */
    public static void printArray(int[] arr, String name) {
        System.out.print(name + ": [");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) System.out.print(", ");
        }
        System.out.println("]");
    }
    
    /**
     * Print list in a formatted way
     * 
     * @param list list to print
     * @param name name of the list
     */
    public static void printList(List<Integer> list, String name) {
        if (list == null) {
            System.out.println(name + ": null (impossible to make amount)");
            return;
        }
        
        System.out.print(name + ": [");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i));
            if (i < list.size() - 1) System.out.print(", ");
        }
        System.out.println("]");
    }
    
    /**
     * Run performance comparison between different approaches
     * 
     * @param coins array of coin denominations
     * @param amount target amount
     */
    public static void performanceComparison(int[] coins, int amount) {
        System.out.println("\n⚡ PERFORMANCE COMPARISON");
        System.out.println("-" .repeat(40));
        
        // Test Bottom-up DP
        long startTime = System.nanoTime();
        int result1 = coinChangeMinCoins(coins, amount);
        long endTime = System.nanoTime();
        long dpTime = endTime - startTime;
        
        // Test Memoization
        startTime = System.nanoTime();
        int result2 = coinChangeMinCoinsMemo(coins, amount);
        endTime = System.nanoTime();
        long memoTime = endTime - startTime;
        
        System.out.printf("%-20s | Result: %3d | Time: %8d ns%n", "Bottom-up DP", result1, dpTime);
        System.out.printf("%-20s | Result: %3d | Time: %8d ns%n", "Memoization", result2, memoTime);
        
        if (dpTime < memoTime) {
            System.out.println("🏆 Bottom-up DP is faster for this input");
        } else {
            System.out.println("🏆 Memoization is faster for this input");
        }
    }
    
    /**
     * Main method with comprehensive demonstrations
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("🪙 COMPREHENSIVE COIN CHANGE PROBLEMS DEMO");
        System.out.println("=" .repeat(50));
        
        System.out.println("\n📖 About Coin Change Problems:");
        System.out.println("The Coin Change problem is a fundamental dynamic programming problem");
        System.out.println("with applications in making change, resource allocation, and optimization.");
        System.out.println("Time Complexity: O(n × amount) | Space Complexity: O(amount)");
        
        // Interactive input
        System.out.println("\n🎯 INTERACTIVE COIN CHANGE DEMO");
        System.out.println("-" .repeat(35));
        
        System.out.print("Enter number of coin types: ");
        int n = scanner.nextInt();
        
        int[] coins = new int[n];
        System.out.println("Enter coin denominations:");
        for (int i = 0; i < n; i++) {
            System.out.print("Coin " + (i + 1) + ": ");
            coins[i] = scanner.nextInt();
        }
        
        System.out.print("Enter target amount: ");
        int amount = scanner.nextInt();
        
        if (!isValidInput(coins, amount)) {
            scanner.close();
            return;
        }
        
        printArray(coins, "Coins");
        System.out.println("Target Amount: " + amount);
        
        // Test all approaches
        System.out.println("\n🔍 TESTING ALL APPROACHES");
        System.out.println("-" .repeat(30));
        
        // 1. Minimum Coins Problem
        System.out.println("\n1️⃣ MINIMUM COINS PROBLEM");
        int minCoins = coinChangeMinCoins(coins, amount);
        if (minCoins == -1) {
            System.out.println("❌ Impossible to make amount " + amount + " with given coins");
        } else {
            System.out.println("✅ Minimum coins needed: " + minCoins);
            
            // Show actual coins used
            List<Integer> coinsUsed = coinChangeWithCoins(coins, amount);
            printList(coinsUsed, "Coins used");
            
            // Verify the sum
            int sum = coinsUsed.stream().mapToInt(Integer::intValue).sum();
            System.out.println("🔢 Verification: " + coinsUsed.size() + " coins sum to " + sum);
        }
        
        // 2. Count Ways Problem
        System.out.println("\n2️⃣ COUNT WAYS PROBLEM");
        int ways = coinChangeWays(coins, amount);
        System.out.println("🔢 Number of ways to make " + amount + ": " + ways);
        
        if (ways > 0 && ways <= 20) { // Only show details for reasonable number of ways
            System.out.println("📝 Different combinations exist to make this amount");
        } else if (ways > 20) {
            System.out.println("📝 Too many combinations to display (" + ways + " ways)");
        }
        
        // Performance comparison
        if (amount <= 1000) { // Only for reasonable amounts
            performanceComparison(coins, amount);
        }
        
        // Predefined test cases
        System.out.println("\n🧪 PREDEFINED TEST CASES");
        System.out.println("-" .repeat(30));
        
        // Test Case 1: Standard coins
        System.out.println("\n✅ Test Case 1: Standard US Coins");
        int[] usCoin = {1, 5, 10, 25};
        int usAmount = 67;
        printArray(usCoin, "Coins");
        System.out.println("Amount: " + usAmount);
        
        int usMin = coinChangeMinCoins(usCoin, usAmount);
        int usWays = coinChangeWays(usCoin, usAmount);
        List<Integer> usCoinsUsed = coinChangeWithCoins(usCoin, usAmount);
        
        System.out.println("Minimum coins: " + usMin);
        System.out.println("Number of ways: " + usWays);
        printList(usCoinsUsed, "Optimal solution");
        
        // Test Case 2: Impossible case
        System.out.println("\n❌ Test Case 2: Impossible Case");
        int[] impossibleCoins = {3, 5};
        int impossibleAmount = 1;
        printArray(impossibleCoins, "Coins");
        System.out.println("Amount: " + impossibleAmount);
        
        int impossibleResult = coinChangeMinCoins(impossibleCoins, impossibleAmount);
        System.out.println("Result: " + (impossibleResult == -1 ? "Impossible" : impossibleResult));
        
        // Test Case 3: Large denominations
        System.out.println("\n🏦 Test Case 3: Large Denominations");
        int[] largeCoins = {1, 7, 10};
        int largeAmount = 14;
        printArray(largeCoins, "Coins");
        System.out.println("Amount: " + largeAmount);
        
        int largeMin = coinChangeMinCoins(largeCoins, largeAmount);
        List<Integer> largeCoinsUsed = coinChangeWithCoins(largeCoins, largeAmount);
        System.out.println("Minimum coins: " + largeMin);
        printList(largeCoinsUsed, "Optimal solution");
        
        // Edge cases
        System.out.println("\n🔍 EDGE CASES");
        System.out.println("-" .repeat(20));
        
        System.out.println("Amount = 0: " + coinChangeMinCoins(coins, 0) + " coins");
        System.out.println("Ways for amount = 0: " + coinChangeWays(coins, 0) + " way(s)");
        
        // Algorithm complexity analysis
        System.out.println("\n📊 ALGORITHM ANALYSIS");
        System.out.println("-" .repeat(25));
        System.out.println("Problem Variant           | Time Complexity | Space Complexity");
        System.out.println("-" .repeat(65));
        System.out.println("Minimum Coins (DP)       | O(n × amount)   | O(amount)");
        System.out.println("Minimum Coins (Memo)     | O(n × amount)   | O(amount)");
        System.out.println("Count Ways (1D DP)       | O(n × amount)   | O(amount)");
        System.out.println("Count Ways (2D DP)       | O(n × amount)   | O(n × amount)");
        System.out.println("With Coin Tracking       | O(n × amount)   | O(amount)");
        
        // Real-world applications
        System.out.println("\n💡 REAL-WORLD APPLICATIONS");
        System.out.println("-" .repeat(30));
        System.out.println("💰 Financial Systems:");
        System.out.println("  • ATM cash dispensing optimization");
        System.out.println("  • Currency exchange calculations");
        System.out.println("  • Payment processing systems");
        
        System.out.println("\n🏭 Resource Allocation:");
        System.out.println("  • Manufacturing resource optimization");
        System.out.println("  • Inventory management");
        System.out.println("  • Budget allocation problems");
        
        System.out.println("\n🎮 Game Development:");
        System.out.println("  • In-game currency systems");
        System.out.println("  • Resource management games");
        System.out.println("  • Achievement point calculations");
        
        scanner.close();
        System.out.println("\n🌟 Coin Change Demo completed!");
        System.out.println("🚀 Perfect for Hacktoberfest contributions! Happy coding!");
    }
}
