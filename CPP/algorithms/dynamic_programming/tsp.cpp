#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;
int n; // number of cities
vector<vector<int>> dist; // adjacency matrix of distances
vector<vector<int>> dp;   // dp[mask][i]: minimum cost to visit all cities in 'mask' ending at city 'i'

// Function to solve TSP using DP and Bitmasking
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // return to the starting city
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int minCost = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city);
            minCost = min(minCost, newCost);
        }
    }

    return dp[mask][pos] = minCost;
}

int main() {
    // Sample 4-city TSP graph
    dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    n = dist.size();

    // Initialize dp array with -1
    dp = vector<vector<int>>(1 << n, vector<int>(n, -1));

    int result = tsp(1, 0); // start from city 0, visited mask = 1 (only city 0 visited)
    cout << "Minimum TSP cost: " << result << endl;

    return 0;
}
