#include <bits/stdc++.h>
using namespace std;

vector<int> kahnTopoSort(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    
    // Step 1: Compute in-degree of all nodes
    for (int u = 0; u < V; u++) {
        for (auto v : adj[u]) {
            indegree[v]++;
        }
    }

    // Step 2: Push all 0 in-degree nodes into queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    // Step 3: Process queue
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        topo.push_back(u);

        for (auto v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }

    // Step 4: Check if topo sort exists
    if ((int)topo.size() != V) {
        cout << "Graph has a cycle, no topo sort possible!\n";
        return {};
    }
    return topo;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Graph edges
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    vector<int> topo = kahnTopoSort(V, adj);

    cout << "Topological Sort: ";
    for (int node : topo) cout << node << " ";
    cout << "\n";

    return 0;
}
