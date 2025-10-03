/*
 * Algorithm: Breadth-First Search (BFS)
 * Description: Graph traversal algorithm that explores vertices level by level
 * Time Complexity: O(V + E) where V is vertices and E is edges
 * Space Complexity: O(V) for queue and visited array
 * Author: DSA Code Repository
 * Date: 2025-10-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Queue structure for BFS
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// Function to create a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    return q->rear == -1;
}

// Add element to queue
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue overflow!\n");
        return;
    }
    
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

// Remove element from queue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow!\n");
        return -1;
    }
    
    int item = q->items[q->front];
    q->front++;
    
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    
    return item;
}

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
 * Add an edge to the graph
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
 * Perform BFS traversal starting from a given vertex
 * @param graph: Pointer to the graph
 * @param startVertex: Starting vertex for BFS
 */
void BFS(Graph* graph, int startVertex) {
    if (graph == NULL || startVertex < 0 || startVertex >= graph->vertices) {
        printf("Error: Invalid starting vertex\n");
        return;
    }
    
    bool visited[MAX_VERTICES] = {false};
    Queue* queue = createQueue();
    
    printf("BFS Traversal starting from vertex %d: ", startVertex);
    
    // Mark start vertex as visited and enqueue it
    visited[startVertex] = true;
    enqueue(queue, startVertex);
    
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        
        // Check all adjacent vertices
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    
    printf("\n");
    free(queue);
}

/**
 * Check if there's a path between two vertices using BFS
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 * @return: 1 if path exists, 0 otherwise
 */
int hasPath(Graph* graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices) {
        return 0;
    }
    
    if (src == dest) {
        return 1;
    }
    
    bool visited[MAX_VERTICES] = {false};
    Queue* queue = createQueue();
    
    visited[src] = true;
    enqueue(queue, src);
    
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1) {
                if (i == dest) {
                    free(queue);
                    return 1;
                }
                
                if (!visited[i]) {
                    visited[i] = true;
                    enqueue(queue, i);
                }
            }
        }
    }
    
    free(queue);
    return 0;
}

/**
 * Find shortest path distance using BFS (unweighted graph)
 * @param graph: Pointer to the graph
 * @param src: Source vertex
 * @param dest: Destination vertex
 * @return: Shortest distance, -1 if no path exists
 */
int shortestPath(Graph* graph, int src, int dest) {
    if (graph == NULL || src < 0 || src >= graph->vertices || 
        dest < 0 || dest >= graph->vertices) {
        return -1;
    }
    
    if (src == dest) {
        return 0;
    }
    
    bool visited[MAX_VERTICES] = {false};
    int distance[MAX_VERTICES];
    Queue* queue = createQueue();
    
    // Initialize distances
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = -1;
    }
    
    visited[src] = true;
    distance[src] = 0;
    enqueue(queue, src);
    
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[currentVertex] + 1;
                enqueue(queue, i);
                
                if (i == dest) {
                    int result = distance[dest];
                    free(queue);
                    return result;
                }
            }
        }
    }
    
    free(queue);
    return -1;
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
 * Test function to demonstrate BFS algorithm
 */
void test_bfs() {
    printf("Testing BFS Algorithm\n");
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
    
    // BFS from different starting vertices
    BFS(graph1, 0);
    BFS(graph1, 3);
    
    // Test path finding
    printf("\nPath Testing:\n");
    printf("Path from 0 to 5: %s\n", hasPath(graph1, 0, 5) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 1 to 2: %s\n", hasPath(graph1, 1, 2) ? "EXISTS" : "NOT EXISTS");
    
    // Test shortest path
    printf("\nShortest Path Testing:\n");
    printf("Shortest distance from 0 to 5: %d\n", shortestPath(graph1, 0, 5));
    printf("Shortest distance from 1 to 2: %d\n", shortestPath(graph1, 1, 2));
    
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
    BFS(graph2, 0);
    
    printf("Path from 0 to 3: %s\n", hasPath(graph2, 0, 3) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 3 to 0: %s\n", hasPath(graph2, 3, 0) ? "EXISTS" : "NOT EXISTS");
    
    // Test Case 3: Disconnected graph
    printf("\n\nTest Case 3: Disconnected Graph\n");
    printf("-------------------------------\n");
    
    Graph* graph3 = createGraph(5);
    
    // Add edges creating two components: {0,1} and {2,3,4}
    addEdge(graph3, 0, 1);
    addEdge(graph3, 2, 3);
    addEdge(graph3, 3, 4);
    
    printGraph(graph3);
    BFS(graph3, 0);  // Will only visit component {0,1}
    BFS(graph3, 2);  // Will visit component {2,3,4}
    
    printf("Path from 0 to 2: %s\n", hasPath(graph3, 0, 2) ? "EXISTS" : "NOT EXISTS");
    printf("Path from 2 to 4: %s\n", hasPath(graph3, 2, 4) ? "EXISTS" : "NOT EXISTS");
    
    // Cleanup
    free(graph1);
    free(graph2);
    free(graph3);
}

int main() {
    test_bfs();
    return 0;
}