/**
 * @file disjoint_set_union.cpp
 * @brief Simple and optimized implementation of Disjoint Set Union (Union-Find)
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
