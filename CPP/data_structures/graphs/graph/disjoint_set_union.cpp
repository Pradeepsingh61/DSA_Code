/**
 * @file disjoint_set_union.cpp
 * @brief Implementation of the Disjoint Set Union (DSU) data structure.
 *
 * ---
 * @section description_dsu Algorithm Description
 * The Disjoint Set Union (DSU), or Union-Find, data structure manages a collection
 * of disjoint (non-overlapping) sets.
 *
 * It provides two primary operations:
 * 1. find(i): Finds the representative (or "leader") of the set that element 'i'
 * belongs to.
 * 2. unite(i, j): Merges the two sets containing elements 'i' and 'j' into a
 * single set.
 *
 * This implementation uses two powerful optimizations:
 * 1. Path Compression: During a 'find' operation, it makes every node on the
 * path point directly to the root. This flattens the tree.
 * 2. Union by Size: During a 'unite' operation, it attaches the root of the
 * smaller tree to the root of the larger tree. This keeps the trees
 * from becoming too deep.
 *
 * ---
 * @section applications Use Cases
 * - Detecting cycles in an undirected graph.
 * - Kruskal's algorithm for finding a Minimum Spanning Tree (MST).
 * - Finding connected components in a graph.
 * - Solving connectivity problems (e.g., "Are these two people in the
 * same friend group?").
 *
 * ---
 * @section complexity Complexity Analysis
 *
 * Let N = the number of elements in the DSU.
 * Let \alpha(N) = the Inverse Ackermann function. This function grows
 * extremely slowly and is practically constant (less than 5) for all
 * realistic values of N.
 *
 * @subsection time Time Complexity
 * - **Constructor (DSU(N)):** O(N)
 * We initialize two vectors of size N.
 * - **find(i):** O(\alpha(N)) (Amortized)
 * Thanks to path compression, finding the root is nearly constant time
 * on average.
 * - **unite(i, j):** O(\alpha(N)) (Amortized)
 * This involves two 'find' operations and one constant-time link,
 * so it's also nearly constant time on average due to the optimizations.
 * - **inSameSet(i, j):** O(\alpha(N)) (Amortized)
 * This is just two 'find' operations.
 *
 * @subsection space Space Complexity
 * - **Overall:** O(N)
 * We store two vectors, 'parent' and 'component_size', both of size N.
 */
#include <iostream>
#include <vector>
#include <numeric> // for std::iota

// ---------------------- DSU Class ----------------------
class DSU {
private:
    std::vector<int> parent;          // parent[i] = parent of node i
    std::vector<int> component_size;  // size of each connected component
    int num_components;               // total number of disjoint sets

public:
    // Constructor: initializes DSU with 'n' elements (0 to n-1)
    DSU(int n) {
        num_components = n;
        parent.resize(n);
        component_size.resize(n);

        std::iota(parent.begin(), parent.end(), 0); // parent[i] = i
        std::fill(component_size.begin(), component_size.end(), 1); // all sizes = 1
    }

    // Find operation with path compression
    int find(int i) {
        if (parent[i] == i) return i;       // if i is its own parent → root
        return parent[i] = find(parent[i]); // path compression step
    }

    // Union operation with union by size
    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) return false; // already in same set

        // attach smaller tree to larger tree
        if (component_size[rootA] < component_size[rootB])
            std::swap(rootA, rootB);

        parent[rootB] = rootA;
        component_size[rootA] += component_size[rootB];
        num_components--;
        return true;
    }

    // Check if two elements belong to the same set
    bool inSameSet(int a, int b) {
        return find(a) == find(b);
    }

    // Get size of the set containing element 'i'
    int getComponentSize(int i) {
        return component_size[find(i)];
    }

    // Get total number of disjoint sets
    int getComponentCount() {
        return num_components;
    }
};

// ---------------------- Main Function ----------------------
int main() {
    DSU dsu(5); // 5 elements → {0}, {1}, {2}, {3}, {4}

    // Merge some sets
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    // Check relationships
    std::cout << "Are 0 and 2 in same set? " 
              << (dsu.inSameSet(0, 2) ? "Yes" : "No") << "\n";

    std::cout << "Are 1 and 3 in same set? " 
              << (dsu.inSameSet(1, 3) ? "Yes" : "No") << "\n";

    // Show component sizes
    std::cout << "Size of component containing 0: " 
              << dsu.getComponentSize(0) << "\n";

    // Total number of disjoint sets
    std::cout << "Total components: " 
              << dsu.getComponentCount() << "\n";

    return 0;
}
