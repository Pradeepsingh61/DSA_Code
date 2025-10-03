// Dijkstra’s Algorithm — Single Source Shortest Path
// Problem
//   Given a weighted graph with non-negative edge weights,
//   find the shortest path from a source vertex to all other vertices.
//
// Approach
//   1. Use a priority queue (min-heap) to always expand the next closest vertex.
//   2. Initialize distances[] with infinity, except source = 0.
//   3. While queue not empty:
//        - Extract vertex u with smallest dist[u].
//        - For each neighbor v of u, relax edge (u,v):
//          if dist[u] + weight(u,v) < dist[v], update dist[v].
//
// Complexity
//   Time  : O((V + E) log V) — using priority queue
//   Space : O(V + E) — adjacency list + distance array + heap
//
// Input
//   - Number of vertices (V)
//   - Number of edges (E)
//   - Edge list {u, v, w} (u → v with weight w)
//   - Source vertex (src)
//
// Output
//   - Shortest distance from src to all vertices

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
    adj[v].push_back({u, w}); // undirected; remove if directed
  }

  int src;
  cin >> src;

  const int INF = numeric_limits<int>::max();
  vector<int> dist(V, INF);
  dist[src] = 0;

  // min-heap {distance, vertex}
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  pq.push({0, src});

  while (!pq.empty())
  {
    int d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (d > dist[u])
      continue; // outdated entry

    for (auto &edge : adj[u])
    {
      int v = edge.first, w = edge.second;
      if (dist[u] + w < dist[v])
      {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }

  cout << "Shortest distances from source " << src << ":\n";
  for (int i = 0; i < V; i++)
  {
    if (dist[i] == INF)
      cout << i << " : INF\n";
    else
      cout << i << " : " << dist[i] << "\n";
  }

  return 0;
}

/*
Example Input:
5 6
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1
0

Visualization:
Graph:
       (2)
   0 ------- 1
    \       / \
   (4)\   (1)  (7)
      \   /     \
        2 ------- 3
         \       /
         (3)   (1)
           \   /
             4

Execution:
dist = [0, INF, INF, INF, INF]
Start from src=0

Step 1: Pick 0 → dist[0]=0
  Relax edges:
    0→1 (2) → dist[1]=2
    0→2 (4) → dist[2]=4
dist = [0,2,4,INF,INF]

Step 2: Pick 1 (dist=2)
  Relax edges:
    1→2 (1) → dist[2]=min(4,2+1)=3
    1→3 (7) → dist[3]=2+7=9
dist = [0,2,3,9,INF]

Step 3: Pick 2 (dist=3)
  Relax edges:
    2→4 (3) → dist[4]=3+3=6
dist = [0,2,3,9,6]

Step 4: Pick 4 (dist=6) → relax 4→3 (1):
    dist[3]=min(9,6+1)=7
dist = [0,2,3,7,6]

Step 5: Pick 3 (dist=7) → no better updates

Final distances from 0:
0 : 0
1 : 2
2 : 3
3 : 7
4 : 6

Time  : O((V+E) log V)
Space : O(V+E)
*/

// add: Dijkstra PR
