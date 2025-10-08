// BellmanFord.go
//
// Bellman-Ford Single-Source Shortest Paths (numeric node IDs)
//
// Description:
//   Bellman-Ford computes shortest path distances from a single source in a
//   weighted directed graph (weights may be negative). It also detects
//   negative-weight cycles reachable from the source.
//
// Notes:
//   - Edges are added as directed edges with AddEdge(u, v, w).
//     For undirected graphs, add both directions explicitly.
//   - If a negative-weight cycle reachable from `start` exists, the algorithm
//     reports it (returns negCycle=true) and distances/parents are not returned.
//
// Complexity:
//   - Time: O(V * E)
//   - Space: O(V + E)
//
// File contents:
//   - Graph type and methods (AddEdge, AddNode).
//   - BellmanFord(start) returning (dist, parent, negCycle).
//   - Test harness with Bellman-Ford-specific tests (negative edges, reachable
//     negative cycles, unreachable vertices, single node, etc.).

package main

import (
	"fmt"
	"os"
	"sort"
	"strconv"
)

// Edge represents a directed edge u -> v with weight.
type Edge struct {
	U, V  int
	Weight int
}

// Graph represents a directed weighted graph. Use AddEdge(u,v,w) to add a
// directed edge u -> v. For undirected graphs add both directions manually.
type Graph struct {
	adj   map[int][]Edge // adjacency list (for convenience)
	edges []Edge         // list of directed edges (used by Bellman-Ford)
}

// NewGraph constructs an empty graph.
func NewGraph() *Graph {
	return &Graph{
		adj:   make(map[int][]Edge),
		edges: []Edge{},
	}
}

// AddNode ensures a node exists in the adjacency map.
func (g *Graph) AddNode(id int) {
	if _, ok := g.adj[id]; !ok {
		g.adj[id] = []Edge{}
	}
}

// AddEdge adds a directed edge u -> v with weight w.
// If you want an undirected edge, call AddEdge(u,v,w) and AddEdge(v,u,w).
func (g *Graph) AddEdge(u, v, w int) {
	g.AddNode(u)
	g.AddNode(v)
	e := Edge{U: u, V: v, Weight: w}
	g.adj[u] = append(g.adj[u], e)
	g.edges = append(g.edges, e)
}

// Bellman-Ford computes shortest distances from `start`.
// Returns (dist, parent, negCycle).
//   - If start not present => (nil, nil, false).
//   - If negCycle==true => a negative cycle reachable from start exists;
//     in that case dist and parent are nil because distances are undefined.
func (g *Graph) BellmanFord(start int) (map[int]int, map[int]int, bool) {
	// start must exist
	if _, ok := g.adj[start]; !ok {
		return nil, nil, false
	}

	// Build nodes list
	nodes := make([]int, 0, len(g.adj))
	for n := range g.adj {
		nodes = append(nodes, n)
	}
	// Sort nodes to make iteration deterministic for tests/printing
	sort.Ints(nodes)

	// INF chosen as a safe fraction of MaxInt to avoid overflow on additions.
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	// Initialize distances and parents
	dist := make(map[int]int, len(g.adj))
	parent := make(map[int]int, len(g.adj))
	for _, n := range nodes {
		dist[n] = INF
		parent[n] = -1 // -1 means no predecessor
	}
	dist[start] = 0

	V := len(nodes)

	// Relax edges V-1 times
	for i := 0; i < V-1; i++ {
		changed := false
		for _, e := range g.edges {
			if dist[e.U] != INF && dist[e.U]+e.Weight < dist[e.V] {
				dist[e.V] = dist[e.U] + e.Weight
				parent[e.V] = e.U
				changed = true
			}
		}
		// optimization: if no change on this pass, break early
		if !changed {
			break
		}
	}

	// Check for negative-weight cycles reachable from start
	for _, e := range g.edges {
		if dist[e.U] != INF && dist[e.U]+e.Weight < dist[e.V] {
			// negative cycle reachable
			return nil, nil, true
		}
	}

	return dist, parent, false
}

// Helper: reconstruct path from start to target using parent map.
// Returns nil if target unreachable (parent chain ends at -1 and target != start).
func reconstructPath(parent map[int]int, start, target int) []int {
	path := []int{}
	cur := target
	for cur != -1 {
		path = append([]int{cur}, path...)
		if cur == start {
			return path
		}
		cur = parent[cur]
	}
	// didn't reach start => unreachable
	return nil
}

