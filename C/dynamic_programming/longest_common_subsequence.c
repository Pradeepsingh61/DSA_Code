/*
 * Algorithm: Longest Common Subsequence (LCS) using Dynamic Programming
 * Description: Find the length and actual LCS between two strings
 * Time Complexity: O(m * n) where m, n are lengths of strings
 * Space Complexity: O(m * n) for standard DP, O(min(m, n)) for optimized
 * Author: DSA Code Repository
 * Date: 2025-10-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 1000

/**
 * Recursive LCS solution (naive approach for comparison)
 * @param str1: First string
 * @param str2: Second string
 * @param m: Length of first string
 * @param n: Length of second string
 * @return: Length of LCS
 */
int lcs_recursive(char* str1, char* str2, int m, int n) {
    // Base case: if either string is empty
    if (m == 0 || n == 0) {
        return 0;
    }
    
    // If last characters match
    if (str1[m - 1] == str2[n - 1]) {
        return 1 + lcs_recursive(str1, str2, m - 1, n - 1);
    }
    
    // If last characters don't match
    int lcs1 = lcs_recursive(str1, str2, m - 1, n);
    int lcs2 = lcs_recursive(str1, str2, m, n - 1);
    
    return (lcs1 > lcs2) ? lcs1 : lcs2;
}

/**
 * LCS using memoization (top-down DP)
 * @param str1: First string
 * @param str2: Second string
 * @param m: Length of first string
 * @param n: Length of second string
 * @param memo: Memoization table
 * @return: Length of LCS
 */
int lcs_memoization_util(char* str1, char* str2, int m, int n, int memo[][MAX_LEN]) {
    // Base case
    if (m == 0 || n == 0) {
        return 0;
    }
    
    // If already computed
    if (memo[m][n] != -1) {
        return memo[m][n];
    }
    
    // If characters match
    if (str1[m - 1] == str2[n - 1]) {
        memo[m][n] = 1 + lcs_memoization_util(str1, str2, m - 1, n - 1, memo);
    } else {
        // If characters don't match
        int lcs1 = lcs_memoization_util(str1, str2, m - 1, n, memo);
        int lcs2 = lcs_memoization_util(str1, str2, m, n - 1, memo);
        memo[m][n] = (lcs1 > lcs2) ? lcs1 : lcs2;
    }
    
    return memo[m][n];
}

/**
 * LCS using memoization wrapper
 * @param str1: First string
 * @param str2: Second string
 * @return: Length of LCS
 */
int lcs_memoization(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    if (m >= MAX_LEN || n >= MAX_LEN) {
        printf("Error: String length exceeds maximum limit\n");
        return -1;
    }
    
    // Initialize memoization table
    int memo[MAX_LEN][MAX_LEN];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j] = -1;
        }
    }
    
    return lcs_memoization_util(str1, str2, m, n, memo);
}

/**
 * LCS using tabulation (bottom-up DP)
 * @param str1: First string
 * @param str2: Second string
 * @return: Length of LCS
 */
int lcs_tabulation(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // Create DP table
    int dp[m + 1][n + 1];
    
    // Fill the DP table bottom-up
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Base case: empty string
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            // Characters match
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            // Characters don't match
            else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    return dp[m][n];
}

/**
 * LCS with space optimization (O(min(m,n)) space)
 * @param str1: First string
 * @param str2: Second string
 * @return: Length of LCS
 */
int lcs_space_optimized(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // Make sure str1 is the shorter string for space optimization
    if (m > n) {
        return lcs_space_optimized(str2, str1);
    }
    
    // Use only two rows instead of full table
    int prev[m + 1], curr[m + 1];
    
    // Initialize previous row
    for (int i = 0; i <= m; i++) {
        prev[i] = 0;
    }
    
    // Fill the table
    for (int j = 1; j <= n; j++) {
        curr[0] = 0; // First column is always 0
        
        for (int i = 1; i <= m; i++) {
            if (str1[i - 1] == str2[j - 1]) {
                curr[i] = 1 + prev[i - 1];
            } else {
                curr[i] = (prev[i] > curr[i - 1]) ? prev[i] : curr[i - 1];
            }
        }
        
        // Copy current row to previous row for next iteration
        for (int i = 0; i <= m; i++) {
            prev[i] = curr[i];
        }
    }
    
    return prev[m];
}

