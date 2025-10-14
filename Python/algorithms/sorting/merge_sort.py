# Merge Sort Algorithm
# Language: Python
# Category: Sorting
# Difficulty: Medium
# Time Complexity: O(n log n)
# Space Complexity: O(n)

"""
Merge Sort is a Divide and Conquer algorithm that recursively divides
an array into halves, sorts each half, and merges the sorted halves into
a single sorted array.

Steps:
1. Divide: Split the array into two halves.
2. Conquer: Recursively sort each half.
3. Combine: Merge the sorted halves.

Complexity Analysis:
- Time Complexity: O(n log n)
- Space Complexity: O(n)
"""

def merge_sort(arr):
    """Performs merge sort and returns a sorted list."""
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_sorted = merge_sort(arr[:mid])
    right_sorted = merge_sort(arr[mid:])

    return merge(left_sorted, right_sorted)


def merge(left, right):
    """Merges two sorted lists into one sorted list."""
    merged = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    merged.extend(left[i:])
    merged.extend(right[j:])
    return merged


# Example Test Cases
if __name__ == "__main__":
    test_cases = [
        [38, 27, 43, 3, 9, 82, 10],
        [5, 2, 8, 1, 3],
        [],
        [1],
        [10, 10, 10],
    ]

    for i, arr in enumerate(test_cases, 1):
        print(f"Test Case {i}:")
        print("Original:", arr)
        print("Sorted:  ", merge_sort(arr))
        print("-" * 30)
