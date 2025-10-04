# Given a string s, find the length of the longest palindromic subsequence in s.
# A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.



#  this is a functional problem, you don't have to input anything.


def longestPalindromeSubseq(s):
    n = len(s)
    dp = [[0] * n for _ in range(n)]
    for i in range(n):
        dp[i][i] = 1
    for length in range(2, n+1):
        for i in range(n - length + 1):
            j = i + length - 1
            if s[i] == s[j]:
                dp[i][j] = 2 + (dp[i+1][j-1] if j-1 >= i+1 else 0)
            else:
                dp[i][j] = max(dp[i+1][j], dp[i][j-1])
    return dp[0][n-1]




# Sample Input
7
xbcrcdb
# Sample Output
5
# Explanation
"bcrcb" is the longest palindromic subsequence.

# Sample Input
4
cbbd
# Sample Output
2
# Explanation
"bb" is the longest palindromic subsequence.