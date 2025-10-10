// FloydWarshall.go
//
// Floyd–Warshall All-Pairs Shortest Paths (numeric node IDs)
//
// Description:
//   Floyd–Warshall computes shortest-path distances between every pair of
//   vertices in a directed weighted graph (weights may be negative).
//   It can also detect negative-weight cycles (a negative value on the
//   diagonal after the algorithm indicates such a cycle).
//
// Features / Notes:
//   - Directed edges using AddEdge(u, v, w). For undirected graphs add both directions.
//   - Returns distance and "next" matrices (maps) for path reconstruction.
//   - Detects negative-weight cycles reachable between any pair (reported via negCycle).
//   - Deterministic node order by sorting node IDs for predictable test outputs.
//   - Tests print full distance matrices, next-pointer matrices and example paths.
//
// Complexity:
//   - Time: O(V^3)
//   - Space: O(V^2)

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

// Graph holds directed edges and adjacency convenience storage.
type Graph struct {
	adj   map[int][]Edge
	edges []Edge
}

// NewGraph constructs an empty graph.
func NewGraph() *Graph {
	return &Graph{
		adj:   make(map[int][]Edge),
		edges: []Edge{},
	}
}

// AddNode ensures node exists in the adjacency map.
func (g *Graph) AddNode(id int) {
	if _, ok := g.adj[id]; !ok {
		g.adj[id] = []Edge{}
	}
}

// AddEdge adds a directed edge u -> v with weight w.
func (g *Graph) AddEdge(u, v, w int) {
	g.AddNode(u)
	g.AddNode(v)
	e := Edge{U: u, V: v, Weight: w}
	g.adj[u] = append(g.adj[u], e)
	g.edges = append(g.edges, e)
}

// FloydWarshall computes all-pairs shortest paths.
// Returns:
//   - dist map: dist[u][v] = shortest distance (INT INF if unreachable)
//   - next map: next[u][v] = next node on shortest path from u to v, -1 if none
//   - negCycle: true if a negative-weight cycle exists (dist[i][i] < 0 for some i)
// If the graph is empty, returns (nil, nil, false).
func (g *Graph) FloydWarshall() (map[int]map[int]int, map[int]map[int]int, bool) {
	if len(g.adj) == 0 {
		return nil, nil, false
	}

	// Deterministic ordering of nodes
	nodes := make([]int, 0, len(g.adj))
	for n := range g.adj {
		nodes = append(nodes, n)
	}
	sort.Ints(nodes)
	n := len(nodes)
	idx := make(map[int]int, n)
	for i, v := range nodes {
		idx[v] = i
	}

	// INF chosen to avoid overflow on additions
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	// initialize dist and next matrices (by index)
	dist := make([][]int, n)
	nextIdx := make([][]int, n)
	for i := 0; i < n; i++ {
		dist[i] = make([]int, n)
		nextIdx[i] = make([]int, n)
		for j := 0; j < n; j++ {
			if i == j {
				dist[i][j] = 0
				nextIdx[i][j] = j // path from i to i is trivial
			} else {
				dist[i][j] = INF
				nextIdx[i][j] = -1
			}
		}
	}

	// set direct edges
	for _, e := range g.edges {
		u := idx[e.U]
		v := idx[e.V]
		// keep the smallest if multiple edges between same directed pair
		if e.Weight < dist[u][v] {
			dist[u][v] = e.Weight
			nextIdx[u][v] = v
		}
	}

	// Floyd-Warshall main loops
	for k := 0; k < n; k++ {
		for i := 0; i < n; i++ {
			// skip if i->k unreachable
			if dist[i][k] == INF {
				continue
			}
			for j := 0; j < n; j++ {
				if dist[k][j] == INF {
					continue
				}
				// careful about overflow: both are bounded by INF and sums won't overflow
				if dist[i][k]+dist[k][j] < dist[i][j] {
					dist[i][j] = dist[i][k] + dist[k][j]
					// next on path i->j is next on i->k
					nextIdx[i][j] = nextIdx[i][k]
				}
			}
		}
	}

	// Detect negative cycles (if any dist[i][i] < 0)
	for i := 0; i < n; i++ {
		if dist[i][i] < 0 {
			return nil, nil, true
		}
	}

	// Convert matrices back to node-keyed maps for user convenience
	distMap := make(map[int]map[int]int, n)
	nextMap := make(map[int]map[int]int, n) // nextMap[u][v] = next node id, or -1
	for i, u := range nodes {
		distMap[u] = make(map[int]int, n)
		nextMap[u] = make(map[int]int, n)
		for j, v := range nodes {
			distMap[u][v] = dist[i][j]
			if nextIdx[i][j] == -1 {
				nextMap[u][v] = -1
			} else {
				nextMap[u][v] = nodes[nextIdx[i][j]]
			}
		}
	}

	return distMap, nextMap, false
}

