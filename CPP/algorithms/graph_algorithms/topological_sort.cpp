/**
 * Algorithm: Topological Sort
 * Description: Linear ordering of vertices in a Directed Acyclic Graph (DAG) such that 
 *              for every directed edge (u, v), vertex u comes before v in the ordering
 * Time Complexity: O(V + E) where V is vertices and E is edges
 * Space Complexity: O(V) for storing the result and auxiliary data structures
 * 
 * Key Concepts:
 * - Works only on Directed Acyclic Graphs (DAGs)
 * - Multiple valid topological orderings may exist
 * - Uses DFS-based approach and Kahn's algorithm (BFS-based)
 * - Cycle detection to verify DAG property
 * 
 * Applications:
 * - Task scheduling with dependencies
 * - Course prerequisite ordering
 * - Build systems and dependency resolution
 * - Compiler design (symbol table construction)
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
#include <unordered_set>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

/**
 * Graph class supporting directed graphs for topological sorting
 */
class DirectedGraph {
private:
    int vertices;
    vector<vector<int>> adjacencyList;
    map<int, string> vertexLabels;  // Optional labels for vertices

public:
    /**
     * Constructor to initialize graph with given number of vertices
     * @param v Number of vertices
     */
    DirectedGraph(int v) : vertices(v) {
        adjacencyList.resize(v);
    }

    /**
     * Add directed edge from source to destination
     * @param src Source vertex
     * @param dest Destination vertex
     */
    void addEdge(int src, int dest) {
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            adjacencyList[src].push_back(dest);
        } else {
            cout << "Error: Invalid vertices " << src << " -> " << dest << endl;
        }
    }

    /**
     * Set label for a vertex (optional, for better readability)
     * @param vertex Vertex number
     * @param label String label for the vertex
     */
    void setVertexLabel(int vertex, const string& label) {
        if (vertex >= 0 && vertex < vertices) {
            vertexLabels[vertex] = label;
        }
    }

    /**
     * Get label for a vertex
     * @param vertex Vertex number
     * @return Label string or vertex number as string
     */
    string getVertexLabel(int vertex) const {
        auto it = vertexLabels.find(vertex);
        return (it != vertexLabels.end()) ? it->second : to_string(vertex);
    }

    /**
     * Get number of vertices
     * @return Number of vertices
     */
    int getVertices() const { return vertices; }

    /**
     * Get adjacency list for a vertex
     * @param vertex Vertex number
     * @return Vector of adjacent vertices
     */
    const vector<int>& getAdjacent(int vertex) const {
        static vector<int> empty;
        return (vertex >= 0 && vertex < vertices) ? adjacencyList[vertex] : empty;
    }

    /**
     * Check if graph has a cycle using DFS
     * @return true if cycle exists, false otherwise
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
     * DFS helper function for cycle detection
     * @param vertex Current vertex
     * @param color Color array for vertices
     * @return true if cycle found
     */
    bool hasCycleDFS(int vertex, vector<int>& color) const {
        color[vertex] = 1; // Mark as gray (being processed)
        
        for (int neighbor : adjacencyList[vertex]) {
            if (color[neighbor] == 1) { // Gray vertex found (back edge)
                return true;
            }
            if (color[neighbor] == 0 && hasCycleDFS(neighbor, color)) {
                return true;
            }
        }
        
        color[vertex] = 2; // Mark as black (completely processed)
        return false;
    }

public:
    /**
     * Print graph structure
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
                for (size_t j = 0; j < adjacencyList[i].size(); j++) {
                    cout << getVertexLabel(adjacencyList[i][j]);
                    if (j < adjacencyList[i].size() - 1) cout << ", ";
                }
                cout << "]";
            }
            cout << endl;
        }
    }
};

/**
 * Topological Sort using DFS (Depth-First Search) approach
 * @param graph Input directed graph
 * @return Vector containing topologically sorted vertices
 */
vector<int> topologicalSortDFS(const DirectedGraph& graph) {
    int vertices = graph.getVertices();
    vector<bool> visited(vertices, false);
    stack<int> resultStack;
    
    // Perform DFS for all unvisited vertices
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            topologicalSortDFSUtil(graph, i, visited, resultStack);
        }
    }
    
    // Extract result from stack
    vector<int> result;
    while (!resultStack.empty()) {
        result.push_back(resultStack.top());
        resultStack.pop();
    }
    
    return result;
}

/**
 * DFS utility function for topological sort
 * @param graph Input graph
 * @param vertex Current vertex
 * @param visited Visited array
 * @param resultStack Stack to store result
 */
