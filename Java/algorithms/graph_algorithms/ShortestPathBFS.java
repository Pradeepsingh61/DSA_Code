package Java.algorithms.graph_algorithms;

import java.util.*;

/**
 * ShortestPathBFS
 * 
 * Computes shortest distances from a source vertex to all other vertices in an unweighted graph
 * using Breadth-First Search (BFS).
 */
/**
 * ShortestPathBFS
 *
 * Description:
 * Computes the shortest distance from a source vertex to all other vertices
 * in an unweighted graph using Breadth-First Search (BFS).
 *
 * Time Complexity: O(V + E)
 *   - V = number of vertices
 *   - E = number of edges
 *   - Each vertex and edge is visited once during BFS traversal
 *
 * Space Complexity: O(V)
 *   - Stores distance array, visited array, and BFS queue
 */

public class ShortestPathBFS {

    /**
     * Computes shortest distances from source to all vertices
     * 
     * @param graph adjacency list of the graph
     * @param source source vertex
     * @return array of distances (-1 if vertex is unreachable)
     */
    public static int[] shortestPath(int[][] graph, int source) {
        int n = graph.length;
        int[] distance = new int[n];
        Arrays.fill(distance, -1); // initialize distances as -1
        boolean[] visited = new boolean[n];

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(source);
        visited[source] = true;
        distance[source] = 0;

        while (!queue.isEmpty()) {
            int current = queue.poll();

            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[current] + 1;
                    queue.offer(neighbor);
                }
            }
        }

        return distance;
    }

    // Test cases
    public static void main(String[] args) {
        // Test case 1: small connected graph
        int[][] graph1 = { {1, 2}, {0, 3}, {0, 3}, {1, 2} };
        int[] result1 = shortestPath(graph1, 0);
        System.out.println(Arrays.toString(result1)); // Expected: [0, 1, 1, 2]

        // Test case 2: disconnected graph
        int[][] graph2 = { {1}, {0}, {}, {} };
        int[] result2 = shortestPath(graph2, 0);
        System.out.println(Arrays.toString(result2)); // Expected: [0, 1, -1, -1]

        // Test case 3: single-node graph
        int[][] graph3 = { {} };
        int[] result3 = shortestPath(graph3, 0);
        System.out.println(Arrays.toString(result3)); // Expected: [0]
    }
}
