/*
 * Graph Adjacency List Implementation
 *
 * Description:
 * This program implements an undirected graph using an adjacency list representation.
 * Each vertex maintains a list of its adjacent vertices. The graph supports adding edges
 * between vertices and printing the complete adjacency list structure.
 *
 * Time Complexity:
 * - addEdge(): O(1) - Constant time insertion at the end of the list
 * - print(): O(V + E) - where V is the number of vertices and E is the number of edges
 *
 * Space Complexity:
 * - O(V + E) - Stores V adjacency lists with a total of 2E entries (each edge stored twice)
 *
 * Author: @Enimi-dev
 */

#include <iostream>
#include <list>
#include <vector>
class Graph{
    int v;  // Number of vertices in the graph
    std::list<int> *arr;  // Array of lists to represent adjacency list
public:
    Graph(int val) {  // Constructor to initialize the graph with 'val' vertices
        this->v = val;
        arr = new std::list<int>[v];
    }
    void addEdge(int u, int v) {  // Add an undirected edge between vertex u and vertex v
        arr[v].push_back(u);
        arr[u].push_back(v);
    }
    void print() {  // Print the adjacency list representation of the graph
        for (int i=0; i<v; i++) {
            std::cout << i << " : ";
            for (auto val: arr[i]) {
                std::cout<<val<<" ";
            }
            std::cout<<std::endl;
        }
    }
};
int main() {
    Graph g(5);  // Create a graph with 5 vertices (0 to 4)
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    g.print();

    return 0;
}
