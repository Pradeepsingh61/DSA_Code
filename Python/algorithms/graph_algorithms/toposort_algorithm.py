'''Purpose: Orders vertices of a Directed Acyclic Graph (DAG) such that for every directed edge u → v, vertex u comes before v in the ordering.

Type: Graph Algorithm

Use Cases: Task scheduling, course prerequisite ordering, build systems, etc.

Approach: We can implement Toposort using DFS:

For each unvisited node, perform a DFS.

After visiting all neighbors, push the node to a stack.

At the end, pop nodes from the stack to get the topological order.

Time Complexity: O(V + E)

Space Complexity: O(V)'''

# Topological Sorting using DFS in Python

from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)

    # Add an edge from u to v
    def add_edge(self, u, v):
        self.graph[u].append(v)

    # Recursive helper function for DFS
    def _dfs(self, v, visited, stack):
        visited[v] = True
        for neighbor in self.graph[v]:
            if not visited[neighbor]:
                self._dfs(neighbor, visited, stack)
        stack.append(v)  # Push vertex after visiting neighbors

    # Topological Sort
    def topological_sort(self):
        visited = [False] * self.V
        stack = []

        for i in range(self.V):
            if not visited[i]:
                self._dfs(i, visited, stack)

        # Return in reverse order
        return stack[::-1]

# Main function
if __name__ == "__main__":
    # Example graph
    g = Graph(6)
    g.add_edge(5, 2)
    g.add_edge(5, 0)
    g.add_edge(4, 0)
    g.add_edge(4, 1)
    g.add_edge(2, 3)
    g.add_edge(3, 1)

    print("Topological Sort of the given graph:")
    order = g.topological_sort()
    print(order)
