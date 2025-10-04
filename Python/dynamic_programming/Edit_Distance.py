# Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
# You have the following three operations permitted on the string word1:

# Insert a character
# Delete a character
# Replace a character


# ask:
# Since this will be a functional problem, you don't have to take input. You just have to complete the function minDistance() that takes two strings word1 and word2 as its parameters.

# Custom Input:
# The input consists of two lines:
# The first line contains the initial string word1.
# The second line contains the target string word2.



def minDistance(word1, word2):
    m, n = len(word1), len(word2)
    dp = [[0]*(n+1) for i in range(m+1)]
    for i in range(m+1):
        dp[i][0] = i
    for j in range(n+1):
        dp[0][j] = j
    for i in range(1, m+1):
        for j in range(1, n+1):
            if word1[i-1] == word2[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
    return dp[m][n]








# Input:
family
smile
# Output:
3
Explanation:
family → amily (delete 'f')
amily → smily (replace 'a' with 's')
smily → smile (replace 'y' with 'e')

# Input:
intention
execution
# Output:
5
# Explanation
intention → inention (remove 't')
inention → enention (replace 'i' with 'e')
enention → exention (replace 'n' with 'x')
exention → exection (replace 'n' with 'c')
exection → execution (insert 'u')