/*
 * Algorithm Name:
 * Floyd-Warshall Algorithm (All-Pairs Shortest Path)
 *
 * Programming Language:
 * C
 *
 * Category:
 * Dynamic Programming / Graph Algorithms
 *
 * Difficulty Level:
 * Medium to Hard
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> Floyd-Warshall finds the shortest paths between all pairs of vertices
 *       in a weighted directed graph. It can handle negative edge weights but
 *       not negative cycles (which it can detect).
 *
 * 2. Approach / Idea:
 *    -> Uses dynamic programming with a 3D approach conceptually
 *    -> For each vertex k, update shortest path from i to j through k
 *    -> If dist[i][k] + dist[k][j] < dist[i][j], update dist[i][j]
 *    -> Considers all vertices as intermediate vertices systematically
 *
 * 3. Complexity:
 *    Time: O(V³) where V is the number of vertices
 *    Space: O(V²) for the distance matrix
 *
 * 4. Key Features:
 *    -> Handles negative edge weights (unlike Dijkstra)
 *    -> Detects negative cycles in the graph
 *    -> Finds shortest paths between ALL pairs of vertices
 *    -> Uses dynamic programming principle of optimal substructure
 *
 * 5. Applications:
 *    -> Network routing protocols
 *    -> Game theory and economics (transitive closure)
 *    -> Finding shortest routes in transportation networks
 *    -> Detecting arbitrage opportunities in currency exchange
 *
 * 6. Comparison with other algorithms:
 *    -> Dijkstra: Single-source, O((V+E)logV), no negative weights
 *    -> Bellman-Ford: Single-source, O(VE), handles negative weights
 *    -> Floyd-Warshall: All-pairs, O(V³), handles negative weights
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define INF 99999
#define MAX_VERTICES 100

// Structure to represent a graph
typedef struct {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int dist[MAX_VERTICES][MAX_VERTICES];
    int next[MAX_VERTICES][MAX_VERTICES]; // For path reconstruction
} Graph;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void floydWarshall(Graph* graph);
void printDistanceMatrix(Graph* graph);
void printPath(Graph* graph, int start, int end);
void printAllPaths(Graph* graph);
bool hasNegativeCycle(Graph* graph);
void demonstrateAlgorithm(Graph* graph);
void printStep(Graph* graph, int k, int step);
Graph* createSampleGraph();
Graph* createGraphFromInput();
void printGraphInfo(Graph* graph);
void findShortestPath(Graph* graph, int start, int end);
void analyzeGraph(Graph* graph);
void freeGraph(Graph* graph);

int main() {
    int choice;
    Graph* graph = NULL;
    
    printf("=== Floyd-Warshall All-Pairs Shortest Path Algorithm ===\n\n");
    
    while (1) {
        printf("\n=== Floyd-Warshall Operations ===\n");
        printf("1.  Create graph from input\n");
        printf("2.  Use sample graph\n");
        printf("3.  Add edge to current graph\n");
        printf("4.  Run Floyd-Warshall algorithm\n");
        printf("5.  Display distance matrix\n");
        printf("6.  Find shortest path between two vertices\n");
        printf("7.  Display all shortest paths\n");
        printf("8.  Check for negative cycles\n");
        printf("9.  Step-by-step algorithm demonstration\n");
        printf("10. Analyze graph properties\n");
        printf("11. Display graph information\n");
        printf("0.  Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (graph) freeGraph(graph);
                graph = createGraphFromInput();
                printf("Graph created successfully!\n");
                break;
                
            case 2:
                if (graph) freeGraph(graph);
                graph = createSampleGraph();
                printf("Sample graph created!\n");
                printGraphInfo(graph);
                break;
                
            case 3:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                int src, dest, weight;
                printf("Enter source vertex (0-%d): ", graph->vertices - 1);
                scanf("%d", &src);
                printf("Enter destination vertex (0-%d): ", graph->vertices - 1);
                scanf("%d", &dest);
                printf("Enter edge weight: ");
                scanf("%d", &weight);
                
                if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
                    addEdge(graph, src, dest, weight);
                    printf("Edge added: %d -> %d (weight: %d)\n", src, dest, weight);
                } else {
                    printf("Invalid vertex numbers!\n");
                }
                break;
                
            case 4:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printf("Running Floyd-Warshall algorithm...\n");
                floydWarshall(graph);
                printf("Algorithm completed successfully!\n");
                break;
                
            case 5:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printDistanceMatrix(graph);
                break;
                
            case 6:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                int start, end;
                printf("Enter start vertex (0-%d): ", graph->vertices - 1);
                scanf("%d", &start);
                printf("Enter end vertex (0-%d): ", graph->vertices - 1);
                scanf("%d", &end);
                
                if (start >= 0 && start < graph->vertices && end >= 0 && end < graph->vertices) {
                    findShortestPath(graph, start, end);
                } else {
                    printf("Invalid vertex numbers!\n");
                }
                break;
                
            case 7:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printAllPaths(graph);
                break;
                
            case 8:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                if (hasNegativeCycle(graph)) {
                    printf("⚠️  Graph contains negative cycle!\n");
                } else {
                    printf("✅ Graph does not contain negative cycles\n");
                }
                break;
                
            case 9:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                demonstrateAlgorithm(graph);
                break;
                
            case 10:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                analyzeGraph(graph);
                break;
                
            case 11:
                if (!graph) {
                    printf("Please create a graph first!\n");
                    break;
                }
                printGraphInfo(graph);
                break;
                
            case 0:
                if (graph) freeGraph(graph);
                printf("Exiting Floyd-Warshall program. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/**
 * Create a new graph with specified number of vertices
 * 
 * @param vertices: Number of vertices in the graph
 * @return: Pointer to the created graph
 */
