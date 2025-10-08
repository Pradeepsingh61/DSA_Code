"""
Topological Sort (DFS-based)
----------------------------
Description:
    Performs topological sorting on a Directed Acyclic Graph (DAG) using Depth-First Search.
    Returns a linear ordering of vertices such that for every directed edge u → v, u comes before v.

Algorithm:
    - Build an adjacency list from the edge list.
    - Use DFS to explore each node.
    - After visiting all descendants, push the node onto a stack.
    - Reverse the stack to get the topological order.

Time Complexity: O(V + E)
Space Complexity: O(V)

"""

def topological_sort(vertices, edges):
    # Validate that vertex list is not empty
    if not vertices:
        raise ValueError("Vertex list is empty.")

    # Validate that all edge endpoints exist in the graph
    for u, v in edges:
        if u not in vertices or v not in vertices:
            raise ValueError(f"Edge contains undefined vertex: ({u}, {v})")

    # Step 1: Build adjacency list
    adj = {v: [] for v in vertices}
    for u, v in edges:
        adj[u].append(v)

    visited = set()
    stack = []

    # Step 2: Depth-First Search helper
    def dfs(node):
        visited.add(node)
        for neighbor in adj[node]:
            if neighbor not in visited:
                dfs(neighbor)
        stack.append(node)  # Post-order push

    # Step 3: Perform DFS from all unvisited nodes
    for v in vertices:
        if v not in visited:
            dfs(v)

    return stack[::-1]  # Reverse to get topological order


# ------------------ Test Cases ------------------

def run_tests():
    print("Running Topological Sort test cases...\n")

    # Test Case 1: Simple DAG
    vertices1 = ['A', 'B', 'C', 'D']
    edges1 = [('A', 'B'), ('B', 'C'), ('A', 'C'), ('C', 'D')]
    print("Test Case 1:")
    print(topological_sort(vertices1, edges1), "\n")

    # Test Case 2: DAG with branching
    vertices2 = ['X', 'Y', 'Z', 'W']
    edges2 = [('X', 'Y'), ('X', 'Z'), ('Y', 'W'), ('Z', 'W')]
    print("Test Case 2:")
    print(topological_sort(vertices2, edges2), "\n")

    # Test Case 3: Disconnected DAG
    vertices3 = ['P', 'Q', 'R', 'S']
    edges3 = [('P', 'Q'), ('R', 'S')]
    print("Test Case 3:")
    print(topological_sort(vertices3, edges3), "\n")

    # Test Case 4: Empty graph
    vertices4 = []
    edges4 = []
    try:
        print("Test Case 4:")
        topological_sort(vertices4, edges4)
    except ValueError as e:
        print("Exception caught -", e, "\n")

    # Test Case 5: Invalid edge vertex
    try:
        print("Test Case 5:")
        topological_sort(['A', 'B'], [('A', 'C')])
    except ValueError as e:
        print("Exception caught -", e, "\n")


if __name__ == "__main__":
    run_tests()
