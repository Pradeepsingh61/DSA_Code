#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

/*
    Graph Implementation in C++ using Adjacency List
    ------------------------------------------------
    - We use an unordered_map<int, list<int>> to store adjacency information.
    - Each vertex (int) is mapped to a list of its neighbors.
    - The graph is undirected, so every edge (u, v) is stored twice:
        * v in u's list
        * u in v's list
*/

class Graph {
private:
    // Adjacency list representation
    unordered_map<int, list<int>> adjList;

public:
    // Function to add an edge between two vertices
    void addEdge(int v1, int v2) {
        adjList[v1].push_back(v2);  // Add v2 to v1's adjacency list
        adjList[v2].push_back(v1);  // Add v1 to v2's adjacency list (undirected)
    }

    // Function to display the graph
    void displayGraph() {
        cout << "Graph Adjacency List Representation:\n";
        for (const auto& vertex : adjList) {
            cout << vertex.first << " --> ";
            for (const auto& neighbor : vertex.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Function to check if a vertex exists
    bool hasVertex(int v) {
        return adjList.find(v) != adjList.end();
    }

    // Function to check if an edge exists
    bool hasEdge(int v1, int v2) {
        if (!hasVertex(v1) || !hasVertex(v2)) return false;
        for (auto neighbor : adjList[v1]) {
            if (neighbor == v2) return true;
        }
        return false;
    }

    // Function to return degree of a vertex
    int degree(int v) {
        if (!hasVertex(v)) {
            cout << "Vertex " << v << " does not exist!" << endl;
            return -1;
        }
        return adjList[v].size();
    }
};

int main() {
    Graph g;

    // Adding edges (undirected graph)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Displaying the graph
    g.displayGraph();

    // Checking vertices and edges
    cout << "\nCheck if vertex 3 exists: " << (g.hasVertex(3) ? "Yes" : "No") << endl;
    cout << "Check if edge (1, 3) exists: " << (g.hasEdge(1, 3) ? "Yes" : "No") << endl;
    cout << "Check if edge (0, 4) exists: " << (g.hasEdge(0, 4) ? "Yes" : "No") << endl;

    // Checking degree of vertices
    cout << "\nDegree of vertex 1: " << g.degree(1) << endl;
    cout << "Degree of vertex 3: " << g.degree(3) << endl;

    return 0;
}
