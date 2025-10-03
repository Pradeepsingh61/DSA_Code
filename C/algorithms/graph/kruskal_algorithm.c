/*
 * Algorithm: Kruskal's Algorithm for Minimum Spanning Tree
 * Description: Finds minimum spanning tree using greedy approach and union-find
 * Time Complexity: O(E log E) where E is the number of edges
 * Space Complexity: O(V + E) where V is vertices and E is edges
 * Author: DSA Code Repository
 * Date: 2025-10-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

// Edge structure
typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

// Graph structure for Kruskal's algorithm
typedef struct {
    int vertices;
    int edges;
    Edge edgeList[MAX_EDGES];
} Graph;

// Union-Find (Disjoint Set) structure
typedef struct {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
} UnionFind;

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
    graph->edges = 0;
    
    return graph;
}

/**
 * Add an edge to the graph
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 * @param weight: Weight of the edge
 */
void addEdge(Graph* graph, int src, int dest, int weight) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices || graph->edges >= MAX_EDGES) {
        printf("Error: Invalid edge (%d, %d) with weight %d\n", src, dest, weight);
        return;
    }
    
    graph->edgeList[graph->edges].src = src;
    graph->edgeList[graph->edges].dest = dest;
    graph->edgeList[graph->edges].weight = weight;
    graph->edges++;
}

/**
 * Initialize Union-Find data structure
 * @param uf: Pointer to UnionFind structure
 * @param vertices: Number of vertices
 */
void initializeUnionFind(UnionFind* uf, int vertices) {
    for (int i = 0; i < vertices; i++) {
        uf->parent[i] = i;  // Each vertex is its own parent initially
        uf->rank[i] = 0;    // Initial rank is 0
    }
}

/**
 * Find the root of a vertex with path compression
 * @param uf: Pointer to UnionFind structure
 * @param vertex: Vertex to find root for
 * @return: Root of the vertex
 */
int find(UnionFind* uf, int vertex) {
    if (uf->parent[vertex] != vertex) {
        uf->parent[vertex] = find(uf, uf->parent[vertex]); // Path compression
    }
    return uf->parent[vertex];
}

/**
 * Union two sets by rank
 * @param uf: Pointer to UnionFind structure
 * @param x: First vertex
 * @param y: Second vertex
 * @return: 1 if union performed, 0 if already in same set
 */
int unionSets(UnionFind* uf, int x, int y) {
    int rootX = find(uf, x);
    int rootY = find(uf, y);
    
    if (rootX == rootY) {
        return 0; // Already in same set
    }
    
    // Union by rank
    if (uf->rank[rootX] < uf->rank[rootY]) {
        uf->parent[rootX] = rootY;
    } else if (uf->rank[rootX] > uf->rank[rootY]) {
        uf->parent[rootY] = rootX;
    } else {
        uf->parent[rootY] = rootX;
        uf->rank[rootX]++;
    }
    
    return 1;
}

/**
 * Compare function for sorting edges by weight
 * @param a: First edge
 * @param b: Second edge
 * @return: Comparison result
 */
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

/**
 * Kruskal's algorithm to find Minimum Spanning Tree
 * @param graph: Pointer to the graph
 * @param mst: Array to store MST edges
 * @return: Total weight of MST, -1 if MST doesn't exist
 */
int kruskalMST(Graph* graph, Edge mst[]) {
    if (graph == NULL || graph->vertices < 2) {
        printf("Error: Invalid graph for MST\n");
        return -1;
    }
    
    // Sort edges by weight
    qsort(graph->edgeList, graph->edges, sizeof(Edge), compareEdges);
    
    UnionFind uf;
    initializeUnionFind(&uf, graph->vertices);
    
    int mstWeight = 0;
    int mstEdges = 0;
    int maxMSTEdges = graph->vertices - 1;
    
    printf("Processing edges in sorted order:\n");
    printf("Edge\t\tWeight\tStatus\n");
    printf("----\t\t------\t------\n");
    
    for (int i = 0; i < graph->edges && mstEdges < maxMSTEdges; i++) {
        Edge currentEdge = graph->edgeList[i];
        
        printf("(%d, %d)\t\t%d\t", currentEdge.src, currentEdge.dest, currentEdge.weight);
        
        // Check if adding this edge creates a cycle
        if (unionSets(&uf, currentEdge.src, currentEdge.dest)) {
            // No cycle, add to MST
            mst[mstEdges] = currentEdge;
            mstWeight += currentEdge.weight;
            mstEdges++;
            printf("Added\n");
        } else {
            // Would create cycle, skip
            printf("Rejected (cycle)\n");
        }
    }
    
    // Check if MST is complete
    if (mstEdges != maxMSTEdges) {
        printf("Error: Graph is not connected, MST impossible\n");
        return -1;
    }
    
    return mstWeight;
}

/**
 * Check if graph is connected using Union-Find
 * @param graph: Pointer to the graph
 * @return: 1 if connected, 0 otherwise
 */
