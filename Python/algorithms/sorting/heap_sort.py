"""
Heap Sort Algorithm
Time Complexity: O(n log n) in all cases
Space Complexity: O(1) - sorts in place
Author: Karanjot Singh
Date: October 2025
Hacktoberfest 2025
"""

def heapify(arr, n, i):
    """
    Heapify subtree rooted at index i

    Args:
        arr: Array to heapify
        n: Size of heap
        i: Root index of subtree
    """
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    # Check if left child exists and is greater than root
    if left < n and arr[left] > arr[largest]:
        largest = left

    # Check if right child exists and is greater than largest so far
    if right < n and arr[right] > arr[largest]:
        largest = right

    # If largest is not root, swap and continue heapifying
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heap_sort(arr):
    """
    Heap sort implementation

    Steps:
    1. Build max heap from array
    2. Extract elements one by one from heap
    3. Place extracted element at the end

    Args:
        arr: List to sort (modified in place)
    """
    n = len(arr)

    # Build max heap
    # Start from last non-leaf node and heapify each node
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extract elements from heap one by one
    for i in range(n - 1, 0, -1):
        # Move current root to end
        arr[0], arr[i] = arr[i], arr[0]

        # Heapify the reduced heap
        heapify(arr, i, 0)


def heap_sort_copy(arr):
    """
    Heap sort that returns sorted copy

    Args:
        arr: List to sort

    Returns:
        Sorted copy of the list
    """
    arr_copy = arr.copy()
    heap_sort(arr_copy)
    return arr_copy


# Test cases
if __name__ == "__main__":
    print("=== Heap Sort Algorithm ===\n")

    # Test case 1: Random array
    test1 = [12, 11, 13, 5, 6, 7]
    print(f"Original array: {test1}")
    sorted1 = heap_sort_copy(test1)
    print(f"Sorted array:   {sorted1}")

    # Test case 2: Already sorted
    test2 = [1, 2, 3, 4, 5]
    print(f"\nOriginal array: {test2}")
    sorted2 = heap_sort_copy(test2)
    print(f"Sorted array:   {sorted2}")

    # Test case 3: Reverse sorted
    test3 = [10, 8, 6, 4, 2]
    print(f"\nOriginal array: {test3}")
    sorted3 = heap_sort_copy(test3)
    print(f"Sorted array:   {sorted3}")

    # Test case 4: Array with duplicates
    test4 = [4, 10, 3, 5, 1, 3, 10]
    print(f"\nOriginal array: {test4}")
    sorted4 = heap_sort_copy(test4)
    print(f"Sorted array:   {sorted4}")

    # Test case 5: Large array
    test5 = [64, 34, 25, 12, 22, 11, 90, 88, 45, 50, 23, 36]
    print(f"\nOriginal array: {test5}")
    sorted5 = heap_sort_copy(test5)
    print(f"Sorted array:   {sorted5}")

    # Test case 6: Single element
    test6 = [42]
    print(f"\nOriginal array: {test6}")
    sorted6 = heap_sort_copy(test6)
    print(f"Sorted array:   {sorted6}")

    print("\n✅ All test cases completed!")
