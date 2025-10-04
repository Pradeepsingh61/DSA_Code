# Section: Dynamic Programming

"""
Algorithm: 0/1 Knapsack Problem
Purpose: Determines the maximum value that can be obtained by selecting items
         without exceeding the weight capacity, where each item can be chosen at most once.

Time Complexity: O(n * W), where n is the number of items and W is the knapsack capacity
Space Complexity: O(n * W), for the DP table

Approach:
Uses bottom-up dynamic programming to fill a table where dp[i][w] represents the
maximum value achievable using the first i items with total weight not exceeding w.
"""

def knapsack_01(weights, values, capacity):
    # Input validation
    if not isinstance(weights, list) or not isinstance(values, list):
        raise ValueError("Weights and values must be lists.")
    if not isinstance(capacity, int) or capacity < 0:
        raise ValueError("Capacity must be a non-negative integer.")
    if len(weights) != len(values):
        raise ValueError("Weights and values lists must be of the same length.")

    n = len(weights)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    # Build DP table
    for i in range(1, n + 1):
        for w in range(capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1])
            else:
                dp[i][w] = dp[i - 1][w]

    return dp[n][capacity]


# 🧪 Test Cases
if __name__ == "__main__":
    test_cases = [
        ([1, 2, 3], [10, 15, 40], 6, 65),
        ([2, 3, 4, 5], [3, 4, 5, 6], 5, 7),
        ([1, 2, 3], [10, 20, 30], 0, 0),
        ([1], [100], 1, 100),
        ([1, 2], [10, 20], 1, 10),
        ([4, 5, 1], [1, 2, 3], 4, 3)
    ]

    for i, (weights, values, cap, expected) in enumerate(test_cases):
        result = knapsack_01(weights, values, cap)
        print(f"Test Case {i+1}: knapsack_01({weights}, {values}, {cap}) = {result}")
        assert result == expected, f"Failed on test case {i+1}"
