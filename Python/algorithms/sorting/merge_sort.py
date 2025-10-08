# Merge Sort Algorithm
# Language: Python
# Category: Sorting
# Time Complexity: O(n log n)
# Space Complexity: O(n)

"""
Merge Sort is a classic Divide and Conquer algorithm.

It works in three main steps:
1 Divide: Split the array into two halves.
2 Conquer: Recursively sort both halves.
3 Combine: Merge the sorted halves into a single sorted array.

Key Advantages:
- Guaranteed O(n log n) performance.
- Stable sorting algorithm.
- Ideal for large datasets.

Drawback:
- Requires extra space (O(n)) for merging.
"""

def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    # Step 1: Divide
    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]

    # Step 2: Conquer (sort recursively)
    left_sorted = merge_sort(left)
    right_sorted = merge_sort(right)

    # Step 3: Combine (merge results)
    return merge(left_sorted, right_sorted)


def merge(left, right):
    result = []
    i = j = 0

    # Compare and merge
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    # Add remaining elements
    result.extend(left[i:])
    result.extend(right[j:])
    return result


if __name__ == "__main__":
    data = [38, 27, 43, 3, 9, 82, 10]
    print("Original Array:", data)
    sorted_data = merge_sort(data)
    print("Sorted Array:", sorted_data)
