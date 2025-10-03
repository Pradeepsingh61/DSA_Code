#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to find minimum number of attempts needed
int eggDrop(int eggs, int floors) {
    vector<vector<int>> dp(eggs + 1, vector<int>(floors + 1, 0));

    // Base cases
    for (int i = 1; i <= eggs; i++)
        dp[i][0] = 0, dp[i][1] = 1;
    for (int j = 1; j <= floors; j++)
        dp[1][j] = j;

    // Fill the rest using DP
    for (int e = 2; e <= eggs; e++) {
        for (int f = 2; f <= floors; f++) {
            dp[e][f] = INT_MAX;
            for (int k = 1; k <= f; k++) {
                int attempts = 1 + max(dp[e - 1][k - 1], dp[e][f - k]);
                dp[e][f] = min(dp[e][f], attempts);
            }
        }
    }

    return dp[eggs][floors];
}

int main() {
    int eggs, floors;
    cout << "Enter number of eggs: ";
    cin >> eggs;
    cout << "Enter number of floors: ";
    cin >> floors;

    int minAttempts = eggDrop(eggs, floors);
    cout << "Minimum number of attempts needed: " << minAttempts << endl;

    return 0;
}
