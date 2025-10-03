/*
 * Algorithm: Coin Change Problem using Dynamic Programming
 * Description: Find minimum coins needed and number of ways to make change
 * Time Complexity: O(amount * num_coins) for both variants
 * Space Complexity: O(amount) for optimized versions
 * Author: DSA Code Repository
 * Date: 2025-10-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_AMOUNT 10000
#define MAX_COINS 100

/**
 * Recursive solution for minimum coins (naive approach)
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Minimum number of coins needed
 */
int min_coins_recursive(int coins[], int num_coins, int amount) {
    // Base case
    if (amount == 0) {
        return 0;
    }
    
    if (amount < 0) {
        return -1; // Invalid
    }
    
    int min_result = INT_MAX;
    
    // Try each coin
    for (int i = 0; i < num_coins; i++) {
        int sub_result = min_coins_recursive(coins, num_coins, amount - coins[i]);
        
        if (sub_result != -1 && sub_result < min_result) {
            min_result = sub_result + 1;
        }
    }
    
    return (min_result == INT_MAX) ? -1 : min_result;
}

/**
 * Minimum coins using memoization (top-down DP)
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @param memo: Memoization array
 * @return: Minimum number of coins needed
 */
int min_coins_memoization_util(int coins[], int num_coins, int amount, int memo[]) {
    // Base case
    if (amount == 0) {
        return 0;
    }
    
    if (amount < 0) {
        return -1;
    }
    
    // Check if already computed
    if (memo[amount] != -2) {
        return memo[amount];
    }
    
    int min_result = INT_MAX;
    
    // Try each coin
    for (int i = 0; i < num_coins; i++) {
        if (coins[i] <= amount) {
            int sub_result = min_coins_memoization_util(coins, num_coins, amount - coins[i], memo);
            
            if (sub_result != -1 && sub_result < min_result) {
                min_result = sub_result + 1;
            }
        }
    }
    
    memo[amount] = (min_result == INT_MAX) ? -1 : min_result;
    return memo[amount];
}

/**
 * Minimum coins using memoization wrapper
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Minimum number of coins needed
 */
int min_coins_memoization(int coins[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0) {
        return -1;
    }
    
    int memo[MAX_AMOUNT];
    
    // Initialize memoization array
    for (int i = 0; i <= amount; i++) {
        memo[i] = -2; // Uncomputed state
    }
    
    return min_coins_memoization_util(coins, num_coins, amount, memo);
}

/**
 * Minimum coins using tabulation (bottom-up DP)
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Minimum number of coins needed
 */
int min_coins_tabulation(int coins[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0) {
        return -1;
    }
    
    if (amount == 0) {
        return 0;
    }
    
    int dp[amount + 1];
    
    // Initialize DP array
    dp[0] = 0; // Base case: 0 coins needed for amount 0
    
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX; // Initialize to impossible value
    }
    
    // Fill the DP table
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < num_coins; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }
    
    return (dp[amount] == INT_MAX) ? -1 : dp[amount];
}

/**
 * Find the actual coins used for minimum coin change
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @param result_coins: Array to store the coins used
 * @return: Number of coins used (-1 if impossible)
 */
int min_coins_with_path(int coins[], int num_coins, int amount, int result_coins[]) {
    if (amount < 0 || num_coins <= 0) {
        return -1;
    }
    
    if (amount == 0) {
        return 0;
    }
    
    int dp[amount + 1];
    int parent[amount + 1]; // To track which coin was used
    
    // Initialize arrays
    dp[0] = 0;
    parent[0] = -1;
    
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
        parent[i] = -1;
    }
    
    // Fill the DP table
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < num_coins; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                    parent[i] = j; // Store which coin was used
                }
            }
        }
    }
    
    if (dp[amount] == INT_MAX) {
        return -1; // Impossible to make change
    }
    
    // Backtrack to find the coins used
    int num_result_coins = 0;
    int current_amount = amount;
    
    while (current_amount > 0) {
        int coin_index = parent[current_amount];
        result_coins[num_result_coins++] = coins[coin_index];
        current_amount -= coins[coin_index];
    }
    
    return num_result_coins;
}

/**
 * Count number of ways to make change (unlimited coins)
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Number of ways to make change
 */
