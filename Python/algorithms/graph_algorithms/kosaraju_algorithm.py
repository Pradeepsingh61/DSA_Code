""""
Kosaraju’s Algorithm
Description:Finds all Strongly Connected Components (SCCs) in a directed graph.
Time Complexity: O(V + E)
Space Complexity: O(V + E)
"""

from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)

    # Add an edge from u to v
    def add_edge(self, u, v):
        self.graph[u].append(v)

    # DFS utility
    def _dfs(self, v, visited, component):
        visited[v] = True
        component.append(v)
        for neighbor in self.graph[v]:
            if not visited[neighbor]:
                self._dfs(neighbor, visited, component)

    # Transpose the graph
    def _transpose(self):
        g_t = Graph(self.V)
        for v in self.graph:
            for u in self.graph[v]:
                g_t.add_edge(u, v)
        return g_t

    # Kosaraju's Algorithm to find SCCs
    def kosaraju_scc(self):
        visited = [False] * self.V
        stack = []

        # Step 1: Fill vertices in stack according to finishing times
        for i in range(self.V):
            if not visited[i]:
                self._fill_order(i, visited, stack)

        # Step 2: Transpose the graph
        transposed = self._transpose()

        # Step 3: Process all vertices in order defined by stack
        visited = [False] * self.V
        sccs = []
        while stack:
            v = stack.pop()
            if not visited[v]:
                component = []
                transposed._dfs(v, visited, component)
                sccs.append(component)

        return sccs

    # Helper function for first DFS to fill stack
    def _fill_order(self, v, visited, stack):
        visited[v] = True
        for neighbor in self.graph[v]:
            if not visited[neighbor]:
                self._fill_order(neighbor, visited, stack)
        stack.append(v)

# test Cases
if __name__ == "__main__":
    g = Graph(5)
    g.add_edge(1, 0)
    g.add_edge(0, 2)
    g.add_edge(2, 1)
    g.add_edge(0, 3)
    g.add_edge(3, 4)

    print("Strongly Connected Components:")
    sccs = g.kosaraju_scc()
    for i, component in enumerate(sccs, 1):
        print(f"Component {i}: {component}")

