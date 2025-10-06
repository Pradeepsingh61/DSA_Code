// Floyd–Warshall Algorithm — All-Pairs Shortest Path
// Problem
//   Compute shortest distances between every pair of vertices in a weighted graph.
//
// Approach
//   1. Initialize dist[i][j]:
//        - 0 if i==j
//        - weight(u,v) if edge exists
//        - INF otherwise
//   2. For k in [0..V-1] (intermediate vertex):
//        for i in [0..V-1] (source):
//          for j in [0..V-1] (destination):
//             dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
//   3. After all iterations, dist[i][j] is the shortest distance.
//
// Complexity
//   Time  : O(V^3)
//   Space : O(V^2)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;
  const int INF = 1e9;

  vector<vector<int>> dist(V, vector<int>(V, INF));
  for (int i = 0; i < V; i++)
    dist[i][i] = 0;

  for (int i = 0; i < E; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    dist[u][v] = min(dist[u][v], w);
    dist[v][u] = min(dist[v][u], w); // remove if directed
  }

  cout << "Initial distance matrix:\n";
  for (auto &row : dist)
  {
    for (auto x : row)
      cout << (x == INF ? -1 : x) << " ";
    cout << "\n";
  }
  cout << "\n";

  // Floyd–Warshall dry run
  for (int k = 0; k < V; k++)
  {
    cout << "Considering intermediate vertex k=" << k << ":\n";
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        if (dist[i][k] < INF && dist[k][j] < INF)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // print matrix after this k
    for (auto &row : dist)
    {
      for (auto x : row)
        cout << (x == INF ? -1 : x) << " ";
      cout << "\n";
    }
    cout << "\n";
  }

  cout << "Final All-Pairs Shortest Distances:\n";
  for (auto &row : dist)
  {
    for (auto x : row)
      cout << (x == INF ? -1 : x) << " ";
    cout << "\n";
  }

  return 0;
}

/*
Example Input:
4 5
0 1 5
0 3 10
1 2 3
2 3 1
0 2 100

Visualization:
Graph:
   (5)        (3)       (1)
0 ----- 1 -------- 2 -------- 3
 \                               ^
  \____________ (10) ___________/

Dry Run Steps:

Initial dist:
0   5 100 10
5   0   3 -1
100 3   0  1
10  -1  1  0

k = 0 (using vertex 0 as intermediate):
- dist[2][3] = min(1, dist[2][0]+dist[0][3]) = min(1,100+10)=1 (no change)
- dist[2][0] = min(100, dist[2][0]+dist[0][0]) = 100 (no change)
... print matrix

k = 1 (vertex 1 intermediate):
- dist[0][2] = min(100, dist[0][1]+dist[1][2]) = min(100,5+3)=8
- dist[3][0] = min(10, dist[3][1]+dist[1][0]) = min(10, INF+5)=10 (no change)
... print matrix

k = 2 (vertex 2 intermediate):
- dist[0][3] = min(10, dist[0][2]+dist[2][3]) = min(10,8+1)=9
- dist[1][3] = min(INF, 3+1)=4
... print matrix

k = 3 (vertex 3 intermediate):
- no further updates

Final dist:
0 5 8 9
5 0 3 4
8 3 0 1
9 4 1 0
*/

// prepare PR
