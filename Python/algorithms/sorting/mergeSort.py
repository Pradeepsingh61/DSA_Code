"""
Algorithm: Merge Sort

Description:
    Merge Sort is a Divide and Conquer sorting algorithm. It divides the input 
    array into two halves, recursively sorts them, and then merges the sorted halves 
    to produce a fully sorted array.

Steps:
    1. Divide the array into two halves until each subarray has one element.
    2. Recursively sort both halves.
    3. Merge the sorted halves to form a larger sorted array.

Use Case:
    Merge Sort is useful when stable sorting is required or when working with 
    linked lists, external sorting (large data that doesn’t fit into memory), 
    and scenarios where worst-case performance guarantees are important.

Time Complexity:
    - Best Case: O(N log N)
    - Average Case: O(N log N)
    - Worst Case: O(N log N)
    
Space Complexity:
    O(N) auxiliary space (due to temporary arrays during merging).

Stability:
    Merge Sort is a **stable sorting algorithm**, meaning it maintains the 
    relative order of equal elements.
"""
