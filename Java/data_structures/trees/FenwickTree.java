/**
 * Fenwick Tree (Binary Indexed Tree) Implementation in Java
 * 
 * Algorithm Name: Fenwick Tree (Binary Indexed Tree)
 * Programming Language: Java
 * Category: Data Structures - Trees
 * Difficulty Level: Medium (Intermediate)
 * 
 * Algorithm Description:
 * A Fenwick Tree (Binary Indexed Tree) is a data structure that efficiently supports
 * prefix sum queries and point updates on an array. It provides both operations in
 * O(log n) time complexity, making it much more efficient than naive approaches.
 * 
 * Key Features:
 * - Range sum queries in O(log n)
 * - Point updates in O(log n)
 * - Space complexity: O(n)
 * - Uses bit manipulation for efficient tree traversal
 * 
 * Applications:
 * - Prefix sum calculations
 * - Range sum queries
 * - Frequency counting
 * - Inversion counting
 * - 2D range sum queries (with 2D Fenwick Tree)
 */

import java.util.Arrays;

public class FenwickTree {
    private int[] tree;
    private int n;
    
    /**
     * Constructor to initialize Fenwick Tree
     * @param size Size of the array
     */
    public FenwickTree(int size) {
        this.n = size;
        this.tree = new int[n + 1]; // 1-indexed for easier bit manipulation
    }
    
    /**
     * Constructor to initialize Fenwick Tree with an array
     * @param arr Input array to build the tree from
     */
    public FenwickTree(int[] arr) {
        this.n = arr.length;
        this.tree = new int[n + 1];
        
        // Build the tree by updating each element
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }
    
    /**
     * Update the value at index by adding delta
     * Time Complexity: O(log n)
     * @param index 0-based index to update
     * @param delta Value to add to the current value
     */
    public void update(int index, int delta) {
        index++; // Convert to 1-based indexing
        
        while (index <= n) {
            tree[index] += delta;
            index += index & (-index); // Add the lowest set bit
        }
    }
    
    /**
     * Set the value at index to val
     * Time Complexity: O(log n)
     * @param index 0-based index to set
     * @param val New value to set
     */
    public void set(int index, int val) {
        int currentVal = query(index, index);
        update(index, val - currentVal);
    }
    
    /**
     * Get prefix sum from index 0 to index (inclusive)
     * Time Complexity: O(log n)
     * @param index 0-based index (inclusive)
     * @return Sum from 0 to index
     */
    public int prefixSum(int index) {
        index++; // Convert to 1-based indexing
        int sum = 0;
        
        while (index > 0) {
            sum += tree[index];
            index -= index & (-index); // Remove the lowest set bit
        }
        
        return sum;
    }
    
    /**
     * Get range sum from left to right (both inclusive)
     * Time Complexity: O(log n)
     * @param left Left boundary (0-based, inclusive)
     * @param right Right boundary (0-based, inclusive)
     * @return Sum from left to right
     */
    public int query(int left, int right) {
        if (left > right) return 0;
        if (left == 0) return prefixSum(right);
        return prefixSum(right) - prefixSum(left - 1);
    }
    
    /**
     * Get the current value at a specific index
     * Time Complexity: O(log n)
     * @param index 0-based index
     * @return Current value at index
     */
    public int get(int index) {
        return query(index, index);
    }
    
    /**
     * Display the current state of the tree (for debugging)
     */
    public void displayTree() {
        System.out.println("Fenwick Tree: " + Arrays.toString(Arrays.copyOfRange(tree, 1, n + 1)));
    }
    
    /**
     * Get the size of the tree
     * @return Size of the tree
     */
    public int size() {
        return n;
    }
    
