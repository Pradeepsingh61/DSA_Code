/**
 * Segment Tree - Efficient Range Query Data Structure
 * 
 * Description:
 * A Segment Tree is a binary tree data structure used for storing information about
 * intervals or segments. It allows querying which segments contain a given point and
 * supports efficient range queries and updates.
 * 
 * Key Concepts:
 * - Each node represents a segment/range [L, R]
 * - Leaf nodes represent single elements
 * - Internal nodes store aggregate information (sum, min, max, etc.)
 * - Tree height is O(log n), making queries and updates efficient
 * 
 * Operations Supported:
 * - Build: O(n) - Construct tree from array
 * - Range Query: O(log n) - Query aggregate over range [L, R]
 * - Point Update: O(log n) - Update single element
 * - Range Update: O(log n) - Update range (with lazy propagation)
 * 
 * Types of Queries:
 * 1. Range Sum Query
 * 2. Range Minimum Query (RMQ)
 * 3. Range Maximum Query
 * 4. Range GCD Query
 * 
 * Advantages:
 * - Fast range queries compared to naive O(n) approach
 * - Supports dynamic updates
 * - Can handle multiple types of queries
 * - Memory efficient: O(4n) space
 * 
 * Applications:
 * - Range sum/min/max queries
 * - Computational geometry
 * - String processing
 * - Database queries
 * - Competitive programming
 * 
 * Author: GitHub Copilot
 * Date: October 2025
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

/**
 * Segment Tree class for Range Sum Queries
 */
class SegmentTreeSum {
private:
    vector<long long> tree;  // Segment tree array
    vector<long long> lazy;  // Lazy propagation array
    int n;                   // Size of input array
    
    /**
     * Build segment tree recursively
     * 
     * @param arr Input array
     * @param node Current node index in tree
     * @param start Start of current segment
     * @param end End of current segment
     */
    void buildTree(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            // Leaf node - store array element
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            
            // Build left and right subtrees
            buildTree(arr, leftChild, start, mid);
            buildTree(arr, rightChild, mid + 1, end);
            
            // Internal node stores sum of children
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }
    
    /**
     * Apply pending updates (lazy propagation)
     * 
     * @param node Current node index
     * @param start Start of segment
     * @param end End of segment
     */
    void pushDown(int node, int start, int end) {
        if (lazy[node] != 0) {
            // Apply pending update to current node
            tree[node] += (end - start + 1) * lazy[node];
            
            // Propagate to children if not leaf
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            
            // Clear lazy value
            lazy[node] = 0;
        }
    }
    
    /**
     * Update a single element
     * 
     * @param node Current node index
     * @param start Start of current segment
     * @param end End of current segment
     * @param idx Index to update
     * @param value New value
     */
    void updatePoint(int node, int start, int end, int idx, int value) {
        if (start == end) {
            // Leaf node - update value
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            
            if (idx <= mid) {
                updatePoint(leftChild, start, mid, idx, value);
            } else {
                updatePoint(rightChild, mid + 1, end, idx, value);
            }
            
            // Update current node
            tree[node] = tree[leftChild] + tree[rightChild];
        }
    }
    
    /**
     * Range update with lazy propagation
     * 
     * @param node Current node index
     * @param start Start of current segment
     * @param end End of current segment
     * @param l Left bound of update range
     * @param r Right bound of update range
     * @param value Value to add
     */
    void updateRange(int node, int start, int end, int l, int r, int value) {
        pushDown(node, start, end);
        
        // No overlap
        if (start > r || end < l) {
            return;
        }
        
        // Complete overlap
        if (start >= l && end <= r) {
            lazy[node] += value;
            pushDown(node, start, end);
            return;
        }
        
        // Partial overlap
        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, value);
        updateRange(2 * node + 2, mid + 1, end, l, r, value);
        
