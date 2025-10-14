/*
 * Algorithm: Depth-First Search (DFS)
 * Description: Graph traversal algorithm that explores as far as possible before backtracking
 * Time Complexity: O(V + E) where V is vertices and E is edges
 * Space Complexity: O(V) for recursion stack and visited array
 * Author: DSA Code Repository
 * Date: 2025-10-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Graph structure using adjacency matrix
typedef struct {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

/**
 * Create a new graph with given number of vertices
 * @param vertices: Number of vertices in the graph
 * @return: Pointer to the created graph
 */
Graph* createGraph(int vertices) {
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Error: Invalid number of vertices\n");
        return NULL;
    }
    
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    // Initialize adjacency matrix with 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}

/**
 * Add an undirected edge to the graph
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 */
void addEdge(Graph* graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices) {
        printf("Error: Invalid edge (%d, %d)\n", src, dest);
        return;
    }
    
    // For undirected graph
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

/**
 * Add a directed edge to the graph
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 */
void addDirectedEdge(Graph* graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices) {
        printf("Error: Invalid edge (%d, %d)\n", src, dest);
        return;
    }
    
    graph->adjMatrix[src][dest] = 1;
}

/**
 * Recursive DFS utility function
 * @param graph: Pointer to the graph
 * @param vertex: Current vertex
 * @param visited: Array to track visited vertices
 */
void DFS_util(Graph* graph, int vertex, bool visited[]) {
    // Mark current vertex as visited and print it
    visited[vertex] = true;
    printf("%d ", vertex);
    
    // Recursively visit all adjacent unvisited vertices
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFS_util(graph, i, visited);
        }
    }
}

/**
 * Perform DFS traversal starting from a given vertex
 * @param graph: Pointer to the graph
 * @param startVertex: Starting vertex for DFS
 */
void DFS(Graph* graph, int startVertex) {
    if (graph == NULL || startVertex < 0 || startVertex >= graph->vertices) {
        printf("Error: Invalid starting vertex\n");
        return;
    }
    
    bool visited[MAX_VERTICES] = {false};
    
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFS_util(graph, startVertex, visited);
    printf("\n");
}

/**
 * Perform DFS traversal for entire graph (handles disconnected components)
 * @param graph: Pointer to the graph
 */
void DFS_complete(Graph* graph) {
    if (graph == NULL) {
        printf("Error: Graph is NULL\n");
        return;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int component = 1;
    
    printf("Complete DFS Traversal:\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            printf("Component %d: ", component++);
            DFS_util(graph, i, visited);
            printf("\n");
        }
    }
}

/**
 * Check if there's a path between two vertices using DFS
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 * @return: 1 if path exists, 0 otherwise
 */
