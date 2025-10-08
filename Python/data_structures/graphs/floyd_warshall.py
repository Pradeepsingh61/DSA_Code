"""
Floyd-Warshall Algorithm
------------------------
Description:
    Computes shortest paths between all pairs of vertices in a weighted graph using dynamic programming.
    Supports negative edge weights but does not detect negative weight cycles.

Algorithm:
    - Initialize a distance matrix with infinity for all pairs except self-loops (0).
    - Populate the matrix with direct edge weights.
    - For each intermediate vertex k, update dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).

Time Complexity: O(V^3)
Space Complexity: O(V^2)

"""

def floyd_warshall(vertices, edges):
    # Validate that vertex list is not empty
    if not vertices:
        raise ValueError("Vertex list is empty.")

    # Validate that all edge endpoints exist in the graph
    for u, v, _ in edges:
        if u not in vertices or v not in vertices:
            raise ValueError(f"Edge contains undefined vertex: ({u}, {v})")

    # Step 1: Initialize distance matrix with infinity
    dist = {i: {j: float('inf') for j in vertices} for i in vertices}
    for v in vertices:
        dist[v][v] = 0  # Distance to self is zero

    # Step 2: Populate initial edge weights
    for u, v, w in edges:
        dist[u][v] = w

    # Step 3: Floyd-Warshall core logic
    for k in vertices:
        for i in vertices:
            for j in vertices:
                # If going through k offers a shorter path, update it
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    return dist


# ------------------ Test Cases ------------------

def run_tests():
    print("Running Floyd-Warshall test cases...\n")

    # Test Case 1: Basic graph
    vertices1 = ['A', 'B', 'C']
    edges1 = [
        ('A', 'B', 4),
        ('B', 'C', 1),
        ('A', 'C', 10)
    ]
    print("Test Case 1:")
    print(floyd_warshall(vertices1, edges1), "\n")

    # Test Case 2: Graph with negative weights
    vertices2 = ['X', 'Y', 'Z']
    edges2 = [
        ('X', 'Y', 3),
        ('Y', 'Z', -2),
        ('Z', 'X', 5)
    ]
    print("Test Case 2:")
    print(floyd_warshall(vertices2, edges2), "\n")

    # Test Case 3: Disconnected graph
    vertices3 = ['P', 'Q', 'R']
    edges3 = [
        ('P', 'Q', 7)
    ]
    print("Test Case 3:")
    print(floyd_warshall(vertices3, edges3), "\n")

    # Test Case 4: Invalid edge vertex
    try:
        print("Test Case 4:")
        floyd_warshall(['A', 'B'], [('A', 'C', 2)])
    except ValueError as e:
        print("Exception caught -", e, "\n")

    # Test Case 5: Empty vertex list
    try:
        print("Test Case 5:")
        floyd_warshall([], [('A', 'B', 1)])
    except ValueError as e:
        print("Exception caught -", e, "\n")


if __name__ == "__main__":
    run_tests()
