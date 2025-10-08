# Merge Sort Algorithm in Python
# Description:
# Merge Sort is a Divide and Conquer algorithm that recursively divides
# the array into halves, sorts each half, and merges them back together.

def merge_sort(arr):
    """
    Function to perform merge sort on a list.
    Args:
        arr (list): List of elements to be sorted.
    Returns:
        list: Sorted list.
    """
    if len(arr) <= 1:
        return arr

    # Step 1: Divide the array into two halves
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    # Step 2: Recursively sort both halves
    left_sorted = merge_sort(left_half)
    right_sorted = merge_sort(right_half)

    # Step 3: Merge the sorted halves
    return merge(left_sorted, right_sorted)


def merge(left, right):
    """
    Merge two sorted lists into a single sorted list.
    """
    merged = []
    i = j = 0

    # Compare elements and merge in sorted order
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # Add remaining elements (if any)
    merged.extend(left[i:])
    merged.extend(right[j:])

    return merged


# Example usage
if __name__ == "__main__":
    arr = [38, 27, 43, 3, 9, 82, 10]
    print("Original Array:", arr)
    sorted_arr = merge_sort(arr)
    print("Sorted Array:", sorted_arr)
