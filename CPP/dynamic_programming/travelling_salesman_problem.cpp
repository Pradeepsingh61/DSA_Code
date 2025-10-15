#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n; // Number of cities
vector<vector<int>> dist;
vector<vector<int>> dp;

// Recursive function using DP + Bitmasking
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)  // all cities visited
        return dist[pos][0];   // return to starting city

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // if city not visited
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    // Example Input
    n = 4;
    dist = {
        {0, 20, 42, 25},
        {20, 0, 30, 34},
        {42, 30, 0, 10},
        {25, 34, 10, 0}
    };

    dp.assign(1 << n, vector<int>(n, -1));

    cout << "Travelling Salesman Problem\n";
    cout << "Number of cities: " << n << "\n";
    cout << "Distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(4) << dist[i][j] << " ";
        cout << endl;
    }

    int result = tsp(1, 0);
    cout << "\nMinimum cost to visit all cities and return: " << result << endl;

    return 0;
}
