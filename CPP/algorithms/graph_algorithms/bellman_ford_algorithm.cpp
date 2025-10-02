/*
 * Algorithm: Bellman-Ford Algorithm
 * Language: C++
 * Description: 
 * Finds the shortest path from a single source node to all other nodes in a 
 * weighted, directed graph. It correctly handles graphs with negative weight 
 * edges and detects the presence of negative cycles.
 * Time Complexity: O(V * E) // V is the number of vertices, E is the number of edges
 * Space Complexity: O(V + E) // To store distances, predecessors, and edges
 * Author: Adi-3108
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 
#include <string>

using namespace std;
// Define a large number to represent infinity
const int INF = numeric_limits<int>::max();


struct Edge {
    int source, destination, weight;
};

/**
 * @brief Implements the Bellman-Ford algorithm to find shortest paths and detect negative cycles.
 * * @param V The number of vertices in the graph.
 * @param E The number of edges in the graph.
 * @param edges A vector of Edge structures representing the graph.
 * @param source The starting vertex for the shortest path search.
 * @param distance A reference to a vector where the shortest distances will be stored.
 * @return bool True if successful and NO negative cycle is detected, false otherwise (failure or cycle).
 */
bool bellmanFord(int V, int E, const vector<Edge>& edges, int source, vector<int>& distance) {
    
    
    if (V <= 0) {
        cerr << "FAIL: Number of vertices (V) must be positive.\n";
        return false;
    }
    if (source < 0 || source >= V) {
        cerr << "FAIL: Source vertex index is invalid (must be between 0 and " << V - 1 << ").\n";
        return false;
    }
    for (const auto& edge : edges) {
        if (edge.source < 0 || edge.source >= V || edge.destination < 0 || edge.destination >= V) {
            cerr << "FAIL: Edge index (" << edge.source << ", " << edge.destination << ") is out of bounds [0, " << V - 1 << "].\n";
            return false;
        }
    }
    
    
    distance.assign(V, INF);
    distance[source] = 0;

    // Phase 1: Relax all edges V - 1 times 
    for (int i = 0; i < V - 1; ++i) {
        bool updated = false;
        for (const auto& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

           
            if (distance[u] != INF && (long long)distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                updated = true;
            }
        }
        if (!updated) {
            break;
        }
    }

    // Phase 2: Check for Negative Cycles 
    for (const auto& edge : edges) {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;

        if (distance[u] != INF && (long long)distance[u] + weight < distance[v]) {
            cerr << "Warning: Negative cycle detected! Paths are unreliable.\n";
            return false;
        }
    }

    return true; // Success
}

// Test function 
void testBellmanFord() {
    cout << " Testing Bellman-Ford Algorithm  " << endl;

    // --- Test Case 1: Standard Graph (Fixed to remove the negative cycle 4->3->4) ---
    // V=5, E=8. Source = 0.
    // Fixed edge: (4, 3, 1) changed to (4, 3, 3) to break the 4->3->4 negative cycle.
    int V1 = 5; 
    int E1 = 8;
    int source1 = 0;
    vector<Edge> edges1 = {
        {0, 1, 6}, {0, 2, 7}, {1, 3, 5}, {1, 4, -4}, 
        {2, 3, -1}, {3, 4, -2}, {4, 0, 2}, {4, 3, 3} // Changed (4,3,1) to (4,3,3)
    };
    vector<int> dist1;
    
    cout << "\nTest Case 1 (Standard Graph):\n";
    bool result1 = bellmanFord(V1, E1, edges1, source1, dist1);

    cout << "Cycle Detected: " << (result1 ? "No" : "Yes (Failure)") << endl;
    cout << "Successful Path Calculation: " << (result1 ? "Yes" : "No") << endl;
    
    cout << "Shortest Paths from Node " << source1 << ": [";
    if (result1) {
        // Expected distances: [0, 2, 7, 5, 2]
        for (int i = 0; i < V1; ++i) {
            cout << dist1[i] << (i == V1 - 1 ? "" : ", ");
        }
    } else {
        cout << "N/A (Paths Unreliable)";
    }
    cout << "]" << endl;
    
    //  Test Case 2: Graph with Negative Cycle (FAIL) 
    int V2 = 3;
    int E2 = 3;
    int source2 = 0;
    vector<Edge> edges2 = {
        {0, 1, 1}, {1, 2, -2}, {2, 0, 0} // Negative Cycle
    };
    vector<int> dist2;

    cout << "\nTest Case 2 (Negative Cycle Detection):\n";
    bool result2 = bellmanFord(V2, E2, edges2, source2, dist2);

    cout << "Cycle Detected: " << (result2 ? "No (FAIL)" : "Yes") << endl;
    cout << "Successful Path Calculation: " << (result2 ? "Yes (FAIL)" : "No") << endl;
    
    //  Test Case 3: Invalid Source Vertex (Validation Fail) 
    int V3 = 5; 
    int source3 = 5; // Invalid index [0, 4]
    vector<Edge> edges3 = {};
    vector<int> dist3;
    
    cout << "Test Case 3 (Invalid Input Validation):" << endl;
    bool result3 = bellmanFord(V3, 0, edges3, source3, dist3);
    
    cout << "Input Valid: " << (result3 ? "Yes" : "No") << endl;
}

int main() {
    testBellmanFord();
    return 0;
}