    /**
     * Main method with comprehensive test cases
     */
    public static void main(String[] args) {
        System.out.println("=== Fenwick Tree (Binary Indexed Tree) Demo ===\n");
        
        // Test Case 1: Basic operations
        System.out.println("Test Case 1: Basic Operations");
        int[] arr = {1, 3, 5, 7, 9, 11};
        FenwickTree ft = new FenwickTree(arr);
        
        System.out.println("Original array: " + Arrays.toString(arr));
        System.out.println("Prefix sum [0-2]: " + ft.prefixSum(2)); // Should be 1+3+5 = 9
        System.out.println("Range sum [1-4]: " + ft.query(1, 4)); // Should be 3+5+7+9 = 24
        System.out.println("Value at index 3: " + ft.get(3)); // Should be 7
        
        // Test Case 2: Updates
        System.out.println("\nTest Case 2: Updates");
        ft.update(2, 5); // Add 5 to index 2 (5 becomes 10)
        System.out.println("After adding 5 to index 2:");
        System.out.println("New value at index 2: " + ft.get(2)); // Should be 10
        System.out.println("New range sum [1-4]: " + ft.query(1, 4)); // Should be 3+10+7+9 = 29
        
        // Test Case 3: Set operation
        System.out.println("\nTest Case 3: Set Operation");
        ft.set(4, 15); // Set index 4 to 15 (was 9)
        System.out.println("After setting index 4 to 15:");
        System.out.println("Value at index 4: " + ft.get(4)); // Should be 15
        System.out.println("Range sum [3-5]: " + ft.query(3, 5)); // Should be 7+15+11 = 33
        
        // Test Case 4: Edge cases
        System.out.println("\nTest Case 4: Edge Cases");
        System.out.println("Single element range [2-2]: " + ft.query(2, 2)); // Should be 10
        System.out.println("Full array sum [0-5]: " + ft.query(0, 5)); // Should be sum of all elements
        System.out.println("Empty range [3-2]: " + ft.query(3, 2)); // Should be 0
        
        // Test Case 5: Large array performance test
        System.out.println("\nTest Case 5: Performance Test with Large Array");
        int size = 100000;
        FenwickTree largeFt = new FenwickTree(size);
        
        long startTime = System.nanoTime();
        
        // Perform multiple updates and queries
        for (int i = 0; i < 1000; i++) {
            largeFt.update(i % size, 1);
            largeFt.query(0, i % size);
        }
        
        long endTime = System.nanoTime();
        double duration = (endTime - startTime) / 1_000_000.0; // Convert to milliseconds
        
        System.out.println("Performed 1000 updates and 1000 queries on array of size " + size);
        System.out.println("Time taken: " + String.format("%.2f", duration) + " ms");
        
        // Test Case 6: Frequency counting example
        System.out.println("\nTest Case 6: Frequency Counting Example");
        FenwickTree freqTree = new FenwickTree(10); // For numbers 0-9
        
        // Add some numbers
        int[] numbers = {1, 3, 1, 5, 3, 1, 7, 5, 9, 1};
        for (int num : numbers) {
            freqTree.update(num, 1); // Increment frequency
        }
        
        System.out.println("Numbers added: " + Arrays.toString(numbers));
        System.out.println("Frequency of 1: " + freqTree.get(1)); // Should be 4
        System.out.println("Frequency of 3: " + freqTree.get(3)); // Should be 2
        System.out.println("Count of numbers <= 5: " + freqTree.prefixSum(5)); // Should be 8
        System.out.println("Count of numbers in range [3-7]: " + freqTree.query(3, 7)); // Should be 5
        
        System.out.println("\n=== Demo Complete ===");
    }
}

/*
Time Complexity Analysis:
- Construction: O(n log n) when built from array, O(1) for empty tree
- Update: O(log n)
- Query (range sum): O(log n)
- Prefix sum: O(log n)
- Space Complexity: O(n)

Space Complexity: O(n) for storing the tree array

Key Advantages:
1. Efficient range sum queries and updates
2. Simple implementation using bit manipulation
3. Cache-friendly due to array-based structure
4. Supports both point updates and range queries
5. Can be extended to 2D for matrix operations

Applications:
- Competitive programming problems involving range sums
- Database indexing for range queries
- Real-time analytics with frequent updates
- Inversion counting in arrays
- Order statistics problems
*/

/*
Expected Output:
=== Fenwick Tree (Binary Indexed Tree) Demo ===

Test Case 1: Basic Operations
Original array: [1, 3, 5, 7, 9, 11]
Prefix sum [0-2]: 9
Range sum [1-4]: 24
Value at index 3: 7

Test Case 2: Updates
After adding 5 to index 2:
New value at index 2: 10
New range sum [1-4]: 29

Test Case 3: Set Operation
After setting index 4 to 15:
Value at index 4: 15
Range sum [3-5]: 33

Test Case 4: Edge Cases
Single element range [2-2]: 10
Full array sum [0-5]: 43
Empty range [3-2]: 0

Test Case 5: Performance Test with Large Array
Performed 1000 updates and 1000 queries on array of size 100000
Time taken: [varies] ms

Test Case 6: Frequency Counting Example
Numbers added: [1, 3, 1, 5, 3, 1, 7, 5, 9, 1]
Frequency of 1: 4
Frequency of 3: 2
Count of numbers <= 5: 8
Count of numbers in range [3-7]: 5

=== Demo Complete ===
*/
