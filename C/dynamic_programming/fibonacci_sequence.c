/*
 * Algorithm: Fibonacci Sequence using Dynamic Programming
 * Description: Calculate Fibonacci numbers using memoization and tabulation
 * Time Complexity: O(n) for DP, O(2^n) for naive recursion
 * Space Complexity: O(n) for memoization, O(1) for optimized tabulation
 * Author: DSA Code Repository
 * Date: 2025-10-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 100

/**
 * Naive recursive Fibonacci (for comparison)
 * @param n: Position in Fibonacci sequence
 * @return: nth Fibonacci number
 */
long long fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

/**
 * Fibonacci using memoization (top-down DP)
 * @param n: Position in Fibonacci sequence
 * @param memo: Memoization array
 * @return: nth Fibonacci number
 */
long long fibonacci_memoization_util(int n, long long memo[]) {
    if (n <= 1) {
        return n;
    }
    
    if (memo[n] != -1) {
        return memo[n]; // Return cached result
    }
    
    memo[n] = fibonacci_memoization_util(n - 1, memo) + 
              fibonacci_memoization_util(n - 2, memo);
    
    return memo[n];
}

/**
 * Fibonacci using memoization wrapper
 * @param n: Position in Fibonacci sequence
 * @return: nth Fibonacci number
 */
long long fibonacci_memoization(int n) {
    if (n < 0) {
        printf("Error: Negative input not allowed\n");
        return -1;
    }
    
    long long memo[MAX_N];
    
    // Initialize memoization array
    for (int i = 0; i <= n && i < MAX_N; i++) {
        memo[i] = -1;
    }
    
    return fibonacci_memoization_util(n, memo);
}

/**
 * Fibonacci using tabulation (bottom-up DP)
 * @param n: Position in Fibonacci sequence
 * @return: nth Fibonacci number
 */
