# Graph Algorithms in C++

This directory contains efficient implementations of fundamental graph algorithms in C++, showcasing various graph traversal, topological ordering, and analysis techniques.

## 📁 Available Implementations

### 1. Topological Sort - `topological_sort.cpp`
**Description**: Linear ordering of vertices in a Directed Acyclic Graph (DAG) such that for every directed edge (u, v), vertex u comes before v in the ordering.

**Key Features**:
- **Two Algorithms**: DFS-based and Kahn's algorithm (BFS-based)
- **Cycle Detection**: Validates DAG property before sorting
- **Multiple Orderings**: Find all possible topological orderings
- **Labeled Vertices**: Support for custom vertex names/labels
- **Interactive Mode**: Create custom graphs and analyze them
- **Real-world Examples**: Course prerequisites, task scheduling

**Time Complexity**: O(V + E) where V is vertices and E is edges  
**Space Complexity**: O(V) for auxiliary data structures

**Applications**:
- Task scheduling with dependencies
- Course prerequisite planning
- Build systems and compilation order
- Deadlock detection in operating systems
- Symbol table construction in compilers
- Package dependency resolution

**Algorithm Implementations**:

1. **DFS-based Topological Sort**:
   - Uses depth-first search with post-order traversal
   - Maintains a stack to store vertices in reverse topological order
   - Natural recursive implementation

2. **Kahn's Algorithm (BFS-based)**:
   - Uses in-degree counting and queue-based processing
   - Processes vertices with zero in-degree first
   - Iterative approach with better cycle detection

**Code Highlights**:
```cpp
// Create a directed graph
DirectedGraph graph(6);
graph.setVertexLabel(0, "Math101");
graph.setVertexLabel(1, "CS101");

// Add prerequisite relationships
graph.addEdge(0, 2);  // Math101 -> Math201
graph.addEdge(1, 3);  // CS101 -> CS201

// Check if graph is a DAG
if (!graph.hasCycle()) {
    // DFS-based topological sort
    vector<int> dfsResult = topologicalSortDFS(graph);
    
    // Kahn's algorithm
    vector<int> kahnResult = topologicalSortKahn(graph);
    
    // Find all possible orderings
    vector<vector<int>> allOrderings = allTopologicalSorts(graph);
}
```

**Features Demonstrated**:
- **DirectedGraph Class**: Complete graph representation with adjacency lists
- **Cycle Detection**: DFS-based cycle detection using color coding
- **Vertex Labeling**: Custom labels for better readability
- **Multiple Examples**: Course scheduling, task dependencies, linear chains
- **Error Handling**: Comprehensive validation and error messages

## 🚀 How to Run

### Compile and Run Topological Sort
```bash
# Compile
g++ -o topological_sort topological_sort.cpp

# Run
./topological_sort
```

### Program Modes
1. **Demonstration Mode**: See predefined examples with detailed explanations
2. **Interactive Mode**: Create your own directed graph and analyze it

## 📊 Algorithm Comparison

| Algorithm | Approach | Implementation | Cycle Detection | Best Use Case |
|-----------|----------|----------------|-----------------|---------------|
| DFS-based | Recursive | Stack-based | During traversal | Simple graphs |
| Kahn's | Iterative | Queue-based | Explicit check | Large graphs |

## 🎯 When to Use Topological Sort

**✅ Use Topological Sort When**:
- You have a directed acyclic graph (DAG)
- Need to order tasks with dependencies
- Scheduling problems with prerequisites
- Building dependency resolution systems
- Detecting deadlocks in systems

**❌ Cannot Use When**:
- Graph contains cycles (not a DAG)
- Working with undirected graphs
- Need shortest paths (use Dijkstra/Bellman-Ford)
- Finding connected components (use DFS/BFS)

## 🔧 Graph Input Formats

The implementation supports flexible graph creation:

**Method 1: Programmatic Creation**
```cpp
DirectedGraph graph(5);
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 3);
```

**Method 2: Interactive Input**
```
Enter number of vertices: 4
Enter directed edges: 
0 1
0 2  
1 3
2 3
-1 -1
```

**Method 3: Labeled Vertices**
```cpp
graph.setVertexLabel(0, "Database");
graph.setVertexLabel(1, "Programming");
graph.setVertexLabel(2, "DataStructures");
```

## 📚 Educational Value

This implementation demonstrates:

**Graph Theory Concepts**:
- Directed Acyclic Graphs (DAGs)
- Graph traversal algorithms
- Cycle detection techniques
- Topological ordering properties

**Algorithm Design Patterns**:
- Depth-First Search (DFS)
- Breadth-First Search (BFS)
- Backtracking for all solutions
- State-space search

**Data Structures**:
- Adjacency list representation
- Stack and queue usage
- Vector and map containers
- Color coding for graph states

**Real-world Applications**:
- Dependency resolution
- Task scheduling
- Compilation systems
- Package managers

## 🔍 Complexity Analysis

### Time Complexity
- **DFS-based**: O(V + E) - visits each vertex and edge once
- **Kahn's Algorithm**: O(V + E) - processes each vertex and edge once
- **All Orderings**: O(V! × V) - exponential for finding all solutions
- **Cycle Detection**: O(V + E) - single DFS traversal

### Space Complexity
- **Graph Storage**: O(V + E) for adjacency list
- **Auxiliary Space**: O(V) for visited arrays, stacks, queues
- **Result Storage**: O(V) for single ordering, O(V! × V) for all orderings

## 🤝 Contributing

Feel free to contribute additional graph algorithms:

**Graph Traversal**:
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Bidirectional Search

**Shortest Path Algorithms**:
- Dijkstra's Algorithm
- Bellman-Ford Algorithm
- Floyd-Warshall Algorithm
- A* Search Algorithm

**Minimum Spanning Tree**:
- Kruskal's Algorithm
- Prim's Algorithm
- Borůvka's Algorithm

**Advanced Graph Algorithms**:
- Strongly Connected Components (Tarjan's, Kosaraju's)
- Articulation Points and Bridges
- Maximum Flow algorithms
- Graph Coloring algorithms

## 📖 References

- [Introduction to Algorithms - CLRS](https://mitpress.mit.edu/books/introduction-algorithms)
- [Graph Theory - Diestel](https://www.springer.com/gp/book/9783662575604)
- [Algorithms in C++ - Sedgewick](https://www.informit.com/store/algorithms-in-c-plus-plus-parts-1-4-fundamentals-data-9780201350883)
- [GeeksforGeeks Topological Sort](https://www.geeksforgeeks.org/topological-sorting/)

---

**Author**: Abhijit  
**Hacktoberfest 2025**: ✅  
**Language**: C++  
**Category**: Graph Algorithms