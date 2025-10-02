# Greedy Algorithms in C++

This directory contains implementations of fundamental greedy algorithms in C++, showcasing graph algorithms and optimization techniques that make locally optimal choices.

## 📁 Available Implementations

### 1. Floyd-Warshall Algorithm - `floyd_warshall_algorithm.cpp`
**Description**: Finds shortest paths between all pairs of vertices in a weighted graph using dynamic programming. Handles negative edge weights and detects negative cycles.

**Key Features**:
- All-pairs shortest path algorithm
- Handles weighted graphs with negative edges
- Detects negative weight cycles
- Path reconstruction capability
- Formatted distance matrix output
- Multiple comprehensive test cases

**Time Complexity**: O(V³) where V is the number of vertices  
**Space Complexity**: O(V²)

**Applications**:
- Network routing and analysis
- Finding transitive closure
- Game theory and AI pathfinding
- Social network analysis
- Route optimization in transportation

**Code Highlights**:
```cpp
// Create graph with 4 vertices
Graph g(4);

// Add directed edges (source, destination, weight)
g.addEdge(0, 1, 5);
g.addEdge(1, 2, 3);
g.addEdge(2, 3, 1);

// Run Floyd-Warshall algorithm
if (g.floydWarshall()) {
    g.printDistanceMatrix();
    g.printAllPathsFromSource(0);
}
```

**Algorithm Features**:
- **Dynamic Programming**: Iteratively improves shortest path estimates
- **Negative Edge Support**: Unlike Dijkstra, handles negative weights
- **Cycle Detection**: Identifies negative weight cycles
- **Path Reconstruction**: Tracks and displays complete shortest paths

### 2. Huffman Encoding - `huffman_algo.cpp`
**Description**: Data compression algorithm that creates optimal prefix-free binary codes based on character frequencies.

**Key Features**:
- Greedy algorithm for optimal encoding
- Prefix-free code generation
- Character frequency analysis
- Binary tree construction

**Time Complexity**: O(n log n)  
**Space Complexity**: O(n)

**Applications**:
- File compression (ZIP, GZIP)
- Data transmission optimization
- Image compression (JPEG)
- Network bandwidth optimization

### 3. Kruskal's Algorithm - `kruskal_algorithm.cpp`
**Description**: Finds the Minimum Spanning Tree (MST) of a weighted undirected graph using greedy approach and Union-Find data structure.

**Key Features**:
- Greedy MST construction
- Union-Find for cycle detection
- Edge sorting by weight
- Optimal tree selection

**Time Complexity**: O(E log E) where E is the number of edges  
**Space Complexity**: O(V + E)

**Applications**:
- Network design (minimum cost connections)
- Circuit design and VLSI layout
- Clustering algorithms
- Approximation algorithms for TSP

## 🚀 How to Run

### Compile and Run Floyd-Warshall
```bash
# Compile with C++17 standard
g++ -std=c++17 -Wall -Wextra floyd_warshall_algorithm.cpp -o floyd_warshall

# Run the program
./floyd_warshall
```

### Windows (PowerShell)
```powershell
g++ -std=c++17 floyd_warshall_algorithm.cpp -o floyd_warshall.exe
.\floyd_warshall.exe
```

### Compile and Run Other Algorithms
```bash
# Huffman Encoding
g++ -std=c++17 huffman_algo.cpp -o huffman
./huffman

# Kruskal's Algorithm
g++ -std=c++17 kruskal_algorithm.cpp -o kruskal
./kruskal
```

## 📊 Algorithm Comparison

| Algorithm | Type | Time Complexity | Space Complexity | Use Case |
|-----------|------|----------------|------------------|----------|
| Floyd-Warshall | All-Pairs Shortest Path | O(V³) | O(V²) | Dense graphs, all-pairs distances |
| Huffman | Compression | O(n log n) | O(n) | Data compression, encoding |
| Kruskal | MST | O(E log E) | O(V+E) | Minimum spanning tree |

## 🎯 When to Use Each Algorithm

### Use Floyd-Warshall When:
- ✅ Need shortest paths between ALL pairs of vertices
- ✅ Graph has negative edge weights (but no negative cycles)
- ✅ Graph is dense (many edges)
- ✅ Need transitive closure of a graph
- ✅ Working with small to medium sized graphs

### Use Huffman When:
- ✅ Need optimal prefix-free encoding
- ✅ Compressing data based on frequency
- ✅ Building variable-length codes
- ✅ Minimizing average code length

### Use Kruskal When:
- ✅ Need minimum spanning tree
- ✅ Working with undirected weighted graphs
- ✅ Designing network infrastructure
- ✅ Graph is sparse (fewer edges)

## 🔧 Graph Representations

### Floyd-Warshall Uses Adjacency Matrix:
```cpp
Graph g(4);  // 4 vertices
g.addEdge(0, 1, 5);   // Edge from 0 to 1 with weight 5
g.addEdge(1, 2, 3);   // Edge from 1 to 2 with weight 3
g.addEdge(2, 3, 1);   // Edge from 2 to 3 with weight 1
```

