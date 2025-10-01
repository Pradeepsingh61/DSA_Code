"""
Radix Sort Algorithm
Time Complexity: O(d * (n + k)) where d is number of digits, k is range of digits
Space Complexity: O(n + k)
Author: Karanjot Singh
Date: October 2025
Hacktoberfest 2025
"""

def counting_sort_for_radix(arr, exp):
    """
    Counting sort based on digit position (exp)
    Used as subroutine in radix sort

    Args:
        arr: Array to sort
        exp: Current digit position (1, 10, 100, ...)
    """
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    # Store count of occurrences
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1

    # Change count[i] to contain actual position in output
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build output array
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1

    # Copy output array to arr
    for i in range(n):
        arr[i] = output[i]


def radix_sort(arr):
    """
    Radix sort implementation for non-negative integers

    Sorts by processing digits from least significant to most significant
    Uses counting sort as stable sort for each digit

    Args:
        arr: List of non-negative integers to sort (modified in place)
    """
    if not arr:
        return

    # Find maximum number to determine number of digits
    max_num = max(arr)

    # Apply counting sort to sort elements based on place value
    exp = 1
    while max_num // exp > 0:
        counting_sort_for_radix(arr, exp)
        exp *= 10


def radix_sort_copy(arr):
    """
    Radix sort that returns sorted copy

    Args:
        arr: List of non-negative integers to sort

    Returns:
        Sorted copy of the list
    """
    arr_copy = arr.copy()
    radix_sort(arr_copy)
    return arr_copy


# Test cases
if __name__ == "__main__":
    print("=== Radix Sort Algorithm ===\n")

    # Test case 1: Random array
    test1 = [170, 45, 75, 90, 802, 24, 2, 66]
    print(f"Original array: {test1}")
    sorted1 = radix_sort_copy(test1)
    print(f"Sorted array:   {sorted1}")

    # Test case 2: Already sorted
    test2 = [1, 2, 3, 4, 5]
    print(f"\nOriginal array: {test2}")
    sorted2 = radix_sort_copy(test2)
    print(f"Sorted array:   {sorted2}")

    # Test case 3: Reverse sorted
    test3 = [543, 321, 123, 54, 21]
    print(f"\nOriginal array: {test3}")
    sorted3 = radix_sort_copy(test3)
    print(f"Sorted array:   {sorted3}")

    # Test case 4: Array with duplicates
    test4 = [100, 50, 200, 50, 100, 25]
    print(f"\nOriginal array: {test4}")
    sorted4 = radix_sort_copy(test4)
    print(f"Sorted array:   {sorted4}")

    # Test case 5: Single digit numbers
    test5 = [9, 3, 7, 1, 5, 2, 8]
    print(f"\nOriginal array: {test5}")
    sorted5 = radix_sort_copy(test5)
    print(f"Sorted array:   {sorted5}")

    # Test case 6: Large numbers
    test6 = [12345, 987, 54321, 123, 9876, 456]
    print(f"\nOriginal array: {test6}")
    sorted6 = radix_sort_copy(test6)
    print(f"Sorted array:   {sorted6}")

    # Test case 7: Single element
    test7 = [42]
    print(f"\nOriginal array: {test7}")
    sorted7 = radix_sort_copy(test7)
    print(f"Sorted array:   {sorted7}")

    print("\n✅ All test cases completed!")
