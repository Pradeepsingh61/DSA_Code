# Given a directed graph with n vertices and m edges, determine and print the maximum absolute difference between the in-degree and out-degree of any vertex in the graph.

# The first line contains two integers, n and m, representing the number of vertices and the number of directed edges respectively.
# The next m lines each contain two integers u and v, representing a directed edge from vertex u to vertex v.


def maxAbsoluteDegreeDiff(n, edgeList):
    indegree = [0] * n
    outdegree = [0] * n
        for u, v in edgeList:
        outdegree[u] += 1
        indegree[v] += 1
        max_diff = 0
    for i in range(n):
        max_diff = max(max_diff, abs(indegree[i] - outdegree[i]))
    
    return max_diff





Input
4 4
0 1  
0 2  
1 2  
2 3

Output
2

Let's compute the in-degree and out-degree for each vertex:
Vertex 0 → out: 2 (to 1, 2), in: 0 → |0 − 2| = 2
Vertex 1 → out: 1 (to 2), in: 1 (from 0) → |1 − 1| = 0
Vertex 2 → out: 1 (to 3), in: 2 (from 0, 1) → |2 − 1| = 1
Vertex 3 → out: 0, in: 1 (from 2) → |1 − 0| = 1
The maximum value is 2 (from Vertex 0).