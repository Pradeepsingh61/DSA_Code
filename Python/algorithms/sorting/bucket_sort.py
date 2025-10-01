"""
Algorithm: Bucket Sort
Description: Sorts elements by distributing them into buckets, sorting each bucket, and then combining them
Time Complexity: Worst - O(n^2)
Space Complexity: O(n + k)
Author: Kashyap
Date: 2025-10-01
"""

def insertion_sort(bucket: list):
    """
    Sort a single bucket using Insertion Sort.
    
    We use Insertion Sort because buckets usually have few elements,
    making it efficient for small arrays.
    
    Args:
        bucket (list): List of numbers in a bucket
    """
    for current_index in range(1, len(bucket)):
        current_value = bucket[current_index]
        position = current_index - 1
        
        # Shift larger elements one position to the right
        while position >= 0 and bucket[position] > current_value:
            bucket[position + 1] = bucket[position]
            position -= 1
        bucket[position + 1] = current_value


def bucket_sort(array: list):
    """
    Sort the input array using Bucket Sort.

    Steps:
    1. Create empty buckets. Each bucket will hold elements in a value range.
    2. Distribute elements into buckets based on their value.
    3. Sort each bucket individually.
    4. Merge all sorted buckets back into the original array.
    
    Args:
        array (list): List of numbers to be sorted

    Example:
        arr = [0.78, 0.17, 0.39, 0.26, 0.72]
        bucket_sort(arr)
        arr -> [0.17, 0.26, 0.39, 0.72, 0.78]
    """
    n = len(array)
    if n == 0:
        return 

    buckets = [[] for _ in range(n)] # create the n empty lists

    # Distribute elements into buckets
    for value in array:
        bucket_index = int(n * value)
        if bucket_index == n:  # Edge case: value == 1
            bucket_index = n - 1
        buckets[bucket_index].append(value)

    # Sort each bucket individually using insertion sort
    for bucket in buckets:
        insertion_sort(bucket)

    # Merge all buckets into the original array
    current_index = 0
    for bucket in buckets:
        for value in bucket:
            array[current_index] = value
            current_index += 1


# -------------------------------
# Main func and test cases
# -------------------------------

if __name__ == "__main__":
    # Test case 1: 
    test_array1 = [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]
    bucket_sort(test_array1)
    print("Sorted array 1:", test_array1)  # [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94]

    # Test case 2:
    test_array2 = [0.1, 0.2, 0.3, 0.4, 0.5]
    bucket_sort(test_array2)
    print("Sorted array 2:", test_array2)  # [0.1, 0.2, 0.3, 0.4, 0.5]

    # Test case 3:
    test_array3 = [0.4, 0.2, 0.4, 0.1, 0.2]
    bucket_sort(test_array3)
    print("Sorted array 3:", test_array3)  # [0.1, 0.2, 0.2, 0.4, 0.4]

    # Test case 4: 
    test_array4 = []
    bucket_sort(test_array4)
    print("Sorted array 4:", test_array4)  # []

    # Test case 5:
    test_array5 = [0.5]
    bucket_sort(test_array5)
    print("Sorted array 5:", test_array5)  # [0.5]

