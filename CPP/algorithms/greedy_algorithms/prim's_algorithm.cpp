#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

void primMST(int V, vector<pair<int, int>> adj[])
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    int start_node = 0;
    pq.push({0, start_node});
    key[start_node] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
        {
            continue;
        }

        inMST[u] = true;

        for (auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && key[v] > weight)
            {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    int total_weight = 0;
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (int i = 1; i < V; ++i)
    {
        if (parent[i] != -1)
        {
            cout << parent[i] << " -- " << i << " == " << key[i] << endl;
            total_weight += key[i];
        }
    }
    cout << "Total weight of MST: " << total_weight << endl;
}

void addEdge(vector<pair<int, int>> adj[], int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

int main()
{
    int V = 5;
    vector<pair<int, int>> adj[V];

    addEdge(adj, 0, 1, 2);
    addEdge(adj, 0, 3, 6);
    addEdge(adj, 1, 2, 3);
    addEdge(adj, 1, 3, 8);
    addEdge(adj, 1, 4, 5);
    addEdge(adj, 2, 4, 7);
    addEdge(adj, 3, 4, 9);

    primMST(V, adj);

    return 0;
}