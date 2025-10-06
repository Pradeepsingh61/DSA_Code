/*
 * Bellman–Ford — Single-Source Shortest Paths (+ Negative-Cycle Check)
 * ===================================================================
 * ✍️ Algorithm Description
 * -----------------------
 * Bellman–Ford computes shortest path distances from a single source in a
 * weighted directed graph — even when there are negative edge weights.
 * It can also detect the presence of any negative-weight cycle reachable
 * from the source (or anywhere, using a super-source trick).
 *
 * Core idea:
 * 1) Initialize dist[src] = 0, all others = +∞.
 * 2) Relax all edges V-1 times (where V is #vertices).
 *    - A "relax" on edge (u -> v, w) does: dist[v] = min(dist[v], dist[u] + w).
 * 3) Do one more pass over all edges:
 *    - If any distance can still be improved, a negative-weight cycle exists.
 *
 * Use cases:
 * - Shortest paths with negative edges (no negative cycles reachable from src)
 * - Financial arbitrage detection (negative cycles)
 * - As a subroutine in Johnson’s algorithm (reweighting for all-pairs)
 *
 * 📊 Complexity Analysis
 * ----------------------
 * Let V = number of vertices, E = number of edges.
 * Time:  O(V * E) — V-1 relaxation rounds plus a final scan.
 * Space: O(V)     — distance array (+ optional parent array).
 *
 * 💡 Notes
 * - `bellmanFord1` (array distances) is fastest when vertices are 0..V-1.
 * - `bellmanFordMap` (HashMap distances) is handy if vertex ids are sparse or labeled.
 * - `hasNegativeCycleAnywhere` adds a super-source → detects ANY neg cycle in the graph.
 * - Distances use `long` to reduce overflow risk. Use `INF` as a large sentinel.
 */

 import java.util.*;

 class Solution {
 
     // Use a large INF sentinel to avoid overflow when adding weights.
     private static final long INF = (long)1e18;
 
     /**
      * Bellman–Ford with array distances (vertices assumed 0..V-1).
      *
      * @param V     number of vertices
      * @param edges directed weighted edges as [u, v, w]
      * @param src   source vertex
      * @return      distances array; if a negative cycle is reachable from src,
      *              returns null to signal "no well-defined shortest paths"
      */
     public static long[] bellmanFord1(int V, int[][] edges, int src) {
         long[] dist = new long[V];
         Arrays.fill(dist, INF);
         dist[src] = 0;
 
         // Relax edges V-1 times
         for (int i = 1; i <= V - 1; i++) {
             boolean changed = false;
             for (int[] e : edges) {
                 int u = e[0], v = e[1];
                 long w = e[2];
                 if (dist[u] != INF && dist[u] + w < dist[v]) {
                     dist[v] = dist[u] + w;
                     changed = true;
                 }
             }
             // Early exit if no update in a round
             if (!changed) break;
         }
 
         // Check for a negative cycle reachable from src
         for (int[] e : edges) {
             int u = e[0], v = e[1];
             long w = e[2];
             if (dist[u] != INF && dist[u] + w < dist[v]) {
                 return null; // Negative cycle detected (reachable from src)
             }
         }
         return dist;
     }
 
     /**
      * Bellman–Ford with HashMap distances (good for sparse / labeled vertices).
      * Vertices are still 0..V-1 here, but you can adapt to arbitrary ids
      * by mapping them to [0..n-1] and keeping only present keys in the map.
      *
      * @param V     number of vertices
      * @param edges directed weighted edges as [u, v, w]
      * @param src   source vertex
      * @return      distance map; null if a negative cycle is reachable from src
      */
     public static HashMap<Integer, Long> bellmanFordMap(int V, int[][] edges, int src) {
         HashMap<Integer, Long> dist = new HashMap<>();
         for (int i = 0; i < V; i++) dist.put(i, INF);
         dist.put(src, 0L);
 
         for (int i = 1; i <= V - 1; i++) {
             boolean changed = false;
             for (int[] e : edges) {
                 int u = e[0], v = e[1];
                 long w = e[2];
                 long du = dist.get(u);
                 long dv = dist.get(v);
                 if (du != INF && du + w < dv) {
                     dist.put(v, du + w);
                     changed = true;
                 }
             }
             if (!changed) break;
         }
 
         for (int[] e : edges) {
             int u = e[0], v = e[1];
             long w = e[2];
             long du = dist.get(u);
             long dv = dist.get(v);
             if (du != INF && du + w < dv) {
                 return null; // Negative cycle detected (reachable from src)
             }
         }
         return dist;
     }
 
     /**
      * Detect ANY negative-weight cycle in the graph (not just reachable from a given src).
      * Technique: add a super-source S connected to all nodes with 0-weight edges, run BF.
      *
      * @param V     number of vertices
      * @param edges directed weighted edges as [u, v, w]
      * @return      true if any negative-weight cycle exists; false otherwise
      */
     public static boolean hasNegativeCycleAnywhere(int V, int[][] edges) {
         // Build a new edge list with an extra super-source (-1) conceptually.
         // Implementation trick: initialize all dist[i]=0 and run V rounds.
         long[] dist = new long[V];
         Arrays.fill(dist, 0L); // Equivalent to relaxing from a super-source with 0 edges to all
 
         // Relax V times; if we can still relax on the V-th time, a neg cycle exists anywhere.
         for (int i = 1; i <= V; i++) {
             boolean changed = false;
             for (int[] e : edges) {
                 int u = e[0], v = e[1];
                 long w = e[2];
                 if (dist[u] + w < dist[v]) {
                     dist[v] = dist[u] + w;
                     changed = true;
                     if (i == V) return true; // improvement on the V-th round => negative cycle
                 }
             }
             if (!changed) break;
         }
         return false;
     }
 
     // ----------------------------
     // ✅ Test Cases / Examples
     // ----------------------------
     public static void main(String[] args) {
         // 1) Positive weights only
         int V1 = 5;
         int[][] E1 = {
             {0,1,6}, {0,3,7},
             {1,2,5}, {1,3,8}, {1,4,-4},
             {2,1,-2}, {3,2,-3}, {3,4,9},
             {4,0,2}, {4,2,7}
         };
         System.out.println("Case 1: Positive & some negative edges (no neg cycle, src=0)");
         System.out.println("hasNegativeCycleAnywhere: " + hasNegativeCycleAnywhere(V1, E1)); // false
         System.out.println("bellmanFord1 distances from 0: " + Arrays.toString(bellmanFord1(V1, E1, 0)));
 
         // 2) Negative edge but no negative cycle
         int V2 = 4;
         int[][] E2 = {
             {0,1,1}, {1,2,-1}, {2,3,-1}
         };
         System.out.println("\nCase 2: Negative edges, no cycle (src=0)");
         System.out.println("hasNegativeCycleAnywhere: " + hasNegativeCycleAnywhere(V2, E2)); // false
         System.out.println("bellmanFordMap distances from 0: " + bellmanFordMap(V2, E2, 0));
 
         // 3) Graph with a negative cycle reachable from src
         //    Cycle: 1 -> 2 -> 3 -> 1 with total weight -3
         int V3 = 4;
         int[][] E3 = {
             {0,1,2}, {1,2,-2}, {2,3,-2}, {3,1,1}
         };
         System.out.println("\nCase 3: Negative cycle reachable from src=0");
         System.out.println("hasNegativeCycleAnywhere: " + hasNegativeCycleAnywhere(V3, E3)); // true
         long[] d3 = bellmanFord1(V3, E3, 0);
         System.out.println("bellmanFord1 distances from 0: " + (d3 == null ? "NEGATIVE CYCLE" : Arrays.toString(d3)));
 
         // 4) Disconnected graph (unreachable nodes remain INF)
         int V4 = 6;
         int[][] E4 = {
             {0,1,3}, {1,2,4},          // component 1
             {3,4,1}, {4,5,1}           // component 2 (disconnected from src=0)
         };
         System.out.println("\nCase 4: Disconnected graph (src=0)");
         System.out.println("hasNegativeCycleAnywhere: " + hasNegativeCycleAnywhere(V4, E4)); // false
         long[] d4 = bellmanFord1(V4, E4, 0);
         System.out.println("bellmanFord1 distances from 0: " + Arrays.toString(d4));
         // Expect: [0, 3, 7, INF, INF, INF]
 
         // 5) Single vertex, no edges
         int V5 = 1;
         int[][] E5 = {};
         System.out.println("\nCase 5: Single node (src=0)");
         System.out.println("hasNegativeCycleAnywhere: " + hasNegativeCycleAnywhere(V5, E5)); // false
         System.out.println("bellmanFord1 distances from 0: " + Arrays.toString(bellmanFord1(V5, E5, 0)));
     }
 }
 