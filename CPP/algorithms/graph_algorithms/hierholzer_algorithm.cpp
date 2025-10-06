/*
 * Algorithm: Hierholzer’s Algorithm (Eulerian Path / Circuit)
 *
 * Problem:
 *   Given a connected graph (directed or undirected), find an Eulerian Path or Circuit.
 *   - Eulerian Path: visits every edge exactly once.
 *   - Eulerian Circuit: Eulerian Path that starts and ends on the same vertex.
 *
 * Eulerian Path Conditions:
 *   - Undirected: At most 2 vertices have odd degree.
 *   - Directed: exactly 1 vertex has (out = in + 1), exactly 1 has (in = out + 1),
 *               all others: indegree == outdegree.
 *
 * Eulerian Circuit Conditions:
 *   - Undirected: all vertices have even degree.
 *   - Directed: indegree == outdegree for every vertex.
 *
 * Approach (Hierholzer’s Algorithm):
 *   1. Pick starting vertex:
 *        - Circuit → any vertex.
 *        - Path → vertex with (outdeg > indeg).
 *   2. Traverse edges using a stack, removing them as you go.
 *   3. If stuck, backtrack → add vertex to final path.
 *   4. Reverse final path → Eulerian Path / Circuit.
 *
 * Complexity:
 *   - O(E), since each edge is used exactly once.
 */

#include <bits/stdc++.h>
using namespace std;

class Eulerian
{
public:
  vector<int> findEulerianPath(int n, vector<vector<int>> &edges)
  {
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0), outdeg(n, 0);

    // Build adjacency list
    for (auto &e : edges)
    {
      int u = e[0], v = e[1];
      adj[u].push_back(v);
      outdeg[u]++;
      indeg[v]++;
    }

    // Find start node (for path vs circuit)
    int start = 0;
    for (int i = 0; i < n; i++)
    {
      if (outdeg[i] - indeg[i] == 1)
        start = i; // Eulerian path start
    }

    vector<int> path, stack = {start};

    // Hierholzer’s Algorithm
    while (!stack.empty())
    {
      int u = stack.back();
      if (!adj[u].empty())
      {
        // Go deeper using available edge
        int v = adj[u].back();
        adj[u].pop_back(); // remove edge u→v
        stack.push_back(v);

        // 🔎 Visualization step
        // cout << "Traverse edge " << u << " -> " << v << endl;
      }
      else
      {
        // No more edges → add to path (backtrack)
        path.push_back(u);
        stack.pop_back();

        // 🔎 Visualization step
        // cout << "Backtrack: add " << u << " to path" << endl;
      }
    }

    reverse(path.begin(), path.end()); // final path
    return path;
  }
};

int main()
{
  // Example Graph: Eulerian Circuit
  int n = 4;
  vector<vector<int>> edges = {
      {0, 1}, {1, 2}, {2, 0}, {0, 3}, {3, 0}};

  Eulerian solver;
  vector<int> path = solver.findEulerianPath(n, edges);

  cout << "Eulerian Path/Circuit: ";
  for (int v : path)
    cout << v << " ";
  cout << endl;

  /*
   * Visualization for this graph:
   *
   * Edges: 0->1, 1->2, 2->0, 0->3, 3->0
   *
   * Step walk:
   *   Start at 0
   *   0 -> 3
   *   3 -> 0
   *   0 -> 1
   *   1 -> 2
   *   2 -> 0
   *
   * Backtracking order:
   *   0 (dead end) → 2 → 1 → 0 → 3 → 0
   *
   * Final Eulerian Circuit:
   *   0 → 3 → 0 → 1 → 2 → 0
   */
}
