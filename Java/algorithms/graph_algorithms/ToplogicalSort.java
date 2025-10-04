/*
 * Topological Sorting using Kahn's Algorithm (BFS Approach)
 * --------------------------------------------------------
 * This class provides two implementations of Topological Sorting:
 * 
 * 1. topoSort1:
 *    - Uses a HashMap to maintain the indegree of nodes.
 *    - Constructs an adjacency list and performs BFS to generate
 *      a valid topological order of vertices.
 * 
 * 2. topoSort2:
 *    - Uses an integer array instead of a HashMap for indegree tracking.
 *    - This version also helps in detecting cycles:
 *         -> If the number of processed vertices is less than V,
 *            then a cycle exists in the graph.
 * 
 * Both methods implement Kahn's Algorithm and are useful for 
 * Directed Acyclic Graphs (DAGs).
 */

 import java.util.*;

 class Solution {
    
    public static ArrayList<Integer> topoSort1(int V, int[][] edges) {
        // Implementation using HashMap for indegree
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        HashMap<Integer,Integer> indg = new HashMap<>();
        
        for(int i = 0;i<V;i++){
            indg.put(i,0);
            adj.add(new ArrayList<>());
        }
        
        for(int [] x : edges){
            indg.put(x[1] , indg.getOrDefault(x[1] ,0)+1);
            adj.get(x[0]).add(x[1]);
        }
        
        Queue<Integer> queue = new LinkedList<>();
        ArrayList<Integer> result = new ArrayList<>();
        
        for(int i = 0;i<V;i++){
            if(indg.get(i) == 0){
                queue.offer(i);
            }
        }
        
        while(!queue.isEmpty()){
            int current = queue.poll();
            result.add(current);
            
            for(int x : adj.get(current)){
                indg.put(x,indg.get(x)-1);
                if(indg.get(x) == 0){
                    queue.offer(x);
                }
            }
        }
        
        return result;
    }

    // Array Version Instead of Map 
    public static boolean topoSort2(int V, int[][] edges) {
        // Implementation using array for indegree + cycle detection
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        
        for(int i = 0;i<V;i++){
            adj.add(new ArrayList<>());
        }
        
        int [] indg = new int[V];
        
        for(int [] arr : edges){
            adj.get(arr[0]).add(arr[1]);
            indg[arr[1]]++;
        }
        
        Queue<Integer> queue = new LinkedList<>();
        ArrayList<Integer> result = new ArrayList<>();
        
        for(int i = 0;i<V;i++){
            if(indg[i] == 0){
                queue.offer(i);
            }
        }
        
        while(!queue.isEmpty()){
            int current = queue.poll();
            result.add(current);
            
            for(int x : adj.get(current)){
                indg[x]--;
                if(indg[x] == 0){
                    queue.offer(x);
                }
            }
        }
        
        // If result size != V, a cycle exists
        return result.size() != V; 
    }
}
