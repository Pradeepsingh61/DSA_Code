from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        """
        Max profit with at most 2 transactions using DP tabulation.
        """
        if not prices:
            return 0
        
        n = len(prices)
        max_transactions = 2

        # dp[i][buy][c] -> max profit from day i with 'buy' state and c transactions left
        dp = [[[0]*(max_transactions+1) for _ in range(2)] for _ in range(n+1)]

        # Fill table from last day to first
        for i in range(n-1, -1, -1):
            for c in range(1, max_transactions+1):
                # If we can buy
                dp[i][1][c] = max(-prices[i] + dp[i+1][0][c], dp[i+1][1][c])
                # If we must sell
                dp[i][0][c] = max(prices[i] + dp[i+1][1][c-1], dp[i+1][0][c])

        # Start from day 0, can buy, 2 transactions left
        return dp[0][1][2]

# -------------------------------
# Test Cases
# -------------------------------
if __name__ == "__main__":
    solution = Solution()
    
    test_cases = [
        ([3,3,5,0,0,3,1,4], 6),
        ([1,2,3,4,5], 4),
        ([7,6,4,3,1], 0),
        ([1,2], 1),
        ([1], 0)
    ]
    
    for prices, expected in test_cases:
        result = solution.maxProfit(prices)
        print(f"Prices: {prices} => Max Profit: {result} | Expected: {expected}")
