from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        """
        Max profit with only one transaction using DP tabulation.
        """
        if not prices:
            return 0
        
        n = len(prices)
        # dp[i][0] = max profit on day i if we cannot buy (holding stock)
        # dp[i][1] = max profit on day i if we can buy (not holding stock)
        dp = [[0]*2 for _ in range(n+1)]
        
        # Base case: dp[n][*] = 0 (no days left)
        dp[n][0] = dp[n][1] = 0
        
        # Fill table from last day to first
        for i in range(n-1, -1, -1):
            # If we can buy, we have two options: buy today or skip
            dp[i][1] = max(-prices[i] + dp[i+1][0], dp[i+1][1])
            # If we cannot buy (must sell), two options: sell today or skip
            dp[i][0] = max(prices[i] + dp[i+1][1], dp[i+1][0])
        
        # Start from day 0 and not holding stock
        return dp[0][1]

# -------------------------------
# Test Cases
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
