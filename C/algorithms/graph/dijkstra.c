/**
 * Dijkstra's Algorithm (Single-Source Shortest Path) - C Implementation
 *
 * Description:
 * Finds the shortest path distances from a source vertex to all other vertices
 * in a weighted directed graph with non-negative edge weights.
 *
 * Input format (from stdin):
 *  - First line: V E           (number of vertices and edges)
 *  - Next E lines: u v w       (edge from u to v with weight w)
 *  - Last line: src            (source vertex)
 *  Vertices are 0-indexed in the range [0, V-1].
 *
 * Output:
 *  - Prints one line per vertex: "dist[src->i] = D" where D is the distance
 *    from src to i, or INF if unreachable.
 *
 * Time Complexity:
 *  - Using adjacency list + simple O(V) min selection: O(V^2 + E)
 *    (Good for small/medium graphs without extra dependencies.)
 *  - With a binary heap priority queue, it can be improved to O((V + E) log V).
 *
 * Space Complexity:
 *  - O(V + E) for the adjacency list and auxiliary arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    Edge **heads;
    int numVertices;
} Graph;

static Edge *createEdge(int to, int weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if (!edge) {
        fprintf(stderr, "Memory allocation failed for Edge.\n");
        exit(EXIT_FAILURE);
    }
    edge->to = to;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

static Graph createGraph(int numVertices) {
    Graph graph;
    graph.numVertices = numVertices;
    graph.heads = (Edge **)calloc(numVertices, sizeof(Edge *));
    if (!graph.heads) {
        fprintf(stderr, "Memory allocation failed for graph heads.\n");
        exit(EXIT_FAILURE);
    }
    return graph;
}

static void addEdge(Graph *graph, int from, int to, int weight) {
    Edge *edge = createEdge(to, weight);
    edge->next = graph->heads[from];
    graph->heads[from] = edge;
}

static void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Edge *curr = graph->heads[i];
        while (curr) {
            Edge *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->heads);
}

static int extractMinUnvisited(int *dist, int *visited, int V) {
    int minIndex = -1;
    int minValue = INT_MAX;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < minValue) {
            minValue = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

static void dijkstra(const Graph *graph, int source, int *dist) {
    int V = graph->numVertices;
    int *visited = (int *)calloc(V, sizeof(int));
    if (!visited) {
        fprintf(stderr, "Memory allocation failed for visited array.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = extractMinUnvisited(dist, visited, V);
        if (u == -1) {
            break; // No reachable unvisited vertices remain
        }
        visited[u] = 1;

        for (Edge *edge = graph->heads[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            int w = edge->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    free(visited);
}

static void printDistances(const int *dist, int V, int src) {
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("dist[%d->%d] = INF\n", src, i);
        } else {
            printf("dist[%d->%d] = %d\n", src, i, dist[i]);
        }
    }
}

int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) {
        fprintf(stderr, "Invalid input. Expected: V E\n");
        return 1;
    }

    if (V <= 0) {
        fprintf(stderr, "Number of vertices must be positive.\n");
        return 1;
    }

    Graph graph = createGraph(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            fprintf(stderr, "Invalid edge input at line %d. Expected: u v w\n", i + 1);
            freeGraph(&graph);
            return 1;
        }
        if (u < 0 || u >= V || v < 0 || v >= V || w < 0) {
            fprintf(stderr, "Invalid edge values: u=%d v=%d w=%d\n", u, v, w);
            freeGraph(&graph);
            return 1;
        }
        addEdge(&graph, u, v, w);
    }

    int src;
    if (scanf("%d", &src) != 1) {
        fprintf(stderr, "Invalid input. Expected source vertex.\n");
        freeGraph(&graph);
        return 1;
    }
    if (src < 0 || src >= V) {
        fprintf(stderr, "Source vertex out of range.\n");
        freeGraph(&graph);
        return 1;
    }

    int *dist = (int *)malloc(V * sizeof(int));
    if (!dist) {
        fprintf(stderr, "Memory allocation failed for dist array.\n");
        freeGraph(&graph);
        return 1;
    }

    dijkstra(&graph, src, dist);
    printDistances(dist, V, src);

    free(dist);
    freeGraph(&graph);
    return 0;
}


