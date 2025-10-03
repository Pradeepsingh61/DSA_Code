// Tarjan's Algorithm — Find Bridges in an Undirected Graph
// Problem : Find all bridges (critical edges) in a graph
// Approach: DFS with discovery times (disc) and low-link values (low)
// Complexity Analysis:
//   Time  : O(V + E)
//   Space : O(V + E)

#include <iostream>
#include <vector>
#include <algorithm> // for min
using namespace std;

class TarjanBridges
{
  int V;
  vector<int> disc, low; // discovery time and low-link values
  vector<int> visited;   // visited markers
  int timer;             // global discovery timer

  void dfs(int u, int parent, vector<vector<int>> &adj, vector<pair<int, int>> &bridges)
  {
    visited[u] = 1;
    disc[u] = low[u] = timer++;

    for (int v : adj[u])
    {
      if (v == parent)
        continue; // ignore parent edge

      if (!visited[v])
      {
        dfs(v, u, adj, bridges);
        low[u] = min(low[u], low[v]);

        // Bridge condition
        if (low[v] > disc[u])
        {
          bridges.push_back({u, v});
        }
      }
      else
      {
        // back edge
        low[u] = min(low[u], disc[v]);
      }
    }
  }

public:
  TarjanBridges(int n)
  {
    V = n;
    disc.assign(V, -1);
    low.assign(V, -1);
    visited.assign(V, 0);
    timer = 0;
  }

  vector<pair<int, int>> findBridges(vector<vector<int>> &edges)
  {
    // Build adjacency list: O(V + E) space
    vector<vector<int>> adj(V);
    for (auto &e : edges)
    {
      int u = e[0], v = e[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<pair<int, int>> bridges;
    // Run DFS from each component root: O(V + E) time
    for (int i = 0; i < V; i++)
    {
      if (!visited[i])
      {
        dfs(i, -1, adj, bridges);
      }
    }
    return bridges;
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;

  vector<vector<int>> edges;
  edges.reserve(E);
  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    edges.push_back({u, v});
  }

  TarjanBridges solver(V);
  vector<pair<int, int>> bridges = solver.findBridges(edges);

  cout << "Bridges in graph:\n";
  for (auto &b : bridges)
  {
    cout << b.first << " - " << b.second << "\n";
  }

  return 0;
}

/*
🔹 Visualization Example

Graph:
Vertices: 0,1,2,3,4
Edges:
0-1, 1-2, 2-0, 1-3, 3-4

ASCII:
       0
      / \
     1---2
     |
     3
     |
     4

Step 1: DFS Traversal (with discovery time disc and low-link low)
- Start at node 0, timer=0
- DFS path: 0 -> 1 -> 2 -> 0 (back edge), then 1 -> 3 -> 4

Node states:
Node  disc  low
0     0     0
1     1     1
2     2     0  (back edge to 0)
3     3     3
4     4     4

Step 2: Bridge Detection
- Edge 1-3: low[3] = 3 > disc[1] = 1 → Bridge
- Edge 3-4: low[4] = 4 > disc[3] = 3 → Bridge
- Other edges (0-1, 0-2, 1-2) form cycles → Not bridges

Step 3: Output
Bridges = {(1,3), (3,4)}

🔹 Complexity Explanation:

Time Complexity O(V + E):
- Each vertex is visited exactly once in DFS → O(V)
- Each edge is traversed exactly twice (once per endpoint) → O(E)
- So total = O(V + E)

Space Complexity O(V + E):
- Adjacency list stores each edge twice → O(V + E)
- Arrays disc, low, visited → O(V)
- Recursion stack in DFS → O(V) in worst case
- Total = O(V + E)
*/