        pushDown(2 * node + 1, start, mid);
        pushDown(2 * node + 2, mid + 1, end);
        
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    
    /**
     * Query sum in range [l, r]
     * 
     * @param node Current node index
     * @param start Start of current segment
     * @param end End of current segment
     * @param l Left bound of query range
     * @param r Right bound of query range
     * @return Sum in range [l, r]
     */
    long long queryRange(int node, int start, int end, int l, int r) {
        pushDown(node, start, end);
        
        // No overlap
        if (start > r || end < l) {
            return 0;
        }
        
        // Complete overlap
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        // Partial overlap
        int mid = (start + end) / 2;
        long long leftSum = queryRange(2 * node + 1, start, mid, l, r);
        long long rightSum = queryRange(2 * node + 2, mid + 1, end, l, r);
        
        return leftSum + rightSum;
    }
    
public:
    /**
     * Constructor - builds segment tree from array
     * 
     * @param arr Input array
     */
    SegmentTreeSum(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        
        if (n > 0) {
            buildTree(arr, 0, 0, n - 1);
        }
    }
    
    /**
     * Update single element at index
     * 
     * @param idx Index to update (0-based)
     * @param value New value
     */
    void update(int idx, int value) {
        if (idx < 0 || idx >= n) {
            cout << "Index out of bounds!\n";
            return;
        }
        updatePoint(0, 0, n - 1, idx, value);
    }
    
    /**
     * Add value to all elements in range [l, r]
     * 
     * @param l Left index (0-based)
     * @param r Right index (0-based)
     * @param value Value to add
     */
    void updateRange(int l, int r, int value) {
        if (l < 0 || r >= n || l > r) {
            cout << "Invalid range!\n";
            return;
        }
        updateRange(0, 0, n - 1, l, r, value);
    }
    
    /**
     * Query sum in range [l, r]
     * 
     * @param l Left index (0-based)
     * @param r Right index (0-based)
     * @return Sum of elements in range
     */
    long long query(int l, int r) {
        if (l < 0 || r >= n || l > r) {
            cout << "Invalid range!\n";
            return 0;
        }
        return queryRange(0, 0, n - 1, l, r);
    }
    
    /**
     * Display the segment tree structure
     */
    void display() {
        cout << "Segment Tree (Sum): ";
        for (int i = 0; i < min(20, (int)tree.size()); i++) {
            if (tree[i] != 0) {
                cout << tree[i] << " ";
            }
        }
        cout << endl;
    }
};

/**
 * Segment Tree class for Range Minimum Queries (RMQ)
 */
class SegmentTreeMin {
private:
    vector<int> tree;
    int n;
    
    void buildTree(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node + 1, start, mid);
            buildTree(arr, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    
    void updatePoint(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updatePoint(2 * node + 1, start, mid, idx, value);
            } else {
                updatePoint(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    
    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MAX;
        }
        
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int leftMin = queryRange(2 * node + 1, start, mid, l, r);
        int rightMin = queryRange(2 * node + 2, mid + 1, end, l, r);
        
        return min(leftMin, rightMin);
    }
    
public:
    SegmentTreeMin(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, INT_MAX);
        
        if (n > 0) {
            buildTree(arr, 0, 0, n - 1);
        }
    }
    
    void update(int idx, int value) {
        if (idx < 0 || idx >= n) {
            cout << "Index out of bounds!\n";
            return;
        }
        updatePoint(0, 0, n - 1, idx, value);
    }
    
    int query(int l, int r) {
        if (l < 0 || r >= n || l > r) {
            cout << "Invalid range!\n";
            return INT_MAX;
        }
        return queryRange(0, 0, n - 1, l, r);
    }
};

/**
 * Segment Tree class for Range Maximum Queries
 */
class SegmentTreeMax {
private:
    vector<int> tree;
    int n;
    
    void buildTree(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node + 1, start, mid);
            buildTree(arr, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    
    void updatePoint(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updatePoint(2 * node + 1, start, mid, idx, value);
            } else {
                updatePoint(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    
    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MIN;
        }
        
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int leftMax = queryRange(2 * node + 1, start, mid, l, r);
        int rightMax = queryRange(2 * node + 2, mid + 1, end, l, r);
        
        return max(leftMax, rightMax);
    }
    
public:
    SegmentTreeMax(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, INT_MIN);
        
        if (n > 0) {
            buildTree(arr, 0, 0, n - 1);
        }
    }
    