int isConnected(Graph* graph) {
    if (graph == NULL || graph->vertices <= 1) {
        return 1;
    }
    
    UnionFind uf;
    initializeUnionFind(&uf, graph->vertices);
    
    // Union all edges
    for (int i = 0; i < graph->edges; i++) {
        unionSets(&uf, graph->edgeList[i].src, graph->edgeList[i].dest);
    }
    
    // Check if all vertices have same root
    int root = find(&uf, 0);
    for (int i = 1; i < graph->vertices; i++) {
        if (find(&uf, i) != root) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * Print all edges in the graph
 * @param graph: Pointer to the graph
 */
void printGraph(Graph* graph) {
    if (graph == NULL) {
        printf("Graph is NULL\n");
        return;
    }
    
    printf("\nGraph edges:\n");
    printf("Edge\t\tWeight\n");
    printf("----\t\t------\n");
    
    for (int i = 0; i < graph->edges; i++) {
        printf("(%d, %d)\t\t%d\n", 
               graph->edgeList[i].src, 
               graph->edgeList[i].dest, 
               graph->edgeList[i].weight);
    }
}

/**
 * Print MST edges and total weight
 * @param mst: Array of MST edges
 * @param vertices: Number of vertices
 * @param totalWeight: Total weight of MST
 */
void printMST(Edge mst[], int vertices, int totalWeight) {
    printf("\nMinimum Spanning Tree:\n");
    printf("Edge\t\tWeight\n");
    printf("----\t\t------\n");
    
    for (int i = 0; i < vertices - 1; i++) {
        printf("(%d, %d)\t\t%d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
    
    printf("\nTotal MST Weight: %d\n", totalWeight);
}

/**
 * Create a sample graph for testing
 * @return: Pointer to created test graph
 */
Graph* createTestGraph1() {
    Graph* graph = createGraph(4);
    
    // Add edges with weights
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 3, 15);
    addEdge(graph, 2, 3, 4);
    
    return graph;
}

/**
 * Create another sample graph for testing
 * @return: Pointer to created test graph
 */
Graph* createTestGraph2() {
    Graph* graph = createGraph(6);
    
    // Add edges with weights (more complex graph)
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 10);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 5, 6);
    addEdge(graph, 4, 5, 3);
    
    return graph;
}

/**
 * Create disconnected graph for testing
 * @return: Pointer to created test graph
 */
Graph* createDisconnectedGraph() {
    Graph* graph = createGraph(5);
    
    // Add edges creating two components: {0,1,2} and {3,4}
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 3, 4, 3);
    // No edge connecting the two components
    
    return graph;
}

/**
 * Test function to demonstrate Kruskal's algorithm
 */
void test_kruskal() {
    printf("Testing Kruskal's Algorithm for Minimum Spanning Tree\n");
    printf("====================================================\n");
    
    Edge mst[MAX_VERTICES];
    
    // Test Case 1: Simple connected graph
    printf("\nTest Case 1: Simple Connected Graph\n");
    printf("-----------------------------------\n");
    
    Graph* graph1 = createTestGraph1();
    printGraph(graph1);
    
    printf("\nIs graph connected: %s\n", isConnected(graph1) ? "YES" : "NO");
    
    int mstWeight1 = kruskalMST(graph1, mst);
    if (mstWeight1 != -1) {
        printMST(mst, graph1->vertices, mstWeight1);
    }
    
    // Test Case 2: More complex graph
    printf("\n\nTest Case 2: Complex Connected Graph\n");
    printf("------------------------------------\n");
    
    Graph* graph2 = createTestGraph2();
    printGraph(graph2);
    
    printf("\nIs graph connected: %s\n", isConnected(graph2) ? "YES" : "NO");
    
    int mstWeight2 = kruskalMST(graph2, mst);
    if (mstWeight2 != -1) {
        printMST(mst, graph2->vertices, mstWeight2);
    }
    
    // Test Case 3: Disconnected graph
    printf("\n\nTest Case 3: Disconnected Graph\n");
    printf("-------------------------------\n");
    
    Graph* graph3 = createDisconnectedGraph();
    printGraph(graph3);
    
    printf("\nIs graph connected: %s\n", isConnected(graph3) ? "YES" : "NO");
    
    int mstWeight3 = kruskalMST(graph3, mst);
    if (mstWeight3 == -1) {
        printf("MST cannot be formed for disconnected graph!\n");
    }
    
    // Test Case 4: Single vertex
    printf("\n\nTest Case 4: Single Vertex Graph\n");
    printf("--------------------------------\n");
    
    Graph* graph4 = createGraph(1);
    printf("Graph with 1 vertex:\n");
    printGraph(graph4);
    
    printf("Is graph connected: %s\n", isConnected(graph4) ? "YES" : "NO");
    printf("MST for single vertex: Not applicable (no edges needed)\n");
    
    // Test Case 5: Two vertices
    printf("\n\nTest Case 5: Two Vertices Graph\n");
    printf("-------------------------------\n");
    
    Graph* graph5 = createGraph(2);
    addEdge(graph5, 0, 1, 5);
    printGraph(graph5);
    
    printf("\nIs graph connected: %s\n", isConnected(graph5) ? "YES" : "NO");
    
    int mstWeight5 = kruskalMST(graph5, mst);
    if (mstWeight5 != -1) {
        printMST(mst, graph5->vertices, mstWeight5);
    }
    
    // Cleanup
    free(graph1);
    free(graph2);
    free(graph3);
    free(graph4);
    free(graph5);
}

int main() {
    test_kruskal();
    return 0;
}