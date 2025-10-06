#include <bits/stdc++.h>
using namespace std;

/*
======================================================
Prim's Algorithm: Minimum Spanning Tree (MST)
======================================================
Description:
Prim's algorithm finds the Minimum Spanning Tree (MST) of a weighted 
undirected graph. The MST is a subset of edges connecting all vertices 
with the minimum total edge weight, without forming cycles.

Approach:
1. Start with a single vertex (we start with vertex 0).
2. Pick the smallest edge connecting a vertex in MST to a vertex outside MST.
3. Include that edge and repeat until all vertices are included in MST.

Time Complexity:
- O(V^2), where V is the number of vertices (using adjacency matrix).
- Using priority queues (min-heap) can reduce it to O(E log V).

Space Complexity:
- O(V^2) for adjacency matrix.
======================================================
*/

const int INF = 1e9; // Infinity value for initialization

int main() {
    int n; // Number of vertices
    cout << "Enter number of vertices: ";
    cin >> n;

    // Input adjacency matrix
    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix (0 for no edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    // key[i] -> Minimum weight edge to include vertex i in MST
    vector<int> key(n, INF);

    // inMST[i] -> True if vertex i is included in MST
    vector<bool> inMST(n, false);

    // parent[i] -> Stores the parent of vertex i in MST
    vector<int> parent(n, -1);

    // Start from vertex 0
    key[0] = 0;

    // MST will have n vertices
    for (int count = 0; count < n - 1; count++) {
        // Step 1: Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = -1;
        int minKey = INF;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        // Step 2: Include this vertex in MST
        inMST[u] = true;

        // Step 3: Update key and parent for adjacent vertices
        for (int v = 0; v < n; v++) {
            // If there is an edge u-v and v is not in MST and weight is smaller
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST
    cout << "\nEdges in the Minimum Spanning Tree (MST):\n";
    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
    }

    return 0;
}

//added to prism branch