void topologicalSortDFSUtil(const DirectedGraph& graph, int vertex, 
                           vector<bool>& visited, stack<int>& resultStack) {
    visited[vertex] = true;
    
    // Visit all adjacent vertices
    for (int neighbor : graph.getAdjacent(vertex)) {
        if (!visited[neighbor]) {
            topologicalSortDFSUtil(graph, neighbor, visited, resultStack);
        }
    }
    
    // Push current vertex to stack after visiting all dependents
    resultStack.push(vertex);
}

/**
 * Topological Sort using Kahn's Algorithm (BFS approach)
 * @param graph Input directed graph
 * @return Vector containing topologically sorted vertices
 */
vector<int> topologicalSortKahn(const DirectedGraph& graph) {
    int vertices = graph.getVertices();
    vector<int> inDegree(vertices, 0);
    
    // Calculate in-degree for all vertices
    for (int i = 0; i < vertices; i++) {
        for (int neighbor : graph.getAdjacent(i)) {
            inDegree[neighbor]++;
        }
    }
    
    // Initialize queue with vertices having 0 in-degree
    queue<int> zeroInDegreeQueue;
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            zeroInDegreeQueue.push(i);
        }
    }
    
    vector<int> result;
    
    // Process vertices with 0 in-degree
    while (!zeroInDegreeQueue.empty()) {
        int vertex = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        result.push_back(vertex);
        
        // Reduce in-degree of all adjacent vertices
        for (int neighbor : graph.getAdjacent(vertex)) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroInDegreeQueue.push(neighbor);
            }
        }
    }
    
    // Check if topological sort is possible (no cycles)
    if (result.size() != vertices) {
        cout << "Error: Graph contains a cycle. Topological sort not possible." << endl;
        return vector<int>(); // Return empty vector
    }
    
    return result;
}

/**
 * Find all possible topological orderings using backtracking
 * @param graph Input directed graph
 * @return Vector of all possible topological orderings
 */
vector<vector<int>> allTopologicalSorts(const DirectedGraph& graph) {
    int vertices = graph.getVertices();
    vector<int> inDegree(vertices, 0);
    
    // Calculate in-degree
    for (int i = 0; i < vertices; i++) {
        for (int neighbor : graph.getAdjacent(i)) {
            inDegree[neighbor]++;
        }
    }
    
    vector<vector<int>> allSorts;
    vector<int> currentSort;
    vector<bool> visited(vertices, false);
    
    allTopologicalSortsUtil(graph, inDegree, visited, currentSort, allSorts);
    
    return allSorts;
}

/**
 * Utility function for finding all topological sorts
 */
void allTopologicalSortsUtil(const DirectedGraph& graph, vector<int>& inDegree,
                            vector<bool>& visited, vector<int>& currentSort,
                            vector<vector<int>>& allSorts) {
    int vertices = graph.getVertices();
    bool hasAvailable = false;
    
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && inDegree[i] == 0) {
            hasAvailable = true;
            
            // Include current vertex in result
            visited[i] = true;
            currentSort.push_back(i);
            
            // Reduce in-degree of adjacent vertices
            for (int neighbor : graph.getAdjacent(i)) {
                inDegree[neighbor]--;
            }
            
            // Recursively find remaining ordering
            allTopologicalSortsUtil(graph, inDegree, visited, currentSort, allSorts);
            
            // Backtrack
            visited[i] = false;
            currentSort.pop_back();
            for (int neighbor : graph.getAdjacent(i)) {
                inDegree[neighbor]++;
            }
        }
    }
    
    // If no vertex available, we have a complete ordering
    if (!hasAvailable && currentSort.size() == vertices) {
        allSorts.push_back(currentSort);
    }
}

/**
 * Print topological ordering result
 * @param graph Graph for vertex labels
 * @param result Topological ordering
 * @param algorithmName Name of algorithm used
 */
