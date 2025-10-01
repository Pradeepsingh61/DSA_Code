"""
Graph Traversal Algorithms - BFS and DFS
Time Complexity: O(V + E) where V = vertices, E = edges
Space Complexity: O(V) for visited set and queue/stack
Author: Karanjot Singh
Date: October 2025
Hacktoberfest 2025
"""

from collections import deque, defaultdict


class Graph:
    """Graph representation using adjacency list"""

    def __init__(self):
        self.graph = defaultdict(list)

    def add_edge(self, u, v):
        """
        Add an edge to the graph (undirected)

        Args:
            u: Source vertex
            v: Destination vertex
        """
        self.graph[u].append(v)
        self.graph[v].append(u)

    def add_directed_edge(self, u, v):
        """
        Add a directed edge to the graph

        Args:
            u: Source vertex
            v: Destination vertex
        """
        self.graph[u].append(v)

    def bfs(self, start):
        """
        Breadth-First Search traversal

        Visits nodes level by level using a queue
        Useful for: shortest path, level-order traversal

        Args:
            start: Starting vertex

        Returns:
            List of vertices in BFS order
        """
        visited = set()
        queue = deque([start])
        visited.add(start)
        result = []

        while queue:
            vertex = queue.popleft()
            result.append(vertex)

            # Visit all adjacent vertices
            for neighbor in self.graph[vertex]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        return result

    def dfs(self, start):
        """
        Depth-First Search traversal (iterative)

        Visits nodes by going deep into branches using a stack
        Useful for: path finding, cycle detection, topological sort

        Args:
            start: Starting vertex

        Returns:
            List of vertices in DFS order
        """
        visited = set()
        stack = [start]
        result = []

        while stack:
            vertex = stack.pop()

            if vertex not in visited:
                visited.add(vertex)
                result.append(vertex)

                # Add neighbors to stack (reverse order for consistent traversal)
                for neighbor in reversed(self.graph[vertex]):
                    if neighbor not in visited:
                        stack.append(neighbor)

        return result

    def dfs_recursive(self, start, visited=None):
        """
        Depth-First Search traversal (recursive)

        Args:
            start: Starting vertex
            visited: Set of visited vertices (used internally)

        Returns:
            List of vertices in DFS order
        """
        if visited is None:
            visited = set()

        visited.add(start)
        result = [start]

        for neighbor in self.graph[start]:
            if neighbor not in visited:
                result.extend(self.dfs_recursive(neighbor, visited))

        return result

    def is_connected(self, start):
        """
        Check if all vertices are reachable from start

        Args:
            start: Starting vertex

        Returns:
            True if graph is connected, False otherwise
        """
        visited = set()
        self._dfs_visit(start, visited)
        return len(visited) == len(self.graph)

    def _dfs_visit(self, vertex, visited):
        """Helper method for connectivity check"""
        visited.add(vertex)
        for neighbor in self.graph[vertex]:
            if neighbor not in visited:
                self._dfs_visit(neighbor, visited)


# Test cases
if __name__ == "__main__":
    print("=== Graph Traversal - BFS and DFS ===\n")

    # Test case 1: Simple undirected graph
    print("--- Test Case 1: Undirected Graph ---")
    g1 = Graph()
    edges1 = [(0, 1), (0, 2), (1, 3), (1, 4), (2, 5), (2, 6)]

    print(f"Adding edges: {edges1}")
    for u, v in edges1:
        g1.add_edge(u, v)

    print(f"BFS from vertex 0: {g1.bfs(0)}")
    print(f"DFS from vertex 0 (iterative): {g1.dfs(0)}")
    print(f"DFS from vertex 0 (recursive): {g1.dfs_recursive(0)}")

    # Test case 2: Directed graph
    print("\n--- Test Case 2: Directed Graph ---")
    g2 = Graph()
    directed_edges = [(0, 1), (0, 2), (1, 3), (2, 3), (3, 4)]

    print(f"Adding directed edges: {directed_edges}")
    for u, v in directed_edges:
        g2.add_directed_edge(u, v)

    print(f"BFS from vertex 0: {g2.bfs(0)}")
    print(f"DFS from vertex 0 (iterative): {g2.dfs(0)}")

    # Test case 3: Larger graph
    print("\n--- Test Case 3: Larger Graph ---")
    g3 = Graph()
    edges3 = [(0, 1), (0, 4), (1, 2), (1, 3), (1, 4), (2, 3), (3, 4)]

    print(f"Adding edges: {edges3}")
    for u, v in edges3:
        g3.add_edge(u, v)

    print(f"BFS from vertex 0: {g3.bfs(0)}")
    print(f"DFS from vertex 0: {g3.dfs(0)}")

    # Test case 4: Linear graph
    print("\n--- Test Case 4: Linear Graph ---")
    g4 = Graph()
    edges4 = [(1, 2), (2, 3), (3, 4), (4, 5)]

    print(f"Adding edges: {edges4}")
    for u, v in edges4:
        g4.add_edge(u, v)

    print(f"BFS from vertex 1: {g4.bfs(1)}")
    print(f"DFS from vertex 1: {g4.dfs(1)}")

    # Test case 5: Disconnected graph check
    print("\n--- Test Case 5: Connectivity Check ---")
    g5 = Graph()
    g5.add_edge(0, 1)
    g5.add_edge(1, 2)
    g5.add_edge(3, 4)  # Disconnected component

    print(f"Graph with vertices: 0-1-2 and 3-4")
    print(f"Is connected from 0? {g5.is_connected(0)}")

    print("\n✅ All test cases completed!")
