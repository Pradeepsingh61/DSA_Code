"""
Quick Sort Algorithm
Time Complexity: O(n log n) average, O(n²) worst case
Space Complexity: O(log n) due to recursion stack
Author: Karanjot Singh
Date: October 2025
Hacktoberfest 2025
"""

def partition(arr, low, high):
    """
    Partition function for quick sort
    Places pivot element at correct position and arranges smaller elements to left
    and greater elements to right of pivot

    Args:
        arr: List to partition
        low: Starting index
        high: Ending index

    Returns:
        Partition index
    """
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def quick_sort(arr, low=0, high=None):
    """
    Quick sort implementation using divide and conquer

    Args:
        arr: List to sort
        low: Starting index (default 0)
        high: Ending index (default None, uses len(arr)-1)
    """
    if high is None:
        high = len(arr) - 1

    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)


def quick_sort_wrapper(arr):
    """
    Wrapper function that returns sorted array

    Args:
        arr: List to sort

    Returns:
        Sorted list
    """
    arr_copy = arr.copy()
    quick_sort(arr_copy)
    return arr_copy


# Test cases
if __name__ == "__main__":
    print("=== Quick Sort Algorithm ===\n")

    # Test case 1: Random array
    test1 = [64, 34, 25, 12, 22, 11, 90]
    print(f"Original array: {test1}")
    sorted1 = quick_sort_wrapper(test1)
    print(f"Sorted array:   {sorted1}")

    # Test case 2: Already sorted
    test2 = [1, 2, 3, 4, 5]
    print(f"\nOriginal array: {test2}")
    sorted2 = quick_sort_wrapper(test2)
    print(f"Sorted array:   {sorted2}")

    # Test case 3: Reverse sorted
    test3 = [9, 7, 5, 3, 1]
    print(f"\nOriginal array: {test3}")
    sorted3 = quick_sort_wrapper(test3)
    print(f"Sorted array:   {sorted3}")

    # Test case 4: Array with duplicates
    test4 = [5, 2, 8, 2, 9, 1, 5]
    print(f"\nOriginal array: {test4}")
    sorted4 = quick_sort_wrapper(test4)
    print(f"Sorted array:   {sorted4}")

    # Test case 5: Single element
    test5 = [42]
    print(f"\nOriginal array: {test5}")
    sorted5 = quick_sort_wrapper(test5)
    print(f"Sorted array:   {sorted5}")

    print("\n✅ All test cases completed!")
