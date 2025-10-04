/*
 * Topological Sort — Kahn's Algorithm (BFS)
 * ========================================
 * ✍️ Algorithm Description
 * -----------------------
 * A topological order of a directed graph lists vertices such that
 * every directed edge u -> v places u before v in the order. This is
 * only possible for Directed Acyclic Graphs (DAGs).
 *
 * Kahn's Algorithm (BFS approach) works by:
 * 1) Building an adjacency list and indegree for each vertex.
 * 2) Enqueuing all vertices with indegree 0 (no prerequisites).
 * 3) Repeatedly:
 *    - Dequeue a vertex, append to the order.
 *    - Decrease indegree of its neighbors.
 *    - Any neighbor reaching indegree 0 is enqueued.
 * 4) If we process exactly V vertices, we have a valid topo order.
 *    If not, a cycle exists (graph is not a DAG).
 *
 * Use cases:
 * - Task scheduling with dependencies (build systems, course planning)
 * - Ordering compilation units
 * - Resolving package installation order
 *
 * 📊 Complexity Analysis
 * ----------------------
 * Let V = number of vertices, E = number of edges.
 * Time:  O(V + E) — each node and edge is processed once.
 * Space: O(V + E) — adjacency list + indegree array + queue + output.
 *
 * 💡 Notes
 * - `topoSort1` uses a HashMap for indegree (handy with sparse/labeled nodes).
 * - `topoSort2` uses an int[] for indegree (faster when nodes are 0..V-1).
 * - `hasCycleKahn` returns true if a cycle exists (no topo order).
 */

 import java.util.*;

 class Solution {
 
     /**
      * Topological sort using HashMap for indegree.
      *
      * @param V     number of vertices (assumed labeled 0..V-1)
      * @param edges list of directed edges as [u, v] meaning u -> v
      * @return      a valid topological ordering (size V if DAG)
      */
     public static ArrayList<Integer> topoSort1(int V, int[][] edges) {
         // Build adjacency list and indegree map
         ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
         HashMap<Integer, Integer> indeg = new HashMap<>();
 
         for (int i = 0; i < V; i++) {
             indeg.put(i, 0);
             adj.add(new ArrayList<>());
         }
 
         for (int[] e : edges) {
             int u = e[0], v = e[1];
             adj.get(u).add(v);
             indeg.put(v, indeg.get(v) + 1);
         }
 
         // Initialize queue with all 0-indegree nodes
         Queue<Integer> q = new LinkedList<>();
         for (int i = 0; i < V; i++) {
             if (indeg.get(i) == 0) q.offer(i);
         }
 
         // Kahn's BFS
         ArrayList<Integer> order = new ArrayList<>();
         while (!q.isEmpty()) {
             int cur = q.poll();
             order.add(cur);
 
             // "Remove" edges cur -> nbr by decreasing indegree
             for (int nbr : adj.get(cur)) {
                 indeg.put(nbr, indeg.get(nbr) - 1);
                 if (indeg.get(nbr) == 0) q.offer(nbr);
             }
         }
         return order; // size < V implies cycle
     }
 
     /**
      * Topological sort using array indegree (faster when vertices are 0..V-1).
      *
      * @param V     number of vertices
      * @param edges list of directed edges as [u, v]
      * @return      a valid topological ordering (size V if DAG)
      */
     public static ArrayList<Integer> topoSort2(int V, int[][] edges) {
         // Build adjacency list
         ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
         for (int i = 0; i < V; i++) adj.add(new ArrayList<>());
 
         int[] indeg = new int[V];
         for (int[] e : edges) {
             int u = e[0], v = e[1];
             adj.get(u).add(v);
             indeg[v]++;
         }
 
         Queue<Integer> q = new LinkedList<>();
         for (int i = 0; i < V; i++) if (indeg[i] == 0) q.offer(i);
 
         ArrayList<Integer> order = new ArrayList<>();
         while (!q.isEmpty()) {
             int cur = q.poll();
             order.add(cur);
 
             for (int nbr : adj.get(cur)) {
                 if (--indeg[nbr] == 0) q.offer(nbr);
             }
         }
         return order; // size < V implies cycle
     }
 
     /**
      * Pure cycle detection using Kahn's algorithm.
      *
      * @param V     number of vertices
      * @param edges list of directed edges as [u, v]
      * @return      true if a cycle exists; false if DAG
      */
     public static boolean hasCycleKahn(int V, int[][] edges) {
         ArrayList<Integer> order = topoSort2(V, edges);
         return order.size() != V;
     }
 
     // ----------------------------
     // ✅ Test Cases / Examples
     // ----------------------------
     public static void main(String[] args) {
         // 1) Simple DAG
         int V1 = 6;
         int[][] E1 = {
             {5, 2}, {5, 0},
             {4, 0}, {4, 1},
             {2, 3}, {3, 1}
         };
         System.out.println("DAG (topoSort1): " + topoSort1(V1, E1));
         System.out.println("DAG (topoSort2): " + topoSort2(V1, E1));
         System.out.println("DAG has cycle?  " + hasCycleKahn(V1, E1)); // false
 
         // 2) Disconnected DAG (multiple components)
         int V2 = 5;
         int[][] E2 = {
             {0, 1}, {0, 2}, // component 1
             {3, 4}          // component 2
         };
         System.out.println("Multi-comp DAG (topoSort2): " + topoSort2(V2, E2));
         System.out.println("Multi-comp has cycle?      " + hasCycleKahn(V2, E2)); // false
 
         // 3) Single vertex, no edges
         int V3 = 1;
         int[][] E3 = {};
         System.out.println("Single node (topoSort2): " + topoSort2(V3, E3));
         System.out.println("Single node has cycle?  " + hasCycleKahn(V3, E3)); // false
 
         // 4) Graph with a cycle: 0->1->2->0
         int V4 = 3;
         int[][] E4 = { {0,1}, {1,2}, {2,0} };
         System.out.println("Cycle graph (topoSort2): " + topoSort2(V4, E4)); // size < V
         System.out.println("Cycle graph has cycle?   " + hasCycleKahn(V4, E4)); // true
 
         // 5) Edge case: multiple zero-indegree choices
         int V5 = 4;
         int[][] E5 = { {1,2}, {1,3} }; // 0 and 1 start at indegree 0
         System.out.println("Multiple starts (topoSort2): " + topoSort2(V5, E5));
         System.out.println("Multiple starts has cycle?   " + hasCycleKahn(V5, E5)); // false
     }
 }
 