### Example Distance Matrix Output:
```
     0     1     2     3
-------------------------
0 |  0     5     8     9
1 | INF    0     3     4
2 | INF   INF    0     1
3 | INF   INF   INF    0
```

## 📚 Educational Value

These implementations demonstrate:

**Data Structures**:
- Distance matrices
- Path reconstruction arrays
- Priority queues
- Union-Find with optimizations

**Algorithm Techniques**:
- Greedy algorithms
- Dynamic programming
- Graph traversal strategies
- Optimization problems

**Problem-Solving Patterns**:
- Relaxation techniques
- Cycle detection
- Path reconstruction
- Negative weight handling

## 🎓 Floyd-Warshall Deep Dive

### Algorithm Steps:
1. **Initialize**: Set direct edge weights, infinity for no edges
2. **Iterate**: For each intermediate vertex k (0 to V-1):
   - For each pair (i, j): Check if path through k is shorter
   - Update: `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`
3. **Verify**: Check diagonal for negative cycles

### Six Comprehensive Examples:
1. **Basic Weighted Graph** - Standard shortest paths
2. **Negative Edges** - Handling negative weights correctly
3. **Complete Graph** - Bidirectional connections
4. **Disconnected Graph** - Multiple components handling
5. **Negative Cycle Detection** - Identifying problematic cycles
6. **Transitive Closure** - Reachability analysis

### When NOT to Use Floyd-Warshall:
- ❌ Very large graphs (V > 1000) - too slow
- ❌ Only need single-source paths - use Dijkstra or Bellman-Ford
- ❌ Sparse graphs - Johnson's algorithm is better
- ❌ Only need connectivity - use simpler algorithms

## 🤝 Contributing

Feel free to contribute additional greedy algorithms:

**Graph Algorithms**:
- Dijkstra's Algorithm (single-source shortest path)
- Prim's Algorithm (MST alternative)
- Bellman-Ford Algorithm (negative weights, single source)
- Johnson's Algorithm (all-pairs for sparse graphs)

**Optimization Algorithms**:
- Activity Selection Problem
- Fractional Knapsack
- Job Sequencing with Deadlines
- Minimum Platforms Problem

**Other Greedy Algorithms**:
- Coin Change (greedy version)
- Interval Scheduling
- Merge Intervals
- Gas Station Problem

### Contribution Guidelines:
1. Follow the existing code style (snake_case for files)
2. Include comprehensive documentation
3. Add multiple test cases with edge cases
4. Provide complexity analysis
5. Include real-world applications
6. Compile with `-Wall -Wextra` (no warnings)

## 📖 Comparison with Other Shortest Path Algorithms

| Algorithm | Single/All Pairs | Negative Weights | Time Complexity | Best For |
|-----------|-----------------|------------------|-----------------|----------|
| **Floyd-Warshall** | All Pairs | ✅ Yes | O(V³) | Dense, all-pairs |
| **Dijkstra** | Single Source | ❌ No | O((V+E) log V) | Non-negative weights |
| **Bellman-Ford** | Single Source | ✅ Yes | O(V×E) | Negative weights, single source |
| **Johnson's** | All Pairs | ✅ Yes | O(V² log V + VE) | Sparse graphs |

## 🔍 Key Concepts

### Greedy Algorithm Properties:
1. **Greedy Choice Property**: Local optimum leads to global optimum
2. **Optimal Substructure**: Optimal solution contains optimal sub-solutions
3. **No Backtracking**: Once a choice is made, it's never reconsidered

### Floyd-Warshall Specifics:
- Uses **dynamic programming** (not purely greedy)
- Builds solution by considering intermediate vertices
- Matrix-based approach for dense graphs
- In-place updates possible

## 📖 References

- [Introduction to Algorithms - CLRS](https://mitpress.mit.edu/books/introduction-algorithms)
- [Algorithm Design Manual - Skiena](https://www.algorist.com/)
- [Algorithms - Sedgewick](https://algs4.cs.princeton.edu/home/)
- [CP-Algorithms](https://cp-algorithms.com/)
- [GeeksforGeeks - Greedy Algorithms](https://www.geeksforgeeks.org/greedy-algorithms/)

## 🏆 Algorithm Highlights

### Floyd-Warshall Special Features:
- 🔥 Handles negative weights (unique for all-pairs algorithms)
- 🔍 Detects negative cycles automatically
- 📊 Returns complete distance matrix
- 🎯 Path reconstruction included
- 💡 Six comprehensive test cases
- ✨ Beautiful formatted output

### Real-World Floyd-Warshall Applications:
1. **Network Routing**: Finding optimal routes in computer networks
2. **Urban Planning**: Analyzing transportation networks
3. **Game AI**: Pathfinding with multiple agents
4. **Social Networks**: Finding shortest connection paths
5. **Logistics**: Multi-destination route optimization

---

**Contributors**: Multiple authors (see individual files)  
**Hacktoberfest 2025**: ✅  
**Language**: C++  
**Category**: Greedy Algorithms & Dynamic Programming  
**Standard**: C++17 or higher
