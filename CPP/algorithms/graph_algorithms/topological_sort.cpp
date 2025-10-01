/**
 * Algorithm: Topological Sort
 * Description: Linear ordering of vertices in a Directed Acyclic Graph (DAG)
 * Time Complexity: O(V + E) where V is vertices and E is edges
 * Space Complexity: O(V) for auxiliary data structures
 * 
 * Applications:
 * - Task scheduling with dependencies
 * - Course prerequisite planning
 * - Build systems and compilation order
 * - Deadlock detection in operating systems
 * 
 * @author Abhijit
 * @version 1.0
 * @since October 2025
 * Hacktoberfest 2025
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <map>
using namespace std;

/**
 * Graph class for directed graphs
 */
class DirectedGraph {
private:
    int vertices;
    vector<vector<int> > adjacencyList;
    map<int, string> vertexLabels;

public:
    /**
     * Constructor
     */
    DirectedGraph(int v) : vertices(v) {
        adjacencyList.resize(v);
    }

    /**
     * Add directed edge
     */
    void addEdge(int src, int dest) {
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            adjacencyList[src].push_back(dest);
        }
    }

    /**
     * Set vertex label
     */
    void setVertexLabel(int vertex, const string& label) {
        if (vertex >= 0 && vertex < vertices) {
            vertexLabels[vertex] = label;
        }
    }

    /**
     * Get vertex label
     */
    string getVertexLabel(int vertex) const {
        map<int, string>::const_iterator it = vertexLabels.find(vertex);
        if (it != vertexLabels.end()) {
            return it->second;
        }
        char buffer[10];
        sprintf(buffer, "%d", vertex);
        return string(buffer);
    }

    /**
     * Get number of vertices
     */
    int getVertices() const { 
        return vertices; 
    }

    /**
     * Get adjacent vertices
     */
    const vector<int>& getAdjacent(int vertex) const {
        static vector<int> empty;
        if (vertex >= 0 && vertex < vertices) {
            return adjacencyList[vertex];
        }
        return empty;
    }

    /**
     * Check if graph has cycle
     */
    bool hasCycle() const {
        vector<int> color(vertices, 0); // 0: white, 1: gray, 2: black
        
        for (int i = 0; i < vertices; i++) {
            if (color[i] == 0) {
                if (hasCycleDFS(i, color)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    /**
     * DFS helper for cycle detection
     */
    bool hasCycleDFS(int vertex, vector<int>& color) const {
        color[vertex] = 1; // Gray
        
        for (int i = 0; i < (int)adjacencyList[vertex].size(); i++) {
            int neighbor = adjacencyList[vertex][i];
            if (color[neighbor] == 1) { // Back edge found
                return true;
            }
            if (color[neighbor] == 0 && hasCycleDFS(neighbor, color)) {
                return true;
            }
        }
        
        color[vertex] = 2; // Black
        return false;
    }

public:
    /**
     * Print graph
     */
    void printGraph() const {
        cout << "\nGraph Structure:" << endl;
        cout << "=================" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << getVertexLabel(i) << " -> ";
            if (adjacencyList[i].empty()) {
                cout << "[]";
            } else {
                cout << "[";
                for (int j = 0; j < (int)adjacencyList[i].size(); j++) {
                    cout << getVertexLabel(adjacencyList[i][j]);
                    if (j < (int)adjacencyList[i].size() - 1) cout << ", ";
                }
                cout << "]";
            }
            cout << endl;
        }
    }
};

/**
 * DFS utility for topological sort
 */
void topologicalSortDFSUtil(const DirectedGraph& graph, int vertex, 
                           vector<bool>& visited, stack<int>& resultStack) {
    visited[vertex] = true;
    
    const vector<int>& neighbors = graph.getAdjacent(vertex);
    for (int i = 0; i < (int)neighbors.size(); i++) {
        if (!visited[neighbors[i]]) {
            topologicalSortDFSUtil(graph, neighbors[i], visited, resultStack);
        }
    }
    
    resultStack.push(vertex);
}

/**
 * Topological Sort using DFS
 */
vector<int> topologicalSortDFS(const DirectedGraph& graph) {
    int vertices = graph.getVertices();
    vector<bool> visited(vertices, false);
    stack<int> resultStack;
    
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            topologicalSortDFSUtil(graph, i, visited, resultStack);
        }
    }
    
    vector<int> result;
    while (!resultStack.empty()) {
        result.push_back(resultStack.top());
        resultStack.pop();
    }
    
    return result;
}

