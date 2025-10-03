# 📌 Merge Sort Algorithm
# Language: Python
# Category: Sorting
# Time Complexity: O(n log n)
# Space Complexity: O(n)

"""
Merge Sort is a classic Divide and Conquer algorithm.
It works in three main steps:
1. Divide: Split the array into two halves.
2. Conquer: Recursively sort the two halves.
3. Combine: Merge the two sorted halves into a single sorted array.
"""

def merge_sort(arr):
    """
    Sorts the input list 'arr' using the Merge Sort algorithm.
    :param arr: list of elements (int/float) to be sorted
    :return: sorted list
    """
    # Base condition: if array has 0 or 1 elements, it's already sorted
    if len(arr) <= 1:
        return arr

    # Step 1: Divide the array into two halves
    mid = len(arr) // 2
    left_half = merge_sort(arr[:mid])
    right_half = merge_sort(arr[mid:])

    # Step 2: Merge the sorted halves
    return merge(left_half, right_half)


def merge(left, right):
    """
    Merges two sorted lists 'left' and 'right' into a single sorted list.
    :param left: sorted list
    :param right: sorted list
    :return: merged sorted list
    """
    merged = []
    i = j = 0

    # Compare elements of both halves and add the smaller one
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # If there are remaining elements in left or right, add them
    merged.extend(left[i:])
    merged.extend(right[j:])

    return merged


# 🧪 Example usage
if __name__ == "__main__":
    sample_array = [38, 27, 43, 3, 9, 82, 10]
    print("Original array:", sample_array)
    sorted_array = merge_sort(sample_array)
    print("Sorted array:", sorted_array)
