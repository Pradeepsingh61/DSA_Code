from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if not prices:
            return 0

        n = len(prices)
        # Initialize DP table: n days x 2 states (0: not holding, 1: holding)
        dp = [[0]*2 for _ in range(n)]

        # Base cases
        dp[0][0] = 0           # Not holding stock on first day
        dp[0][1] = -prices[0]  # Buy stock on first day

        # Fill DP table
        for i in range(1, n):
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  # sell today or do nothing
            dp[i][1] = max(dp[i-1][1], -prices[i])              # buy today or do nothing

        return dp[n-1][0]

# -------------------------------
# Test cases
# -------------------------------
if __name__ == "__main__":
    solution = Solution()
    
    test_cases = [
        ([7,1,5,3,6,4], 5),
        ([7,6,4,3,1], 0),
        ([], 0),
        ([5], 0),
        ([1,2,3,4,5], 4),
        ([3,3,3,3], 0)
    ]
    
    for prices, expected in test_cases:
        result = solution.maxProfit(prices)
        print(f"Prices: {prices} => Max Profit: {result} | Expected: {expected}")