/**
 * Find and print the actual LCS string
 * @param str1: First string
 * @param str2: Second string
 * @param lcs: Buffer to store LCS
 * @return: Length of LCS
 */
int find_lcs_string(char* str1, char* str2, char* lcs) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // Create DP table
    int dp[m + 1][n + 1];
    
    // Fill the DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    // Backtrack to find the actual LCS
    int lcs_length = dp[m][n];
    lcs[lcs_length] = '\0'; // Null terminate
    
    int i = m, j = n, index = lcs_length - 1;
    
    while (i > 0 && j > 0) {
        // If characters match, include in LCS
        if (str1[i - 1] == str2[j - 1]) {
            lcs[index] = str1[i - 1];
            i--;
            j--;
            index--;
        }
        // Move to the direction of larger value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    
    return lcs_length;
}

/**
 * Find all possible LCS strings (for when multiple LCS exist)
 * @param str1: First string
 * @param str2: Second string
 */
void find_all_lcs(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    
    // This is a complex operation, so we'll just print the count
    // and show one example LCS
    char lcs[MAX_LEN];
    int length = find_lcs_string(str1, str2, lcs);
    
    printf("LCS Length: %d\n", length);
    printf("One possible LCS: \"%s\"\n", lcs);
    
    // Note: Finding all LCS requires more complex recursive backtracking
    // which can be exponential in the worst case
}

/**
 * Calculate LCS for multiple string pairs and compare performance
 * @param pairs: Array of string pairs
 * @param num_pairs: Number of pairs
 */
