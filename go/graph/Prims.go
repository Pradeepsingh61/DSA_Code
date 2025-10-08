// PrimMST.go
//
// Prim's Algorithm - Minimum Spanning Tree (numeric node IDs)
//
// Description:
//   Prim's algorithm finds a minimum spanning tree (MST) of a connected,
//   undirected, weighted graph. This implementation uses a min-heap to pick
//   the smallest-weight edge crossing the cut and grows the MST until all
//   vertices are included (or determines the graph is disconnected).
//
// Purpose / Use cases:
//   - Compute MST and its total weight.
//   - Useful for network design, clustering approximations, etc.
//
// Approach / Methodology:
//   - Represent undirected weighted graph with adjacency list map[int][]Edge.
//   - Use a visited set and a min-heap of crossing edges (weight, u, v).
//   - Start from `start` node: push its edges, repeatedly pick smallest edge
//     connecting into unvisited node, add to MST, push new edges.
//   - If all nodes become visited, return MST edges & total weight; otherwise
//     return nil to indicate no spanning tree (disconnected graph).
//
// Complexity Analysis:
//   - Time: O(E log E) (or O(E log V) more precisely) due to heap operations.
//   - Space: O(E + V) for adjacency and heap.
//
// File contents:
//   - Graph type and methods (AddEdge, AddNode).
//   - Prim(start) returns []MEdge (MST edges) and total weight, or nil if not found.
//   - Tests print MST after each test and indicate pass/fail.
//
// Author: (your name)
// Date:   (optional)

package main

import (
	"container/heap"
	"fmt"
	"os"
	"sort"
	"strconv"
)

// MEdge represents an undirected weighted edge (u -- weight -- v).
type MEdge struct {
	U, V   int
	Weight int
}

// Graph represents an undirected weighted graph with integer node IDs.
type Graph struct {
	adj map[int][]MEdge // adjacency list: node -> list of edges (neighbors)
}

// NewGraph creates and returns an empty Graph.
func NewGraph() *Graph {
	return &Graph{adj: make(map[int][]MEdge)}
}

// AddNode ensures a node entry exists in the adjacency map.
func (g *Graph) AddNode(id int) {
	if _, ok := g.adj[id]; !ok {
		g.adj[id] = []MEdge{}
	}
}

// AddEdge adds an undirected weighted edge between a and b.
// If nodes don't exist yet they are created automatically.
// The order of AddEdge calls may influence deterministic tie-breaking.
func (g *Graph) AddEdge(a, b, w int) {
	g.AddNode(a)
	g.AddNode(b)
	g.adj[a] = append(g.adj[a], MEdge{U: a, V: b, Weight: w})
	g.adj[b] = append(g.adj[b], MEdge{U: b, V: a, Weight: w})
}

// -------- min-heap for crossing edges --------

// heapItem is stored in the priority queue. It keeps (weight, from, to)
// and we break ties deterministically by from then to.
type heapItem struct {
	weight int
	from   int
	to     int
}

// edgeHeap implements heap.Interface ordered by weight, then from, then to.
type edgeHeap []heapItem

func (h edgeHeap) Len() int { return len(h) }
func (h edgeHeap) Less(i, j int) bool {
	if h[i].weight != h[j].weight {
		return h[i].weight < h[j].weight
	}
	if h[i].from != h[j].from {
		return h[i].from < h[j].from
	}
	return h[i].to < h[j].to
}
func (h edgeHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }
func (h *edgeHeap) Push(x interface{}) {
	*h = append(*h, x.(heapItem))
}
func (h *edgeHeap) Pop() interface{} {
	old := *h
	n := len(old)
	it := old[n-1]
	*h = old[:n-1]
	return it
}

// -------- Prim's algorithm --------

