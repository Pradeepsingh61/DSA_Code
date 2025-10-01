"""
Algorithm: Heap Sort
Description: Comparison-based sorting algorithm using binary heap data structure
Time Complexity: O(n log n) for all cases
Space Complexity: O(1) auxiliary space
Author: Abhijit
"""

def heapify(arr, n, i):
    """
    Heapify a subtree rooted with node i.
    
    Args:
        arr: Array to heapify
        n: Size of heap
        i: Root index of subtree to heapify
    """
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left

    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heap_sort(input_data):
    """
    Sorts an array using heap sort algorithm.

    Args:
        input_data: List of comparable elements to sort

    Returns:
        List: Sorted array in ascending order

    Raises:
        ValueError: When input is invalid
        TypeError: When input is not a list
    """
    if input_data is None:
        raise ValueError("Input cannot be None")
    
    if not isinstance(input_data, list):
        raise TypeError("Input must be a list")
    
    if not input_data:
        return []
    
    # Create a copy to avoid modifying original
    arr = input_data.copy()
    n = len(arr)

    # Build max heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extract elements from heap one by one
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)

    return arr


def main():
    """Test the algorithm with example cases."""
    # Test Case 1
    test_data = [64, 34, 25, 12, 22, 11, 90]
    result = heap_sort(test_data)
    print(f"Original: {test_data}")
    print(f"Sorted: {result}")

    # Test Case 2 - Edge case
    edge_case = []
    try:
        result = heap_sort(edge_case)
        print(f"Empty array result: {result}")
    except ValueError as e:
        print(f"Handled edge case: {e}")

    # Test Case 3 - Single element
    single_element = [42]
    result = heap_sort(single_element)
    print(f"Single element: {single_element} -> {result}")

    # Test Case 4 - Already sorted
    sorted_array = [1, 2, 3, 4, 5]
    result = heap_sort(sorted_array)
    print(f"Already sorted: {sorted_array} -> {result}")

    # Test Case 5 - Reverse sorted
    reverse_sorted = [5, 4, 3, 2, 1]
    result = heap_sort(reverse_sorted)
    print(f"Reverse sorted: {reverse_sorted} -> {result}")


if __name__ == "__main__":
    main()