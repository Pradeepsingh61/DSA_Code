# Section: Graph Algorithms

"""
Algorithm: Dijkstra's Shortest Path
Purpose: Finds the shortest path from a source node to all other nodes in a weighted graph.

Time Complexity: O((V + E) * log V), using a priority queue
Space Complexity: O(V + E), for adjacency list and distance tracking

Approach:
Uses a min-heap (priority queue) to greedily expand the shortest known paths.
Updates distances to neighbors if a shorter path is found.
"""

import heapq

def dijkstra(graph, start):
    # Input validation
    if not isinstance(graph, dict):
        raise ValueError("Graph must be a dictionary with adjacency lists.")
    if start not in graph:
        raise ValueError("Start node must exist in the graph.")

    # Initialize distances and priority queue
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    visited = set()
    heap = [(0, start)]  # (distance, node)

    while heap:
        current_dist, current_node = heapq.heappop(heap)

        if current_node in visited:
            continue
        visited.add(current_node)

        for neighbor, weight in graph[current_node]:
            if neighbor in visited:
                continue
            new_dist = current_dist + weight
            if new_dist < distances[neighbor]:
                distances[neighbor] = new_dist
                heapq.heappush(heap, (new_dist, neighbor))

    return distances


# 🧪 Test Cases
if __name__ == "__main__":
    graph = {
        'A': [('B', 1), ('C', 4)],
        'B': [('C', 2), ('D', 5)],
        'C': [('D', 1)],
        'D': []
    }

    expected = {'A': 0, 'B': 1, 'C': 3, 'D': 4}
    result = dijkstra(graph, 'A')
    print("Shortest distances from A:", result)
    assert result == expected, "Test case failed for graph starting at A"

    # Edge case: disconnected node
    graph['E'] = []
    result = dijkstra(graph, 'A')
    assert result['E'] == float('inf'), "Disconnected node should have infinite distance"
