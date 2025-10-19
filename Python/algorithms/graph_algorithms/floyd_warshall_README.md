### 3. Floyd-Warshall Algorithm - `floyd_warshall.py`
**Description**: Computes shortest paths between **all pairs of vertices** in a weighted graph.  
It can handle **negative edge weights** (but no negative cycles) and works for both directed and undirected graphs.

**Key Features**:
- Finds shortest paths between every pair of vertices
- Supports graphs with negative edge weights
- Simple and easy-to-understand matrix-based implementation
- Includes example usage for testing

**Time Complexity**: O(V³), where V is the number of vertices  
**Space Complexity**: O(V²), for storing the distance matrix  

**Applications**:
- Network routing and optimization
- Finding shortest paths in road networks
- Game AI pathfinding
- All-pairs shortest distance analysis

**Code Highlights**:
```python
from floyd_warshall import floyd_warshall

graph = [
    [0, 3, float('inf'), 7],
    [8, 0, 2, float('inf')],
    [5, float('inf'), 0, 1],
    [2, float('inf'), float('inf'), 0]
]

shortest_paths = floyd_warshall(graph)
print("All pairs shortest path matrix:")
for row in shortest_paths:
    print(row)


All pairs shortest path matrix:
[0, 3, 5, 7]
[5, 0, 2, 4]
[3, 6, 0, 1]
[2, 5, 7, 0]


Graph represented as adjacency matrix:
- graph[i][j] = weight of edge from vertex i to j
- float('inf') = no edge between i and j
