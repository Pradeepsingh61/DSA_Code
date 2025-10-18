def counting_sort_for_radix(arr, exp):
    """
    Helper function: Counting sort based on digit represented by exp
    """
    n = len(arr)
    output = [0] * n
    count = [0] * 10  # Base 10 digits (0-9)
    
    # Store count of occurrences
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    
    # Change count[i] to contain actual position
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # Build output array
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    
    # Copy output to arr
    for i in range(n):
        arr[i] = output[i]


def radix_sort(arr):
    """
    Radix Sort Algorithm (LSD - Least Significant Digit)
    Time Complexity: O(d * (n + k)) where d is number of digits, k is base
    Space Complexity: O(n + k)
    
    Sorts integers by processing individual digits.
    Works from least significant to most significant digit.
    """
    if not arr:
        return arr
    
    # Find the maximum number to know number of digits
    max_num = max(arr)
    
    # Do counting sort for every digit
    # exp is 10^i where i is current digit number
    exp = 1
    while max_num // exp > 0:
        counting_sort_for_radix(arr, exp)
        exp *= 10
    
    return arr


def radix_sort_with_negatives(arr):
    """
    Radix Sort that handles negative numbers
    """
    if not arr:
        return arr
    
    # Separate positive and negative numbers
    negative = [abs(x) for x in arr if x < 0]
    positive = [x for x in arr if x >= 0]
    
    # Sort both arrays
    if negative:
        radix_sort(negative)
        negative.reverse()  # Reverse for correct order
        negative = [-x for x in negative]
    
    if positive:
        radix_sort(positive)
    
    # Combine results
    return negative + positive


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [170, 45, 75, 90, 802, 24, 2, 66]
    print("Original array:", arr1)
    print("Sorted array:", radix_sort(arr1.copy()))
    
    # Test case 2
    arr2 = [329, 457, 657, 839, 436, 720, 355]
    print("\nOriginal array:", arr2)
    print("Sorted array:", radix_sort(arr2.copy()))
    
    # Test case 3 - Single digit numbers
    arr3 = [5, 2, 8, 1, 9, 3, 7]
    print("\nSingle digits:", arr3)
    print("Sorted array:", radix_sort(arr3.copy()))
    
    # Test case 4 - With negative numbers
    arr4 = [170, -45, 75, -90, 802, 24, -2, 66]
    print("\nWith negatives:", arr4)
    print("Sorted array:", radix_sort_with_negatives(arr4.copy()))
    
    # Test case 5 - Large numbers
    arr5 = [9999, 1234, 5678, 100, 9876]
    print("\nLarge numbers:", arr5)
    print("Sorted array:", radix_sort(arr5.copy()))