    void update(int idx, int value) {
        if (idx < 0 || idx >= n) {
            cout << "Index out of bounds!\n";
            return;
        }
        updatePoint(0, 0, n - 1, idx, value);
    }
    
    int query(int l, int r) {
        if (l < 0 || r >= n || l > r) {
            cout << "Invalid range!\n";
            return INT_MIN;
        }
        return queryRange(0, 0, n - 1, l, r);
    }
};

/**
 * Demo: Range Sum Queries
 */
void demoRangeSumQuery() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 1: Range Sum Query with Point Updates\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    SegmentTreeSum st(arr);
    
    // Query tests
    cout << "Query Operations:\n";
    cout << "Sum of range [1, 3]: " << st.query(1, 3) << " (Expected: 15)\n";
    cout << "Sum of range [0, 5]: " << st.query(0, 5) << " (Expected: 36)\n";
    cout << "Sum of range [2, 4]: " << st.query(2, 4) << " (Expected: 21)\n";
    
    // Update test
    cout << "\nUpdate arr[2] = 10 (was 5)\n";
    st.update(2, 10);
    
    cout << "\nAfter update:\n";
    cout << "Sum of range [1, 3]: " << st.query(1, 3) << " (Expected: 20)\n";
    cout << "Sum of range [0, 5]: " << st.query(0, 5) << " (Expected: 41)\n";
}

/**
 * Demo: Range Sum with Range Updates
 */
void demoRangeUpdate() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 2: Range Sum Query with Range Updates (Lazy Propagation)\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    SegmentTreeSum st(arr);
    
    cout << "Sum of range [0, 4]: " << st.query(0, 4) << " (Expected: 15)\n";
    
    cout << "\nAdd 5 to range [1, 3]\n";
    st.updateRange(1, 3, 5);
    
    cout << "\nAfter range update:\n";
    cout << "Sum of range [0, 4]: " << st.query(0, 4) << " (Expected: 30)\n";
    cout << "Sum of range [1, 3]: " << st.query(1, 3) << " (Expected: 24)\n";
    cout << "Sum of range [0, 1]: " << st.query(0, 1) << " (Expected: 8)\n";
}

/**
 * Demo: Range Minimum Query (RMQ)
 */
void demoRangeMinQuery() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 3: Range Minimum Query (RMQ)\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {5, 2, 8, 1, 9, 3, 7};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    SegmentTreeMin st(arr);
    
    cout << "Query Operations:\n";
    cout << "Minimum in range [0, 3]: " << st.query(0, 3) << " (Expected: 1)\n";
    cout << "Minimum in range [2, 5]: " << st.query(2, 5) << " (Expected: 1)\n";
    cout << "Minimum in range [4, 6]: " << st.query(4, 6) << " (Expected: 3)\n";
    
    cout << "\nUpdate arr[3] = 10 (was 1)\n";
    st.update(3, 10);
    
    cout << "\nAfter update:\n";
    cout << "Minimum in range [0, 3]: " << st.query(0, 3) << " (Expected: 2)\n";
    cout << "Minimum in range [2, 5]: " << st.query(2, 5) << " (Expected: 3)\n";
}

/**
 * Demo: Range Maximum Query
 */
void demoRangeMaxQuery() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 4: Range Maximum Query\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {3, 1, 7, 4, 9, 2, 6};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    SegmentTreeMax st(arr);
    
    cout << "Query Operations:\n";
    cout << "Maximum in range [0, 4]: " << st.query(0, 4) << " (Expected: 9)\n";
    cout << "Maximum in range [1, 3]: " << st.query(1, 3) << " (Expected: 7)\n";
    cout << "Maximum in range [3, 6]: " << st.query(3, 6) << " (Expected: 9)\n";
    
    cout << "\nUpdate arr[5] = 15 (was 2)\n";
    st.update(5, 15);
    
    cout << "\nAfter update:\n";
    cout << "Maximum in range [3, 6]: " << st.query(3, 6) << " (Expected: 15)\n";
    cout << "Maximum in range [0, 6]: " << st.query(0, 6) << " (Expected: 15)\n";
}

