"""
0/1 Knapsack Problem using 2D Dynamic Programming
-------------------------------------------------

Objective:
This file explains the **2D DP approach** to the classic 0/1 Knapsack problem
in the simplest and most educational way possible.

Problem Statement:
Given N items, each with a certain weight and value, and a bag with a maximum weight
capacity (W), we must select items to maximize total value without exceeding W.

This is a perfect problem to understand **2D Dynamic Programming**.

-------------------------------------------------
Approach Explanation
-------------------------------------------------
We build a DP table (2D array) where:
    dp[i][w] = Maximum value we can achieve
               using the first i items (0..i-1) and
               capacity w.

Transition:
    If we do NOT take the ith item → dp[i][w] = dp[i-1][w]
    If we take the ith item (if it fits) → dp[i][w] = value[i-1] + dp[i-1][w - weight[i-1]]

Final Answer → dp[n][W]

-------------------------------------------------
Complexity Analysis:
-------------------------------------------------
Time Complexity:  O(N * W)
Space Complexity: O(N * W)
Where:
    N = number of items
    W = maximum capacity of the bag

"""

# -------------------------------------------------
# Step 1: Define the knapsack solver function
# -------------------------------------------------
def knapsack_2d(weights, values, capacity):
    """
    Solves the 0/1 Knapsack problem using 2D Dynamic Programming.

    Parameters:
        weights  : list of item weights
        values   : list of item values
        capacity : maximum capacity of the bag

    Returns:
        max_value       : Maximum value that can be obtained
        chosen_items    : List of item indices chosen
        dp              : 2D DP table
    """

    n = len(weights)

    # Create DP table with all 0s
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    # -------------------------------------------------
    # Step 2: Fill DP table
    # -------------------------------------------------
    for i in range(1, n + 1):
        for w in range(1, capacity + 1):

            # If current item's weight is more than current capacity, skip it
            if weights[i - 1] > w:
                dp[i][w] = dp[i - 1][w]

            else:
                # Either we take the item or we don’t — choose max
                include = values[i - 1] + dp[i - 1][w - weights[i - 1]]
                exclude = dp[i - 1][w]
                dp[i][w] = max(include, exclude)

    # -------------------------------------------------
    # Step 3: Backtrack to find chosen items
    # -------------------------------------------------
    chosen_items = []
    w = capacity

    for i in range(n, 0, -1):
        # If value comes from including the current item
        if dp[i][w] != dp[i - 1][w]:
            chosen_items.append(i - 1)
            w -= weights[i - 1]

    chosen_items.reverse()  # maintain original order

    # -------------------------------------------------
    # Step 4: Return final results
    # -------------------------------------------------
    max_value = dp[n][capacity]
    return max_value, chosen_items, dp


# -------------------------------------------------
# Step 5: Utility function to print DP table
# -------------------------------------------------
def print_dp_table(dp, weights, values):
    """
    Prints the DP table in a readable format with item info.
    """
    n = len(weights)
    cap = len(dp[0]) - 1

    print("\n2D DP Table (rows = items, columns = capacity):\n")
    header = ["w\\i"] + [str(i) for i in range(cap + 1)]
    print("\t".join(header))

    for i in range(n + 1):
        row_label = "0 (no items)" if i == 0 else f"{i} (wt={weights[i-1]}, val={values[i-1]})"
        row_values = [str(dp[i][j]) for j in range(cap + 1)]
        print(row_label + "\t" + "\t".join(row_values))


# -------------------------------------------------
# Step 6: Run example test cases
# -------------------------------------------------
if __name__ == "__main__":

    # Example 1 (Basic)
    weights = [2, 1, 3, 2]
    values = [12, 10, 20, 15]
    capacity = 5

    print("Example 1: Understanding 2D DP through 0/1 Knapsack\n")
    print(f"Weights : {weights}")
    print(f"Values  : {values}")
    print(f"Capacity: {capacity}\n")

    max_value, chosen, dp = knapsack_2d(weights, values, capacity)

    # Print DP table
    print_dp_table(dp, weights, values)

    print("\nFinal Results:")
    print(f"Maximum Value: {max_value}")
    print(f"Chosen Item Indices: {chosen}")
    print("Chosen Items (index → weight, value):")
    for idx in chosen:
        print(f"  Item {idx}: (w={weights[idx]}, v={values[idx]})")

    # Example 2 (Edge Case: small capacity)
    print("\nExample 2: Edge Case with Small Capacity")
    weights2 = [4, 5, 1]
    values2 = [1, 2, 3]
    cap2 = 4
    max_val2, chosen2, dp2 = knapsack_2d(weights2, values2, cap2)
    print(f"Weights: {weights2}, Values: {values2}, Capacity: {cap2}")
    print(f"Max Value = {max_val2}, Chosen = {chosen2}")