// compareDistances compares two distance maps, treating INF equivalently.
// expected may be nil to indicate Bellman-Ford should have returned nil (e.g., start missing).
func compareDistances(got, expected map[int]int, INF int) bool {
	if got == nil && expected == nil {
		return true
	}
	if (got == nil) != (expected == nil) {
		return false
	}
	if len(got) != len(expected) {
		return false
	}
	for k, ev := range expected {
		gv, ok := got[k]
		if !ok {
			return false
		}
		if ev == INF {
			if gv != INF {
				return false
			}
		} else {
			if gv != ev {
				return false
			}
		}
	}
	return true
}

// pretty print distances (prints INF for unreachable nodes).
func printDistParent(dist, parent map[int]int) {
	// compute INF as before
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	if dist == nil {
		fmt.Println("Distances: nil")
		fmt.Println("Parents  : nil")
		return
	}
	// Collect and sort node ids for deterministic output
	nodes := make([]int, 0, len(dist))
	for n := range dist {
		nodes = append(nodes, n)
	}
	sort.Ints(nodes)
	fmt.Println("Node  Distance  Parent")
	for _, n := range nodes {
		d := dist[n]
		p := parent[n]
		ds := ""
		if d == INF {
			ds = "INF"
		} else {
			ds = fmt.Sprintf("%d", d)
		}
		ps := "-"
		if p != -1 {
			ps = fmt.Sprintf("%d", p)
		}
		fmt.Printf("%4d  %8s  %6s\n", n, ds, ps)
	}
}

// run tests specially chosen for Bellman-Ford behavior.
func runTests() {
	fmt.Println("Bellman-Ford Tests (directed edges) — printing results for each test\n")

	// Precompute INF for test expectations
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	// ---------- Test 1: simple DAG / positive weights ----------
	// Graph:
	// 1 -> 2 (4)
	// 1 -> 3 (2)
	// 2 -> 3 (3)
	// 2 -> 4 (2)
	// 3 -> 2 (1)
	// 3 -> 4 (7)
	// Expected shortest distances from 1:
	// 1:0, 2:3 (1->3->2), 3:2, 4:5 (1->3->2->4)
	g1 := NewGraph()
	g1.AddEdge(1, 2, 4)
	g1.AddEdge(1, 3, 2)
	g1.AddEdge(2, 3, 3)
	g1.AddEdge(2, 4, 2)
	g1.AddEdge(3, 2, 1)
	g1.AddEdge(3, 4, 7)

	expected1 := map[int]int{
		1: 0,
		2: 3,
		3: 2,
		4: 5,
	}

	dist1, parent1, neg1 := g1.BellmanFord(1)
	fmt.Println("Test 1: simple positive/zero-negative-free graph")
	if neg1 {
		fmt.Println("  [FAIL] Unexpected negative cycle detected")
	} else {
		printDistParent(dist1, parent1)
	}
	// verify distances
	if !neg1 && compareDistances(dist1, expected1, INF) {
		fmt.Println("[PASS] Test 1\n")
	} else {
		fmt.Println("[FAIL] Test 1 (distances mismatch)\n")
	}

	// ---------- Test 2: negative edge but no negative cycle ----------
	// Graph:
	// 1 -> 2 (6)
	// 1 -> 3 (7)
	// 2 -> 3 (8)
	// 2 -> 4 (5)
	// 2 -> 5 (-4)
	// 3 -> 4 (-3)
	// 4 -> 2 (-2)
	// 5 -> 4 (9)
	// This classic example has negative edges but no negative cycle reachable from 1.
	// Expected shortest distances from 1:
	// 1:0, 2:2 (1->3->4->2: 7 + -3 + -2 = 2), 3:7, 4:4, 5:-2
	g2 := NewGraph()
	g2.AddEdge(1, 2, 6)
	g2.AddEdge(1, 3, 7)
	g2.AddEdge(2, 3, 8)
	g2.AddEdge(2, 4, 5)
	g2.AddEdge(2, 5, -4)
	g2.AddEdge(3, 4, -3)
	g2.AddEdge(4, 2, -2)
	g2.AddEdge(5, 4, 9)

	expected2 := map[int]int{
		1:  0,
		2:  2,
		3:  7,
		4:  4,
		5: -2,
	}

	dist2, parent2, neg2 := g2.BellmanFord(1)
	fmt.Println("Test 2: negative edges but no negative cycle (classic example)")
	if neg2 {
		fmt.Println("  [FAIL] Unexpected negative cycle detected")
	} else {
		printDistParent(dist2, parent2)
		// show example path reconstruction: path from 1 to 5
		path15 := reconstructPath(parent2, 1, 5)
		fmt.Printf("Example path 1 -> 5: %v\n", path15)
	}
	if !neg2 && compareDistances(dist2, expected2, INF) {
		fmt.Println("[PASS] Test 2\n")
	} else {
		fmt.Println("[FAIL] Test 2 (distances mismatch)\n")
	}

	// ---------- Test 3: negative cycle reachable from start ----------
	// Graph:
	// 1 -> 2 (1)
	// 2 -> 3 (-2)
	// 3 -> 1 (-2)  // cycle weight = -3
	// 3 -> 4 (2)
	// Start at 1 -> negative cycle reachable, algorithm should detect it.
	g3 := NewGraph()
	g3.AddEdge(1, 2, 1)
	g3.AddEdge(2, 3, -2)
	g3.AddEdge(3, 1, -2)
	g3.AddEdge(3, 4, 2)

	dist3, parent3, neg3 := g3.BellmanFord(1)
	fmt.Println("Test 3: negative-weight cycle reachable from start")
	if neg3 {
		fmt.Println("  Negative cycle detected reachable from start -> distances undefined")
		fmt.Println("[PASS] Test 3 (negative cycle correctly detected)\n")
	} else {
		fmt.Println("  [FAIL] Did not detect expected negative cycle")
		printDistParent(dist3, parent3)
		fmt.Println("[FAIL] Test 3\n")
	}

	// ---------- Test 4: disconnected graph / unreachable nodes ----------
	// Graph:
	// 1 -> 2 (3)
	// 2 -> 3 (4)
	// Node 4 exists but is isolated
	g4 := NewGraph()
	g4.AddEdge(1, 2, 3)
	g4.AddEdge(2, 3, 4)
	g4.AddNode(4) // isolated node

	expected4 := map[int]int{
		1: 0,
		2: 3,
		3: 7,
		4: INF, // unreachable
	}

	dist4, parent4, neg4 := g4.BellmanFord(1)
	fmt.Println("Test 4: disconnected graph (unreachable vertices)")
	if neg4 {
		fmt.Println("  [FAIL] Unexpected negative cycle detected")
	} else {
		printDistParent(dist4, parent4)
	}
	if !neg4 && compareDistances(dist4, expected4, INF) {
		fmt.Println("[PASS] Test 4\n")
	} else {
		fmt.Println("[FAIL] Test 4 (distances mismatch)\n")
	}

	// ---------- Test 5: single node ----------
	g5 := NewGraph()
	g5.AddNode(42)
	expected5 := map[int]int{
		42: 0,
	}
	dist5, parent5, neg5 := g5.BellmanFord(42)
	fmt.Println("Test 5: single isolated node (start is the node itself)")
	if neg5 {
		fmt.Println("  [FAIL] Unexpected negative cycle")
	} else {
		printDistParent(dist5, parent5)
	}
	if !neg5 && compareDistances(dist5, expected5, INF) {
		fmt.Println("[PASS] Test 5\n")
	} else {
		fmt.Println("[FAIL] Test 5 (distances mismatch)\n")
	}

	// ---------- Test 6: start missing ----------
	// Run Bellman-Ford with a start node that does not exist in the graph.
	g6 := NewGraph()
	g6.AddEdge(1, 2, 5)
	dist6, parent6, neg6 := g6.BellmanFord(99)
	fmt.Println("Test 6: start missing (should return nil, nil, false)")
	if dist6 == nil && parent6 == nil && !neg6 {
		fmt.Println("[PASS] Test 6\n")
	} else {
		fmt.Println("[FAIL] Test 6\n")
	}

	fmt.Println("Bellman-Ford tests completed.")
}