// Prim runs Prim's algorithm starting from `start`.
// Returns (mstEdges, totalWeight).
// If start not present, or the graph is disconnected (no spanning tree), returns (nil, 0).
func (g *Graph) Prim(start int) ([]MEdge, int) {
	// start must exist
	if _, ok := g.adj[start]; !ok {
		return nil, 0
	}

	visited := make(map[int]bool, len(g.adj))
	h := &edgeHeap{}
	heap.Init(h)

	// helper: push all edges from node u to heap
	pushEdges := func(u int) {
		for _, e := range g.adj[u] {
			if !visited[e.V] {
				heap.Push(h, heapItem{weight: e.Weight, from: u, to: e.V})
			}
		}
	}

	visited[start] = true
	pushEdges(start)

	mst := make([]MEdge, 0, len(g.adj)-1)
	total := 0

	for h.Len() > 0 && len(visited) < len(g.adj) {
		it := heap.Pop(h).(heapItem)
		if visited[it.to] {
			continue
		}
		// take this edge into MST
		mst = append(mst, MEdge{U: it.from, V: it.to, Weight: it.weight})
		total += it.weight
		visited[it.to] = true
		pushEdges(it.to)
	}

	// Check if all nodes are visited (spanning tree exists)
	if len(visited) != len(g.adj) {
		return nil, 0
	}
	return mst, total
}

// -------- helpers for tests and comparison --------

// normalizeEdgeKey returns a canonical string key for an undirected edge+weight
// (min,max,weight) so we can compare MST edge sets ignoring order.
func normalizeEdgeKey(e MEdge) string {
	u, v := e.U, e.V
	if u > v {
		u, v = v, u
	}
	return fmt.Sprintf("%d-%d-%d", u, v, e.Weight)
}

// edgesEqualSet checks whether two edge slices represent the same undirected set
// (order-insensitive). Nil == Nil; nil != empty slice.
func edgesEqualSet(a []MEdge, b []MEdge) bool {
	if a == nil && b == nil {
		return true
	}
	if (a == nil) != (b == nil) {
		return false
	}
	if len(a) != len(b) {
		return false
	}
	m := make(map[string]int)
	for _, e := range a {
		m[normalizeEdgeKey(e)]++
	}
	for _, e := range b {
		k := normalizeEdgeKey(e)
		if m[k] == 0 {
			return false
		}
		m[k]--
	}
	for _, v := range m {
		if v != 0 {
			return false
		}
	}
	return true
}

// sortEdgesForPrint returns a stable, human-friendly ordering for printing (u,v,w) by u,v,w.
func sortEdgesForPrint(edges []MEdge) []MEdge {
	cp := make([]MEdge, len(edges))
	copy(cp, edges)
	sort.Slice(cp, func(i, j int) bool {
		ui, vi := cp[i].U, cp[i].V
		uj, vj := cp[j].U, cp[j].V
		// normalize order for comparison but keep stored U,V as-is for clarity
		if ui == uj {
			if vi == vj {
				return cp[i].Weight < cp[j].Weight
			}
			return vi < vj
		}
		return ui < uj
	})
	return cp
}

// printMST prints MST edges and total weight in a readable way.
func printMST(mst []MEdge, total int) {
	if mst == nil {
		fmt.Printf("MST: nil (start missing or graph disconnected)\n")
		return
	}
	if len(mst) == 0 {
		fmt.Printf("MST: (no edges) total weight = %d\n", total)
		return
	}
	s := sortEdgesForPrint(mst)
	fmt.Printf("MST edges (u --w--> v):\n")
	for _, e := range s {
		fmt.Printf("  %d --%d--> %d\n", e.U, e.Weight, e.V)
	}
	fmt.Printf("Total weight = %d\n", total)
}

