""""
Purpose: Finds the shortest paths between all pairs of vertices in a weighted graph (can handle negative weights but no negative cycles)."""
# Floyd-Warshall Algorithm in Python
# Function to implement Floyd-Warshall Algorithm
def floyd_warshall(graph):
    """
    graph: 2D list of edge weights (adjacency matrix)
           graph[i][j] = weight of edge from i to j, or float('inf') if no edge
    Returns: 2D list with shortest distances between all pairs
    """
    # Number of vertices
    V = len(graph)
    
    # Initialize distance matrix same as graph
    dist = [list(row) for row in graph]  # deep copy

    # Add all vertices one by one as intermediate vertices
    for k in range(V):
        for i in range(V):
            for j in range(V):
                # Update dist[i][j] if going through k is shorter
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    
    return dist

# Utility function to print the distance matrix
def print_matrix(dist):
    V = len(dist)
    print("Shortest distances between every pair of vertices:")
    for i in range(V):
        for j in range(V):
            if dist[i][j] == float('inf'):
                print("INF", end="\t")
            else:
                print(dist[i][j], end="\t")
        print()

# Main function
if __name__ == "__main__":
    # Example graph represented as adjacency matrix
    INF = float('inf')
    graph = [
        [0, 3, INF, 5],
        [2, 0, INF, 4],
        [INF, 1, 0, INF],
        [INF, INF, 2, 0]
    ]

    # Compute shortest paths
    shortest_distances = floyd_warshall(graph)
    
    # Print the result
    print_matrix(shortest_distances)
