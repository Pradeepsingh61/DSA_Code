class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])  # Path compression
        return self.parent[u]
    
    def union(self, u, v):
        rootU = self.find(u)
        rootV = self.find(v)
        if rootU != rootV:
            if self.rank[rootU] < self.rank[rootV]:
                self.parent[rootU] = rootV
            elif self.rank[rootU] > self.rank[rootV]:
                self.parent[rootV] = rootU
            else:
                self.parent[rootV] = rootU
                self.rank[rootU] += 1
            return True
        return False

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []  # Each edge: (weight, u, v)
    
    def add_edge(self, u, v, w):
        self.edges.append((w, u, v))
    
    def kruskal(self):
        self.edges.sort()
        ds = DisjointSet(self.V)
        mst = []
        total_weight = 0
        
        for w, u, v in self.edges:
            if ds.union(u, v):  # If no cycle formed
                mst.append((u, v, w))
                total_weight += w
        
        print("Edges in the MST:")
        for u, v, w in mst:
            print(f"{u} -- {v} == {w}")
        print("Total weight of MST:", total_weight)

# Example usage:
if __name__ == "__main__":
    g = Graph(6)
    g.add_edge(0, 1, 4)
    g.add_edge(0, 2, 4)
    g.add_edge(1, 2, 2)
    g.add_edge(1, 0, 4)
    g.add_edge(2, 0, 4)
    g.add_edge(2, 1, 2)
    g.add_edge(2, 3, 3)
    g.add_edge(2, 5, 2)
    g.add_edge(2, 4, 4)
    g.add_edge(3, 2, 3)
    g.add_edge(3, 4, 3)
    g.add_edge(4, 2, 4)
    g.add_edge(4, 3, 3)
    g.add_edge(5, 2, 2)
    g.add_edge(5, 4, 3)

    g.kruskal()
