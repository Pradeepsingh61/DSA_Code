// DFSTraversal.go
//
// Depth-First Search (DFS) Traversal - Numeric Node IDs
//
// Description:
//   DFS is a graph traversal algorithm that explores as far as possible
//   along each branch before backtracking. This implementation uses recursion
//   and returns nodes in preorder (the order they are first discovered).
//
// Purpose / Use cases:
//   - Enumerate nodes by depth-first order.
//   - Detect cycles, compute connected components, topological sorts (with mods).
//   - Useful in search problems, path finding (not shortest by edges), etc.
//
// Approach / Methodology:
//   - Represent an undirected graph with an adjacency list map[int][]int.
//   - Maintain a visited set and recursively visit neighbors in insertion order.
//   - The order nodes are appended when first visited is the DFS visit order.
//
// Complexity Analysis:
//   - Time complexity: O(V + E)
//   - Space complexity: O(V) for visited set + recursion stack (worst-case O(V)).
//
// File contents:
//   - Graph type and methods (AddEdge, AddNode).
//   - DFS function that returns visit order (slice of ints) or nil if start missing.
//   - Simple test harness with deterministic small numeric graphs and pass/fail checks.
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
// DFS deterministic visit order for the same insertion order.
func (g *Graph) AddEdge(a, b int) {
	g.adj[a] = append(g.adj[a], b)
	g.adj[b] = append(g.adj[b], a)
}

// DFS runs depth-first search starting from `start` (preorder).
// Returns a slice with the visit order (nodes in the order first discovered).
// If the start node is not present in the graph, DFS returns nil.
//
// Time complexity: O(V + E)
// Space complexity: O(V)
func (g *Graph) DFS(start int) []int {
	// If the start node is not present, return nil to indicate an invalid start.
	if _, ok := g.adj[start]; !ok {
		return nil
	}

	visited := make(map[int]bool, len(g.adj))
	visitOrder := make([]int, 0, len(g.adj))

	var dfsRec func(int)
	dfsRec = func(u int) {
		visited[u] = true
		visitOrder = append(visitOrder, u)
		for _, nb := range g.adj[u] {
			if !visited[nb] {
				dfsRec(nb)
			}
		}
	}

	dfsRec(start)
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

// expect checks the DFS output against expected result and prints pass/fail.
func expect(got, expected []int, testName string) {
	// Always print the DFS order to make results explicit.
	fmt.Printf("%s - DFS order: %v\n", testName, got)
	if compareSlices(got, expected) {
		fmt.Printf("[PASS] %s\n\n", testName)
	} else {
		fmt.Printf("[FAIL] %s\n", testName)
		fmt.Printf("  Got     : %v\n", got)
		fmt.Printf("  Expected: %v\n\n", expected)
	}
}

// runTests builds small numeric graphs and runs compact, deterministic tests.
func runTests() {
	fmt.Println("DFS Traversal Tests (numeric nodes)\n")

	// Graph G:
	// 1 - 2 - 4
	// |
	// 3 - 5 - 6
	//
	// (Edges are added in order to make DFS deterministic for the tests)
	g := NewGraph()
	g.AddEdge(1, 2) // neighbors: 1:[2], 2:[1]
	g.AddEdge(1, 3) // 1:[2,3], 3:[1]
	g.AddEdge(2, 4) // 2:[1,4], 4:[2]
	g.AddEdge(3, 5) // 3:[1,5], 5:[3]
	g.AddEdge(5, 6) // 5:[3,6], 6:[5]
	// Add isolated node 7 (no edges)
	g.AddNode(7)

	// Test 1: start = 1 (connected component)
	// Expected DFS preorder:
	// 1,2,4,3,5,6
	expected1 := []int{1, 2, 4, 3, 5, 6}
	got1 := g.DFS(1)
	expect(got1, expected1, "Test 1: start=1 (connected)")

	// Test 2: start = 3 (middle node)
	// Expected order: 3,1,2,4,5,6
	expected2 := []int{3, 1, 2, 4, 5, 6}
	got2 := g.DFS(3)
	expect(got2, expected2, "Test 2: start=3 (middle node)")

	// Test 3: isolated node start = 7
	// Node 7 exists but is isolated => visit order [7]
	expected3 := []int{7}
	got3 := g.DFS(7)
	expect(got3, expected3, "Test 3: start=7 (isolated node)")

	// Test 4: start missing => nil returned
	got4 := g.DFS(99)
	expect(got4, nil, "Test 4: start missing (99) => nil")

	// Test 5: empty graph => start not present => nil
	empty := NewGraph()
	got5 := empty.DFS(1)
	expect(got5, nil, "Test 5: empty graph => start not found")

	fmt.Println("Tests completed.")
}

// main: runs tests by default. If first CLI argument is present and is an integer,
// builds the sample graph and runs DFS starting from that node, printing only the visit order.
func main() {
	// If CLI arg provided, run DFS interactively on the sample graph and print the visit order.
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

		order := g.DFS(start)
		if order == nil {
			fmt.Printf("Start node %d not found in graph\n", start)
			return
		}
		// Print the DFS visit order explicitly for interactive runs.
		fmt.Printf("DFS visit order from %d: %v\n", start, order)
		return
	}

	// No CLI arg: run the compact test suite.
	runTests()
}
