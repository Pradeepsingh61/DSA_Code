# Graph Algorithms

This directory contains implementations of various graph algorithms.

## Aho-Corasick Algorithm for Pattern Searching

Aho-Corasick is an efficient string-matching algorithm that can find all occurrences of a finite set of patterns in a given text string. It runs in O(n + m + z) time, where n is the length of the text, m is the total length of all patterns, and z is the number of pattern occurrences.

### Key Concepts

1. **Trie (Prefix Tree)**: A tree data structure that stores patterns for efficient lookup
2. **Failure Links**: Similar to KMP algorithm's prefix function, tells where to go when a character mismatch occurs
3. **Dictionary Links**: Connect nodes to the nearest pattern-ending nodes

### Algorithm Steps

1. Build a trie of the patterns
2. Create failure links using BFS
3. Create dictionary links for finding overlapping patterns
4. Process the text character by character using the constructed automaton

### Applications

- Multiple pattern string matching
- Virus/intrusion detection
- Plagiarism detection
- Bioinformatics (DNA sequence matching)
- Content filtering and data mining

### Usage Example

```cpp
// Create an Aho-Corasick automaton with a set of patterns
vector<string> patterns = {"he", "she", "his", "hers"};
AhoCorasick ac(patterns);

// Search for all pattern occurrences in a text
string text = "ahishershe";
vector<pair<int, int>> matches = ac.search(text);
```

### References

- Aho, A. V., & Corasick, M. J. (1975). "Efficient string matching: An aid to bibliographic search"
- Commentz-Walter, B. (1979). "A string matching algorithm fast on the average"

## Dinic's Algorithm for Maximum Flow

Dinic's algorithm is an efficient algorithm for computing the maximum flow in a flow network, improving on the Ford-Fulkerson algorithm. It runs in O(V²E) time and is much faster in practice for many problems.

### Key Concepts

1. **Flow Network**: A directed graph where each edge has a capacity and a flow, with source and sink vertices.
2. **Level Graph**: A graph where vertices are assigned levels according to their shortest distance from the source.
3. **Blocking Flow**: A flow where every path from source to sink has at least one saturated edge.

### Algorithm Steps

1. Create a level graph using BFS
2. Find blocking flows using DFS 
3. Repeat until no more augmenting paths can be found

### Applications

- Network Flow Problems
- Bipartite Matching
- Image Segmentation
- Circulation Problems
- Scheduling Problems

### Usage Example

```cpp
// Create a flow network with 6 vertices
DinicMaxFlow network(6);

// Add edges (from, to, capacity)
network.addEdge(0, 1, 16);
network.addEdge(0, 2, 13);
// ... more edges ...

// Calculate maximum flow from source (0) to sink (5)
int maxFlow = network.maxFlow(0, 5);
```

### References

- Dinic, E. A. (1970). "Algorithm for solution of a problem of maximum flow in networks with power estimation"
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). "Introduction to Algorithms" (3rd ed.)
