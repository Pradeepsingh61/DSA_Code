# Graph Algorithms in Python

This directory contains implementations of fundamental graph algorithms in Python, showcasing various graph traversal, shortest path, and spanning tree algorithms.

## 📁 Available Implementations

### 1. Dijkstra's Algorithm - `dijkstra_algorithm.py`
**Description**: Finds shortest paths from a source vertex to all other vertices in a weighted graph with non-negative edge weights.

**Key Features**:
- Single-source shortest path algorithm
- Handles weighted graphs with non-negative weights
- Uses priority queue for efficient vertex selection
- Provides path reconstruction

**Time Complexity**: O((V + E) log V) using priority queue  
**Space Complexity**: O(V)

**Applications**:
- GPS navigation systems
- Network routing protocols
- Social network analysis
- Game pathfinding

### 2. Kruskal's Algorithm - `kruskals_algorithm.py`
**Description**: Finds the Minimum Spanning Tree (MST) of a weighted undirected graph using greedy approach and Union-Find data structure.

**Key Features**:
- Greedy algorithm for MST construction
- Union-Find data structure for cycle detection
- Step-by-step execution tracking
- Interactive and demonstration modes
- Comprehensive error handling and validation

**Time Complexity**: O(E log E) where E is the number of edges  
**Space Complexity**: O(V + E) where V is the number of vertices

**Applications**:
- Network design (connecting cities with minimum cost)
- Circuit design and VLSI layout
- Clustering algorithms
- Image segmentation
- Approximation algorithms for TSP

**Code Highlights**:
```python
# Create graph and add edges
graph = Graph(6)
graph.add_edge(0, 1, 4)
graph.add_edge(1, 2, 1)
graph.add_edge(2, 3, 4)

# Find MST using Kruskal's algorithm
mst_edges, total_weight = kruskals_mst(graph)
print(f"MST total weight: {total_weight}")

# Get step-by-step execution
mst_edges, weight, steps = kruskals_with_steps(graph)
for step in steps:
    print(step)
```

**Union-Find Data Structure**:
- **Path Compression**: Optimizes find operations
- **Union by Rank**: Balances tree height during union operations
- **Cycle Detection**: Efficiently detects if adding an edge creates a cycle

## 🚀 How to Run

### Run Dijkstra's Algorithm
```bash
python dijkstra_algorithm.py
```

### Run Kruskal's Algorithm
```bash
python kruskals_algorithm.py
```

### Program Modes
Both implementations offer:
1. **Interactive Mode**: Create custom graphs and see results
2. **Demonstration Mode**: Pre-built examples with detailed explanations

## 📊 Algorithm Comparison

| Algorithm | Type | Time Complexity | Space Complexity | Use Case |
|-----------|------|----------------|------------------|----------|
| Dijkstra | Shortest Path | O((V+E) log V) | O(V) | Single-source shortest paths |
| Kruskal | MST | O(E log E) | O(V+E) | Minimum spanning tree |

## 🎯 When to Use Each Algorithm

### Use Dijkstra When:
- ✅ Finding shortest paths from one vertex to all others
- ✅ All edge weights are non-negative
- ✅ Need actual shortest distances
- ✅ Working with road networks, communication networks

### Use Kruskal When:
- ✅ Need to connect all vertices with minimum total cost
- ✅ Working with undirected, weighted graphs
- ✅ Designing network infrastructure
- ✅ Finding minimum cost to connect components

## 🔧 Graph Representations

Both algorithms support different graph input formats:

**Adjacency List Format**:
```python
graph = {
    0: [(1, 4), (2, 3)],  # vertex: [(neighbor, weight), ...]
    1: [(0, 4), (2, 1)],
    2: [(0, 3), (1, 1)]
}
```

**Edge List Format**:
```python
edges = [
    (0, 1, 4),  # (u, v, weight)
    (0, 2, 3),
    (1, 2, 1)
]
```

## 📚 Educational Value

These implementations demonstrate:

**Data Structures**:
- Priority Queues (heapq)
- Union-Find with optimizations
- Graph representations

**Algorithm Techniques**:
- Greedy algorithms
- Dynamic programming concepts
- Path compression and union by rank

**Problem-Solving Patterns**:
- Graph traversal strategies
- Optimization problems
- Cycle detection techniques

## 🤝 Contributing

Feel free to contribute additional graph algorithms:

**Shortest Path Algorithms**:
- Bellman-Ford Algorithm
- Floyd-Warshall Algorithm
- A* Search Algorithm
- Johnson's Algorithm

**Spanning Tree Algorithms**:
- Prim's Algorithm
- Borůvka's Algorithm

**Traversal Algorithms**:
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Topological Sort

**Flow Algorithms**:
- Ford-Fulkerson Method
- Edmonds-Karp Algorithm
- Dinic's Algorithm

**Advanced Algorithms**:
- Strongly Connected Components
- Articulation Points and Bridges
- Minimum Cut algorithms

## 📖 References

- [Introduction to Algorithms - CLRS](https://mitpress.mit.edu/books/introduction-algorithms)
- [Graph Theory - Diestel](https://www.springer.com/gp/book/9783662575604)
- [Algorithms - Sedgewick](https://algs4.cs.princeton.edu/home/)
- [GeeksforGeeks Graph Algorithms](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)

---

**Contributors**: Multiple authors (see individual files)  
**Hacktoberfest 2025**: ✅  
**Language**: Python  
**Category**: Graph Algorithms