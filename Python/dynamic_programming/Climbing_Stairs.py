from typing import List

class Solution:
    def climbStairs(self, n: int) -> int:
        """
        Number of distinct ways to climb to the top using DP tabulation.
        Recurrence: dp[i] = dp[i-1] + dp[i-2]
        Base Cases:
            dp[0] = 1  # one way to stay at the ground (do nothing)
            dp[1] = 1  # one way to climb one step
        """
        if n <= 1:
            return 1
        
        dp = [0] * (n + 1)
        dp[0], dp[1] = 1, 1
        
        for i in range(2, n + 1):
            dp[i] = dp[i - 1] + dp[i - 2]
        
        return dp[n]


# -------------------------------
# Test Cases
# -------------------------------
if __name__ == "__main__":
    solution = Solution()
    
    test_cases = [
        (1, 1),
        (2, 2),
        (3, 3),
        (4, 5),
        (5, 8),
        (10, 89)
    ]
    
    for n, expected in test_cases:
        result = solution.climbStairs(n)
        print(f"Steps: {n} => Ways: {result} | Expected: {expected}")
