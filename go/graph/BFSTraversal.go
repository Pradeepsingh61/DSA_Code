// BFSTraversal.go
//
// Breadth-First Search (BFS) Traversal - Numeric Node IDs
//
// Description:
//   BFS is a graph traversal algorithm that visits vertices in increasing
//   order of their distance (number of edges) from a chosen start vertex.
//   It uses a queue (FIFO) to explore the graph layer-by-layer. BFS is the
//   canonical way to compute shortest path distances (in edges) in an
//   unweighted graph and to enumerate nodes by level.
//
// Purpose / Use cases:
//   - Compute the order in which nodes are visited (level-order traversal).
//   - Find shortest paths in unweighted graphs (by edge count).
//   - Discover connected components or check reachability.
//   - Useful in many graph problems: bipartiteness test, shortest path in
//     unweighted graphs, minimum number of moves in puzzles, etc.
//
// Approach / Methodology:
//   - Represent an undirected graph with an adjacency list map[int][]int.
//   - Maintain a visited set and a queue of nodes to process.
//   - Start from the source node: mark visited, enqueue it, then repeatedly
//     dequeue a node, visit it, and enqueue all its unvisited neighbors.
//   - The order nodes are dequeued is the BFS visit order (layer-by-layer).
//
// Complexity Analysis:
//   - Time complexity: O(V + E)
//       where V = number of vertices and E = number of edges. Each vertex is
//       enqueued/dequeued at most once and each edge is examined once.
//   - Space complexity: O(V)
//       for the visited set and the queue (in worst case the queue can hold O(V)).
//
// File contents:
//   - Graph type and methods (AddEdge, AddNode).
//   - BFS function that returns visit order (slice of ints) or nil if start missing.
//   - Simple test harness with deterministic small numeric graphs and pass/fail checks.
//   - Tests now print the BFS visit order for each case.
//
// Author: (your name)
// Date:   (optional)

package main

import (
	"fmt"
	"os"
	"strconv"
)

// Graph represents an undirected graph with integer node IDs.
type Graph struct {
	adj map[int][]int // adjacency list: node -> list of neighbors
}

// NewGraph creates and returns an empty Graph.
func NewGraph() *Graph {
	return &Graph{adj: make(map[int][]int)}
}

// AddNode ensures a node entry exists in the adjacency map.
// It's safe to call this before adding edges if you want isolated nodes.
func (g *Graph) AddNode(id int) {
	if _, ok := g.adj[id]; !ok {
		g.adj[id] = []int{}
	}
}

// AddEdge adds an undirected edge between a and b.
// If nodes don't exist yet they are created automatically.
// The order of AddEdge calls determines neighbor order and therefore
// BFS deterministic visit order for the same insertion order.
func (g *Graph) AddEdge(a, b int) {
	g.adj[a] = append(g.adj[a], b)
	g.adj[b] = append(g.adj[b], a)
}

// BFS runs breadth-first search starting from `start`.
// Returns a slice with the visit order (nodes in the order they were dequeued).
// If the start node is not present in the graph, BFS returns nil.
//
// Time complexity: O(V + E)
// Space complexity: O(V)
func (g *Graph) BFS(start int) []int {
	// If the start node is not present, return nil to indicate an invalid start.
	if _, ok := g.adj[start]; !ok {
		return nil
	}

	visited := make(map[int]bool, len(g.adj)) // tracks visited nodes
	queue := make([]int, 0, len(g.adj))        // queue implemented as a slice
	head := 0                                  // index of current head in queue

	// Initialize BFS
	visited[start] = true
	queue = append(queue, start)

	visitOrder := make([]int, 0, len(g.adj))

	// Process queue until empty
	for head < len(queue) {
		cur := queue[head]
		head++
		visitOrder = append(visitOrder, cur)

		// Visit neighbors in the order they were added.
		for _, nb := range g.adj[cur] {
			if !visited[nb] {
				visited[nb] = true
				queue = append(queue, nb)
			}
		}
	}

	return visitOrder
}

