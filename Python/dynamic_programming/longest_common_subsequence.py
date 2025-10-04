# Section: Dynamic Programming

"""
Algorithm: Longest Common Subsequence (LCS)
Purpose: Finds the length of the longest subsequence common to two strings.

Time Complexity: O(m * n), where m and n are lengths of the input strings
Space Complexity: O(m * n), for the DP table

Description:
Uses bottom-up dynamic programming to build a table where dp[i][j] represents
the length of the LCS of the first i characters of string1 and first j characters of string2.
"""

def longest_common_subsequence(string1, string2):
    # Input validation
    if not isinstance(string1, str) or not isinstance(string2, str):
        raise ValueError("Both inputs must be strings.")

    m, n = len(string1), len(string2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # Build DP table
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if string1[i - 1] == string2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    return dp[m][n]


# 🧪 Test Cases
if __name__ == "__main__":
    test_cases = [
        ("abcde", "ace", 3),
        ("abc", "abc", 3),
        ("abc", "def", 0),
        ("", "", 0),
        ("a", "a", 1),
        ("abcdef", "fbdamn", 2)
    ]

    for i, (s1, s2, expected) in enumerate(test_cases):
        result = longest_common_subsequence(s1, s2)
        print(f"Test Case {i+1}: LCS('{s1}', '{s2}') = {result}")
        assert result == expected, f"Failed on test case {i+1}"
