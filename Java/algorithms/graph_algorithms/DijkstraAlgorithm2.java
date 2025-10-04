
import java.util.*;

/**
 * Algorithm Name : Dijkstra Algorithm
 * Programming Language: Java
 * Category: Graph Algorithms
 * Difficulty Level: Medium (Intermediate)
 *
 * Problem Statement:
 * Implement Dijkstra’s Algorithm to find the shortest path from a single
 * source vertex to all other vertices in a weighted graph (non-negative edge weights)
 * using a priority queue (min-heap) for optimization.
 *
 * Requirements:
 * - Input:
 *      Number of vertices: V
 *      Number of edges: E
 *      Edges with weights (u, v, w)
 *      Starting vertex: s
 * - Output:
 *      Shortest distance from source to all vertices
 *
 * Complexity:
 * - Time Complexity: O((V + E) * log V)
 * - Space Complexity: O(V + E)
 *
 * Additional Notes:
 * - Negative edge weights are not supported (Dijkstra assumes non-negative edges).
 */
public class DijkstraAlgorithm2 {

    // Inner class to represent a graph edge (destination vertex and weight)
    static class Edge {
        int vertex, weight;
        Edge(int vertex, int weight) {
            this.vertex = vertex;
            this.weight = weight;
        }
    }

    /**
     * Dijkstra’s Algorithm implementation.
     * Uses a PriorityQueue (min-heap) to efficiently get the vertex with the smallest distance.
     */
    public static int[] dijkstra(List<List<Edge>> graph, int source, int V) {
        // Initialize distance array with "infinity" (here, Integer.MAX_VALUE)
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        // Min-heap: stores pairs (distance, vertex)
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{0, source}); // distance = 0, vertex = source

        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int currDist = current[0];
            int u = current[1];

            // Skip if we have already found a better distance
            if (currDist > dist[u]) continue;

            // Traverse all adjacent vertices
            for (Edge edge : graph.get(u)) {
                int v = edge.vertex;
                int weight = edge.weight;

                // Relaxation step: if found shorter path to v, update it
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.offer(new int[]{dist[v], v});
                }
            }
        }
        return dist;
    }

    /**
     * Utility function to add an edge to the adjacency list.
     * Since this example is for a directed graph — remove one addEdge call below for undirected.
     */
    public static void addEdge(List<List<Edge>> graph, int u, int v, int w) {
        graph.get(u).add(new Edge(v, w));
    }

    /**
     * Sample test cases:
     * - Small connected graph
     * - Graph with multiple paths
     * - Single-node graph
     */
    public static void main(String[] args) {
        // Example 1: Small connected graph
        int V1 = 5;
        List<List<Edge>> graph1 = new ArrayList<>();
        for (int i = 0; i < V1; i++) graph1.add(new ArrayList<>());

        addEdge(graph1, 0, 1, 10);
        addEdge(graph1, 0, 4, 5);
        addEdge(graph1, 1, 2, 1);
        addEdge(graph1, 4, 1, 3);
        addEdge(graph1, 4, 2, 9);
        addEdge(graph1, 2, 3, 4);
        addEdge(graph1, 4, 3, 2);

        int source1 = 0;
        int[] dist1 = dijkstra(graph1, source1, V1);
        System.out.println("Shortest distances from vertex " + source1 + ": " + Arrays.toString(dist1));
        System.out.println();

        // Example 2: Graph with multiple paths
        int V2 = 4;
        List<List<Edge>> graph2 = new ArrayList<>();
        for (int i = 0; i < V2; i++) graph2.add(new ArrayList<>());

        addEdge(graph2, 0, 1, 1);
        addEdge(graph2, 0, 2, 4);
        addEdge(graph2, 1, 2, 2);
        addEdge(graph2, 1, 3, 6);
        addEdge(graph2, 2, 3, 3);

        int source2 = 0;
        int[] dist2 = dijkstra(graph2, source2, V2);
        System.out.println("Shortest distances from vertex " + source2 + ": " + Arrays.toString(dist2));
        System.out.println();

        // Example 3: Single-node graph
        int V3 = 1;
        List<List<Edge>> graph3 = new ArrayList<>();
        for (int i = 0; i < V3; i++) graph3.add(new ArrayList<>());

        int source3 = 0;
        int[] dist3 = dijkstra(graph3, source3, V3);
        System.out.println("Shortest distances from vertex " + source3 + ": " + Arrays.toString(dist3));
    }
}