void lcs_performance_analysis(char pairs[][2][100], int num_pairs) {
    printf("LCS Performance Analysis\n");
    printf("========================\n");
    
    for (int p = 0; p < num_pairs; p++) {
        printf("\nPair %d: \"%s\" and \"%s\"\n", p + 1, pairs[p][0], pairs[p][1]);
        printf("String lengths: %lu and %lu\n", strlen(pairs[p][0]), strlen(pairs[p][1]));
        
        clock_t start, end;
        double cpu_time_used;
        int result;
        
        // Recursive (only for small strings)
        if (strlen(pairs[p][0]) <= 15 && strlen(pairs[p][1]) <= 15) {
            start = clock();
            result = lcs_recursive(pairs[p][0], pairs[p][1], strlen(pairs[p][0]), strlen(pairs[p][1]));
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Recursive:      LCS = %d, Time = %f seconds\n", result, cpu_time_used);
        } else {
            printf("Recursive:      Skipped (too slow for large strings)\n");
        }
        
        // Memoization
        start = clock();
        result = lcs_memoization(pairs[p][0], pairs[p][1]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Memoization:    LCS = %d, Time = %f seconds\n", result, cpu_time_used);
        
        // Tabulation
        start = clock();
        result = lcs_tabulation(pairs[p][0], pairs[p][1]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tabulation:     LCS = %d, Time = %f seconds\n", result, cpu_time_used);
        
        // Space optimized
        start = clock();
        result = lcs_space_optimized(pairs[p][0], pairs[p][1]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Space Optimized: LCS = %d, Time = %f seconds\n", result, cpu_time_used);
        
        // Show actual LCS
        char lcs_str[MAX_LEN];
        find_lcs_string(pairs[p][0], pairs[p][1], lcs_str);
        printf("Actual LCS:     \"%s\"\n", lcs_str);
    }
}

/**
 * Special LCS applications
 */
void lcs_applications() {
    printf("\nLCS Applications and Variations\n");
    printf("===============================\n");
    
    // Application 1: File difference (like diff command)
    printf("\n1. File Difference Simulation:\n");
    char file1[] = "ABCDEFGHIJKLMNOP";
    char file2[] = "ABXDEFGHIXJKLQMNOP";
    char lcs[MAX_LEN];
    
    int lcs_len = find_lcs_string(file1, file2, lcs);
    printf("File 1: %s\n", file1);
    printf("File 2: %s\n", file2);
    printf("Common content: %s (length: %d)\n", lcs, lcs_len);
    printf("Similarity: %.2f%%\n", (double)lcs_len / strlen(file1) * 100);
    
    // Application 2: DNA sequence alignment
    printf("\n2. DNA Sequence Alignment:\n");
    char dna1[] = "ATCGATCGATCG";
    char dna2[] = "ATGCATCGATG";
    
    lcs_len = find_lcs_string(dna1, dna2, lcs);
    printf("DNA Sequence 1: %s\n", dna1);
    printf("DNA Sequence 2: %s\n", dna2);
    printf("Common subsequence: %s (length: %d)\n", lcs, lcs_len);
    
    // Application 3: Longest palindromic subsequence
    printf("\n3. Longest Palindromic Subsequence:\n");
    char str[] = "GEEKSFORGEEKS";
    char rev_str[MAX_LEN];
    
    // Reverse the string
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        rev_str[i] = str[len - 1 - i];
    }
    rev_str[len] = '\0';
    
    lcs_len = lcs_tabulation(str, rev_str);
    printf("String: %s\n", str);
    printf("Longest palindromic subsequence length: %d\n", lcs_len);
}

/**
 * Test function to demonstrate LCS algorithms
 */
void test_lcs() {
    printf("Longest Common Subsequence using Dynamic Programming\n");
    printf("====================================================\n");
    
    // Test Case 1: Basic LCS examples
    printf("\nTest Case 1: Basic LCS Examples\n");
    printf("-------------------------------\n");
    
    char str1[] = "AGGTAB";
    char str2[] = "GXTXAYB";
    char lcs[MAX_LEN];
    
    int length = find_lcs_string(str1, str2, lcs);
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("LCS: %s (Length: %d)\n", lcs, length);
    
    // Test Case 2: Edge cases
    printf("\nTest Case 2: Edge Cases\n");
    printf("-----------------------\n");
    
    char test_pairs[][2][50] = {
        {"", "ABC"},           // Empty string
        {"ABC", ""},           // Empty string
        {"ABC", "ABC"},        // Identical strings
        {"ABC", "DEF"},        // No common characters
        {"A", "A"},            // Single character match
        {"ABCD", "DCBA"},      // Reversed strings
        {"AAA", "AAA"},        // Repeated characters
        {"ABCDE", "ACE"}       // Simple subsequence
    };
    
    int num_test_pairs = sizeof(test_pairs) / sizeof(test_pairs[0]);
    
    for (int i = 0; i < num_test_pairs; i++) {
        int len = find_lcs_string(test_pairs[i][0], test_pairs[i][1], lcs);
        printf("LCS(\"%s\", \"%s\") = \"%s\" (Length: %d)\n", 
               test_pairs[i][0], test_pairs[i][1], lcs, len);
    }
    
    // Test Case 3: Performance comparison
    printf("\nTest Case 3: Performance Comparison\n");
    printf("-----------------------------------\n");
    
    char perf_pairs[][2][100] = {
        {"ABCDGH", "AEDFHR"},
        {"PROGRAMMING", "DYNAMIC"},
        {"LONGEST", "STONE"},
        {"ABCDEFGHIJKLMNOP", "ACEGIKMOQ"}
    };
    
    int num_perf_pairs = sizeof(perf_pairs) / sizeof(perf_pairs[0]);
    lcs_performance_analysis(perf_pairs, num_perf_pairs);
    
    // Test Case 4: Applications
    lcs_applications();
    
    // Test Case 5: Large string test
    printf("\nTest Case 5: Large String Test\n");
    printf("------------------------------\n");
    
    char large_str1[200], large_str2[200];
    
    // Generate large test strings
    strcpy(large_str1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcat(large_str1, "abcdefghijklmnopqrstuvwxyz");
    strcat(large_str1, "0123456789");
    
    strcpy(large_str2, "ACEGIKMOQSUWY");
    strcat(large_str2, "bdfhjlnprtvxz");
    strcat(large_str2, "13579");
    
    printf("Large string 1 length: %lu\n", strlen(large_str1));
    printf("Large string 2 length: %lu\n", strlen(large_str2));
    
    clock_t start = clock();
    int large_lcs_len = lcs_space_optimized(large_str1, large_str2);
    clock_t end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("LCS length: %d\n", large_lcs_len);
    printf("Time taken (space optimized): %f seconds\n", time_taken);
}

int main() {
    test_lcs();
    return 0;
}