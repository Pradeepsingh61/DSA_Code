"""
Dijkstra's Shortest Path Algorithm
----------------------------------

🔍 Problem:
Given a weighted graph and a source node, find the shortest path from the source to all other nodes.

📈 Time Complexity:
- O((V + E) * log V) using a priority queue (min-heap)

📦 Space Complexity:
- O(V + E) for adjacency list and distance tracking

👨‍💻 Approach:
- Use a min-heap to always expand the node with the smallest known distance
- Update neighbors if a shorter path is found
- Skip already visited nodes to avoid redundant work
"""

import heapq

def dijkstra(graph: dict, source: int) -> dict:
    """
    Computes shortest paths from the source node to all other nodes using Dijkstra's algorithm.

    Parameters:
    - graph (dict): Adjacency list where graph[u] = [(v, weight), ...]
    - source (int): Starting node

    Returns:
    - dict: Shortest distances from source to each node
    """

    # ✅ Validate input types
    if not isinstance(graph, dict):
        raise TypeError("Graph must be a dictionary of adjacency lists.")
    if source not in graph:
        raise ValueError("Source node must exist in the graph.")

    # Initialize distances to all nodes as infinity
    distances = {node: float('inf') for node in graph}
    distances[source] = 0

    # Track visited nodes to avoid reprocessing
    visited = set()

    # Min-heap to always process the closest unvisited node
    min_heap = [(0, source)]  # (distance, node)

    while min_heap:
        current_dist, current_node = heapq.heappop(min_heap)

        if current_node in visited:
            continue
        visited.add(current_node)

        # Explore neighbors and update distances if a shorter path is found
        for neighbor, weight in graph.get(current_node, []):
            if not isinstance(weight, (int, float)) or weight < 0:
                raise ValueError("Edge weights must be non-negative numbers.")
            distance = current_dist + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(min_heap, (distance, neighbor))

    return distances


# 🧪 Test Cases
if __name__ == "__main__":
    # ✅ Test Case 1: Simple graph
    graph1 = {
        0: [(1, 4), (2, 1)],
        1: [(3, 1)],
        2: [(1, 2), (3, 5)],
        3: []
    }
    source1 = 0
    expected1 = {0: 0, 1: 3, 2: 1, 3: 4}
    result1 = dijkstra(graph1, source1)
    print("Test Case 1:", "✅ Passed" if result1 == expected1 else "❌ Failed")

    # ✅ Test Case 2: Disconnected node
    graph2 = {
        0: [(1, 2)],
        1: [(2, 3)],
        2: [],
        3: []  # Node 3 is disconnected
    }
    source2 = 0
    expected2 = {0: 0, 1: 2, 2: 5, 3: float('inf')}
    result2 = dijkstra(graph2, source2)
    print("Test Case 2:", "✅ Passed" if result2 == expected2 else "❌ Failed")

    # ✅ Test Case 3: Invalid graph input
    try:
        dijkstra("not_a_graph", 0)
    except TypeError:
        print("Test Case 3: ✅ Passed (Caught TypeError)")
    else:
        print("Test Case 3: ❌ Failed")

    # ✅ Test Case 4: Invalid source node
    try:
        dijkstra({0: [(1, 2)]}, 5)
    except ValueError:
        print("Test Case 4: ✅ Passed (Caught ValueError)")
    else:
        print("Test Case 4: ❌ Failed")

    # ✅ Test Case 5: Negative weight edge
    try:
        dijkstra({0: [(1, -5)]}, 0)
    except ValueError:
        print("Test Case 5: ✅ Passed (Caught ValueError)")
    else:
        print("Test Case 5: ❌ Failed")
