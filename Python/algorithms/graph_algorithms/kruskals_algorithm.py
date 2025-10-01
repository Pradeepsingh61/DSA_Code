"""
Algorithm: Kruskal's Algorithm for Minimum Spanning Tree (MST)
Description: Finds the minimum spanning tree of a weighted undirected graph using greedy approach
             and Union-Find data structure to detect cycles
Time Complexity: O(E log E) where E is the number of edges
Space Complexity: O(V + E) where V is the number of vertices
Author: Abhijit
Date: October 2025
Hacktoberfest 2025

Key Concepts:
- Minimum Spanning Tree: A tree that connects all vertices with minimum total edge weight
- Greedy Algorithm: Always chooses the smallest weight edge that doesn't create a cycle
- Union-Find: Efficient data structure to detect cycles and manage connected components
- Disjoint Set: Keeps track of which vertices belong to the same connected component

Applications:
- Network design (connecting cities with minimum cost)
- Circuit design and VLSI layout
- Clustering algorithms
- Image segmentation
- Approximation algorithms for TSP
"""

from typing import List, Tuple, Dict, Set
import heapq


class UnionFind:
    """
    Union-Find (Disjoint Set) data structure with path compression and union by rank.
    Used to efficiently detect cycles in Kruskal's algorithm.
    """
    
    def __init__(self, n: int):
        """
        Initialize Union-Find structure for n vertices.
        
        Args:
            n: Number of vertices (0 to n-1)
        """
        self.parent = list(range(n))  # Each vertex is its own parent initially
        self.rank = [0] * n  # Rank for union by rank optimization
        self.components = n  # Number of connected components
    
    def find(self, x: int) -> int:
        """
        Find the root of the set containing x with path compression.
        
        Args:
            x: Vertex to find root for
            
        Returns:
            Root of the set containing x
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]
    
    def union(self, x: int, y: int) -> bool:
        """
        Union two sets containing x and y using union by rank.
        
        Args:
            x: First vertex
            y: Second vertex
            
        Returns:
            True if union was performed (no cycle), False if already connected (cycle detected)
        """
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x == root_y:
            return False  # Already in same set, would create cycle
        
        # Union by rank: attach smaller tree under larger tree
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
        
        self.components -= 1
        return True
    
    def is_connected(self, x: int, y: int) -> bool:
        """
        Check if two vertices are in the same connected component.
        
        Args:
            x: First vertex
            y: Second vertex
            
        Returns:
            True if vertices are connected, False otherwise
        """
        return self.find(x) == self.find(y)


class Graph:
    """
    Graph representation for Kruskal's algorithm implementation.
    Supports both adjacency list and edge list representations.
    """
    
    def __init__(self, vertices: int):
        """
        Initialize graph with given number of vertices.
        
        Args:
            vertices: Number of vertices in the graph
        """
        self.vertices = vertices
        self.edges = []  # List of (weight, u, v) tuples
        self.adjacency_list = {i: [] for i in range(vertices)}
    
    def add_edge(self, u: int, v: int, weight: float):
        """
        Add an undirected edge to the graph.
        
        Args:
            u: First vertex
            v: Second vertex  
            weight: Weight of the edge
            
        Raises:
            ValueError: If vertices are invalid or weight is negative
        """
        if u < 0 or u >= self.vertices or v < 0 or v >= self.vertices:
            raise ValueError(f"Invalid vertices: {u}, {v}. Must be in range [0, {self.vertices-1}]")
        
        if weight < 0:
            raise ValueError(f"Negative weight {weight} not allowed in MST")
        
        if u == v:
            return  # Ignore self-loops
        
        self.edges.append((weight, u, v))
        self.adjacency_list[u].append((v, weight))
        self.adjacency_list[v].append((u, weight))
    
    def get_edges(self) -> List[Tuple[float, int, int]]:
        """
        Get all edges sorted by weight.
        
        Returns:
            List of (weight, u, v) tuples sorted by weight
        """
        return sorted(self.edges)
    
    def is_connected_graph(self) -> bool:
        """
        Check if the graph is connected using DFS.
        
        Returns:
            True if graph is connected, False otherwise
        """
        if self.vertices == 0:
            return True
        
        visited = [False] * self.vertices
        
        # Find first vertex with edges
        start = 0
        for i in range(self.vertices):
            if self.adjacency_list[i]:
                start = i
                break
        
        # DFS from start vertex
        stack = [start]
        visited[start] = True
        visited_count = 1
        
        while stack:
            vertex = stack.pop()
            for neighbor, _ in self.adjacency_list[vertex]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    visited_count += 1
                    stack.append(neighbor)
        
        # Check if all vertices with edges are visited
        for i in range(self.vertices):
            if self.adjacency_list[i] and not visited[i]:
                return False
        
        return True


def kruskals_mst(graph: Graph) -> Tuple[List[Tuple[int, int, float]], float]:
    """
    Find Minimum Spanning Tree using Kruskal's algorithm.
    
    Args:
        graph: Input graph
        
    Returns:
        Tuple containing:
        - List of MST edges as (u, v, weight) tuples
        - Total weight of MST
        
    Raises:
        ValueError: If graph is not connected
    """
    if not graph.is_connected_graph():
        raise ValueError("Graph is not connected. MST cannot be found.")
    
    if graph.vertices == 0:
        return [], 0.0
    
    # Initialize Union-Find structure
    uf = UnionFind(graph.vertices)
    
    # Get edges sorted by weight
    sorted_edges = graph.get_edges()
    
    mst_edges = []
    total_weight = 0.0
    
    # Process edges in ascending order of weight
    for weight, u, v in sorted_edges:
        # If adding this edge doesn't create a cycle
        if uf.union(u, v):
            mst_edges.append((u, v, weight))
            total_weight += weight
            
            # MST is complete when we have V-1 edges
            if len(mst_edges) == graph.vertices - 1:
                break
    
    return mst_edges, total_weight


def kruskals_with_steps(graph: Graph) -> Tuple[List[Tuple[int, int, float]], float, List[str]]:
    """
    Kruskal's algorithm with detailed step-by-step execution tracking.
    
    Args:
        graph: Input graph
        
    Returns:
        Tuple containing:
        - List of MST edges
        - Total weight of MST  
        - List of step descriptions
    """
    steps = []
    
    if not graph.is_connected_graph():
        raise ValueError("Graph is not connected. MST cannot be found.")
    
    steps.append(f"Starting Kruskal's algorithm with {graph.vertices} vertices and {len(graph.edges)} edges")
    
    uf = UnionFind(graph.vertices)
    sorted_edges = graph.get_edges()
    
    steps.append(f"Sorted edges by weight: {[(u, v, w) for w, u, v in sorted_edges]}")
    
    mst_edges = []
    total_weight = 0.0
    
    for i, (weight, u, v) in enumerate(sorted_edges):
        if uf.is_connected(u, v):
            steps.append(f"Step {i+1}: Edge ({u}, {v}, {weight}) REJECTED - would create cycle")
        else:
            uf.union(u, v)
            mst_edges.append((u, v, weight))
            total_weight += weight
            steps.append(f"Step {i+1}: Edge ({u}, {v}, {weight}) ACCEPTED - added to MST")
            
            if len(mst_edges) == graph.vertices - 1:
                steps.append(f"MST complete with {len(mst_edges)} edges")
                break
    
    return mst_edges, total_weight, steps


def create_sample_graph() -> Graph:
    """
    Create a sample graph for demonstration.
    
    Returns:
        Sample graph with predefined edges
    """
    # Graph with 6 vertices (0-5)
    graph = Graph(6)
    
    # Add edges: (u, v, weight)
    edges = [
        (0, 1, 4), (0, 2, 3), (1, 2, 1), (1, 3, 2),
        (2, 3, 4), (2, 4, 2), (3, 4, 3), (3, 5, 2),
        (4, 5, 6)
    ]
    
    for u, v, weight in edges:
        graph.add_edge(u, v, weight)
    
    return graph


def visualize_mst(graph: Graph, mst_edges: List[Tuple[int, int, float]]):
    """
    Print a text visualization of the MST.
    
    Args:
        graph: Original graph
        mst_edges: MST edges to visualize
    """
    print(f"\n{'='*50}")
    print("MINIMUM SPANNING TREE VISUALIZATION")
    print(f"{'='*50}")
    
    print(f"Vertices: {graph.vertices}")
    print(f"MST Edges: {len(mst_edges)}")
    
    print(f"\nMST Structure:")
    for i, (u, v, weight) in enumerate(mst_edges, 1):
        print(f"  {i}. Vertex {u} ←→ Vertex {v} (weight: {weight})")
    
    # Create adjacency representation of MST
    mst_adj = {i: [] for i in range(graph.vertices)}
    for u, v, weight in mst_edges:
        mst_adj[u].append((v, weight))
        mst_adj[v].append((u, weight))
    
    print(f"\nMST Adjacency List:")
    for vertex in range(graph.vertices):
        neighbors = mst_adj[vertex]
        if neighbors:
            neighbor_str = ", ".join([f"{v}({w})" for v, w in neighbors])
            print(f"  Vertex {vertex}: {neighbor_str}")
        else:
            print(f"  Vertex {vertex}: isolated")


def demonstrate_kruskals():
    """
    Demonstrate Kruskal's algorithm with various examples.
    """
    print("=" * 60)
    print("KRUSKAL'S ALGORITHM FOR MINIMUM SPANNING TREE")
    print("=" * 60)
    
    # Example 1: Basic demonstration
    print("\n📊 Example 1: Standard Graph")
    graph1 = create_sample_graph()
    
    print("Original Graph Edges:")
    for weight, u, v in graph1.get_edges():
        print(f"  Edge ({u}, {v}) with weight {weight}")
    
    mst_edges, total_weight = kruskals_mst(graph1)
    
    print(f"\n🌳 Minimum Spanning Tree:")
    print(f"Total Weight: {total_weight}")
    visualize_mst(graph1, mst_edges)
    
    # Example 2: Step-by-step execution
    print(f"\n\n📝 Example 2: Step-by-Step Execution")
    _, _, steps = kruskals_with_steps(graph1)
    
    for step in steps:
        print(f"  {step}")
    
    # Example 3: Small complete graph
    print(f"\n\n📊 Example 3: Complete Graph (4 vertices)")
    graph2 = Graph(4)
    complete_edges = [
        (0, 1, 10), (0, 2, 6), (0, 3, 5),
        (1, 2, 4), (1, 3, 15), (2, 3, 8)
    ]
    
    for u, v, weight in complete_edges:
        graph2.add_edge(u, v, weight)
    
    mst_edges2, total_weight2 = kruskals_mst(graph2)
    print(f"MST Weight: {total_weight2}")
    visualize_mst(graph2, mst_edges2)
    
    # Example 4: Linear graph
    print(f"\n\n📊 Example 4: Linear Graph (5 vertices)")
    graph3 = Graph(5)
    linear_edges = [(0, 1, 2), (1, 2, 3), (2, 3, 1), (3, 4, 4)]
    
    for u, v, weight in linear_edges:
        graph3.add_edge(u, v, weight)
    
    mst_edges3, total_weight3 = kruskals_mst(graph3)
    print(f"MST Weight: {total_weight3}")
    visualize_mst(graph3, mst_edges3)


def interactive_mode():
    """
    Interactive mode for users to create custom graphs and find MST.
    """
    print("\n" + "=" * 50)
    print("INTERACTIVE KRUSKAL'S ALGORITHM")
    print("=" * 50)
    
    try:
        vertices = int(input("Enter number of vertices: "))
        if vertices <= 0:
            print("Number of vertices must be positive!")
            return
        
        graph = Graph(vertices)
        
        print(f"\nEnter edges for graph with vertices 0 to {vertices-1}")
        print("Format: vertex1 vertex2 weight (or 'done' to finish)")
        
        while True:
            edge_input = input("Edge: ").strip()
            
            if edge_input.lower() == 'done':
                break
            
            try:
                parts = edge_input.split()
                if len(parts) != 3:
                    print("Please enter exactly 3 values: vertex1 vertex2 weight")
                    continue
                
                u, v, weight = int(parts[0]), int(parts[1]), float(parts[2])
                graph.add_edge(u, v, weight)
                print(f"Added edge ({u}, {v}) with weight {weight}")
                
            except ValueError as e:
                print(f"Invalid input: {e}")
                continue
        
        if len(graph.edges) == 0:
            print("No edges added to graph!")
            return
        
        print(f"\nGraph created with {len(graph.edges)} edges")
        
        # Check if connected
        if not graph.is_connected_graph():
            print("⚠️  Warning: Graph is not connected. MST cannot be found.")
            return
        
        # Find MST
        mst_edges, total_weight = kruskals_mst(graph)
        
        print(f"\n🌳 Minimum Spanning Tree found!")
        print(f"Total Weight: {total_weight}")
        visualize_mst(graph, mst_edges)
        
        # Offer step-by-step view
        show_steps = input("\nShow step-by-step execution? (y/n): ").lower().startswith('y')
        if show_steps:
            _, _, steps = kruskals_with_steps(graph)
            print(f"\n📝 Step-by-Step Execution:")
            for step in steps:
                print(f"  {step}")
    
    except KeyboardInterrupt:
        print("\nOperation cancelled by user.")
    except Exception as e:
        print(f"Error: {e}")


def main():
    """
    Main function with user interface for Kruskal's algorithm demonstration.
    """
    print("Kruskal's Algorithm for Minimum Spanning Tree")
    print("============================================")
    print("1. Demonstration mode (predefined examples)")
    print("2. Interactive mode (create your own graph)")
    
    try:
        choice = input("Choose mode (1 or 2): ").strip()
        
        if choice == '1':
            demonstrate_kruskals()
        elif choice == '2':
            interactive_mode()
        else:
            print("Invalid choice! Please enter 1 or 2.")
            return
            
    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
    except Exception as e:
        print(f"An error occurred: {e}")
    
    # Algorithm information
    print(f"\n{'='*60}")
    print("ALGORITHM INFORMATION")
    print(f"{'='*60}")
    print("Time Complexity: O(E log E) - dominated by edge sorting")
    print("Space Complexity: O(V + E) - for Union-Find and edge storage")
    print("Key Features:")
    print("  • Greedy algorithm - always chooses minimum weight edge")
    print("  • Uses Union-Find for efficient cycle detection")
    print("  • Guaranteed to find optimal MST")
    print("  • Works on undirected, weighted graphs")
    print("\nApplications:")
    print("  • Network design and infrastructure")
    print("  • Circuit design and VLSI layout")
    print("  • Clustering and image segmentation")
    print("  • Approximation algorithms")
    print("  • Social network analysis")


if __name__ == "__main__":
    main()