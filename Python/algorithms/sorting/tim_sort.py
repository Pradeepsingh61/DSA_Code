# 📌 Tim Sort Algorithm
# Language: Python
# Category: Sorting
# Time Complexity: O(n log n)
# Space Complexity: O(n)

"""
Tim Sort is a hybrid stable sorting algorithm, derived from merge sort and insertion sort,
designed to perform well on many kinds of real-world data. It is the default sorting
algorithm used in Python's list.sort() and sorted() functions.

It works by dividing the array into blocks called "runs". These runs are then sorted
using insertion sort, and then merged using a modified merge sort.
"""

MIN_MERGE = 32

def calc_min_run(n):
    """Returns the minimum length of a run for Tim Sort."""
    r = 0
    while n >= MIN_MERGE:
        r |= n & 1
        n >>= 1
    return n + r

def insertion_sort(arr, left, right):
    """Sorts a subarray using insertion sort."""
    for i in range(left + 1, right + 1):
        j = i
        while j > left and arr[j] < arr[j - 1]:
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j -= 1

def merge(arr, l, m, r):
    """Merges two sorted subarrays arr[l..m] and arr[m+1..r]."""
    len1, len2 = m - l + 1, r - m
    left, right = [], []
    for i in range(0, len1):
        left.append(arr[l + i])
    for i in range(0, len2):
        right.append(arr[m + 1 + i])

    i, j, k = 0, 0, l

    while i < len1 and j < len2:
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1

    while i < len1:
        arr[k] = left[i]
        k += 1
        i += 1

    while j < len2:
        arr[k] = right[j]
        k += 1
        j += 1

def tim_sort(arr):
    """
    Sorts the input list 'arr' using the Tim Sort algorithm.
    :param arr: list of elements (int/float) to be sorted
    :return: sorted list
    """
    n = len(arr)

    if n == 0:  # Handle empty array
        return arr

    min_run = calc_min_run(n)

    # Sort individual runs of size MIN_MERGE or less using insertion sort
    for i in range(0, n, min_run):
        insertion_sort(arr, i, min((i + min_run - 1), n - 1))

    # Start merging from size MIN_MERGE. It will merge
    # to form size 2*MIN_MERGE, then 4*MIN_MERGE, and so on.
    size = min_run
    while size < n:
        for left in range(0, n, 2 * size):
            mid = min((left + size - 1), (n - 1))
            right = min((left + 2 * size - 1), (n - 1))

            if mid < right:
                merge(arr, left, mid, right)
        size *= 2

    return arr

# 🧪 Example usage
if __name__ == "__main__":
    sample_array = [38, 27, 43, 3, 9, 82, 10]
    print("Original array:", sample_array)
    sorted_array = tim_sort(sample_array)
    print("Sorted array:", sorted_array)

    sample_array_2 = [5, 4, 3, 2, 1]
    print("Original array 2:", sample_array_2)
    sorted_array_2 = tim_sort(sample_array_2)
    print("Sorted array 2:", sorted_array_2)

    sample_array_3 = []
    print("Original array 3:", sample_array_3)
    sorted_array_3 = tim_sort(sample_array_3)
    print("Sorted array 3:", sorted_array_3)

    sample_array_4 = [1]
    print("Original array 4:", sample_array_4)
    sorted_array_4 = tim_sort(sample_array_4)
    print("Sorted array 4:", sorted_array_4)

    sample_array_5 = [1, 2, 3, 4, 5]
    print("Original array 5:", sample_array_5)
    sorted_array_5 = tim_sort(sample_array_5)
    print("Sorted array 5:", sorted_array_5)