//Dijkstra's algorithm is a graph search algorithm used to find the shortest path from a starting node to all other nodes in a weighted graph (with non-negative edge weights).

package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"sync"
)

func main() {
	// Build graph and run Dijkstra's algorithm
	graph := buildGraph()

	// Start city is passed as command-line argument
	city := os.Args[1]
	dijkstra(graph, city)

	// Display shortest path from start city to all other cities
	for _, node := range graph.Nodes {
		fmt.Printf("Shortest time from %s to %s is %d\n",
			city, node.name, node.value)
		for n := node; n.through != nil; n = n.through {
			fmt.Print(n, " <- ")
		}
		fmt.Println(city)
		fmt.Println()
	}
}

// dijkstra runs Dijkstra's algorithm on the graph from the given city.
// Time Complexity: O((V + E) * log V) where V is number of nodes and E is number of edges.
func dijkstra(graph *WeightedGraph, city string) {
	visited := make(map[string]bool)
	heap := &Heap{}

	startNode := graph.GetNode(city)
	startNode.value = 0
	heap.Push(startNode)

	for heap.Size() > 0 {
		current := heap.Pop()
		visited[current.name] = true

		edges := graph.Edges[current.name]
		for _, edge := range edges {
			if !visited[edge.node.name] {
				heap.Push(edge.node)
				// Relaxation step
				if current.value+edge.weight < edge.node.value {
					edge.node.value = current.value + edge.weight
					edge.node.through = current
				}
			}
		}
	}
}

// buildGraph creates a sample undirected, weighted graph.
// Time Complexity: O(N + E) where N is number of nodes and E is number of edges.
func buildGraph() *WeightedGraph {
	graph := NewGraph()
	nodes := AddNodes(graph,
		"London", "Paris", "Amsterdam", "Luxembourg", "Zurich",
		"Rome", "Berlin", "Vienna", "Warsaw", "Istanbul",
	)

	// Add edges (bidirectional)
	graph.AddEdge(nodes["London"], nodes["Paris"], 80)
	graph.AddEdge(nodes["London"], nodes["Luxembourg"], 75)
	graph.AddEdge(nodes["London"], nodes["Amsterdam"], 75)
	graph.AddEdge(nodes["Paris"], nodes["Luxembourg"], 60)
	graph.AddEdge(nodes["Paris"], nodes["Rome"], 125)
	graph.AddEdge(nodes["Luxembourg"], nodes["Berlin"], 90)
	graph.AddEdge(nodes["Luxembourg"], nodes["Zurich"], 60)
	graph.AddEdge(nodes["Luxembourg"], nodes["Amsterdam"], 55)
	graph.AddEdge(nodes["Zurich"], nodes["Vienna"], 80)
	graph.AddEdge(nodes["Zurich"], nodes["Rome"], 90)
	graph.AddEdge(nodes["Zurich"], nodes["Berlin"], 85)
	graph.AddEdge(nodes["Berlin"], nodes["Amsterdam"], 85)
	graph.AddEdge(nodes["Berlin"], nodes["Vienna"], 75)
	graph.AddEdge(nodes["Vienna"], nodes["Rome"], 100)
	graph.AddEdge(nodes["Vienna"], nodes["Istanbul"], 130)
	graph.AddEdge(nodes["Warsaw"], nodes["Berlin"], 80)
	graph.AddEdge(nodes["Warsaw"], nodes["Istanbul"], 180)
	graph.AddEdge(nodes["Rome"], nodes["Istanbul"], 155)

	return graph
}

// ---------- Weighted Graph Definitions ----------

type Node struct {
	name    string // City name
	value   int    // Distance from source
	through *Node  // Previous node in shortest path
}

type Edge struct {
	node   *Node // Target node
	weight int   // Edge weight
}

type WeightedGraph struct {
	Nodes []*Node
	Edges map[string][]*Edge
	mutex sync.RWMutex
}

func NewGraph() *WeightedGraph {
	return &WeightedGraph{
		Edges: make(map[string][]*Edge),
	}
}

