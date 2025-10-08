// KruskalMST.go
//
// Kruskal's Algorithm - Minimum Spanning Tree (numeric node IDs)
//
// Description:
//   Kruskal's algorithm finds a minimum spanning tree (MST) of a connected,
//   undirected, weighted graph by sorting edges and adding them if they
//   connect different components (using union-find).
//
// Purpose / Use cases:
//   - Compute MST and its total weight.
//   - Useful for network design, clustering approximations, etc.
//
// Approach / Methodology:
//   - Represent undirected weighted graph with adjacency list and an edges slice.
//   - Sort all unique undirected edges by (weight, u, v).
//   - Use Union-Find to pick edges that join different components.
//   - If after processing all edges the MST contains V-1 edges, return it;
//     otherwise the graph was disconnected and no spanning tree exists.
//
// Complexity Analysis:
//   - Time: O(E log E) due to sorting + near-constant union-find ops.
//   - Space: O(E + V)
//
// File contents:
//   - Graph type and methods (AddEdge, AddNode).
//   - Union-Find implementation.
//   - Kruskal() that returns []MEdge (MST) and total weight, or nil if not found.
//   - Tests print MST after each test and indicate pass/fail.

package main

import (
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
	adj   map[int][]MEdge // adjacency list: node -> list of neighbor edges
	edges []MEdge         // unique undirected edges (stored with U < V)
}

// NewGraph creates and returns an empty Graph.
func NewGraph() *Graph {
	return &Graph{
		adj:   make(map[int][]MEdge),
		edges: []MEdge{},
	}
}

// AddNode ensures a node entry exists in the adjacency map.
func (g *Graph) AddNode(id int) {
	if _, ok := g.adj[id]; !ok {
		g.adj[id] = []MEdge{}
	}
}

// AddEdge adds an undirected weighted edge between a and b.
// If nodes don't exist yet they are created automatically.
// Edges slice stores each undirected edge exactly once with U < V to avoid duplicates.
func (g *Graph) AddEdge(a, b, w int) {
	g.AddNode(a)
	g.AddNode(b)
	// Add adjacency entries for traversal convenience (both directions)
	g.adj[a] = append(g.adj[a], MEdge{U: a, V: b, Weight: w})
	g.adj[b] = append(g.adj[b], MEdge{U: b, V: a, Weight: w})

	// Store unique undirected edge normalized so U < V
	u, v := a, b
	if u > v {
		u, v = v, u
	}
	g.edges = append(g.edges, MEdge{U: u, V: v, Weight: w})
}

// -------- Union-Find (Disjoint Set) --------

type UnionFind struct {
	parent map[int]int
	rank   map[int]int
}

func NewUnionFind(nodes []int) *UnionFind {
	uf := &UnionFind{
		parent: make(map[int]int, len(nodes)),
		rank:   make(map[int]int, len(nodes)),
	}
	for _, n := range nodes {
		uf.parent[n] = n
		uf.rank[n] = 0
	}
	return uf
}

func (uf *UnionFind) Find(x int) int {
	// path compression
	if uf.parent[x] != x {
		uf.parent[x] = uf.Find(uf.parent[x])
	}
	return uf.parent[x]
}

func (uf *UnionFind) Union(x, y int) bool {
	rx := uf.Find(x)
	ry := uf.Find(y)
	if rx == ry {
		return false
	}
	// union by rank
	if uf.rank[rx] < uf.rank[ry] {
		uf.parent[rx] = ry
	} else if uf.rank[ry] < uf.rank[rx] {
		uf.parent[ry] = rx
	} else {
		uf.parent[ry] = rx
		uf.rank[rx]++
	}
	return true
}

// -------- Kruskal's algorithm --------