void printTopologicalOrder(const DirectedGraph& graph, const vector<int>& result, 
                          const string& algorithmName) {
    cout << "\n" << algorithmName << " Result:" << endl;
    cout << string(50, '=') << endl;
    
    if (result.empty()) {
        cout << "No valid topological ordering found (graph contains cycle)" << endl;
        return;
    }
    
    cout << "Topological Order: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << graph.getVertexLabel(result[i]);
        if (i < result.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "Dependencies satisfied: Each vertex appears before its dependents" << endl;
}

/**
 * Create sample course prerequisite graph
 * @return DirectedGraph representing course dependencies
 */
DirectedGraph createCourseGraph() {
    DirectedGraph graph(6);
    
    // Set course labels
    graph.setVertexLabel(0, "Math101");
    graph.setVertexLabel(1, "CS101");
    graph.setVertexLabel(2, "Math201");
    graph.setVertexLabel(3, "CS201");
    graph.setVertexLabel(4, "CS301");
    graph.setVertexLabel(5, "CS401");
    
    // Add prerequisite relationships (prerequisite -> course)
    graph.addEdge(0, 2);  // Math101 -> Math201
    graph.addEdge(1, 3);  // CS101 -> CS201
    graph.addEdge(2, 4);  // Math201 -> CS301
    graph.addEdge(3, 4);  // CS201 -> CS301
    graph.addEdge(4, 5);  // CS301 -> CS401
    
    return graph;
}

/**
 * Create sample task dependency graph
 * @return DirectedGraph representing task dependencies
 */
DirectedGraph createTaskGraph() {
    DirectedGraph graph(7);
    
    // Set task labels
    graph.setVertexLabel(0, "TaskA");
    graph.setVertexLabel(1, "TaskB");
    graph.setVertexLabel(2, "TaskC");
    graph.setVertexLabel(3, "TaskD");
    graph.setVertexLabel(4, "TaskE");
    graph.setVertexLabel(5, "TaskF");
    graph.setVertexLabel(6, "TaskG");
    
    // Add task dependencies
    graph.addEdge(0, 1);  // TaskA -> TaskB
    graph.addEdge(0, 2);  // TaskA -> TaskC
    graph.addEdge(1, 3);  // TaskB -> TaskD
    graph.addEdge(2, 3);  // TaskC -> TaskD
    graph.addEdge(3, 4);  // TaskD -> TaskE
    graph.addEdge(2, 5);  // TaskC -> TaskF
    graph.addEdge(5, 6);  // TaskF -> TaskG
    
    return graph;
}

/**
 * Demonstrate topological sorting with examples
 */
void demonstrateTopologicalSort() {
    cout << "======================================================" << endl;
    cout << "TOPOLOGICAL SORT DEMONSTRATION" << endl;
    cout << "======================================================" << endl;
    
    // Example 1: Course Prerequisites
    cout << "\n📚 Example 1: Course Prerequisites" << endl;
    DirectedGraph courseGraph = createCourseGraph();
    courseGraph.printGraph();
    
    cout << "\nChecking for cycles..." << endl;
    if (courseGraph.hasCycle()) {
        cout << "❌ Graph contains a cycle! Cannot perform topological sort." << endl;
    } else {
        cout << "✅ Graph is a DAG (Directed Acyclic Graph)" << endl;
        
        vector<int> dfsResult = topologicalSortDFS(courseGraph);
        printTopologicalOrder(courseGraph, dfsResult, "DFS-based Topological Sort");
        
        vector<int> kahnResult = topologicalSortKahn(courseGraph);
        printTopologicalOrder(courseGraph, kahnResult, "Kahn's Algorithm (BFS-based)");
    }
    
    // Example 2: Task Dependencies
    cout << "\n\n🔧 Example 2: Task Dependencies" << endl;
    DirectedGraph taskGraph = createTaskGraph();
    taskGraph.printGraph();
    
    if (!taskGraph.hasCycle()) {
        vector<int> taskOrder = topologicalSortDFS(taskGraph);
        printTopologicalOrder(taskGraph, taskOrder, "Task Execution Order");
        
        // Show all possible orderings for smaller graph
        cout << "\n📝 All Possible Topological Orderings:" << endl;
        vector<vector<int>> allOrders = allTopologicalSorts(taskGraph);
        
        if (allOrders.size() <= 10) { // Limit output for readability
            for (size_t i = 0; i < allOrders.size(); i++) {
                cout << "  Order " << (i+1) << ": ";
                for (size_t j = 0; j < allOrders[i].size(); j++) {
                    cout << taskGraph.getVertexLabel(allOrders[i][j]);
                    if (j < allOrders[i].size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        } else {
            cout << "  Too many orderings (" << allOrders.size() 
                 << ") to display all. Showing first 5:" << endl;
            for (int i = 0; i < 5; i++) {
                cout << "  Order " << (i+1) << ": ";
                for (size_t j = 0; j < allOrders[i].size(); j++) {
                    cout << taskGraph.getVertexLabel(allOrders[i][j]);
                    if (j < allOrders[i].size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        }
    }
    
    // Example 3: Simple Linear Graph
    cout << "\n\n📈 Example 3: Linear Dependency Chain" << endl;
    DirectedGraph linearGraph(4);
    linearGraph.setVertexLabel(0, "Step1");
    linearGraph.setVertexLabel(1, "Step2");
    linearGraph.setVertexLabel(2, "Step3");
    linearGraph.setVertexLabel(3, "Step4");
    
    linearGraph.addEdge(0, 1);
    linearGraph.addEdge(1, 2);
    linearGraph.addEdge(2, 3);
    
    linearGraph.printGraph();
    
    vector<int> linearOrder = topologicalSortKahn(linearGraph);
    printTopologicalOrder(linearGraph, linearOrder, "Linear Chain Ordering");
}

/**
 * Interactive mode for custom graph creation
 */
void interactiveMode() {
    cout << "\n======================================================" << endl;
    cout << "INTERACTIVE TOPOLOGICAL SORT" << endl;
    cout << "======================================================" << endl;
    
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!" << endl;
        return;
    }
    
    DirectedGraph graph(vertices);
    
    cout << "\nEnter vertex labels (optional, press Enter for default numbers):" << endl;
    cin.ignore(); // Clear input buffer
    
    for (int i = 0; i < vertices; i++) {
        cout << "Label for vertex " << i << ": ";
        string label;
        getline(cin, label);
        if (!label.empty()) {
            graph.setVertexLabel(i, label);
        }
    }
    
    cout << "\nEnter directed edges (format: source destination, -1 -1 to finish):" << endl;
    cout << "Vertices are numbered 0 to " << (vertices-1) << endl;
    
    int src, dest;
    while (true) {
        cout << "Edge: ";
        cin >> src >> dest;
        
        if (src == -1 && dest == -1) break;
        
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            graph.addEdge(src, dest);
            cout << "Added edge: " << graph.getVertexLabel(src) 
                 << " -> " << graph.getVertexLabel(dest) << endl;
        } else {
            cout << "Invalid vertices! Please use numbers 0 to " << (vertices-1) << endl;
        }
    }
    
    // Display and analyze graph
    graph.printGraph();
    
    cout << "\nAnalyzing graph..." << endl;
    if (graph.hasCycle()) {
        cout << "❌ Error: Graph contains a cycle!" << endl;
        cout << "Topological sort is only possible for Directed Acyclic Graphs (DAGs)" << endl;
        return;
    }
    
    cout << "✅ Graph is a valid DAG" << endl;
    
    // Perform topological sorts
    vector<int> dfsResult = topologicalSortDFS(graph);
    printTopologicalOrder(graph, dfsResult, "DFS-based Topological Sort");
    
    vector<int> kahnResult = topologicalSortKahn(graph);
    printTopologicalOrder(graph, kahnResult, "Kahn's Algorithm");
    
    // Ask if user wants to see all possible orderings
    if (vertices <= 8) { // Reasonable limit for all orderings
        cout << "\nShow all possible topological orderings? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            vector<vector<int>> allOrders = allTopologicalSorts(graph);
            cout << "\nAll Possible Topological Orderings (" << allOrders.size() << " total):" << endl;
            
            for (size_t i = 0; i < allOrders.size(); i++) {
                cout << "  " << (i+1) << ". ";
                for (size_t j = 0; j < allOrders[i].size(); j++) {
                    cout << graph.getVertexLabel(allOrders[i][j]);
                    if (j < allOrders[i].size() - 1) cout << " -> ";
                }
                cout << endl;
            }
        }
    }
}

/**
 * Main function with user interface
 */
int main() {
    cout << "Topological Sort Algorithm in C++" << endl;
    cout << "=================================" << endl;
    cout << "1. Demonstration mode (predefined examples)" << endl;
    cout << "2. Interactive mode (create custom graph)" << endl;
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
    
    // Algorithm information
    cout << "\n======================================================" << endl;
    cout << "ALGORITHM INFORMATION" << endl;
    cout << "======================================================" << endl;
    cout << "Time Complexity: O(V + E) - visits each vertex and edge once" << endl;
    cout << "Space Complexity: O(V) - for auxiliary data structures" << endl;
    cout << "\nTwo Main Approaches:" << endl;
    cout << "1. DFS-based: Uses recursion and stack for ordering" << endl;
    cout << "2. Kahn's Algorithm: Uses BFS with in-degree tracking" << endl;
    cout << "\nApplications:" << endl;
    cout << "• Task scheduling with dependencies" << endl;
    cout << "• Course prerequisite planning" << endl;
    cout << "• Build systems and compilation order" << endl;
    cout << "• Deadlock detection in operating systems" << endl;
    cout << "• Symbol table construction in compilers" << endl;
    cout << "\nNote: Only works on Directed Acyclic Graphs (DAGs)" << endl;
    
    return 0;
}