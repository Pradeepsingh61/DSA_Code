"""
Longest Common Subsequence (LCS) Algorithm
------------------------------------------

🔍 Problem:
Given two strings, find the longest sequence that appears in both strings in the same order,
but not necessarily consecutively.

📈 Time Complexity: O(m * n)
📦 Space Complexity: O(m * n)
Where m and n are the lengths of the input strings.

✅ Example:
Input: str1 = "AGGTAB", str2 = "GXTXAYB"
Output: "GTAB"
"""

def longest_common_subsequence(str1: str, str2: str) -> str:
    """
    Computes the Longest Common Subsequence (LCS) between two strings using dynamic programming.

    Parameters:
    - str1 (str): First input string
    - str2 (str): Second input string

    Returns:
    - str: The longest common subsequence
    """

    # Validate input types
    if not isinstance(str1, str) or not isinstance(str2, str):
        raise ValueError("Both inputs must be strings.")

    # Handle empty string edge case
    if not str1 or not str2:
        return ""

    m, n = len(str1), len(str2)

    # Initialize a 2D DP table with empty strings
    dp = [["" for _ in range(n + 1)] for _ in range(m + 1)]

    # Fill the DP table
    for i in range(m):
        for j in range(n):
            if str1[i] == str2[j]:
                # Characters match: extend the subsequence
                dp[i + 1][j + 1] = dp[i][j] + str1[i]
            else:
                # Characters don't match: take the longer of two options
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j], key=len)

    # Final cell contains the LCS
    return dp[m][n]


# 🧪 Test Cases
if __name__ == "__main__":
    test_cases = [
        ("AGGTAB", "GXTXAYB", "GTAB"),         # Typical case
        ("ABCDEF", "FBDAMN", "BD"),            # Partial match
        ("", "ABC", ""),                       # Empty first string
        ("ABC", "", ""),                       # Empty second string
        ("ABC", "ABC", "ABC"),                 # Identical strings
        ("ABC", "DEF", ""),                    # No common subsequence
        ("AABBA", "ABABA", "ABBA"),            # Repeated characters
    ]

    for str1, str2, expected in test_cases:
        result = longest_common_subsequence(str1, str2)
        print(f"LCS('{str1}', '{str2}') = '{result}' | Expected: '{expected}' | {'✅' if result == expected else '❌'}")
