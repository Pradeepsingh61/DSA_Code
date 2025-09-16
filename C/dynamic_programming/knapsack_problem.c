C Code for 0/1 Knapsack Problem


#include <stdio.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack problem using Dynamic Programming
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    // Build the table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // dp[n][W] holds the maximum value that can be attained
    return dp[n][W];
}

int main() {
    int n, W;

    // Input: number of items and the capacity of knapsack
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    printf("Enter the capacity of knapsack: ");
    scanf("%d", &W);

    int val[n], wt[n];

    // Input: values and weights of the items
    printf("Enter the values of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    // Call knapsack function
    int result = knapsack(W, wt, val, n);

    printf("Maximum value that can be obtained = %d\n", result);

    return 0;
}
