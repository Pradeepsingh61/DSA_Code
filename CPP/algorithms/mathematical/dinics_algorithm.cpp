/*
 * Dinic's Algorithm for Maximum Flow
 * 
 * This algorithm finds the maximum flow in a flow network using concepts of
 * level graphs and blocking flows. It's one of the most efficient algorithms
 * for solving the maximum flow problem with time complexity O(V^2 * E).
 *
 * The key steps of Dinic's Algorithm are:
 * 1. Create a level graph using BFS
 * 2. Find blocking flows using DFS
 * 3. Repeat until no more augmenting paths can be found
 * 
 * Author: GitHub Copilot
 * Date: October 2, 2025
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class DinicMaxFlow {
private:
    struct Edge {
        int to;         // Target vertex
        int flow;       // Current flow
        int capacity;   // Capacity
        int rev;        // Index of the reverse edge in the adjacency list
        
        Edge(int t, int c, int r) : to(t), flow(0), capacity(c), rev(r) {}
    };
    
    vector<vector<Edge>> graph;  // Adjacency list representation of the graph
    vector<int> level;           // Level of each vertex in the level graph
    vector<int> next;            // Next edge to be explored in DFS
    int vertices;                // Number of vertices
    const int INF = numeric_limits<int>::max();

public:
    // Constructor
    DinicMaxFlow(int n) : vertices(n) {
        graph.resize(n);
        level.resize(n);
        next.resize(n);
    }
    
    // Add an edge from u to v with capacity c
    void addEdge(int u, int v, int c) {
        // Add forward edge
        graph[u].emplace_back(v, c, graph[v].size());
        // Add reverse edge with 0 capacity (for the residual graph)
        graph[v].emplace_back(u, 0, graph[u].size() - 1);
    }
    
    // Build the level graph using BFS
    bool buildLevelGraph(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        
        queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (const Edge& edge : graph[u]) {
                // If level is not assigned and there is capacity remaining
                if (level[edge.to] == -1 && edge.flow < edge.capacity) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        
        // Return true if sink is reachable in the level graph
        return level[sink] != -1;
    }
    
    // Find augmenting paths and augment flow using DFS
    int sendFlow(int u, int sink, int flow) {
        if (u == sink)
            return flow;
            
        // Try all remaining edges in the current level
        for (; next[u] < graph[u].size(); ++next[u]) {
            Edge& edge = graph[u][next[u]];
            
            // If the edge leads to the next level and has remaining capacity
            if (level[edge.to] == level[u] + 1 && edge.flow < edge.capacity) {
                int curr_flow = min(flow, edge.capacity - edge.flow);
                int temp_flow = sendFlow(edge.to, sink, curr_flow);
                
                // If flow was augmented
                if (temp_flow > 0) {
                    // Update flow for the current edge and its reverse edge
                    edge.flow += temp_flow;
                    graph[edge.to][edge.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        
        return 0;  // No augmenting path found
    }
    
    // Calculate the maximum flow from source to sink
    int maxFlow(int source, int sink) {
        if (source == sink)
            return 0;
            
        int total_flow = 0;
        
        // Continue until there are no more augmenting paths
        while (buildLevelGraph(source, sink)) {
            // Reset the next[] array for the new level graph
            fill(next.begin(), next.end(), 0);
            
            // Augment flow while possible
            int flow;
            while ((flow = sendFlow(source, sink, INF)) > 0) {
                total_flow += flow;
            }
        }
        
        return total_flow;
    }
    
    // Print the current flow network
    void printFlowNetwork() {
        cout << "Flow Network:" << endl;
        for (int u = 0; u < vertices; ++u) {
            for (const Edge& edge : graph[u]) {
                if (edge.capacity > 0) { // Only print forward edges
                    cout << u << " -> " << edge.to << " : " 
                         << edge.flow << "/" << edge.capacity << endl;
                }
            }
        }
    }
};

// Example usage
int main() {
    // Example 1: Simple network with 6 vertices
    cout << "Example 1:" << endl;
    DinicMaxFlow network1(6);
    
    // Add edges (from, to, capacity)
    network1.addEdge(0, 1, 16);
    network1.addEdge(0, 2, 13);
    network1.addEdge(1, 2, 10);
    network1.addEdge(1, 3, 12);
    network1.addEdge(2, 1, 4);
    network1.addEdge(2, 4, 14);
    network1.addEdge(3, 2, 9);
    network1.addEdge(3, 5, 20);
    network1.addEdge(4, 3, 7);
    network1.addEdge(4, 5, 4);
    
    int source1 = 0;
    int sink1 = 5;
    cout << "Maximum flow: " << network1.maxFlow(source1, sink1) << endl;
    network1.printFlowNetwork();
    cout << endl;
    
    // Example 2: Bipartite matching problem
    cout << "Example 2 (Bipartite Matching):" << endl;
    // 0 is source, 7 is sink, 1-3 are left set, 4-6 are right set
    DinicMaxFlow network2(8);
    
    // Add edges from source to left set
    network2.addEdge(0, 1, 1);
    network2.addEdge(0, 2, 1);
    network2.addEdge(0, 3, 1);
    
    // Add edges from left set to right set (representing possible matches)
    network2.addEdge(1, 4, 1);
    network2.addEdge(1, 5, 1);
    network2.addEdge(2, 4, 1);
    network2.addEdge(2, 6, 1);
    network2.addEdge(3, 5, 1);
    
    // Add edges from right set to sink
    network2.addEdge(4, 7, 1);
    network2.addEdge(5, 7, 1);
    network2.addEdge(6, 7, 1);
    
    int source2 = 0;
    int sink2 = 7;
    cout << "Maximum matching: " << network2.maxFlow(source2, sink2) << endl;
    network2.printFlowNetwork();
    
    return 0;
}
