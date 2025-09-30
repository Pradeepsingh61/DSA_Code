"""
0/1 Knapsack Problem using Space-Optimized Dynamic Programming

Problem:
Given a list of item weights 'weight' and corresponding profits 'profit', 
and a knapsack capacity 'W', find the maximum total profit for items 
that can fit into the knapsack without exceeding its capacity. 
Each item can be taken at most once.

Algorithm:
1. Use a 1D DP array 'dp' of size (W+1) to store maximum profit for each weight.
2. Iterate over each item:
   a. Traverse the DP array in reverse (from W to item_weight):
      - This ensures we do not reuse the same item multiple times.
   b. Update dp[w] = max(dp[w], dp[w - item_weight] + item_profit)
3. The answer is stored in dp[W].

Time Complexity: O(n * W)
  - We iterate over n items and for each item up to W weights.

Space Complexity: O(W)
  - Only a single array of size W+1 is used.
"""

def knapSack(W, weight, profit, n):
    # Initialize DP array with 0 for all weights
    dp = [0 for _ in range(W + 1)]

    # Iterate over each item
    for i in range(1, n + 1):
        # Traverse weights in reverse to avoid using the same item twice
        for w in range(W, 0, -1):
            if weight[i - 1] <= w:
                dp[w] = max(dp[w], dp[w - weight[i - 1]] + profit[i - 1])
    
    return dp[W]

# Example usage
profit = [60, 100, 120]
weight = [10, 20, 30]
W = 50
n = len(profit)

print("Maximum profit:", knapSack(W, weight, profit, n))
