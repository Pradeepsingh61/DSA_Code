import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

// A class to represent the graph and run the Bellman-Ford algorithm
class BellmanFord {

    // A nested class to represent a weighted edge in the graph
    static class Edge {
        int source, destination, weight;

        Edge(int source, int destination, int weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }
    }

    private final int V; // Number of vertices
    private final List<Edge> edges; // List of all edges

    public BellmanFord(int V) {
        this.V = V;
        this.edges = new ArrayList<>();
    }

    public void addEdge(int source, int destination, int weight) {
        edges.add(new Edge(source, destination, weight));
    }

    /**
     * Finds the shortest paths from a source vertex to all other vertices
     * in a weighted directed graph using the Bellman-Ford algorithm.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * The Bellman-Ford algorithm is a single-source shortest path algorithm that works on
     * directed, weighted graphs. Its key advantage over Dijkstra's algorithm is its ability
     * to handle graphs with negative edge weights. It can also detect if the graph
     * contains a negative-weight cycle that is reachable from the source.
     *
     * DYNAMIC PROGRAMMING & RELAXATION APPROACH:
     * The algorithm works by iteratively "relaxing" edges. A relaxation step for an edge (u, v)
     * with weight 'w' consists of checking if the shortest known path to 'v' can be improved
     * by going through 'u'.
     *
     * Core Idea:
     * If dist[u] + weight(u, v) < dist[v], then we update dist[v] = dist[u] + weight(u, v).
     *
     * Algorithm Steps:
     * 1. INITIALIZATION:
     * - Create a distance array `dist[]` of size V (number of vertices).
     * - Initialize the distance to the source vertex as 0.
     * - Initialize the distances to all other vertices as INFINITY.
     *
     * 2. ITERATIVE RELAXATION:
     * - Repeat the following loop V-1 times:
     * - For each edge (u, v) with weight 'w' in the graph:
     * - Perform the relaxation step: if `dist[u] + w < dist[v]`, update `dist[v]`.
     * - Why V-1 times? A simple shortest path in a graph with V vertices can have at most V-1 edges.
     * In the worst case, each iteration finds the next edge in the shortest path. After V-1
     * iterations, we guarantee that we have found all shortest paths if no negative cycle exists.
     *
     * 3. NEGATIVE CYCLE DETECTION:
     * - After the V-1 iterations, perform one final iteration over all edges.
     * - If for any edge (u, v), we can still perform a relaxation (i.e., if `dist[u] + w < dist[v]`),
     * it means the path can be shortened indefinitely. This is only possible if there is a
     * negative-weight cycle in the graph. In this case, the algorithm reports the cycle's existence.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Time Complexity: O(V * E)
     * where V is the number of vertices and E is the number of edges.
     * The main logic consists of a loop that runs V-1 times (or V times, including the
     * cycle check), and inside this loop, we iterate over all E edges.
     *
     * Space Complexity: O(V)
     * This is the auxiliary space required to store the `dist` array. The space for the
     * graph representation itself (the edge list) is O(E). So total space is O(V + E).
     *
     * @param source The source vertex from which to find shortest paths.
     */
    public void runBellmanFord(int source) {
        // Step 1: Initialize distances array.
        // Set distance to source as 0 and all others as infinite.
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        // Step 2: Relax all edges V-1 times.
        // A simple shortest path from source to any other vertex can have at most V-1 edges.
        for (int i = 1; i < V; ++i) {
            // Iterate through all edges in the graph
            for (Edge edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;

                // Perform the relaxation step
                // Check if a shorter path to 'v' is found through 'u'
                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Step 3: Check for negative-weight cycles.
        // This loop runs one more time (the V-th time) to detect cycles.
        for (Edge edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            // If we can still relax an edge, it means a negative cycle exists.
            if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                System.out.println("Graph contains a negative weight cycle!");
                return; // Exit if a cycle is detected
            }
        }

        // If no negative cycle, print the distances
        printDistances(dist, source);
    }

    private void printDistances(int[] dist, int source) {
        System.out.println("Shortest distances from source vertex " + source + ":");
        for (int i = 0; i < V; ++i) {
            if (dist[i] == Integer.MAX_VALUE) {
                System.out.println("Vertex " + i + " is unreachable.");
            } else {
                System.out.println("Vertex " + i + " \t at distance \t" + dist[i]);
            }
        }
    }

    public static void main(String[] args) {
        int V = 5; // 5 vertices
        BellmanFord graph = new BellmanFord(V);

        // Add edges to the graph
        graph.addEdge(0, 1, -1);
        graph.addEdge(0, 2, 4);
        graph.addEdge(1, 2, 3);
        graph.addEdge(1, 3, 2);
        graph.addEdge(1, 4, 2);
        graph.addEdge(3, 2, 5);
        graph.addEdge(3, 1, 1);
        graph.addEdge(4, 3, -3);

        int sourceVertex = 0;
        graph.runBellmanFord(sourceVertex);

        /*
         Example for Negative Cycle Detection:
         
         int V_cycle = 4;
         BellmanFord cycleGraph = new BellmanFord(V_cycle);
         cycleGraph.addEdge(0, 1, 1);
         cycleGraph.addEdge(1, 2, -1);
         cycleGraph.addEdge(2, 3, -1);
         cycleGraph.addEdge(3, 0, -1); // This edge creates a negative cycle
         
         System.out.println("\n--- Testing Graph with Negative Cycle ---");
         cycleGraph.runBellmanFord(0);
        */
    }
}