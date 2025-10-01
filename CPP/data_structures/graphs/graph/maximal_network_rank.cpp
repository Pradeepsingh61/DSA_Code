#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalNetworkRank(int numCities, vector<vector<int>>& roads) {
        vector<int> degree(numCities, 0);
        vector<vector<int>> adjacency(numCities);
        int maxRank = 0;

        for (int i = 0; i < roads.size(); i++) {
            int cityA = roads[i][0];
            int cityB = roads[i][1];

            adjacency[cityA].push_back(cityB);
            adjacency[cityB].push_back(cityA);

            degree[cityA]++;
            degree[cityB]++;
        }

        for (int cityA = 0; cityA < numCities; cityA++) {
            for (int cityB = cityA + 1; cityB < numCities; cityB++) {
                int rank = degree[cityA] + degree[cityB];
                if (count(adjacency[cityA].begin(), adjacency[cityA].end(), cityB)) {
                    rank--;
                }
                maxRank = max(maxRank, rank);
            }
        }

        return maxRank;
    }
};

int main() {
    Solution solution;

    int numCities = 4;
    vector<vector<int>> roads = {
        {0, 1},
        {0, 3},
        {1, 2},
        {1, 3}
    };

    int result = solution.maximalNetworkRank(numCities, roads);
    cout << "Maximal Network Rank: " << result << endl;

    return 0;
}