// reconstructPath returns a slice of node IDs representing the shortest path
// from u to v using next matrix (as returned by FloydWarshall). Returns nil if
// no path exists (next[u][v] == -1) or next is nil.
func reconstructPath(next map[int]map[int]int, u, v int) []int {
	if next == nil {
		return nil
	}
	nu, ok := next[u]
	if !ok {
		return nil
	}
	if nu[v] == -1 {
		return nil
	}
	path := []int{u}
	cur := u
	for cur != v {
		cur = next[cur][v]
		// guard against malformed next pointers (shouldn't happen in correct next)
		if cur == -1 {
			return nil
		}
		path = append(path, cur)
		// safety: avoid infinite loop — but in valid next this won't run forever
		if len(path) > len(next) {
			return nil
		}
	}
	return path
}

// pretty print distance matrix
func printDistMatrix(dist map[int]map[int]int) {
	if dist == nil {
		fmt.Println("Distance matrix: nil")
		return
	}
	// determine INF same as algorithm
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	// sorted nodes
	nodes := make([]int, 0, len(dist))
	for n := range dist {
		nodes = append(nodes, n)
	}
	sort.Ints(nodes)

	// header
	fmt.Printf("    ")
	for _, v := range nodes {
		fmt.Printf("%8d", v)
	}
	fmt.Println()
	for _, u := range nodes {
		fmt.Printf("%4d", u)
		for _, v := range nodes {
			d := dist[u][v]
			if d == INF {
				fmt.Printf("%8s", "INF")
			} else {
				fmt.Printf("%8d", d)
			}
		}
		fmt.Println()
	}
}

// pretty print next matrix
func printNextMatrix(next map[int]map[int]int) {
	if next == nil {
		fmt.Println("Next matrix: nil")
		return
	}
	nodes := make([]int, 0, len(next))
	for n := range next {
		nodes = append(nodes, n)
	}
	sort.Ints(nodes)

	fmt.Printf("    ")
	for _, v := range nodes {
		fmt.Printf("%6d", v)
	}
	fmt.Println()
	for _, u := range nodes {
		fmt.Printf("%4d", u)
		for _, v := range nodes {
			nx := next[u][v]
			if nx == -1 {
				fmt.Printf("%6s", "-")
			} else {
				fmt.Printf("%6d", nx)
			}
		}
		fmt.Println()
	}
}

// compareDistMaps compares two distance maps considering INF equality.
func compareDistMaps(a, b map[int]map[int]int, INF int) bool {
	if (a == nil) != (b == nil) {
		return false
	}
	if a == nil && b == nil {
		return true
	}
	if len(a) != len(b) {
		return false
	}
	for u := range a {
		au := a[u]
		bu, ok := b[u]
		if !ok {
			return false
		}
		if len(au) != len(bu) {
			return false
		}
		for v, av := range au {
			bv, ok := bu[v]
			if !ok {
				return false
			}
			if av == INF && bv == INF {
				continue
			}
			if av != bv {
				return false
			}
		}
	}
	return true
}

