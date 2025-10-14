"""
Bellman-Ford Algorithm
----------------------
Description:
    Computes shortest paths from a single source vertex to all other vertices in a weighted graph.
    Supports negative weight edges and detects negative weight cycles.

Usage:
    Call bellman_ford(vertices, edges, source) with:
        - vertices: list of node labels
        - edges: list of tuples (u, v, weight)
        - source: starting node label

Time Complexity: O(V * E)
Space Complexity: O(V)


"""

def bellman_ford(vertices, edges, source):
    # Validate that the source exists in the graph
    if source not in vertices:
        raise ValueError(f"Source vertex '{source}' not found in graph.")
    
    # Validate that all edge endpoints exist in the graph
    for u, v, _ in edges:
        if u not in vertices or v not in vertices:
            raise ValueError(f"Edge contains undefined vertex: ({u}, {v})")

    # Step 1: Initialize distances from source to all vertices as infinite
    distance = {v: float('inf') for v in vertices}
    distance[source] = 0

    # Step 2: Relax all edges |V| - 1 times
    for _ in range(len(vertices) - 1):
        for u, v, w in edges:
            # If the current path offers a shorter route, update the distance
            if distance[u] != float('inf') and distance[u] + w < distance[v]:
                distance[v] = distance[u] + w

    # Step 3: Check for negative weight cycles
    for u, v, w in edges:
        if distance[u] != float('inf') and distance[u] + w < distance[v]:
            raise ValueError("Graph contains a negative weight cycle.")

    return distance


# ------------------ Test Cases ------------------

def run_tests():
    print("Running Bellman-Ford test cases...\n")

    # Test Case 1: Basic graph with positive weights
    vertices1 = ['A', 'B', 'C', 'D']
    edges1 = [
        ('A', 'B', 1),
        ('B', 'C', 3),
        ('A', 'C', 10),
        ('C', 'D', 2),
        ('B', 'D', 2)
    ]
    print("Test Case 1:", bellman_ford(vertices1, edges1, 'A'))

    # Test Case 2: Graph with negative weights but no cycle
    vertices2 = ['X', 'Y', 'Z']
    edges2 = [
        ('X', 'Y', 4),
        ('Y', 'Z', -2),
        ('X', 'Z', 5)
    ]
    print("Test Case 2:", bellman_ford(vertices2, edges2, 'X'))

    # Test Case 3: Graph with a negative weight cycle
    vertices3 = ['P', 'Q', 'R']
    edges3 = [
        ('P', 'Q', 1),
        ('Q', 'R', -1),
        ('R', 'P', -1)
    ]
    try:
        print("Test Case 3:", bellman_ford(vertices3, edges3, 'P'))
    except ValueError as e:
        print("Test Case 3: Exception caught -", e)

    # Test Case 4: Invalid source vertex
    try:
        print("Test Case 4:", bellman_ford(['A', 'B'], [('A', 'B', 2)], 'Z'))
    except ValueError as e:
        print("Test Case 4: Exception caught -", e)

    # Test Case 5: Edge with undefined vertex
    try:
        print("Test Case 5:", bellman_ford(['A', 'B'], [('A', 'C', 2)], 'A'))
    except ValueError as e:
        print("Test Case 5: Exception caught -", e)


if __name__ == "__main__":
    run_tests()