// GetNode returns the pointer to the node with given name
// Time Complexity: O(N)
func (g *WeightedGraph) GetNode(name string) (node *Node) {
	g.mutex.RLock()
	defer g.mutex.RUnlock()
	for _, n := range g.Nodes {
		if n.name == name {
			node = n
		}
	}
	return
}

// AddNode adds a node to the graph
func (g *WeightedGraph) AddNode(n *Node) {
	g.mutex.Lock()
	defer g.mutex.Unlock()
	g.Nodes = append(g.Nodes, n)
}

// AddNodes adds multiple nodes to the graph
// Time Complexity: O(N)
func AddNodes(graph *WeightedGraph, names ...string) (nodes map[string]*Node) {
	nodes = make(map[string]*Node)
	for _, name := range names {
		n := &Node{name, math.MaxInt, nil} // Default distance is "infinity"
		graph.AddNode(n)
		nodes[name] = n
	}
	return
}

// AddEdge adds a bidirectional edge to the graph
// Time Complexity: O(1)
func (g *WeightedGraph) AddEdge(n1, n2 *Node, weight int) {
	g.mutex.Lock()
	defer g.mutex.Unlock()
	g.Edges[n1.name] = append(g.Edges[n1.name], &Edge{n2, weight})
	g.Edges[n2.name] = append(g.Edges[n2.name], &Edge{n1, weight})
}

func (n *Node) String() string {
	return n.name
}

func (e *Edge) String() string {
	return e.node.String() + "(" + strconv.Itoa(e.weight) + ")"
}

// ---------- Heap (Min-Heap based on Node.value) ----------

type Heap struct {
	elements []*Node
	mutex    sync.RWMutex
}

// Size returns number of elements in heap
// Time Complexity: O(1)
func (h *Heap) Size() int {
	h.mutex.RLock()
	defer h.mutex.RUnlock()
	return len(h.elements)
}

// Push adds a node into the heap and maintains heap order
// Time Complexity: O(log N)
func (h *Heap) Push(element *Node) {
	h.mutex.Lock()
	defer h.mutex.Unlock()
	h.elements = append(h.elements, element)
	i := len(h.elements) - 1
	// Bubble up to restore min-heap
	for ; i > 0 && h.elements[i].value < h.elements[parent(i)].value; i = parent(i) {
		h.swap(i, parent(i))
	}
}

// Pop removes and returns the node with smallest value (min-heap root)
// Time Complexity: O(log N)
func (h *Heap) Pop() (i *Node) {
	h.mutex.Lock()
	defer h.mutex.Unlock()
	if len(h.elements) == 0 {
		return nil
	}
	i = h.elements[0]
	last := len(h.elements) - 1
	h.elements[0] = h.elements[last]
	h.elements = h.elements[:last]
	h.rearrange(0)
	return
}

// rearrange restores heap order starting from index i
// Time Complexity: O(log N)
func (h *Heap) rearrange(i int) {
	smallest := i
	left, right, size := leftChild(i), rightChild(i), len(h.elements)
	if left < size && h.elements[left].value < h.elements[smallest].value {
		smallest = left
	}
	if right < size && h.elements[right].value < h.elements[smallest].value {
		smallest = right
	}
	if smallest != i {
		h.swap(i, smallest)
		h.rearrange(smallest)
	}
}

func (h *Heap) swap(i, j int) {
	h.elements[i], h.elements[j] = h.elements[j], h.elements[i]
}

func parent(i int) int {
	return (i - 1) / 2
}

func leftChild(i int) int {
	return 2*i + 1
}

func rightChild(i int) int {
	return 2*i + 2
}

// String representation of heap contents
func (h *Heap) String() (str string) {
	return fmt.Sprintf("%q\n", getNames(h.elements))
}

// getNames returns a slice of node names
func getNames(nodes []*Node) (names []string) {
	for _, node := range nodes {
		names = append(names, node.name)
	}
	return
}
