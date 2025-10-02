// Kruskal’s Algorithm using Disjoint Set (Union-Find)
#include <algorithm>
#include <vector>
#include <iostream>

#include <bits/stdc++.h>
using namespace std;

/*
   Disjoint Set Union (Union-Find)
   Uses path compression + union by size
   Time per operation ≈ O(α(V)) (almost constant)
*/
class DisjointSet
{
  vector<int> parent, size;

public:
  DisjointSet(int n)
  {
    parent.resize(n + 1);
    size.resize(n + 1, 1);
    for (int i = 0; i <= n; i++)
      parent[i] = i;
  }

  int findUPar(int node)
  {
    if (parent[node] == node)
      return node;
    return parent[node] = findUPar(parent[node]); // path compression
  }

  bool unionBySize(int u, int v)
  {
    int pu = findUPar(u), pv = findUPar(v);
    if (pu == pv)
      return false; // already in same set (cycle)

    if (size[pu] < size[pv])
      swap(pu, pv);
    parent[pv] = pu;
    size[pu] += size[pv];
    return true;
  }
};

/*
   Kruskal’s Algorithm
   V = number of vertices
   edges = list of {u, v, wt}
   Returns total weight of MST

   Time Complexity:
   - Sorting edges: O(E log E)
   - Union-Find ops: O(E * α(V)) ~ O(E)
   Overall: O(E log E)

   Space Complexity:
   - DSU arrays: O(V)
   - Edge list: O(E)
   Total: O(V + E)
*/
int kruskalMST(int V, vector<vector<int>> &edges)
{
  // Step 1: Sort edges by weight
  sort(edges.begin(), edges.end(), [](auto &a, auto &b)
       { return a[2] < b[2]; });

  DisjointSet ds(V);
  int mstWeight = 0, count = 0;

  // Step 2: Pick edges one by one
  for (auto &e : edges)
  {
    int u = e[0], v = e[1], wt = e[2];
    if (ds.unionBySize(u, v))
    { // if union successful
      mstWeight += wt;
      count++;
      if (count == V - 1)
        break; // MST complete
    }
  }
  return mstWeight;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;
  vector<vector<int>> edges;
  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  cout << "MST Weight = " << kruskalMST(V, edges) << "\n";
  return 0;
}

/*
🔹 Visualization Example
Input:
V = 4, E = 5
Edges:
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Step 1: Sort edges by weight
Edges sorted: (2-3,4), (0-3,5), (0-2,6), (0-1,10), (1-3,15)

Step 2: Process edges
- Pick (2-3,4): no cycle → MST = {(2,3)}, weight = 4
- Pick (0-3,5): no cycle → MST = {(2,3),(0,3)}, weight = 9
- Pick (0-2,6): forms cycle (0-3-2 exists) → skip
- Pick (0-1,10): no cycle → MST = {(2,3),(0,3),(0,1)}, weight = 19
- MST complete with V-1=3 edges

Final MST Weight = 19
Edges in MST = {(2,3), (0,3), (0,1)}

Time Complexity = O(E log E)
Space Complexity = O(V + E)
*/