/**
 * Topological Sort using Kahn's Algorithm
 */
vector<int> topologicalSortKahn(const DirectedGraph& graph) {
    int vertices = graph.getVertices();
    vector<int> inDegree(vertices, 0);
    
    // Calculate in-degree
    for (int i = 0; i < vertices; i++) {
        const vector<int>& neighbors = graph.getAdjacent(i);
        for (int j = 0; j < (int)neighbors.size(); j++) {
            inDegree[neighbors[j]]++;
        }
    }
    
    // Find vertices with 0 in-degree
    queue<int> zeroInDegreeQueue;
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            zeroInDegreeQueue.push(i);
        }
    }
    
    vector<int> result;
    
    while (!zeroInDegreeQueue.empty()) {
        int vertex = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        result.push_back(vertex);
        
        const vector<int>& neighbors = graph.getAdjacent(vertex);
        for (int i = 0; i < (int)neighbors.size(); i++) {
            inDegree[neighbors[i]]--;
            if (inDegree[neighbors[i]] == 0) {
                zeroInDegreeQueue.push(neighbors[i]);
            }
        }
    }
    
    if ((int)result.size() != vertices) {
        cout << "Error: Graph contains a cycle!" << endl;
        return vector<int>();
    }
    
    return result;
}

/**
 * Print topological order result
 */
void printTopologicalOrder(const DirectedGraph& graph, const vector<int>& result, 
                          const string& algorithmName) {
    cout << "\n" << algorithmName << " Result:" << endl;
    cout << "==================================================" << endl;
    
    if (result.empty()) {
        cout << "No valid topological ordering found" << endl;
        return;
    }
    
    cout << "Topological Order: ";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << graph.getVertexLabel(result[i]);
        if (i < (int)result.size() - 1) cout << " -> ";
    }
    cout << endl;
}

/**
 * Create sample course graph
 */
DirectedGraph createCourseGraph() {
    DirectedGraph graph(6);
    
    graph.setVertexLabel(0, "Math101");
    graph.setVertexLabel(1, "CS101");
    graph.setVertexLabel(2, "Math201");
    graph.setVertexLabel(3, "CS201");
    graph.setVertexLabel(4, "CS301");
    graph.setVertexLabel(5, "CS401");
    
    graph.addEdge(0, 2);  // Math101 -> Math201
    graph.addEdge(1, 3);  // CS101 -> CS201
    graph.addEdge(2, 4);  // Math201 -> CS301
    graph.addEdge(3, 4);  // CS201 -> CS301
    graph.addEdge(4, 5);  // CS301 -> CS401
    
    return graph;
}

/**
 * Create sample task graph
 */
DirectedGraph createTaskGraph() {
    DirectedGraph graph(5);
    
    graph.setVertexLabel(0, "TaskA");
    graph.setVertexLabel(1, "TaskB");
    graph.setVertexLabel(2, "TaskC");
    graph.setVertexLabel(3, "TaskD");
    graph.setVertexLabel(4, "TaskE");
    
    graph.addEdge(0, 1);  // TaskA -> TaskB
    graph.addEdge(0, 2);  // TaskA -> TaskC
    graph.addEdge(1, 3);  // TaskB -> TaskD
    graph.addEdge(2, 3);  // TaskC -> TaskD
    graph.addEdge(3, 4);  // TaskD -> TaskE
    
    return graph;
}

/**
 * Demonstrate topological sorting
 */
