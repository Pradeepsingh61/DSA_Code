/*
 * Longest Common Subsequence (LCS) Algorithm
 * 
 * Description:
 * The Longest Common Subsequence algorithm finds the longest subsequence common to two sequences.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements
 * without changing the order of the remaining elements.
 * 
 * This implementation uses dynamic programming with a 2D table to solve the problem:
 * 1. Create a table to store lengths of LCS for all subproblems
 * 2. Fill the table in bottom-up manner
 * 3. The value in dp[m][n] contains the length of LCS
 * 4. Reconstruct the LCS using the filled table
 * 
 * Time Complexity: O(m*n) where m and n are lengths of the two sequences
 * Space Complexity: O(m*n) for the DP table
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to find the length of LCS and the actual LCS
pair<int, string> longestCommonSubsequence(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    
    // Create a table to store lengths of LCS for all subproblems
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill dp[][] in bottom-up manner
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // Length of LCS is dp[m][n]
    int lcsLength = dp[m][n];
    
    // Reconstruct the LCS
    string lcs = "";
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        // If current characters match, include in LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs;
            i--;
            j--;
        }
        // Move in the direction of larger value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return {lcsLength, lcs};
}

// Function to print the DP table (for educational purposes)
void printDPTable(const string& X, const string& Y, const vector<vector<int>>& dp) {
    int m = X.length();
    int n = Y.length();
    
    cout << "DP Table:" << endl;
    cout << "    ";
    for (int j = 0; j < n; j++) {
        cout << Y[j] << " ";
    }
    cout << endl;
    
    for (int i = 0; i <= m; i++) {
        if (i == 0) {
            cout << "  ";
        } else {
            cout << X[i - 1] << " ";
        }
        
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

// Main function with test cases
int main() {
    // Test Case 1: Basic example
    cout << "Test Case 1:" << endl;
    string X1 = "ABCDGH";
    string Y1 = "AEDFHR";
    cout << "String 1: " << X1 << endl;
    cout << "String 2: " << Y1 << endl;
    
    auto result1 = longestCommonSubsequence(X1, Y1);
    cout << "Length of LCS: " << result1.first << endl;
    cout << "LCS: " << result1.second << endl << endl;
    
    // Test Case 2: No common characters
    cout << "Test Case 2:" << endl;
    string X2 = "ABC";
    string Y2 = "DEF";
    cout << "String 1: " << X2 << endl;
    cout << "String 2: " << Y2 << endl;
    
    auto result2 = longestCommonSubsequence(X2, Y2);
    cout << "Length of LCS: " << result2.first << endl;
    cout << "LCS: " << result2.second << endl << endl;
    
    // Test Case 3: One string is a subsequence of the other
    cout << "Test Case 3:" << endl;
    string X3 = "ABCDEFG";
    string Y3 = "ACG";
    cout << "String 1: " << X3 << endl;
    cout << "String 2: " << Y3 << endl;
    
    auto result3 = longestCommonSubsequence(X3, Y3);
    cout << "Length of LCS: " << result3.first << endl;
    cout << "LCS: " << result3.second << endl << endl;
    
    // Test Case 4: Both strings are identical
    cout << "Test Case 4:" << endl;
    string X4 = "PROGRAMMING";
    string Y4 = "PROGRAMMING";
    cout << "String 1: " << X4 << endl;
    cout << "String 2: " << Y4 << endl;
    
    auto result4 = longestCommonSubsequence(X4, Y4);
    cout << "Length of LCS: " << result4.first << endl;
    cout << "LCS: " << result4.second << endl;
    
    return 0;
}