// runTests builds multiple graphs and runs Floyd–Warshall tests tailored to it.
func runTests() {
	fmt.Println("Floyd–Warshall Tests — printing matrices and example paths\n")

	// compute INF for expectations
	maxInt := int(^uint(0) >> 1)
	INF := maxInt / 4

	// ---------- Test 1: simple positive-weight directed graph ----------
	// Graph edges:
	// 1 -> 2 (3)
	// 1 -> 3 (8)
	// 2 -> 3 (2)
	// 3 -> 4 (1)
	// 2 -> 4 (5)
	// Expected all-pairs distances (INF means unreachable)
	g1 := NewGraph()
	g1.AddEdge(1, 2, 3)
	g1.AddEdge(1, 3, 8)
	g1.AddEdge(2, 3, 2)
	g1.AddEdge(3, 4, 1)
	g1.AddEdge(2, 4, 5)

	expected1 := map[int]map[int]int{
		1: {1: 0, 2: 3, 3: 5, 4: 6},
		2: {1: INF, 2: 0, 3: 2, 4: 3},
		3: {1: INF, 2: INF, 3: 0, 4: 1},
		4: {1: INF, 2: INF, 3: INF, 4: 0},
	}
	fmt.Println("Test 1: simple positive-weight directed graph")
	dist1, next1, neg1 := g1.FloydWarshall()
	if neg1 {
		fmt.Println("  [FAIL] unexpected negative cycle")
	} else {
		printDistMatrix(dist1)
		fmt.Println("Next matrix:")
		printNextMatrix(next1)
	}
	if !neg1 && compareDistMaps(dist1, expected1, INF) {
		fmt.Println("[PASS] Test 1\n")
	} else {
		fmt.Println("[FAIL] Test 1 (mismatch)\n")
	}

	// ---------- Test 2: negative edges but no negative cycles ----------
	// Edges:
	// 1 -> 2 (4)
	// 1 -> 3 (1)
	// 3 -> 2 (-2)
	// 2 -> 4 (2)
	// 3 -> 4 (5)
	// Expected shortest distances computed manually.
	g2 := NewGraph()
	g2.AddEdge(1, 2, 4)
	g2.AddEdge(1, 3, 1)
	g2.AddEdge(3, 2, -2)
	g2.AddEdge(2, 4, 2)
	g2.AddEdge(3, 4, 5)

	expected2 := map[int]map[int]int{
		1: {1: 0, 2: -1, 3: 1, 4: 1},
		2: {1: INF, 2: 0, 3: INF, 4: 2},
		3: {1: INF, 2: -2, 3: 0, 4: 3},
		4: {1: INF, 2: INF, 3: INF, 4: 0},
	}
	fmt.Println("Test 2: negative edges but no negative cycles")
	dist2, next2, neg2 := g2.FloydWarshall()
	if neg2 {
		fmt.Println("  [FAIL] unexpected negative cycle")
	} else {
		printDistMatrix(dist2)
		fmt.Println("Next matrix:")
		printNextMatrix(next2)
		// Example path reconstruction: 1 -> 4
		path14 := reconstructPath(next2, 1, 4)
		fmt.Printf("Example path 1 -> 4: %v\n", path14)
	}
	if !neg2 && compareDistMaps(dist2, expected2, INF) {
		fmt.Println("[PASS] Test 2\n")
	} else {
		fmt.Println("[FAIL] Test 2 (mismatch)\n")
	}

	// ---------- Test 3: negative cycle detection ----------
	// Graph:
	// 1 -> 2 (1)
	// 2 -> 3 (-2)
	// 3 -> 1 (-2)  // cycle sum -3
	// 3 -> 4 (2)
	g3 := NewGraph()
	g3.AddEdge(1, 2, 1)
	g3.AddEdge(2, 3, -2)
	g3.AddEdge(3, 1, -2)
	g3.AddEdge(3, 4, 2)

	fmt.Println("Test 3: negative-weight cycle detection (should detect)")
	_, _, neg3 := g3.FloydWarshall()
	if neg3 {
		fmt.Println("[PASS] Test 3 (negative cycle detected)\n")
	} else {
		fmt.Println("[FAIL] Test 3 (failed to detect negative cycle)\n")
	}

	// ---------- Test 4: disconnected graph (unreachable pairs) ----------
	// Graph:
	// 1 -> 2 (3)
	// 2 -> 3 (4)
	// node 4 isolated
	g4 := NewGraph()
	g4.AddEdge(1, 2, 3)
	g4.AddEdge(2, 3, 4)
	g4.AddNode(4)

	expected4 := map[int]map[int]int{
		1: {1: 0, 2: 3, 3: 7, 4: INF},
		2: {1: INF, 2: 0, 3: 4, 4: INF},
		3: {1: INF, 2: INF, 3: 0, 4: INF},
		4: {1: INF, 2: INF, 3: INF, 4: 0},
	}
	fmt.Println("Test 4: disconnected graph (unreachable pairs)")
	dist4, next4, neg4 := g4.FloydWarshall()
	if neg4 {
		fmt.Println("  [FAIL] unexpected negative cycle")
	} else {
		printDistMatrix(dist4)
		fmt.Println("Next matrix:")
		printNextMatrix(next4)
	}
	if !neg4 && compareDistMaps(dist4, expected4, INF) {
		fmt.Println("[PASS] Test 4\n")
	} else {
		fmt.Println("[FAIL] Test 4 (mismatch)\n")
	}

	// ---------- Test 5: single node ----------
	g5 := NewGraph()
	g5.AddNode(42)
	expected5 := map[int]map[int]int{
		42: {42: 0},
	}
	fmt.Println("Test 5: single node")
	dist5, next5, neg5 := g5.FloydWarshall()
	if neg5 {
		fmt.Println("  [FAIL] unexpected negative cycle")
	} else {
		printDistMatrix(dist5)
		fmt.Println("Next matrix:")
		printNextMatrix(next5)
	}
	if !neg5 && compareDistMaps(dist5, expected5, INF) {
		fmt.Println("[PASS] Test 5\n")
	} else {
		fmt.Println("[FAIL] Test 5 (mismatch)\n")
	}

	// ---------- Test 6: empty graph => nil results ----------
	empty := NewGraph()
	fmt.Println("Test 6: empty graph => expect nil results")
	dist6, next6, neg6 := empty.FloydWarshall()
	if dist6 == nil && next6 == nil && !neg6 {
		fmt.Println("[PASS] Test 6\n")
	} else {
		fmt.Println("[FAIL] Test 6\n")
	}

	fmt.Println("Floyd–Warshall tests completed.")
}

// CLI: if a numeric arg provided, demonstrate Floyd–Warshall on a sample graph.
func main() {
	if len(os.Args) > 1 {
		if _, err := strconv.Atoi(os.Args[1]); err == nil {
			g := NewGraph()
			// sample graph: same as Test 2
			g.AddEdge(1, 2, 4)
			g.AddEdge(1, 3, 1)
			g.AddEdge(3, 2, -2)
			g.AddEdge(2, 4, 2)
			g.AddEdge(3, 4, 5)

			dist, next, neg := g.FloydWarshall()
			if neg {
				fmt.Println("Negative cycle detected -> distances undefined")
				return
			}
			fmt.Println("All-pairs distance matrix:")
			printDistMatrix(dist)
			fmt.Println("Next matrix:")
			printNextMatrix(next)
			// example path 1->4
			fmt.Printf("Path 1 -> 4: %v\n", reconstructPath(next, 1, 4))
			return
		}
		// if arg present but non-numeric, fall through to tests
	}
	// default: run tests
	runTests()
}
