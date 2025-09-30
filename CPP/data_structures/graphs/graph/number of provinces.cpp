#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Algorithm: Number of Provinces (Connected Components)
=====================================================

Problem:
Given an adjacency matrix representing connections between cities,
we need to count the number of provinces. 
A province is defined as a group of cities directly or indirectly connected.

Approach:
1. Convert the adjacency matrix into an adjacency list for efficient traversal.
   - Skip self-loops (i != j).
2. Use Depth-First Search (DFS) to explore connected nodes:
   - For every unvisited city, start a DFS and mark all reachable cities.
   - Each DFS call from an unvisited city represents one province.
3. Count how many times DFS is initiated → number of provinces.

=====================================================
Time Complexity:
- Converting adjacency matrix to adjacency list: O(V^2)
- DFS traversal of all nodes and edges: O(V + E)
  (For a dense graph, E ≈ V^2, so worst case O(V^2))
Overall: O(V^2)

Space Complexity:
- Adjacency list storage: O(V + E)
- Visited array: O(V)
- Recursive call stack (DFS): O(V) in worst case
Overall: O(V + E)
=====================================================
*/

class Solution {
private:
    // Depth-First Search helper
    void dfs(int node, vector<int> adjacencyList[], vector<int>& visited) {
        visited[node] = 1; // mark current city as visited
        for (auto neighbor : adjacencyList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adjacencyList, visited);
            }
        }
    }

public:
    int numProvinces(vector<vector<int>> adjacencyMatrix, int V) {
        // Convert adjacency matrix to adjacency list
        vector<int> adjacencyList[V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adjacencyMatrix[i][j] == 1 && i != j) {
                    adjacencyList[i].push_back(j);
                    adjacencyList[j].push_back(i);
                }
            }
        }

        // Visited array to track explored cities
        vector<int> visited(V, 0);
        int provinceCount = 0;

        // Perform DFS for each unvisited city
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                provinceCount++;
                dfs(i, adjacencyList, visited);
            }
        }

        return provinceCount;
    }
};
