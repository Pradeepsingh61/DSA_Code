"""
Floyd Warshall Algorithm:

The Floyd Warshall algorithm finds the shortest distances between
every pair of vertices in a weighted graph (both directed and undirected).

Time Complexity: O(V^3)
Space Complexity: O(V^2)
"""

def floyd_warshall(graph):
    """
    graph: 2D list (adjacency matrix)
           graph[i][j] = weight from i → j or float('inf') if no edge.

    Returns: dist - 2D list of shortest path distances.
    """
    V = len(graph)
    dist = [row[:] for row in graph]

    for k in range(V):
        for i in range(V):
            for j in range(V):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    return dist


if __name__ == "__main__":
    INF = float('inf')
    graph = [
        [0, 3, INF, 5],
        [2, 0, INF, 4],
        [INF, 1, 0, INF],
        [INF, INF, 2, 0]
    ]

    result = floyd_warshall(graph)
    print("All-Pairs Shortest Paths:")
    for row in result:
        print(row)
