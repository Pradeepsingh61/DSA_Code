"""
Data Structure: Kruskal's Minimum Spanning Tree (MST) Algorithm

Description:
    Kruskal's algorithm finds the Minimum Spanning Tree of a graph by
    sorting edges by weight and adding them one by one without creating cycles.

Use Case:
    Useful in network design (telecom, computer networks), clustering, 
    and designing efficient transportation systems.

Time Complexity:
    O(E log E), where E = number of edges (due to sorting edges)

Space Complexity:
    O(V + E), where V = number of vertices, E = number of edges
"""

class DisjointSet:
    """Union-Find data structure for cycle detection."""
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        xroot, yroot = self.find(x), self.find(y)
        if xroot == yroot:
            return False
        if self.rank[xroot] < self.rank[yroot]:
            self.parent[xroot] = yroot
        elif self.rank[xroot] > self.rank[yroot]:
            self.parent[yroot] = xroot
        else:
            self.parent[yroot] = xroot
            self.rank[xroot] += 1
        return True


def kruskal(vertices, edges):
    """
    Compute MST using Kruskal's algorithm.

    Args:
        vertices (int): Number of vertices.
        edges (list of tuples): Each tuple = (weight, u, v)

    Returns:
        list: Edges in the MST
    """
    edges.sort()
    ds = DisjointSet(vertices)
    mst = []
    for weight, u, v in edges:
        if ds.union(u, v):
            mst.append((u, v, weight))
    return mst


def main():
    """Test Kruskal's MST algorithm."""
    vertices = 4
    edges = [
        (10, 0, 1),
        (6, 0, 2),
        (5, 0, 3),
        (15, 1, 3),
        (4, 2, 3)
    ]
    mst = kruskal(vertices, edges)
    print("Edges in MST:", mst)


if __name__ == "__main__":
    main()
