/*
 * Algorithm Name
BFS(Breadth First Search Traversal)

Programming Language
Java

Category
Traversing / Searching

Difficulty Level
Easy

* Algorithm Description : 

1. Problem it solves:

->Used for graph traversal and for finding the shortest path in an unweighted graph.

2. Approach / Idea:
->BFS uses a queue and explores nodes level by level.

->Enqueue the starting node and mark it as visited.

->While the queue is not empty:

->Dequeue a node and process/visit it.

->Enqueue all its unvisited neighbors and mark them visited.

3. Complexity:

Time: O(V + E), where V = number of vertices and E = number of edges.
Space: O(V) for the visited set/array and the queue.

* Author : Surya Pratap Singh

*/

import java.util.*;

public class BFSTraversal{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // Input vertices and edges
        System.out.print("Enter number of vertices: ");
        int V = sc.nextInt();
        System.out.print("Enter number of edges: ");
        int E = sc.nextInt();

        // Graph as adjacency list
        Map<Integer, List<Integer>> graph = new HashMap<>();

        System.out.println("Enter edges (u v): ");
        for (int i = 0; i < E; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            addEdge(graph, u, v); // undirected edge
        }

        System.out.print("Enter starting node: ");
        int start = sc.nextInt();

        System.out.println("BFS Traversal:");
        bfs(graph, start);
    }

    // Function to add edge (undirected graph)
    static void addEdge(Map<Integer, List<Integer>> graph, int u, int v) {
        graph.computeIfAbsent(u, k -> new ArrayList<>()).add(v);
        //avoid the given below line if want directed graph
        graph.computeIfAbsent(v, k -> new ArrayList<>()).add(u);
    }

    // BFS Function
    static void bfs(Map<Integer, List<Integer>> graph, int start) {
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.add(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            int node = queue.poll();
            System.out.print(node + " ");

            for (int neighbour : graph.getOrDefault(node, new ArrayList<>())) {
                if (!visited.contains(neighbour)) {
                    visited.add(neighbour);
                    queue.add(neighbour);
                }
            }
        }
    }
}
