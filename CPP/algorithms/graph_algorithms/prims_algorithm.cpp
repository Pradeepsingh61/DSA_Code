// Prim’s Algorithm — Minimum Spanning Tree (MST)
// Problem
//   Given a weighted, undirected graph, find a subset of edges
//   that connects all vertices with minimum total weight without cycles.
//
// Approach
//   1. Start from any vertex (usually 0), mark it as part of MST.
//   2. Use a priority queue (min-heap) to pick the smallest edge
//      connecting MST to a new vertex.
//   3. Add the chosen vertex to MST and repeat until all vertices included.
//
// Complexity
//   Time  : O((V + E) log V) — using priority queue
//   Space : O(V + E) — adjacency list + key array + heap
//
// Input
//   - Number of vertices (V)
//   - Number of edges (E)
//   - Edge list {u, v, w} (u ↔ v with weight w)
//
// Output
//   - Total weight of MST
//   - Edges included in MST

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;
  vector<vector<pair<int, int>>> adj(V);

  
  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w}); // undirected graph
  }

  const int INF = numeric_limits<int>::max();
  vector<int> key(V, INF);      // minimum edge weight to MST
  vector<int> parent(V, -1);    // store MST edges
  vector<bool> inMST(V, false); // track vertices included

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

  int start = 0;
  key[start] = 0;
  pq.push({0, start});

  while (!pq.empty())
  {
    int w = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (inMST[u])
      continue;

    inMST[u] = true;

    for (auto &edge : adj[u])
    {
      int v = edge.first, weight = edge.second;
      if (!inMST[v] && weight < key[v])
      {
        key[v] = weight;
        parent[v] = u;
        pq.push({key[v], v});
      }
    }
  }

  int totalWeight = 0;
  cout << "Edges in MST:\n";
  for (int v = 0; v < V; v++)
  {
    if (parent[v] != -1)
    {
      cout << parent[v] << " - " << v << " (weight " << key[v] << ")\n";
      totalWeight += key[v];
    }
  }
  cout << "Total MST weight: " << totalWeight << "\n";

  return 0;
}

/*
Example Input:
5 7
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9

Visualization:
Graph:
       (2)
   0 ------- 1
    \       /|\
   (6)\   (3)(5)
      \   /   \
        3       4
        (9)    (7)

Step-by-step Execution:
Start from 0:
- Include 0 → candidate edges: 0→1(2), 0→3(6)
- Pick min edge 0→1(2) → add 1
- Candidate edges: 1→2(3), 1→3(8), 1→4(5), 0→3(6)
- Pick min edge 1→2(3) → add 2
- Candidate edges: 1→3(8), 1→4(5), 2→4(7), 0→3(6)
- Pick min edge 1→4(5) → add 4
- Candidate edges: 0→3(6), 1→3(8), 2→4(7), 3→4(9)
- Pick min edge 0→3(6) → add 3
All vertices included → MST complete

MST edges:
0 - 1 (2)
1 - 2 (3)
1 - 4 (5)
0 - 3 (6)
Total MST weight: 16

Time  : O((V+E) log V)
Space : O(V+E)
*/

// add: Prim PR

// prepare Prim PR

// prepare PR
