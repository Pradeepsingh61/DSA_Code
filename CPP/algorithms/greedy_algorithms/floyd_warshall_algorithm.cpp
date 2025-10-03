/**
 * Floyd-Warshall Algorithm - All Pairs Shortest Path
 * 
 * Description:
 * The Floyd-Warshall algorithm finds the shortest paths between all pairs of vertices
 * in a weighted graph. It works with both positive and negative edge weights (but no
 * negative cycles). The algorithm uses dynamic programming to iteratively improve the
 * shortest path estimates.
 * 
 * Algorithm Steps:
 * 1. Initialize distance matrix with direct edge weights
 * 2. For each intermediate vertex k (1 to n):
 *    - For each pair of vertices (i, j):
 *      - Check if path through k is shorter: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 * 3. Check diagonal for negative values to detect negative cycles
 * 
 * Time Complexity: O(V^3) where V = number of vertices
 * Space Complexity: O(V^2) for distance matrix
 * 
 * Use Cases:
 * - Finding shortest paths between all pairs of vertices
 * - Transitive closure of a graph
 * - Finding strongly connected components
 * - Game theory and AI pathfinding
 * - Network analysis and routing
 * 
 * Author: GitHub Copilot
 * Date: October 2025
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;

const int INF = 1e7; // Using a large number instead of INT_MAX to avoid overflow

/**
 * Class to represent a weighted graph and perform Floyd-Warshall algorithm
 */
class Graph {
private:
    int vertices;                          // Number of vertices
    vector<vector<int>> dist;              // Distance matrix
    vector<vector<int>> next;              // Next vertex in shortest path (for path reconstruction)
    
public:
    /**
     * Constructor to initialize graph with given number of vertices
     * 
     * @param V Number of vertices in the graph
     */
    Graph(int V) {
        vertices = V;
        dist.resize(V, vector<int>(V, INF));
        next.resize(V, vector<int>(V, -1));
        
        // Distance from a vertex to itself is 0
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }
    }
    
    /**
     * Add a directed weighted edge to the graph
     * 
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge
     */
    void addEdge(int u, int v, int weight) {
        dist[u][v] = weight;
        next[u][v] = v;  // Direct edge, next vertex is v
    }
    
    /**
     * Floyd-Warshall algorithm implementation
     * Finds shortest paths between all pairs of vertices
     * 
     * @return true if no negative cycle exists, false otherwise
     */
    bool floydWarshall() {
        cout << "\nRunning Floyd-Warshall Algorithm...\n";
        
        // Main algorithm: Try all vertices as intermediate points
        for (int k = 0; k < vertices; k++) {
            for (int i = 0; i < vertices; i++) {
                for (int j = 0; j < vertices; j++) {
                    // If vertex k is on the shortest path from i to j,
                    // then update the value of dist[i][j]
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];  // Update path
                        }
                    }
                }
            }
        }
        
        // Check for negative weight cycles
        // If distance from a vertex to itself becomes negative, there's a negative cycle
        for (int i = 0; i < vertices; i++) {
            if (dist[i][i] < 0) {
                cout << "\nNegative weight cycle detected!\n";
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * Print the distance matrix in a formatted table
     */
    void printDistanceMatrix() {
        cout << "\n========================================\n";
        cout << "   ALL PAIRS SHORTEST DISTANCE MATRIX   \n";
        cout << "========================================\n\n";
        
        // Print column headers
        cout << "     ";
        for (int i = 0; i < vertices; i++) {
            cout << setw(6) << i;
        }
        cout << "\n    " << string(vertices * 6 + 1, '-') << "\n";
        
        // Print rows
        for (int i = 0; i < vertices; i++) {
            cout << setw(3) << i << " |";
            for (int j = 0; j < vertices; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    /**
     * Reconstruct and print the shortest path between two vertices
     * 
     * @param u Source vertex
     * @param v Destination vertex
     */
    void printPath(int u, int v) {
        if (next[u][v] == -1) {
            cout << "No path exists";
            return;
        }
        
        vector<int> path;
        path.push_back(u);
        
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
    }
    
    /**
     * Print all shortest paths from a specific source vertex
     * 
     * @param source Source vertex
     */
    void printAllPathsFromSource(int source) {
        cout << "\n========================================\n";
        cout << "   SHORTEST PATHS FROM VERTEX " << source << "\n";
        cout << "========================================\n\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << "To vertex " << setw(2) << i << " | Distance: ";
            
            if (dist[source][i] == INF) {
                cout << setw(4) << "INF" << " | Path: No path exists\n";
            } else {
                cout << setw(4) << dist[source][i] << " | Path: ";
                printPath(source, i);
                cout << "\n";
            }
        }
        cout << "\n";
    }
    
    /**
     * Get shortest distance between two vertices
     * 
     * @param u Source vertex
     * @param v Destination vertex
     * @return Shortest distance (INF if no path exists)
     */
    int getDistance(int u, int v) {
        return dist[u][v];
    }
};

/**
 * Example 1: Basic weighted graph
 */
void example1() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 1: Basic Weighted Graph\n";
    cout << string(50, '=') << "\n";
    
    // Create a graph with 4 vertices
    Graph g(4);
    
    // Add edges
    g.addEdge(0, 1, 5);
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);
    
    cout << "\nGraph Structure:\n";
    cout << "  0 --(5)--> 1 --(3)--> 2\n";
    cout << "  |                     |\n";
    cout << " (10)                  (1)\n";
    cout << "  |                     |\n";
    cout << "  v                     v\n";
    cout << "  3 <-------------------+\n";
    
    if (g.floydWarshall()) {
        g.printDistanceMatrix();
        g.printAllPathsFromSource(0);
    }
}

/**
 * Example 2: Graph with negative edges (but no negative cycle)
 */
void example2() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 2: Graph with Negative Edges\n";
    cout << string(50, '=') << "\n";
    
    Graph g(4);
    
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, -3);
    g.addEdge(2, 3, 2);
    g.addEdge(0, 3, 5);
    
    cout << "\nGraph Structure:\n";
    cout << "  0 --(2)--> 1 --(-3)--> 2 --(2)--> 3\n";
    cout << "  |                                  ^\n";
    cout << " (5)                                 |\n";
    cout << "  +----------------------------------+\n";
    
    if (g.floydWarshall()) {
        g.printDistanceMatrix();
        g.printAllPathsFromSource(0);
    }
}

