// FloydWarshall.go
//
// Floyd–Warshall Algorithm - All-Pairs Shortest Path
//
// Description:
//   The Floyd–Warshall algorithm computes the shortest paths between
//   all pairs of vertices in a weighted directed graph. It can handle
//   negative edge weights (but not negative cycles).
//
// Purpose / Use cases:
//   - Network routing, transitive closure, and distance computation.
//   - Detect negative cycles in graphs.
//
// Approach / Methodology:
//   - Dynamic Programming approach.
//   - Initialize a distance matrix with given edge weights.
//   - Iteratively relax edges by trying all intermediate vertices.
//
// Complexity Analysis:
//   - Time: O(V³)
//   - Space: O(V²)
//
// File contents:
//   - FloydWarshall() function.
//   - PrintDistanceMatrix() utility.
//   - Example test in main().

package main

import (
	"fmt"
	"math"
)

// FloydWarshall computes all-pairs shortest paths.
// It modifies and returns the distance matrix.
func FloydWarshall(dist [][]float64) [][]float64 {
	n := len(dist)
	for k := 0; k < n; k++ {
		for i := 0; i < n; i++ {
			for j := 0; j < n; j++ {
				if dist[i][k]+dist[k][j] < dist[i][j] {
					dist[i][j] = dist[i][k] + dist[k][j]
				}
			}
		}
	}
	return dist
}

// PrintDistanceMatrix prints a formatted distance matrix.
func PrintDistanceMatrix(dist [][]float64) {
	fmt.Println("All-Pairs Shortest Path Matrix:")
	for _, row := range dist {
		for _, val := range row {
			if val == math.Inf(1) {
				fmt.Printf("%4s ", "INF")
			} else {
				fmt.Printf("%4.0f ", val)
			}
		}
		fmt.Println()
	}
}

// main runs an example directed graph for Floyd–Warshall.
func main() {
	fmt.Println("Floyd–Warshall Algorithm Demo")

	const INF = math.Inf(1)
	dist := [][]float64{
		{0, 3, INF, 7},
		{8, 0, 2, INF},
		{5, INF, 0, 1},
		{2, INF, INF, 0},
	}

	result := FloydWarshall(dist)
	PrintDistanceMatrix(result)
}
