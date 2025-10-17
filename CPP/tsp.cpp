#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int tsp(int mask, int pos, vector<vector<int>> &dist, vector<vector<int>> &dp, int n) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];   // return to start
    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp, n);
            ans = min(ans, newCost);
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    int n = 4;
    vector<vector<int>> dist = {
        {0, 20, 42, 35},
        {20, 0, 30, 34},
        {42, 30, 0, 12},
        {35, 34, 12, 0}
    };

    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    cout << "Minimum TSP cost: " << tsp(1, 0, dist, dp, n) << endl;
    return 0;
}