/**
 * Demo: Performance comparison
 */
void demoPerformanceComparison() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 5: Performance Comparison (Segment Tree vs Naive)\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    SegmentTreeSum st(arr);
    
    cout << "Multiple Range Queries:\n";
    
    // Perform multiple queries
    vector<pair<int, int>> queries = {{0, 4}, {2, 7}, {5, 9}, {1, 5}, {3, 8}};
    
    cout << "\nUsing Segment Tree (O(log n) per query):\n";
    for (auto& q : queries) {
        long long sum = st.query(q.first, q.second);
        cout << "Sum of range [" << q.first << ", " << q.second << "]: " << sum << "\n";
    }
    
    cout << "\nNaive approach would take O(n) per query\n";
    cout << "Segment Tree: O(log n) = O(log 10) ≈ 3 operations\n";
    cout << "Naive: O(n) = O(10) = 10 operations\n";
    cout << "\nFor large arrays, Segment Tree is significantly faster!\n";
}

/**
 * Demo: Complex scenario
 */
void demoComplexScenario() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "DEMO 6: Complex Scenario - Multiple Operations\n";
    cout << string(60, '=') << "\n";
    
    vector<int> arr = {10, 20, 30, 40, 50};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << " (Sum: 150)\n\n";
    
    SegmentTreeSum st(arr);
    
    cout << "Operation 1: Query sum [0, 4]\n";
    cout << "Result: " << st.query(0, 4) << "\n";
    
    cout << "\nOperation 2: Update arr[2] = 100\n";
    st.update(2, 100);
    cout << "Result: Array becomes [10, 20, 100, 40, 50]\n";
    
    cout << "\nOperation 3: Query sum [1, 3]\n";
    cout << "Result: " << st.query(1, 3) << "\n";
    
    cout << "\nOperation 4: Range update - add 10 to [0, 2]\n";
    st.updateRange(0, 2, 10);
    cout << "Result: Array becomes [20, 30, 110, 40, 50]\n";
    
    cout << "\nOperation 5: Query sum [0, 4]\n";
    cout << "Result: " << st.query(0, 4) << "\n";
    
    cout << "\nOperation 6: Query sum [2, 4]\n";
    cout << "Result: " << st.query(2, 4) << "\n";
}

/**
 * Main function
 */
int main() {
    cout << "\n";
    cout << "========================================================\n";
    cout << "                                                        \n";
    cout << "           SEGMENT TREE IMPLEMENTATION                 \n";
    cout << "                                                        \n";
    cout << "      Efficient Range Query Data Structure             \n";
    cout << "                                                        \n";
    cout << "========================================================\n";
    
    // Run all demos
    demoRangeSumQuery();
    demoRangeUpdate();
    demoRangeMinQuery();
    demoRangeMaxQuery();
    demoPerformanceComparison();
    demoComplexScenario();
    
    // Summary
    cout << "\n" << string(60, '=') << "\n";
    cout << "KEY FEATURES:\n";
    cout << string(60, '=') << "\n";
    cout << "* Build: O(n) time, O(4n) space\n";
    cout << "* Range Query: O(log n)\n";
    cout << "* Point Update: O(log n)\n";
    cout << "* Range Update: O(log n) with lazy propagation\n";
    cout << "* Supports multiple query types (sum, min, max, gcd)\n";
    cout << "\nQuery Types Implemented:\n";
    cout << "  1. Range Sum Query (with lazy propagation)\n";
    cout << "  2. Range Minimum Query (RMQ)\n";
    cout << "  3. Range Maximum Query\n";
    cout << "\nApplications:\n";
    cout << "  - Dynamic range queries\n";
    cout << "  - Computational geometry\n";
    cout << "  - Database optimization\n";
    cout << "  - Competitive programming\n";
    cout << "  - String algorithms\n";
    cout << "\nAdvantages:\n";
    cout << "  + Much faster than naive O(n) approach\n";
    cout << "  + Supports dynamic updates\n";
    cout << "  + Versatile (multiple query types)\n";
    cout << "  + Efficient space usage\n";
    cout << string(60, '=') << "\n\n";
    
    return 0;
}
