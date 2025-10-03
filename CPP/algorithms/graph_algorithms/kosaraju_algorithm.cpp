// Kosaraju’s Algorithm — Find Strongly Connected Components (SCCs)
// Problem
//   Given a directed graph, find all SCCs (maximal groups of vertices
//   where every vertex can reach every other vertex in the group).
//
// Approach
//   1. Perform DFS and store vertices in a stack according to finish times.
//   2. Reverse all edges (transpose the graph).
//   3. Perform DFS on the transposed graph in the order of the stack.
//      Each DFS traversal finds one SCC.
//
// Complexity
//   Time  : O(V + E) — DFS twice, transpose edges
//   Space : O(V + E) — adjacency list + visited arrays + recursion stack
//
// Input
//   - Number of vertices (V)
//   - List of edges {u, v}
//
// Output
//   - List of all SCCs

#include <iostream>
#include <vector>
using namespace std;

int V;
vector<vector<int>> adj;
vector<vector<int>> adjT;
vector<bool> visited;

// DFS for finish time
void dfs1(int u, vector<int> &order)
{
  visited[u] = true;
  for (size_t i = 0; i < adj[u].size(); i++)
  {
    int v = adj[u][i];
    if (!visited[v])
      dfs1(v, order);
  }
  order.push_back(u); // finished
}

// DFS for SCC on transposed graph
void dfs2(int u, vector<int> &component)
{
  visited[u] = true;
  component.push_back(u);
  for (size_t i = 0; i < adjT[u].size(); i++)
  {
    int v = adjT[u][i];
    if (!visited[v])
      dfs2(v, component);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int E;
  cin >> V >> E;
  adj.assign(V, vector<int>());
  adjT.assign(V, vector<int>());

  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adjT[v].push_back(u); // transpose edge
  }

  vector<int> order;
  visited.assign(V, false);

  // Step 1: DFS to get finish times
  for (int i = 0; i < V; i++)
    if (!visited[i])
      dfs1(i, order);

  // Step 2: DFS on transposed graph
  visited.assign(V, false);
  vector<vector<int>> sccs;
  for (int i = V - 1; i >= 0; i--)
  {
    int u = order[i];
    if (!visited[u])
    {
      vector<int> component;
      dfs2(u, component);
      sccs.push_back(component);
    }
  }

  // Output SCCs
  cout << "Strongly Connected Components:\n";
  for (size_t i = 0; i < sccs.size(); i++)
  {
    for (size_t j = 0; j < sccs[i].size(); j++)
      cout << sccs[i][j] << " ";
    cout << "\n";
  }

  return 0;
}

/*
Example Input:
5 5
0 2
2 1
1 0
0 3
3 4

Visualization:
Graph:
0 → 2 → 1 → 0 (cycle)
0 → 3 → 4

Step 1: DFS to record finish times
Stack order (top = last finished): [4, 3, 0, 1, 2]

Step 2: Transpose graph
Edges reversed:
2 → 0
1 → 2
0 → 1
3 → 0
4 → 3

Step 3: DFS on transposed graph using stack order
- Pop 2 → DFS → {0,1,2} (SCC)
- Pop 3 → DFS → {3} (SCC)
- Pop 4 → DFS → {4} (SCC)

Final SCCs:
{0,1,2}, {3}, {4}

Time  : O(V + E)
Space : O(V + E)
*/
