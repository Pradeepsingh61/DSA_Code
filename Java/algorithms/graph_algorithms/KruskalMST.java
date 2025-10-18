/*
 * Algorithm Name
Kruskal's Minimum Spanning Tree (MST)

Programming Language
Java

Category
Graph / Greedy Algorithm / Disjoint Set

Difficulty Level
Medium

* Algorithm Description :

1. Problem it solves:
-> Finds the Minimum Spanning Tree (MST) of a connected, undirected, weighted graph.
-> The MST connects all vertices with the minimum total edge weight and without forming cycles.

2. Approach / Idea:
-> Sort all edges in non-decreasing order of their weights.
-> Initialize Disjoint Set Union (DSU) or Union-Find structure to keep track of connected components.
-> Iterate through sorted edges:
     - For each edge (u, v, w), check if u and v belong to different sets.
     - If yes, include this edge in the MST and union their sets.
     - If no, skip the edge (as it forms a cycle).
-> Continue until MST contains (V - 1) edges.

3. Complexity:
Time: O(E log E) → sorting edges dominates.
Space: O(V + E) → for DSU and edge storage.

* Author : Surya Pratap Singh
*/

// Time Complexity: O(E log E)
// Space Complexity: O(V + E)

import java.util.*;
class Edge {
    int src, dest, wt;
    Edge(int s, int d, int w) {
        src = s;
        dest = d;
        wt = w;
    }
}

class DSU {
    int[] parent, rank;
    
    DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void union(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        
        if (rank[px] < rank[py])
            parent[px] = py;
        else if (rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
}

public class KruskalMST {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter number of vertices: ");
        int V = sc.nextInt();
        System.out.print("Enter number of edges: ");
        int E = sc.nextInt();
        
        List<Edge> edges = new ArrayList<>();
        System.out.println("Enter edges (src dest weight):");
        for (int i = 0; i < E; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int w = sc.nextInt();
            edges.add(new Edge(u, v, w));
        }
        
        // Sort edges by weight
        Collections.sort(edges, (a, b) -> a.wt - b.wt);
        
        DSU dsu = new DSU(V);
        int mstWeight = 0;
        List<Edge> mstEdges = new ArrayList<>();
        
        for (Edge e : edges) {
            if (dsu.find(e.src) != dsu.find(e.dest)) {
                dsu.union(e.src, e.dest);
                mstWeight += e.wt;
                mstEdges.add(e);
            }
        }
        
        System.out.println("\nEdges in MST:");
        for (Edge e : mstEdges) {
            System.out.println(e.src + " - " + e.dest + " : " + e.wt);
        }
        System.out.println("Total weight of MST: " + mstWeight);
        
        sc.close();
    }
}
