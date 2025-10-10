// TopologicalSort.go
//
// Topological Sort (Kahn’s Algorithm)
//
// Description:
//   This program implements Topological Sorting using Kahn’s Algorithm.
//   It finds a valid linear ordering of vertices in a Directed Acyclic Graph (DAG)
//   such that for every directed edge u → v, vertex u comes before v in the ordering.
//
// Purpose / Use cases:
//   - Used for dependency resolution (e.g., build systems, course scheduling).
//   - Works only on Directed Acyclic Graphs (DAG).
//
// Approach / Methodology:
//   - Compute indegree for every vertex.
//   - Use a queue to repeatedly remove nodes with indegree 0 and
//     reduce indegree of their neighbors.
//   - If all nodes are processed, the graph is acyclic.
//   - If not, it contains a cycle.
//
// Complexity Analysis:
//   - Time: O(V + E)
//   - Space: O(V + E)
//
// File contents:
//   - Graph struct and methods.
//   - TopologicalSort() function implementing Kahn’s Algorithm.
//   - Example test in main() for validation.

package main

import (
	"fmt"
)

// Graph represents a directed graph using adjacency list.
type Graph struct {
	adj map[int][]int
}

// NewGraph creates an empty directed graph.
func NewGraph() *Graph {
	return &Graph{
		adj: make(map[int][]int),
	}
}

// AddEdge adds a directed edge from u → v.
func (g *Graph) AddEdge(u, v int) {
	g.adj[u] = append(g.adj[u], v)
	if _, exists := g.adj[v]; !exists {
		g.adj[v] = []int{}
	}
}

// TopologicalSort performs Kahn’s Algorithm to return a valid ordering.
// If the graph contains a cycle, returns an empty slice.
func (g *Graph) TopologicalSort() []int {
	indegree := make(map[int]int)
	for u := range g.adj {
		indegree[u] = 0
	}
	for _, neighbors := range g.adj {
		for _, v := range neighbors {
			indegree[v]++
		}
	}

	queue := []int{}
	for node, deg := range indegree {
		if deg == 0 {
			queue = append(queue, node)
		}
	}

	order := []int{}
	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		order = append(order, u)
		for _, v := range g.adj[u] {
			indegree[v]--
			if indegree[v] == 0 {
				queue = append(queue, v)
			}
		}
	}

	if len(order) != len(g.adj) {
		fmt.Println("Cycle detected — topological sort not possible.")
		return []int{}
	}
	return order
}

// main runs an example DAG to demonstrate Topological Sort.
func main() {
	fmt.Println("Topological Sort (Kahn’s Algorithm) Demo")

	g := NewGraph()
	g.AddEdge(5, 0)
	g.AddEdge(5, 2)
	g.AddEdge(4, 0)
	g.AddEdge(4, 1)
	g.AddEdge(2, 3)
	g.AddEdge(3, 1)

	order := g.TopologicalSort()
	fmt.Printf("Topological Order: %v\n", order)
}