// main: if CLI arg provided, run Bellman-Ford on a sample graph and print results.
// Otherwise run the test suite.
func main() {
	// Sample graph for CLI demonstration (same as Test 2)
	if len(os.Args) > 1 {
		startStr := os.Args[1]
		start, err := strconv.Atoi(startStr)
		if err != nil {
			fmt.Printf("Invalid start node: %q. Provide integer node id.\n", startStr)
			return
		}
		g := NewGraph()
		g.AddEdge(1, 2, 6)
		g.AddEdge(1, 3, 7)
		g.AddEdge(2, 3, 8)
		g.AddEdge(2, 4, 5)
		g.AddEdge(2, 5, -4)
		g.AddEdge(3, 4, -3)
		g.AddEdge(4, 2, -2)
		g.AddEdge(5, 4, 9)

		dist, parent, neg := g.BellmanFord(start)
		fmt.Printf("Bellman-Ford from %d:\n", start)
		if neg {
			fmt.Println("Negative cycle reachable from start -> distances undefined")
			return
		}
		printDistParent(dist, parent)

		// Example: reconstruct path to node 5 (if reachable)
		path := reconstructPath(parent, start, 5)
		if path == nil {
			fmt.Printf("No path from %d to %d\n", start, 5)
		} else {
			fmt.Printf("Path %d -> %d: %v\n", start, 5, path)
		}
		return
	}

	// No CLI args: run tests
	runTests()
}