int hasPath_DFS(Graph* graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices) {
        return 0;
    }
    
    if (src == dest) {
        return 1;
    }
    
    bool visited[MAX_VERTICES] = {false};
    
    // Use iterative DFS with explicit stack
    int stack[MAX_VERTICES];
    int top = -1;
    
    // Push source vertex
    stack[++top] = src;
    
    while (top >= 0) {
        int current = stack[top--];
        
        if (current == dest) {
            return 1;
        }
        
        if (!visited[current]) {
            visited[current] = true;
            
            // Push all unvisited adjacent vertices
            for (int i = graph->vertices - 1; i >= 0; i--) {
                if (graph->adjMatrix[current][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
    
    return 0;
}

/**
 * Detect cycle in undirected graph using DFS
 * @param graph: Pointer to the graph
 * @return: 1 if cycle exists, 0 otherwise
 */
int hasCycle_undirected(Graph* graph) {
    if (graph == NULL) {
        return 0;
    }
    
    bool visited[MAX_VERTICES] = {false};
    
    // Check each component
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            // Use DFS to detect cycle in this component
            int stack[MAX_VERTICES];
            int parent[MAX_VERTICES];
            int top = -1;
            
            stack[++top] = i;
            parent[i] = -1;
            
            while (top >= 0) {
                int current = stack[top--];
                visited[current] = true;
                
                for (int j = 0; j < graph->vertices; j++) {
                    if (graph->adjMatrix[current][j] == 1) {
                        if (!visited[j]) {
                            stack[++top] = j;
                            parent[j] = current;
                        } else if (j != parent[current]) {
                            return 1; // Cycle found
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

/**
 * Detect cycle in directed graph using DFS
 * @param graph: Pointer to the graph
 * @return: 1 if cycle exists, 0 otherwise
 */
int hasCycle_directed(Graph* graph) {
    if (graph == NULL) {
        return 0;
    }
    
    int visited[MAX_VERTICES] = {0}; // 0: unvisited, 1: visiting, 2: visited
    
    for (int i = 0; i < graph->vertices; i++) {
        if (visited[i] == 0) {
            // Use stack for iterative DFS
            int stack[MAX_VERTICES];
            int top = -1;
            
            stack[++top] = i;
            
            while (top >= 0) {
                int current = stack[top];
                
                if (visited[current] == 0) {
                    visited[current] = 1; // Mark as visiting
                    
                    // Push all unvisited adjacent vertices
                    for (int j = 0; j < graph->vertices; j++) {
                        if (graph->adjMatrix[current][j] == 1) {
                            if (visited[j] == 1) {
                                return 1; // Back edge found - cycle detected
                            }
                            if (visited[j] == 0) {
                                stack[++top] = j;
                            }
                        }
                    }
                } else {
                    visited[current] = 2; // Mark as visited
                    top--;
                }
            }
        }
    }
    
    return 0;
}

/**
 * Count number of connected components using DFS
 * @param graph: Pointer to the graph
 * @return: Number of connected components
 */
int countComponents(Graph* graph) {
    if (graph == NULL) {
        return 0;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int count = 0;
    
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            count++;
            DFS_util(graph, i, visited);
        }
    }
    
    return count;
}

/**
 * Print the adjacency matrix of the graph
 * @param graph: Pointer to the graph
 */
void printGraph(Graph* graph) {
    if (graph == NULL) {
        printf("Graph is NULL\n");
        return;
    }
    
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Test function to demonstrate DFS algorithm
 */
void test_dfs() {
    printf("Testing DFS Algorithm\n");
    printf("=====================\n");
    
    // Test Case 1: Simple undirected graph
    printf("\nTest Case 1: Simple Undirected Graph\n");
    printf("------------------------------------\n");
    
    Graph* graph1 = createGraph(6);
    
    // Add edges: 0-1, 0-2, 1-3, 1-4, 2-4, 3-5, 4-5
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 1, 3);
    addEdge(graph1, 1, 4);
    addEdge(graph1, 2, 4);
    addEdge(graph1, 3, 5);
    addEdge(graph1, 4, 5);
    
    printGraph(graph1);
    
    // DFS from different starting vertices
    DFS(graph1, 0);
    DFS(graph1, 3);
    
    // Test path finding
    printf("\nPath Testing:\n");
    printf("Path from 0 to 5: %s\n", hasPath_DFS(graph1, 0, 5) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 1 to 2: %s\n", hasPath_DFS(graph1, 1, 2) ? "EXISTS" : "NOT EXISTS");
    
    // Test cycle detection
    printf("Cycle in undirected graph: %s\n", hasCycle_undirected(graph1) ? "YES" : "NO");
    
    // Test Case 2: Directed graph
    printf("\n\nTest Case 2: Directed Graph\n");
    printf("---------------------------\n");
    
    Graph* graph2 = createGraph(4);
    
    // Add directed edges
    addDirectedEdge(graph2, 0, 1);
    addDirectedEdge(graph2, 0, 2);
    addDirectedEdge(graph2, 1, 2);
    addDirectedEdge(graph2, 2, 3);
    
    printGraph(graph2);
    DFS(graph2, 0);
    
    printf("Path from 0 to 3: %s\n", hasPath_DFS(graph2, 0, 3) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 3 to 0: %s\n", hasPath_DFS(graph2, 3, 0) ? "EXISTS" : "NOT EXISTS");
    printf("Cycle in directed graph: %s\n", hasCycle_directed(graph2) ? "YES" : "NO");
    
    // Test Case 3: Directed graph with cycle
    printf("\n\nTest Case 3: Directed Graph with Cycle\n");
    printf("--------------------------------------\n");
    
    Graph* graph3 = createGraph(4);
    
    // Add directed edges creating a cycle
    addDirectedEdge(graph3, 0, 1);
    addDirectedEdge(graph3, 1, 2);
    addDirectedEdge(graph3, 2, 3);
    addDirectedEdge(graph3, 3, 1); // Creates cycle: 1->2->3->1
    
    printGraph(graph3);
    DFS(graph3, 0);
    printf("Cycle in directed graph: %s\n", hasCycle_directed(graph3) ? "YES" : "NO");
    
    // Test Case 4: Disconnected graph
    printf("\n\nTest Case 4: Disconnected Graph\n");
    printf("-------------------------------\n");
    
    Graph* graph4 = createGraph(7);
    
    // Add edges creating multiple components: {0,1,2}, {3,4}, {5}, {6}
    addEdge(graph4, 0, 1);
    addEdge(graph4, 1, 2);
    addEdge(graph4, 3, 4);
    // Vertices 5 and 6 are isolated
    
    printGraph(graph4);
    DFS_complete(graph4);
    
    int components = countComponents(graph4);
    printf("Number of connected components: %d\n", components);
    
    printf("Path from 0 to 3: %s\n", hasPath_DFS(graph4, 0, 3) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 0 to 2: %s\n", hasPath_DFS(graph4, 0, 2) ? "EXISTS" : "NOT EXISTS");
    
    // Cleanup
    free(graph1);
    free(graph2);
    free(graph3);
    free(graph4);
}

int main() {
    test_dfs();
    return 0;
}