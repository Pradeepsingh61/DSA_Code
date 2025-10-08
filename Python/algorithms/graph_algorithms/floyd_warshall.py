# 📌 Floyd-Warshall Algorithm
# Language: Python
# Category: Graph Algorithms
# Time Complexity: O(V^3)
# Space Complexity: O(V^2)

"""
Floyd-Warshall Algorithm is an algorithm for finding shortest paths in a directed weighted graph
with positive or negative edge weights (but with no negative cycles).

It computes shortest paths between all pairs of nodes in a single pass.
"""

import math

def floyd_warshall(graph):
    """
    Computes the shortest paths between all pairs of nodes in a graph using the Floyd-Warshall algorithm.

    :param graph: A 2D list (matrix) representing the adjacency matrix of the graph.
                  graph[i][j] is the weight of the edge from node i to node j.
                  If there is no edge, the value should be math.inf.
                  Self-loops (i to i) should be 0.
    :return: A 2D list (matrix) where dist[i][j] is the shortest distance from node i to node j.
    """
    num_vertices = len(graph)
    dist = list(map(lambda i: list(map(lambda j: j, i)), graph)) # Initialize dist with the graph itself

    # Add all vertices one by one to the set of intermediate vertices.
    # Before the start of an iteration, shortest distances between all pairs
    # of vertices is calculated using vertices from 0 to k-1 as intermediate vertices.
    # After the end of a iteration, vertex k is added to the set of intermediate vertices
    # and the set becomes {0, 1, .. k}.
    for k in range(num_vertices):
        # Pick all vertices as source one by one
        for i in range(num_vertices):
            # Pick all vertices as destination for the above picked source
            for j in range(num_vertices):
                # If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    return dist

# 🧪 Example usage
if __name__ == "__main__":
    # Example 1: Graph with 4 vertices
    # Representing infinity with math.inf
    INF = math.inf
    graph1 = [
        [0, 5, INF, 10],
        [INF, 0, 3, INF],
        [INF, INF, 0, 1],
        [INF, INF, INF, 0]
    ]
    print("Graph 1:")
    for row in graph1:
        print(row)

    shortest_paths1 = floyd_warshall(graph1)
    print("\nShortest paths for Graph 1:")
    for row in shortest_paths1:
        print([round(x, 2) if x != INF else 'INF' for x in row])

    # Expected output for Graph 1:
    # [0, 5, 8, 9]
    # [INF, 0, 3, 4]
    # [INF, INF, 0, 1]
    # [INF, INF, INF, 0]

    # Example 2: Graph with negative weights (no negative cycles)
    graph2 = [
        [0, 1, INF, INF],
        [INF, 0, -1, INF],
        [INF, INF, 0, -1],
        [-1, INF, INF, 0]
    ]
    print("\nGraph 2:")
    for row in graph2:
        print(row)

    shortest_paths2 = floyd_warshall(graph2)
    print("\nShortest paths for Graph 2:")
    for row in shortest_paths2:
        print([round(x, 2) if x != INF else 'INF' for x in row])

    # Expected output for Graph 2:
    # [0, 1, 0, -1]
    # [-1, 0, -1, -2]
    # [-2, -1, 0, -1]
    # [-1, 0, -1, 0]

    # Example 3: Graph with 2 vertices
    graph3 = [
        [0, 10],
        [5, 0]
    ]
    print("\nGraph 3:")
    for row in graph3:
        print(row)

    shortest_paths3 = floyd_warshall(graph3)
    print("\nShortest paths for Graph 3:")
    for row in shortest_paths3:
        print([round(x, 2) if x != INF else 'INF' for x in row])

    # Expected output for Graph 3:
    # [0, 10]
    # [5, 0]