// Kruskal computes an MST of the whole graph.
// Returns (mstEdges, totalWeight).
// If the graph is empty -> returns nil,0.
// If the graph has exactly 1 node -> returns empty MST slice and weight 0.
// If the graph is disconnected -> returns nil,0.
func (g *Graph) Kruskal() ([]MEdge, int) {
	if len(g.adj) == 0 {
		return nil, 0
	}

	// Prepare nodes list for union-find
	nodes := make([]int, 0, len(g.adj))
	for n := range g.adj {
		nodes = append(nodes, n)
	}

	// Sort edges by (weight, u, v) deterministically
	edges := make([]MEdge, len(g.edges))
	copy(edges, g.edges)
	sort.Slice(edges, func(i, j int) bool {
		if edges[i].Weight != edges[j].Weight {
			return edges[i].Weight < edges[j].Weight
		}
		if edges[i].U != edges[j].U {
			return edges[i].U < edges[j].U
		}
		return edges[i].V < edges[j].V
	})

	uf := NewUnionFind(nodes)
	mst := make([]MEdge, 0, len(g.adj)-1)
	total := 0

	for _, e := range edges {
		if uf.Find(e.U) != uf.Find(e.V) {
			uf.Union(e.U, e.V)
			mst = append(mst, e)
			total += e.Weight
		}
		// quick exit: if mst has V-1 edges we can stop early
		if len(mst) == len(g.adj)-1 {
			break
		}
	}

	// Check if we built a spanning tree
	if len(mst) != len(g.adj)-1 {
		// Special-case: single node graph -> mst len == 0 and len(adj)-1 == 0 -> OK
		if len(g.adj) == 1 && len(mst) == 0 {
			return mst, total
		}
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
		if cp[i].U == cp[j].U {
			if cp[i].V == cp[j].V {
				return cp[i].Weight < cp[j].Weight
			}
			return cp[i].V < cp[j].V
		}
		return cp[i].U < cp[j].U
	})
	return cp
}

// printMST prints MST edges and total weight in a readable way.
func printMST(mst []MEdge, total int) {
	if mst == nil {
		fmt.Printf("MST: nil (graph empty or disconnected)\n")
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
	fmt.Println("Kruskal's Algorithm Tests (numeric nodes)\n")

	// Test Graph 1: same sample as used before
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
	got1, tot1 := g1.Kruskal()
	expect(got1, tot1, expected1, 18, "Test 1: sample graph")

	// Test 2: same graph, ensure result is independent of edge insertion order
	// Rebuild with different insertion sequence (but same edges)
	g1b := NewGraph()
	g1b.AddEdge(4, 6, 8)
	g1b.AddEdge(5, 6, 9)
	g1b.AddEdge(1, 3, 1)
	g1b.AddEdge(3, 4, 2)
	g1b.AddEdge(1, 2, 3)
	g1b.AddEdge(3, 5, 4)
	g1b.AddEdge(4, 5, 6)
	g1b.AddEdge(2, 4, 5)
	g1b.AddEdge(2, 3, 7)
	got2, tot2 := g1b.Kruskal()
	expect(got2, tot2, expected1, 18, "Test 2: sample graph (different insertion order)")

	// Test 3: disconnected graph -> no spanning tree (nil expected)
	g2 := NewGraph()
	g2.AddEdge(1, 2, 1)
	g2.AddEdge(3, 4, 2)
	got3, tot3 := g2.Kruskal()
	expect(got3, tot3, nil, 0, "Test 3: disconnected graph (expect nil)")

	// Test 4: single isolated node (node exists but no edges) -> MST is empty edges, total=0
	g3 := NewGraph()
	g3.AddNode(7)
	got4, tot4 := g3.Kruskal()
	expect(got4, tot4, []MEdge{}, 0, "Test 4: single isolated node => empty MST")

	// Test 5: empty graph => nil
	empty := NewGraph()
	got5, tot5 := empty.Kruskal()
	expect(got5, tot5, nil, 0, "Test 5: empty graph => nil")

	fmt.Println("Tests completed.")
}

func main() {
	// CLI: if an integer arg provided, run Kruskal on the sample graph and print MST.
	if len(os.Args) > 1 {
		_, err := strconv.Atoi(os.Args[1])
		if err != nil {
			fmt.Printf("Invalid arg. Provide integer (ignored for Kruskal CLI example).\n")
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

		mst, total := g.Kruskal()
		fmt.Printf("Kruskal's MST for sample graph:\n")
		printMST(mst, total)
		return
	}

	// default: run tests
	runTests()
}
