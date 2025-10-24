/* Algorithm Name
DFS (Depth First Search Traversal)

Programming Language
Java

Category
Traversing / Searching

Difficulty Level
Easy

* Algorithm Description : 

1. Problem it solves:

-> Used for graph traversal and can be applied for topological sorting, cycle detection, and pathfinding problems.

2. Approach / Idea:
-> DFS uses a stack (can be implemented recursively or iteratively) and explores nodes as deep as possible before backtracking.

-> Start from the source node and mark it as visited.

-> Visit all unvisited neighbors recursively (or using a stack).

-> Continue until all reachable nodes are visited.

3. Complexity:

Time: O(V + E), where V = number of vertices and E = number of edges.
Space: O(V) for the recursion stack or explicit stack and visited set/array.

* Author : Subhodeep Chatterjee

*/

import java.util.*;

public class DFSTraversal {
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

        System.out.println("DFS Traversal:");
        Set<Integer> visited = new HashSet<>();
        dfs(graph, start, visited);
    }

    // Function to add edge (undirected graph)
    static void addEdge(Map<Integer, List<Integer>> graph, int u, int v) {
        graph.computeIfAbsent(u, k -> new ArrayList<>()).add(v);
        // avoid the given below line if you want directed graph
        graph.computeIfAbsent(v, k -> new ArrayList<>()).add(u);
    }

    // Recursive DFS Function
    static void dfs(Map<Integer, List<Integer>> graph, int node, Set<Integer> visited) {
        visited.add(node);
        System.out.print(node + " ");

        for (int neighbour : graph.getOrDefault(node, new ArrayList<>())) {
            if (!visited.contains(neighbour)) {
                dfs(graph, neighbour, visited);
            }
        }
    }
}
