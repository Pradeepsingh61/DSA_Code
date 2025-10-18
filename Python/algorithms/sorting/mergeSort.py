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
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2  
        L = arr[:mid]        
        R = arr[mid:]

        # Recursive calls to sort both halves
        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

        # Merge the two halves
        while i < len(L) and j < len(R):
            if L[i] <= R[j]:   
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        # Copy any remaining elements of L
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        # Copy any remaining elements of R
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1



if __name__ == "__main__":
    arr = [38, 27, 43, 3, 9, 82, 10]
    print("Original array:", arr)
    merge_sort(arr)
    print("Sorted array:", arr)
# Sorted array: [3, 9, 10, 27, 38, 43, 82]