// compareSlices checks equality of two integer slices.
func compareSlices(a, b []int) bool {
	if a == nil && b == nil {
		return true
	}
	if (a == nil) != (b == nil) {
		return false
	}
	if len(a) != len(b) {
		return false
	}
	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

// expect checks the BFS output against expected result and prints pass/fail.
func expect(got, expected []int, testName string) {
	// Always print the BFS order to make results explicit.
	fmt.Printf("%s - BFS order: %v\n", testName, got)
	if compareSlices(got, expected) {
		fmt.Printf("[PASS] %s\n\n", testName)
	} else {
		fmt.Printf("[FAIL] %s\n", testName)
		fmt.Printf("  Got     : %v\n", got)
		fmt.Printf("  Expected: %v\n\n", expected)
	}
}

// runTests builds small numeric graphs and runs compact, deterministic tests.
// These tests are focused only on BFS visit order (the requirement you stated).
func runTests() {
	fmt.Println("BFS Traversal Tests (numeric nodes)\n")

	// Graph G:
	// 1 - 2 - 4
	// |
	// 3 - 5 - 6
	//
	// (Edges are added in order to make BFS deterministic for the tests)
	g := NewGraph()
	g.AddEdge(1, 2) // neighbors: 1:[2], 2:[1]
	g.AddEdge(1, 3) // 1:[2,3], 3:[1]
	g.AddEdge(2, 4) // 2:[1,4], 4:[2]
	g.AddEdge(3, 5) // 3:[1,5], 5:[3]
	g.AddEdge(5, 6) // 5:[3,6], 6:[5]
	// Add isolated node 7 (no edges)
	g.AddNode(7)

	// Test 1: start = 1 (connected component)
	// Expected BFS order:
	// 1,2,3,4,5,6
	expected1 := []int{1, 2, 3, 4, 5, 6}
	got1 := g.BFS(1)
	expect(got1, expected1, "Test 1: start=1 (connected)")

	// Test 2: start = 3 (middle node)
	// Expected order: 3,1,5,2,6,4
	expected2 := []int{3, 1, 5, 2, 6, 4}
	got2 := g.BFS(3)
	expect(got2, expected2, "Test 2: start=3 (middle node)")

	// Test 3: isolated node start = 7
	// Node 7 exists but is isolated => visit order [7]
	expected3 := []int{7}
	got3 := g.BFS(7)
	expect(got3, expected3, "Test 3: start=7 (isolated node)")

	// Test 4: start missing => nil returned
	got4 := g.BFS(99)
	expect(got4, nil, "Test 4: start missing (99) => nil")

	// Test 5: empty graph => start not present => nil
	empty := NewGraph()
	got5 := empty.BFS(1)
	expect(got5, nil, "Test 5: empty graph => start not found")

	fmt.Println("Tests completed.")
}

// main: runs tests by default. If first CLI argument is present and is an integer,
// builds the sample graph and runs BFS starting from that node, printing only the visit order.
func main() {
	// If CLI arg provided, run BFS interactively on the sample graph and print the visit order.
	if len(os.Args) > 1 {
		startStr := os.Args[1]
		start, err := strconv.Atoi(startStr)
		if err != nil {
			fmt.Printf("Invalid start node: %q. Provide integer node id.\n", startStr)
			return
		}
		// Build the same small sample graph used in tests:
		g := NewGraph()
		g.AddEdge(1, 2)
		g.AddEdge(1, 3)
		g.AddEdge(2, 4)
		g.AddEdge(3, 5)
		g.AddEdge(5, 6)
		g.AddNode(7)

		order := g.BFS(start)
		if order == nil {
			fmt.Printf("Start node %d not found in graph\n", start)
			return
		}
		// Print the BFS visit order explicitly for interactive runs.
		fmt.Printf("BFS visit order from %d: %v\n", start, order)
		return
	}

	// No CLI arg: run the compact test suite.
	runTests()
}
