#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Edge
{
    int src, dest, weight;
};

struct DSU
{
    std::vector<int> parent;
    DSU(int n)
    {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            parent[root_i] = root_j;
        }
    }
};

bool compareEdges(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

void kruskalMST(int V, std::vector<Edge> &edges)
{
    std::vector<Edge> result;
    std::sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(V);
    int total_weight = 0;

    for (const auto &edge : edges)
    {
        int src_root = dsu.find(edge.src);
        int dest_root = dsu.find(edge.dest);

        if (src_root != dest_root)
        {
            result.push_back(edge);
            dsu.unite(src_root, dest_root);
            total_weight += edge.weight;
        }
    }

    std::cout << "Edges in the Minimum Spanning Tree:" << std::endl;
    for (const auto &edge : result)
    {
        std::cout << edge.src << " -- " << edge.dest << " == " << edge.weight << std::endl;
    }
    std::cout << "Total weight of MST: " << total_weight << std::endl;
}

int main()
{
    int V = 4;
    std::vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    kruskalMST(V, edges);

    return 0;
}