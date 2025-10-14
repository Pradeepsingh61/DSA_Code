/*
 * Algorithm Name
Disjoint Set Union (Union-Find)

Programming Language
Java

Category
Graph / Disjoint Set

Difficulty Level
Easy

* Algorithm Description :

1. Problem it solves:
-> Helps to group elements into sets and check if two elements belong to the same set.
-> Commonly used in cycle detection and Kruskal’s Minimum Spanning Tree (MST).

2. Approach / Idea:
-> Each element has a parent.
-> If parent[x] == x, it means x is the root.
-> Path compression helps make future find operations faster.
-> Union operation joins two sets by linking their roots.

3. Complexity:
Time: O(α(n)) ≈ constant per operation
Space: O(n)

* Author : Surya Pratap Singh
*/

import java.util.*;

public class DisjointSetUnion {
    int[] parent;
    int[] rank;

    DisjointSetUnion(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }

    boolean connected(int x, int y) {
        return find(x) == find(y);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); // number of nodes
        int q = sc.nextInt(); // number of queries
        DisjointSetUnion dsu = new DisjointSetUnion(n);

        for (int i = 0; i < q; i++) {
            String type = sc.next();
            int a = sc.nextInt();
            int b = sc.nextInt();

            if (type.equals("union")) {
                dsu.union(a, b);
            } else if (type.equals("connected")) {
                System.out.println(dsu.connected(a, b) ? "Yes" : "No");
            }
        }
        sc.close();
    }
}