long long count_ways_unlimited(int coins[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0) {
        return 0;
    }
    
    if (amount == 0) {
        return 1; // One way to make 0: use no coins
    }
    
    long long dp[amount + 1];
    
    // Initialize DP array
    for (int i = 0; i <= amount; i++) {
        dp[i] = 0;
    }
    dp[0] = 1; // Base case
    
    // For each coin
    for (int i = 0; i < num_coins; i++) {
        // Update dp array for all amounts
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    return dp[amount];
}

/**
 * Count number of ways to make change (each coin used at most once)
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Number of ways to make change
 */
long long count_ways_limited(int coins[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0) {
        return 0;
    }
    
    if (amount == 0) {
        return 1;
    }
    
    long long dp[amount + 1];
    
    // Initialize DP array
    for (int i = 0; i <= amount; i++) {
        dp[i] = 0;
    }
    dp[0] = 1; // Base case
    
    // For each coin (process in reverse to avoid using same coin multiple times)
    for (int i = 0; i < num_coins; i++) {
        for (int j = amount; j >= coins[i]; j--) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    return dp[amount];
}

/**
 * Coin change with limited quantities of each coin
 * @param coins: Array of coin denominations
 * @param quantities: Array of available quantities for each coin
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 * @return: Minimum number of coins needed
 */
int min_coins_limited_quantity(int coins[], int quantities[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0) {
        return -1;
    }
    
    if (amount == 0) {
        return 0;
    }
    
    int dp[amount + 1];
    
    // Initialize DP array
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    
    // For each coin type
    for (int i = 0; i < num_coins; i++) {
        // For each quantity of this coin type
        for (int k = 1; k <= quantities[i]; k++) {
            // For each amount (reverse order to avoid using same instance multiple times)
            for (int j = amount; j >= coins[i]; j--) {
                if (dp[j - coins[i]] != INT_MAX) {
                    if (dp[j - coins[i]] + 1 < dp[j]) {
                        dp[j] = dp[j - coins[i]] + 1;
                    }
                }
            }
        }
    }
    
    return (dp[amount] == INT_MAX) ? -1 : dp[amount];
}

/**
 * Performance comparison between different approaches
 * @param coins: Array of coin denominations
 * @param num_coins: Number of coin types
 * @param amount: Target amount
 */
void performance_comparison(int coins[], int num_coins, int amount) {
    clock_t start, end;
    double cpu_time_used;
    int result;
    
    printf("\\nPerformance Comparison for amount %d:\n", amount);
    printf("=====================================\n");
    
    // Recursive (only for small amounts)
    if (amount <= 20) {
        start = clock();
        result = min_coins_recursive(coins, num_coins, amount);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Recursive:    Result = %d, Time = %f seconds\n", result, cpu_time_used);
    } else {
        printf("Recursive:    Skipped (too slow for large amounts)\n");
    }
    
    // Memoization
    start = clock();
    result = min_coins_memoization(coins, num_coins, amount);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Memoization:  Result = %d, Time = %f seconds\n", result, cpu_time_used);
    
    // Tabulation
    start = clock();
    result = min_coins_tabulation(coins, num_coins, amount);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tabulation:   Result = %d, Time = %f seconds\n", result, cpu_time_used);
    
    // Count ways
    start = clock();
    long long ways = count_ways_unlimited(coins, num_coins, amount);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Count Ways:   Result = %lld, Time = %f seconds\n", ways, cpu_time_used);
}

/**
 * Real-world coin change examples
 */
void real_world_examples() {
    printf("\\nReal-World Coin Change Examples\n");
    printf("===============================\n");
    
    // US Currency
    printf("\\n1. US Currency System:\n");
    int us_coins[] = {1, 5, 10, 25, 50, 100}; // cents
    int num_us_coins = sizeof(us_coins) / sizeof(us_coins[0]);
    
    int us_amounts[] = {30, 67, 99, 142, 250};
    int num_us_amounts = sizeof(us_amounts) / sizeof(us_amounts[0]);
    
    for (int i = 0; i < num_us_amounts; i++) {
        int amount = us_amounts[i];
        int min_coins = min_coins_tabulation(us_coins, num_us_coins, amount);
        long long ways = count_ways_unlimited(us_coins, num_us_coins, amount);
        
        printf("Amount: %d cents, Min coins: %d, Ways: %lld\n", amount, min_coins, ways);
        
        // Show actual coins used
        int used_coins[MAX_AMOUNT];
        int num_used = min_coins_with_path(us_coins, num_us_coins, amount, used_coins);
        
        printf("  Coins used: ");
        for (int j = 0; j < num_used; j++) {
            printf("%d ", used_coins[j]);
        }
        printf("\\n");
    }
    
    // European Currency (Euro cents)
    printf("\\n2. European Currency System:\n");
    int euro_coins[] = {1, 2, 5, 10, 20, 50, 100, 200}; // euro cents
    int num_euro_coins = sizeof(euro_coins) / sizeof(euro_coins[0]);
    
    int euro_amounts[] = {37, 83, 156, 299};
    int num_euro_amounts = sizeof(euro_amounts) / sizeof(euro_amounts[0]);
    
    for (int i = 0; i < num_euro_amounts; i++) {
        int amount = euro_amounts[i];
        int min_coins = min_coins_tabulation(euro_coins, num_euro_coins, amount);
        
        printf("Amount: %d euro cents, Min coins: %d\n", amount, min_coins);
    }
    
    // Custom denominations
    printf("\\n3. Custom Denomination System:\n");
    int custom_coins[] = {1, 3, 4, 5}; // Non-standard denominations
    int num_custom_coins = sizeof(custom_coins) / sizeof(custom_coins[0]);
    
    printf("Coin denominations: ");
    for (int i = 0; i < num_custom_coins; i++) {
        printf("%d ", custom_coins[i]);
    }
    printf("\\n");
    
    for (int amount = 1; amount <= 10; amount++) {
        int min_coins = min_coins_tabulation(custom_coins, num_custom_coins, amount);
        long long ways = count_ways_unlimited(custom_coins, num_custom_coins, amount);
        
        printf("Amount: %d, Min coins: %d, Ways: %lld\n", amount, min_coins, ways);
    }
}

/**
 * Test function to demonstrate coin change algorithms
 */
void test_coin_change() {
    printf("Coin Change Problem using Dynamic Programming\n");
    printf("============================================\n");
    
    // Test Case 1: Basic coin change
    printf("\\nTest Case 1: Basic Coin Change\n");
    printf("------------------------------\n");
    
    int coins[] = {1, 5, 10, 25};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    
    printf("Coin denominations: ");
    for (int i = 0; i < num_coins; i++) {
        printf("%d ", coins[i]);
    }
    printf("\\n");
    
    int test_amounts[] = {0, 11, 23, 30, 67, 100};
    int num_test_amounts = sizeof(test_amounts) / sizeof(test_amounts[0]);
    
    for (int i = 0; i < num_test_amounts; i++) {
        int amount = test_amounts[i];
        int min_coins = min_coins_tabulation(coins, num_coins, amount);
        long long ways_unlimited = count_ways_unlimited(coins, num_coins, amount);
        long long ways_limited = count_ways_limited(coins, num_coins, amount);
        
        printf("Amount: %d\n", amount);
        printf("  Min coins: %d\n", min_coins);
        printf("  Ways (unlimited): %lld\n", ways_unlimited);
        printf("  Ways (limited): %lld\n", ways_limited);
        
        // Show the actual coins used
        if (min_coins > 0) {
            int used_coins[MAX_AMOUNT];
            int num_used = min_coins_with_path(coins, num_coins, amount, used_coins);
            
            printf("  Coins used: ");
            for (int j = 0; j < num_used; j++) {
                printf("%d ", used_coins[j]);
            }
            printf("\\n");
        }
        printf("\\n");
    }
    
    // Test Case 2: Edge cases
    printf("Test Case 2: Edge Cases\n");
    printf("-----------------------\n");
    
    // Impossible cases
    int impossible_coins[] = {3, 5};
    int num_impossible = sizeof(impossible_coins) / sizeof(impossible_coins[0]);
    
    printf("Coins that can't make certain amounts: ");
    for (int i = 0; i < num_impossible; i++) {
        printf("%d ", impossible_coins[i]);
    }
    printf("\\n");
    
    for (int amount = 1; amount <= 10; amount++) {
        int result = min_coins_tabulation(impossible_coins, num_impossible, amount);
        printf("Amount %d: %s\\n", amount, 
               (result == -1) ? "Impossible" : "Possible");
    }
    
    // Test Case 3: Performance comparison
    printf("\\nTest Case 3: Performance Comparison\n");
    printf("-----------------------------------\n");
    
    performance_comparison(coins, num_coins, 30);
    performance_comparison(coins, num_coins, 100);
    
    // Test Case 4: Limited quantity coins
    printf("\\nTest Case 4: Limited Quantity Coins\n");
    printf("-----------------------------------\n");
    
    int limited_coins[] = {1, 5, 10, 25};
    int quantities[] = {3, 2, 1, 1}; // Limited quantities
    int num_limited = sizeof(limited_coins) / sizeof(limited_coins[0]);
    
    printf("Coins with limited quantities:\\n");
    for (int i = 0; i < num_limited; i++) {
        printf("  Coin %d: quantity %d\\n", limited_coins[i], quantities[i]);
    }
    
    for (int amount = 20; amount <= 50; amount += 10) {
        int result = min_coins_limited_quantity(limited_coins, quantities, num_limited, amount);
        printf("Amount %d: %s\\n", amount, 
               (result == -1) ? "Impossible" : "Possible");
        if (result != -1) {
            printf("  Min coins needed: %d\\n", result);
        }
    }
    
    // Test Case 5: Real-world examples
    real_world_examples();
    
    // Test Case 6: Large amount test
    printf("\\nTest Case 6: Large Amount Test\n");
    printf("------------------------------\n");
    
    int large_amounts[] = {500, 1000, 2500, 5000};
    int num_large = sizeof(large_amounts) / sizeof(large_amounts[0]);
    
    for (int i = 0; i < num_large; i++) {
        int amount = large_amounts[i];
        
        clock_t start = clock();
        int min_coins = min_coins_tabulation(coins, num_coins, amount);
        clock_t end = clock();
        
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Amount: %d, Min coins: %d, Time: %f seconds\\n", 
               amount, min_coins, time_taken);
    }
}

int main() {
    test_coin_change();
    return 0;
}