void demonstrateTopologicalSort() {
    cout << "=====================================================" << endl;
    cout << "TOPOLOGICAL SORT DEMONSTRATION" << endl;
    cout << "=====================================================" << endl;
    
    // Example 1: Course Prerequisites
    cout << "\nExample 1: Course Prerequisites" << endl;
    DirectedGraph courseGraph = createCourseGraph();
    courseGraph.printGraph();
    
    if (courseGraph.hasCycle()) {
        cout << "Graph contains a cycle!" << endl;
    } else {
        cout << "Graph is a valid DAG" << endl;
        
        vector<int> dfsResult = topologicalSortDFS(courseGraph);
        printTopologicalOrder(courseGraph, dfsResult, "DFS-based Topological Sort");
        
        vector<int> kahnResult = topologicalSortKahn(courseGraph);
        printTopologicalOrder(courseGraph, kahnResult, "Kahn's Algorithm");
    }
    
    // Example 2: Task Dependencies
    cout << "\n\nExample 2: Task Dependencies" << endl;
    DirectedGraph taskGraph = createTaskGraph();
    taskGraph.printGraph();
    
    if (!taskGraph.hasCycle()) {
        vector<int> taskOrder = topologicalSortDFS(taskGraph);
        printTopologicalOrder(taskGraph, taskOrder, "Task Execution Order");
    }
}

/**
 * Interactive mode
 */
void interactiveMode() {
    cout << "\n=====================================================" << endl;
    cout << "INTERACTIVE TOPOLOGICAL SORT" << endl;
    cout << "=====================================================" << endl;
    
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!" << endl;
        return;
    }
    
    DirectedGraph graph(vertices);
    
    cout << "\nEnter directed edges (format: source destination, -1 -1 to finish):" << endl;
    cout << "Vertices are numbered 0 to " << (vertices-1) << endl;
    
    int src, dest;
    while (true) {
        cout << "Edge: ";
        cin >> src >> dest;
        
        if (src == -1 && dest == -1) break;
        
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            graph.addEdge(src, dest);
            cout << "Added edge: " << src << " -> " << dest << endl;
        } else {
            cout << "Invalid vertices!" << endl;
        }
    }
    
    graph.printGraph();
    
    if (graph.hasCycle()) {
        cout << "Error: Graph contains a cycle!" << endl;
        return;
    }
    
    cout << "Graph is a valid DAG" << endl;
    
    vector<int> dfsResult = topologicalSortDFS(graph);
    printTopologicalOrder(graph, dfsResult, "DFS-based Topological Sort");
    
    vector<int> kahnResult = topologicalSortKahn(graph);
    printTopologicalOrder(graph, kahnResult, "Kahn's Algorithm");
}

/**
 * Main function
 */
int main() {
    cout << "Topological Sort Algorithm in C++" << endl;
    cout << "=================================" << endl;
    cout << "1. Demonstration mode" << endl;
    cout << "2. Interactive mode" << endl;
    cout << "Choose mode (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            demonstrateTopologicalSort();
            break;
        case 2:
            interactiveMode();
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }
    
    cout << "\n=====================================================" << endl;
    cout << "ALGORITHM INFORMATION" << endl;
    cout << "=====================================================" << endl;
    cout << "Time Complexity: O(V + E)" << endl;
    cout << "Space Complexity: O(V)" << endl;
    cout << "\nTwo Main Approaches:" << endl;
    cout << "1. DFS-based: Uses recursion and stack" << endl;
    cout << "2. Kahn's Algorithm: Uses BFS with in-degree tracking" << endl;
    cout << "\nApplications:" << endl;
    cout << "- Task scheduling with dependencies" << endl;
    cout << "- Course prerequisite planning" << endl;
    cout << "- Build systems and compilation order" << endl;
    cout << "- Deadlock detection" << endl;
    cout << "\nNote: Only works on Directed Acyclic Graphs (DAGs)" << endl;
    
    return 0;
}