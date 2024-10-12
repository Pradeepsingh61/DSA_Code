#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    0-1 Knapsack Problem:
    The problem involves selecting a subset of items to maximize the total value without exceeding a given weight limit.
    Each item can either be included (1) or excluded (0), hence "0-1".
    
    - We are given a set of `n` items, each with:
      1. A weight: `weights[i]`
      2. A value: `values[i]`
    - We need to determine the maximum value that can be obtained with a weight limit of `W`.
    
    Approach:
    Dynamic Programming (DP) is used to solve this problem efficiently. We build a DP table `dp[i][w]` where:
    - `i` represents the number of items considered so far.
    - `w` represents the current weight capacity.

    The DP formula is:
    - If item `i` is not included, the value is the same as without the item: `dp[i-1][w]`.
    - If item `i` is included (and it fits within the weight), the value is updated as: `dp[i-1][w - weights[i-1]] + values[i-1]`.

    Finally, `dp[n][W]` will contain the maximum value that can be obtained with the given weight limit.
*/

// Function to solve the 0-1 Knapsack Problem using Dynamic Programming
int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D DP table to store maximum value for each item and weight combination
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Iterate through all items and weights
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                // If the current item's weight is less than or equal to the current weight capacity `w`,
                // decide whether to include the item or not (taking the maximum of the two cases)
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                // If the item cannot be included because it exceeds the current weight `w`,
                // carry forward the value from the previous item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Return the maximum value that can be obtained with weight limit `W`
    return dp[n][W];
}

int main() {
    // Maximum weight capacity of the knapsack
    int W = 50;

    // List of weights of the items
    vector<int> weights = {10, 20, 30};

    // Corresponding values of the items
    vector<int> values = {60, 100, 120};

    // Number of items available
    int n = weights.size();

    // Call the knapsack function to get the maximum value
    int maxValue = knapsack(W, weights, values, n);

    // Output the result
    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}

/*
    Example Explanation:
    Consider 3 items with the following properties:
    - Item 1: weight = 10, value = 60
    - Item 2: weight = 20, value = 100
    - Item 3: weight = 30, value = 120
    The knapsack has a maximum capacity of 50 units of weight.

    Using dynamic programming, the algorithm determines that the maximum value we can fit into the knapsack 
    without exceeding the weight limit is 220, obtained by selecting Item 2 and Item 3.

    Time Complexity: O(n * W) where n is the number of items and W is the weight limit.
    Space Complexity: O(n * W) due to the 2D DP array.
*/
