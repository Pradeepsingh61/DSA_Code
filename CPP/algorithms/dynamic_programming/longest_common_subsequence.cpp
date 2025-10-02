/*
 * Algorithm: Longest Common Subsequence (LCS)
 * Language: C++
 * Description: Computes the length of the longest subsequence common to two strings.
 *              A subsequence is a sequence that appears in the same relative order, 
 *              but not necessarily contiguous.
 * Time Complexity: O(n*m) where n = length of first string, m = length of second string
 * Space Complexity: O(n*m)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Function to compute the length of LCS between two strings.
 * Uses bottom-up Dynamic Programming approach.
 *
 * @param s1 First input string
 * @param s2 Second input string
 * @return Length of the longest common subsequence
 */
int longestCommonSubsequence(const string &s1, const string &s2) {
    int n = s1.size();
    int m = s2.size();

    // DP table initialization (n+1 x m+1)
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // Characters match → extend LCS by 1
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // Characters don't match → take max of ignoring one character
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m]; // Length of LCS
}

/**
 * Function to reconstruct the LCS string from the DP table.
 *
 * @param s1 First input string
 * @param s2 Second input string
 * @param dp DP table filled by longestCommonSubsequence
 * @return LCS string
 */
string reconstructLCS(const string &s1, const string &s2, const vector<vector<int>> &dp) {
    string lcs = "";
    int i = s1.size(), j = s2.size();

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs += s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

/**
 * Test function for LCS implementation
 */
void testLCS() {
    vector<pair<string, string>> testCases = {
        {"AGGTAB", "GXTXAYB"},    // LCS: "GTAB"
        {"ABCDEF", "AEBDF"},      // LCS: "ABDF"
        {"HELLO", "WORLD"},       // LCS: "LO"
        {"", "ABC"},              // LCS: ""
        {"ABC", ""}               // LCS: ""
    };

    for (int i = 0; i < testCases.size(); i++) {
        string s1 = testCases[i].first;
        string s2 = testCases[i].second;

        int n = s1.size();
        int m = s2.size();

        // Compute DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i1 = 1; i1 <= n; i1++) {
            for (int j1 = 1; j1 <= m; j1++) {
                if (s1[i1 - 1] == s2[j1 - 1]) dp[i1][j1] = 1 + dp[i1 - 1][j1 - 1];
                else dp[i1][j1] = max(dp[i1 - 1][j1], dp[i1][j1 - 1]);
            }
        }

        int lcsLength = dp[n][m];
        string lcsStr = reconstructLCS(s1, s2, dp);

        cout << "Test Case " << i + 1 << ":\n";
        cout << "String 1: " << s1 << "\n";
        cout << "String 2: " << s2 << "\n";
        cout << "LCS Length: " << lcsLength << "\n";
        cout << "LCS: " << lcsStr << "\n\n";
    }
}

int main() {
    cout << "Testing Longest Common Subsequence (LCS) Implementation\n\n";
    testLCS();
    return 0;
}