long long fibonacci_tabulation(int n) {
    if (n < 0) {
        printf("Error: Negative input not allowed\n");
        return -1;
    }
    
    if (n <= 1) {
        return n;
    }
    
    long long dp[MAX_N];
    
    // Base cases
    dp[0] = 0;
    dp[1] = 1;
    
    // Fill the table bottom-up
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

/**
 * Space-optimized Fibonacci (O(1) space)
 * @param n: Position in Fibonacci sequence
 * @return: nth Fibonacci number
 */
long long fibonacci_optimized(int n) {
    if (n < 0) {
        printf("Error: Negative input not allowed\n");
        return -1;
    }
    
    if (n <= 1) {
        return n;
    }
    
    long long prev2 = 0;  // F(0)
    long long prev1 = 1;  // F(1)
    long long current;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

/**
 * Generate and print first n Fibonacci numbers
 * @param n: Number of Fibonacci numbers to generate
 */
void print_fibonacci_sequence(int n) {
    if (n <= 0) {
        printf("Invalid input for sequence length\n");
        return;
    }
    
    printf("First %d Fibonacci numbers: ", n);
    
    if (n >= 1) printf("0 ");
    if (n >= 2) printf("1 ");
    
    long long prev2 = 0, prev1 = 1, current;
    
    for (int i = 2; i < n; i++) {
        current = prev1 + prev2;
        printf("%lld ", current);
        prev2 = prev1;
        prev1 = current;
    }
    
    printf("\n");
}

/**
 * Check if a number exists in Fibonacci sequence
 * @param target: Number to check
 * @param max_check: Maximum position to check up to
 * @return: Position if found, -1 if not found
 */
int is_fibonacci_number(long long target, int max_check) {
    if (target < 0) {
        return -1;
    }
    
    if (target == 0) return 0;
    if (target == 1) return 1;
    
    long long prev2 = 0, prev1 = 1, current;
    
    for (int i = 2; i <= max_check; i++) {
        current = prev1 + prev2;
        
        if (current == target) {
            return i;
        }
        
        if (current > target) {
            break; // Target is not a Fibonacci number
        }
        
        prev2 = prev1;
        prev1 = current;
    }
    
    return -1;
}

/**
 * Calculate sum of first n Fibonacci numbers
 * @param n: Number of terms to sum
 * @return: Sum of first n Fibonacci numbers
 */
long long fibonacci_sum(int n) {
    if (n <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return 0; // F(0) = 0
    }
    
    if (n == 2) {
        return 1; // F(0) + F(1) = 0 + 1 = 1
    }
    
    // Sum of first n Fibonacci numbers = F(n+2) - 1
    return fibonacci_optimized(n + 1) - 1;
}

/**
 * Performance comparison between different methods
 * @param n: Position to calculate
 */
void performance_comparison(int n) {
    clock_t start, end;
    double cpu_time_used;
    long long result;
    
    printf("\nPerformance Comparison for F(%d):\n", n);
    printf("================================\n");
    
    // Recursive method (only for small n to avoid timeout)
    if (n <= 35) {
        start = clock();
        result = fibonacci_recursive(n);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Recursive:    Result = %lld, Time = %f seconds\n", result, cpu_time_used);
    } else {
        printf("Recursive:    Skipped (too slow for n > 35)\n");
    }
    
    // Memoization
    start = clock();
    result = fibonacci_memoization(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Memoization:  Result = %lld, Time = %f seconds\n", result, cpu_time_used);
    
    // Tabulation
    start = clock();
    result = fibonacci_tabulation(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tabulation:   Result = %lld, Time = %f seconds\n", result, cpu_time_used);
    
    // Optimized
    start = clock();
    result = fibonacci_optimized(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Optimized:    Result = %lld, Time = %f seconds\n", result, cpu_time_used);
}

/**
 * Test function to demonstrate Fibonacci algorithms
 */
void test_fibonacci() {
    printf("Fibonacci Sequence using Dynamic Programming\n");
    printf("============================================\n");
    
    // Test Case 1: Basic Fibonacci calculations
    printf("\nTest Case 1: Basic Fibonacci Calculations\n");
    printf("-----------------------------------------\n");
    
    int test_values[] = {0, 1, 5, 10, 15, 20};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_values[i];
        long long result = fibonacci_optimized(n);
        printf("F(%d) = %lld\n", n, result);
    }
    
    // Test Case 2: Fibonacci sequence generation
    printf("\nTest Case 2: Fibonacci Sequence Generation\n");
    printf("------------------------------------------\n");
    
    print_fibonacci_sequence(15);
    
    // Test Case 3: Check if numbers are Fibonacci
    printf("\nTest Case 3: Fibonacci Number Verification\n");
    printf("------------------------------------------\n");
    
    long long test_numbers[] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 100};
    int num_number_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (int i = 0; i < num_number_tests; i++) {
        int position = is_fibonacci_number(test_numbers[i], 50);
        if (position != -1) {
            printf("%lld is F(%d)\n", test_numbers[i], position);
        } else {
            printf("%lld is NOT a Fibonacci number\n", test_numbers[i]);
        }
    }
    
    // Test Case 4: Sum of Fibonacci numbers
    printf("\nTest Case 4: Sum of Fibonacci Numbers\n");
    printf("-------------------------------------\n");
    
    for (int n = 1; n <= 10; n++) {
        long long sum = fibonacci_sum(n);
        printf("Sum of first %d Fibonacci numbers = %lld\n", n, sum);
    }
    
    // Test Case 5: Performance comparison
    printf("\nTest Case 5: Performance Comparison\n");
    printf("-----------------------------------\n");
    
    performance_comparison(30);
    performance_comparison(40);
    
    // Test Case 6: Large Fibonacci numbers
    printf("\nTest Case 6: Large Fibonacci Numbers\n");
    printf("------------------------------------\n");
    
    int large_values[] = {50, 60, 70, 80, 90};
    int num_large_tests = sizeof(large_values) / sizeof(large_values[0]);
    
    for (int i = 0; i < num_large_tests; i++) {
        int n = large_values[i];
        long long result = fibonacci_optimized(n);
        printf("F(%d) = %lld\n", n, result);
    }
    
    // Test Case 7: Edge cases
    printf("\nTest Case 7: Edge Cases\n");
    printf("-----------------------\n");
    
    printf("F(-1) = %lld (should show error)\n", fibonacci_optimized(-1));
    printf("F(0) = %lld\n", fibonacci_optimized(0));
    printf("F(1) = %lld\n", fibonacci_optimized(1));
    printf("F(2) = %lld\n", fibonacci_optimized(2));
}

int main() {
    test_fibonacci();
    return 0;
}