Graph* createGraph(int vertices) {
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices! Must be between 1 and %d\n", MAX_VERTICES);
        return NULL;
    }
    
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    graph->vertices = vertices;
    
    // Initialize adjacency matrix and distance matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                graph->adjMatrix[i][j] = 0;
                graph->dist[i][j] = 0;
            } else {
                graph->adjMatrix[i][j] = INF;
                graph->dist[i][j] = INF;
            }
            graph->next[i][j] = -1;
        }
    }
    
    return graph;
}

/**
 * Add an edge to the graph
 * 
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 * @param weight: Weight of the edge
 */
void addEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->vertices || dest < 0 || dest >= graph->vertices) {
        printf("Invalid edge parameters!\n");
        return;
    }
    
    graph->adjMatrix[src][dest] = weight;
    graph->dist[src][dest] = weight;
    graph->next[src][dest] = dest;
}

/**
 * Floyd-Warshall algorithm implementation
 * Finds shortest paths between all pairs of vertices
 * 
 * @param graph: Pointer to the graph
 */
void floydWarshall(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    int V = graph->vertices;
    
    // Initialize distance matrix from adjacency matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->dist[i][j] = graph->adjMatrix[i][j];
            if (graph->adjMatrix[i][j] != INF && i != j) {
                graph->next[i][j] = j;
            } else {
                graph->next[i][j] = -1;
            }
        }
    }
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (graph->dist[i][k] != INF && graph->dist[k][j] != INF &&
                    graph->dist[i][k] + graph->dist[k][j] < graph->dist[i][j]) {
                    
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                    graph->next[i][j] = graph->next[i][k];
                }
            }
        }
    }
}

/**
 * Print the distance matrix showing shortest distances between all pairs
 * 
 * @param graph: Pointer to the graph
 */
void printDistanceMatrix(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    int V = graph->vertices;
    
    printf("\n=== Shortest Distance Matrix ===\n");
    printf("     ");
    for (int i = 0; i < V; i++) {
        printf("%6d", i);
    }
    printf("\n");
    
    for (int i = 0; i < V; i++) {
        printf("%3d: ", i);
        for (int j = 0; j < V; j++) {
            if (graph->dist[i][j] == INF) {
                printf("   INF");
            } else {
                printf("%6d", graph->dist[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Print the shortest path between two vertices
 * 
 * @param graph: Pointer to the graph
 * @param start: Starting vertex
 * @param end: Ending vertex
 */
void printPath(Graph* graph, int start, int end) {
    if (!graph || start < 0 || start >= graph->vertices || end < 0 || end >= graph->vertices) {
        printf("Invalid parameters!\n");
        return;
    }
    
    if (graph->next[start][end] == -1) {
        printf("No path exists from %d to %d\n", start, end);
        return;
    }
    
    printf("Path from %d to %d: %d", start, end, start);
    int current = start;
    
    while (current != end) {
        current = graph->next[current][end];
        printf(" -> %d", current);
    }
    
    printf(" (Distance: %d)\n", graph->dist[start][end]);
}

/**
 * Find and display shortest path between two specific vertices
 * 
 * @param graph: Pointer to the graph
 * @param start: Starting vertex
 * @param end: Ending vertex
 */
void findShortestPath(Graph* graph, int start, int end) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    printf("\n=== Shortest Path Analysis ===\n");
    printf("From vertex %d to vertex %d:\n", start, end);
    
    if (graph->dist[start][end] == INF) {
        printf("❌ No path exists!\n");
    } else {
        printf("✅ Shortest distance: %d\n", graph->dist[start][end]);
        printf("Path: ");
        printPath(graph, start, end);
    }
}

/**
 * Print all shortest paths between all pairs of vertices
 * 
 * @param graph: Pointer to the graph
 */
void printAllPaths(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    int V = graph->vertices;
    
    printf("\n=== All Shortest Paths ===\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                printf("From %d to %d: ", i, j);
                if (graph->dist[i][j] == INF) {
                    printf("No path\n");
                } else {
                    printPath(graph, i, j);
                }
            }
        }
    }
}

/**
 * Check if the graph contains negative cycles
 * 
 * @param graph: Pointer to the graph
 * @return: true if negative cycle exists, false otherwise
 */
bool hasNegativeCycle(Graph* graph) {
    if (!graph) {
        return false;
    }
    
    int V = graph->vertices;
    
    // Check diagonal elements for negative values
    for (int i = 0; i < V; i++) {
        if (graph->dist[i][i] < 0) {
            return true;
        }
    }
    
    return false;
}

/**
 * Demonstrate the Floyd-Warshall algorithm step by step
 * 
 * @param graph: Pointer to the graph
 */
void demonstrateAlgorithm(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    printf("\n=== Floyd-Warshall Step-by-Step Demonstration ===\n");
    
    int V = graph->vertices;
    int tempDist[MAX_VERTICES][MAX_VERTICES];
    
    // Initialize with original distances
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            tempDist[i][j] = graph->adjMatrix[i][j];
        }
    }
    
    printf("Initial distance matrix:\n");
    printStep(graph, -1, 0);
    
    // Run algorithm step by step
    for (int k = 0; k < V; k++) {
        printf("\n--- Using vertex %d as intermediate vertex ---\n", k);
        
        bool updated = false;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (tempDist[i][k] != INF && tempDist[k][j] != INF &&
                    tempDist[i][k] + tempDist[k][j] < tempDist[i][j]) {
                    
                    printf("Updating dist[%d][%d]: %d -> %d (via vertex %d)\n",
                           i, j, tempDist[i][j], tempDist[i][k] + tempDist[k][j], k);
                    
                    tempDist[i][j] = tempDist[i][k] + tempDist[k][j];
                    updated = true;
                }
            }
        }
        
        if (!updated) {
            printf("No updates in this iteration.\n");
        }
        
        // Copy temp distances to graph for display
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                graph->dist[i][j] = tempDist[i][j];
            }
        }
        
        printStep(graph, k, k + 1);
    }
    
    printf("\nAlgorithm completed!\n");
}