/**
 * Example 3: Complete graph (all vertices connected)
 */
void example3() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 3: Complete Graph\n";
    cout << string(50, '=') << "\n";
    
    Graph g(3);
    
    // Add edges in both directions
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 11);
    g.addEdge(1, 0, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 3);
    g.addEdge(2, 1, 5);
    
    cout << "\nGraph Structure (bidirectional):\n";
    cout << "      4        2\n";
    cout << "  0 <--> 1 <--> 2\n";
    cout << "  |  6      5   |\n";
    cout << "  |             |\n";
    cout << "  +---(11)-(3)--+\n";
    
    if (g.floydWarshall()) {
        g.printDistanceMatrix();
        g.printAllPathsFromSource(0);
    }
}

/**
 * Example 4: Disconnected graph
 */
void example4() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 4: Disconnected Graph\n";
    cout << string(50, '=') << "\n";
    
    Graph g(5);
    
    // First component
    g.addEdge(0, 1, 3);
    g.addEdge(1, 2, 2);
    
    // Second component (isolated)
    g.addEdge(3, 4, 5);
    
    cout << "\nGraph Structure:\n";
    cout << "  Component 1: 0 --(3)--> 1 --(2)--> 2\n";
    cout << "  Component 2: 3 --(5)--> 4\n";
    
    if (g.floydWarshall()) {
        g.printDistanceMatrix();
        cout << "\nNote: INF indicates no path exists between vertices\n";
        cout << "      (vertices in different components)\n\n";
    }
}

/**
 * Example 5: Negative cycle detection
 */
void example5() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 5: Negative Cycle Detection\n";
    cout << string(50, '=') << "\n";
    
    Graph g(3);
    
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, -3);
    g.addEdge(2, 0, 1);
    
    cout << "\nGraph Structure (forms a negative cycle):\n";
    cout << "      1      -3\n";
    cout << "  0 ----> 1 ----> 2\n";
    cout << "  ^                |\n";
    cout << "  |       1        |\n";
    cout << "  +----------------+\n";
    cout << "\nCycle: 0 -> 1 -> 2 -> 0\n";
    cout << "Sum: 1 + (-3) + 1 = -1 (NEGATIVE!)\n";
    
    g.floydWarshall();
}

/**
 * Example 6: Finding transitive closure
 */
void example6() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXAMPLE 6: Reachability (Transitive Closure)\n";
    cout << string(50, '=') << "\n";
    
    Graph g(4);
    
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(1, 3, 1);
    
    cout << "\nGraph Structure:\n";
    cout << "  0 --> 1 --> 2 --> 3\n";
    cout << "        |           ^\n";
    cout << "        +-----------+\n";
    
    if (g.floydWarshall()) {
        g.printDistanceMatrix();
        
        cout << "\nReachability Analysis:\n";
        cout << "From vertex 0, you can reach: 1, 2, 3\n";
        cout << "From vertex 1, you can reach: 2, 3\n";
        cout << "From vertex 2, you can reach: 3\n";
        cout << "From vertex 3, you can reach: none\n\n";
    }
}

/**
 * Main function demonstrating various test cases
 */
int main() {
    cout << "\n";
    cout << "========================================================\n";
    cout << "                                                        \n";
    cout << "          FLOYD-WARSHALL ALGORITHM DEMONSTRATION        \n";
    cout << "                                                        \n";
    cout << "      All Pairs Shortest Path with Dynamic Programming \n";
    cout << "                                                        \n";
    cout << "========================================================\n";
    
    // Run all examples
    example1();  // Basic weighted graph
    example2();  // Graph with negative edges
    example3();  // Complete graph
    example4();  // Disconnected graph
    example5();  // Negative cycle detection
    example6();  // Transitive closure
    
    // Summary
    cout << "\n" << string(50, '=') << "\n";
    cout << "KEY INSIGHTS:\n";
    cout << string(50, '=') << "\n";
    cout << "* Finds shortest paths between ALL pairs of vertices\n";
    cout << "* Time Complexity: O(V^3)\n";
    cout << "* Space Complexity: O(V^2)\n";
    cout << "* Handles negative edge weights\n";
    cout << "* Detects negative cycles\n";
    cout << "* Uses dynamic programming approach\n";
    cout << "\nWhen to use Floyd-Warshall:\n";
    cout << "  + Need all-pairs shortest paths\n";
    cout << "  + Dense graphs (many edges)\n";
    cout << "  + Graph with negative weights (no negative cycles)\n";
    cout << "  + Small to medium sized graphs\n";
    cout << "  + Transitive closure problems\n";
    cout << "\nAlternatives:\n";
    cout << "  - Dijkstra: Single source, no negative weights\n";
    cout << "  - Bellman-Ford: Single source, handles negative weights\n";
    cout << "  - Johnson's Algorithm: All pairs, sparse graphs\n";
    cout << string(50, '=') << "\n\n";
    
    return 0;
}