// expect checks result against expected and prints pass/fail (and MST).
func expect(got []MEdge, gotTotal int, expected []MEdge, expectedTotal int, testName string) {
	fmt.Printf("%s - Computed MST:\n", testName)
	printMST(got, gotTotal)
	fmt.Println("Expected MST:")
	printMST(expected, expectedTotal)

	pass := edgesEqualSet(got, expected) && (got == nil && expected == nil || gotTotal == expectedTotal)
	if pass {
		fmt.Printf("[PASS] %s\n\n", testName)
	} else {
		fmt.Printf("[FAIL] %s\n\n", testName)
	}
}

// runTests builds small weighted graphs and runs deterministic tests.
func runTests() {
	fmt.Println("Prim's Algorithm Tests (numeric nodes)\n")

	// Test Graph 1:
	// Nodes: 1..6
	// edges:
	// 1-2:3, 1-3:1, 2-3:7, 2-4:5, 3-4:2, 3-5:4, 4-5:6, 4-6:8, 5-6:9
	// Known MST (one valid MST): edges
	// (1-3,1), (3-4,2), (1-2,3), (3-5,4), (4-6,8)  total = 18
	g1 := NewGraph()
	g1.AddEdge(1, 2, 3)
	g1.AddEdge(1, 3, 1)
	g1.AddEdge(2, 3, 7)
	g1.AddEdge(2, 4, 5)
	g1.AddEdge(3, 4, 2)
	g1.AddEdge(3, 5, 4)
	g1.AddEdge(4, 5, 6)
	g1.AddEdge(4, 6, 8)
	g1.AddEdge(5, 6, 9)

	expected1 := []MEdge{
		{U: 1, V: 3, Weight: 1},
		{U: 3, V: 4, Weight: 2},
		{U: 1, V: 2, Weight: 3},
		{U: 3, V: 5, Weight: 4},
		{U: 4, V: 6, Weight: 8},
	}
	got1, tot1 := g1.Prim(1)
	expect(got1, tot1, expected1, 18, "Test 1: sample graph, start=1")

	// Test 2: same graph, start at 3 -> MST should be same set & total
	got2, tot2 := g1.Prim(3)
	expect(got2, tot2, expected1, 18, "Test 2: sample graph, start=3")

	// Test 3: disconnected graph -> no spanning tree (nil expected)
	// component A: 1--2 (w=1)
	// component B: 3--4 (w=2)
	g2 := NewGraph()
	g2.AddEdge(1, 2, 1)
	g2.AddEdge(3, 4, 2)
	got3, tot3 := g2.Prim(1)
	expect(got3, tot3, nil, 0, "Test 3: disconnected graph (expect nil)")

	// Test 4: single isolated node (node exists but no edges) -> MST is empty edges, total=0
	g3 := NewGraph()
	g3.AddNode(7)
	got4, tot4 := g3.Prim(7)
	expect(got4, tot4, []MEdge{}, 0, "Test 4: single isolated node => empty MST")

	// Test 5: start missing => nil
	got5, tot5 := g1.Prim(99)
	expect(got5, tot5, nil, 0, "Test 5: start missing => nil")

	fmt.Println("Tests completed.")
}

func main() {
	// CLI: if an integer arg provided, run Prim on the sample graph and print MST.
	if len(os.Args) > 1 {
		startStr := os.Args[1]
		start, err := strconv.Atoi(startStr)
		if err != nil {
			fmt.Printf("Invalid start node: %q. Provide integer node id.\n", startStr)
			return
		}
		// build sample graph (same as Test 1)
		g := NewGraph()
		g.AddEdge(1, 2, 3)
		g.AddEdge(1, 3, 1)
		g.AddEdge(2, 3, 7)
		g.AddEdge(2, 4, 5)
		g.AddEdge(3, 4, 2)
		g.AddEdge(3, 5, 4)
		g.AddEdge(4, 5, 6)
		g.AddEdge(4, 6, 8)
		g.AddEdge(5, 6, 9)

		mst, total := g.Prim(start)
		fmt.Printf("Prim's MST starting at %d:\n", start)
		printMST(mst, total)
		return
	}

	// default: run tests
	runTests()
}