/**
 * Print current state of distance matrix during demonstration
 * 
 * @param graph: Pointer to the graph
 * @param k: Current intermediate vertex (-1 for initial state)
 * @param step: Current step number
 */
void printStep(Graph* graph, int k, int step) {
    printf("\nStep %d", step);
    if (k >= 0) {
        printf(" (k = %d)", k);
    }
    printf(":\n");
    printDistanceMatrix(graph);
}

/**
 * Create a sample graph for demonstration
 * 
 * @return: Pointer to the sample graph
 */
Graph* createSampleGraph() {
    Graph* graph = createGraph(4);
    if (!graph) return NULL;
    
    // Add edges to create a sample graph
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 3, 7);
    addEdge(graph, 1, 0, 8);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 2, 0, 5);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 0, 2);
    
    return graph;
}

/**
 * Create graph from user input
 * 
 * @return: Pointer to the created graph
 */
Graph* createGraphFromInput() {
    int vertices, edges;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    Graph* graph = createGraph(vertices);
    if (!graph) return NULL;
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            addEdge(graph, src, dest, weight);
        } else {
            printf("Invalid edge! Skipping...\n");
            i--; // Retry this edge
        }
    }
    
    return graph;
}

/**
 * Print basic information about the graph
 * 
 * @param graph: Pointer to the graph
 */
void printGraphInfo(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    printf("\n=== Graph Information ===\n");
    printf("Number of vertices: %d\n", graph->vertices);
    
    int edgeCount = 0;
    printf("Edges:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j] != INF && i != j) {
                printf("  %d -> %d (weight: %d)\n", i, j, graph->adjMatrix[i][j]);
                edgeCount++;
            }
        }
    }
    printf("Total edges: %d\n", edgeCount);
}

/**
 * Analyze graph properties and provide insights
 * 
 * @param graph: Pointer to the graph
 */
void analyzeGraph(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL!\n");
        return;
    }
    
    printf("\n=== Graph Analysis ===\n");
    
    // Run Floyd-Warshall if not already done
    floydWarshall(graph);
    
    int V = graph->vertices;
    int reachablePairs = 0;
    int totalPairs = V * (V - 1); // Excluding self-loops
    
    // Count reachable pairs
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && graph->dist[i][j] != INF) {
                reachablePairs++;
            }
        }
    }
    
    printf("Connectivity: %d/%d pairs are reachable (%.1f%%)\n",
           reachablePairs, totalPairs, (float)reachablePairs * 100 / totalPairs);
    
    // Check for negative cycles
    if (hasNegativeCycle(graph)) {
        printf("⚠️  Contains negative cycles\n");
    } else {
        printf("✅ No negative cycles detected\n");
    }
    
    // Find diameter (longest shortest path)
    int diameter = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && graph->dist[i][j] != INF && graph->dist[i][j] > diameter) {
                diameter = graph->dist[i][j];
            }
        }
    }
    
    if (diameter > 0) {
        printf("Graph diameter: %d\n", diameter);
    }
    
    printf("Algorithm complexity: O(%d³) = O(%d) operations\n", V, V * V * V);
}

/**
 * Free memory allocated for the graph
 * 
 * @param graph: Pointer to the graph to free
 */
void freeGraph(Graph* graph) {
    if (graph) {
        free(graph);
    }
}
