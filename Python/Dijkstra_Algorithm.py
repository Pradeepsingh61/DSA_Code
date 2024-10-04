import heapq

# Dijkstra's Algorithm function
def dijkstra(graph, start):
    # Number of nodes
    n = len(graph)
    
    # Initialize distances with infinity
    distances = {node: float('inf') for node in graph}
    
    # Distance to the start node is 0
    distances[start] = 0
    
    # Priority queue to hold (distance, node)
    priority_queue = [(0, start)]
    
    # Process nodes
    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)
        
        # Skip if the current distance is greater than the known distance
        if current_distance > distances[current_node]:
            continue
        
        # Check neighbors of the current node
        for neighbor, weight in graph[current_node]:
            distance = current_distance + weight
            
            # Only consider this path if it's better
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))
    
    return distances

# Example graph represented as an adjacency list
graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('A', 1), ('C', 2), ('D', 5)],
    'C': [('A', 4), ('B', 2), ('D', 1)],
    'D': [('B', 5), ('C', 1)]
}

# Call the Dijkstra's function
start_node = 'A'
distances = dijkstra(graph, start_node)

# Print the shortest path distances from the start node
print(f"Shortest distances from {start_node}:")
for node, distance in distances.items():
    print(f"{node}: {distance}")
