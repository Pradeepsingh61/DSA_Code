# 📌 Rotate Array Algorithm

"""
Algorithm: Rotate Array
Description: Rotates an array to the right by k steps.

There are several approaches to rotate an array:
1. Using a temporary array: Copy elements to a new array, then copy back.
2. Using slicing (Pythonic way): Concatenate slices of the array.
3. Using reversal: Reverse the entire array, then reverse the first k elements, and finally reverse the remaining n-k elements.
4. Using Juggling Algorithm (for in-place rotation with O(1) space).

Time Complexity:
- Slicing: O(n) for creating new lists.
- Reversal: O(n) as each element is reversed at most twice.
- Temporary array: O(n) for copying elements.

Space Complexity:
- Slicing: O(n) for creating new lists.
- Reversal: O(1) for in-place modification.
- Temporary array: O(n) for the temporary array.

Author: Gemini
"""

def rotate_array_reversal(nums: list[int], k: int) -> None:
    """
    Rotates an array to the right by k steps using the reversal method (in-place).

    The algorithm works in three steps:
    1. Reverse the entire array.
    2. Reverse the first k elements.
    3. Reverse the remaining n-k elements.

    Time Complexity: O(n)
    Space Complexity: O(1)

    Args:
        nums (list[int]): The list of integers to be rotated.
        k (int): The number of steps to rotate the array to the right.
    """
    n = len(nums)
    k %= n  # Handle cases where k is greater than n

    def reverse(arr, start, end):
        while start < end:
            arr[start], arr[end] = arr[end], arr[start]
            start += 1
            end -= 1

    reverse(nums, 0, n - 1)  # Reverse the entire array
    reverse(nums, 0, k - 1)  # Reverse the first k elements
    reverse(nums, k, n - 1)  # Reverse the remaining n-k elements

def rotate_array_slicing(nums: list[int], k: int) -> list[int]:
    """
    Rotates an array to the right by k steps using Python's slicing method.
    This method creates a new list.

    Time Complexity: O(n)
    Space Complexity: O(n)

    Args:
        nums (list[int]): The list of integers to be rotated.
        k (int): The number of steps to rotate the array to the right.

    Returns:
        list[int]: The rotated list.
    """
    n = len(nums)
    k %= n  # Handle cases where k is greater than n
    return nums[n - k:] + nums[:n - k]


if __name__ == "__main__":
    print("Rotate Array Algorithm Tests:")

    # Test cases for reversal method
    print("\nReversal Method (in-place):")
    test_cases_reversal = [
        ([1, 2, 3, 4, 5, 6, 7], 3, [5, 6, 7, 1, 2, 3, 4]),
        ([-1, -100, 3, 99], 2, [3, 99, -1, -100]),
        ([1, 2], 1, [2, 1]),
        ([1], 0, [1]),
        ([1, 2, 3, 4, 5], 5, [1, 2, 3, 4, 5]), # k == n
        ([1, 2, 3, 4, 5], 6, [5, 1, 2, 3, 4])  # k > n
    ]

    for original_nums, k, expected in test_cases_reversal:
        nums_copy = list(original_nums) # Create a copy for in-place modification
        rotate_array_reversal(nums_copy, k)
        print(f"Original: {original_nums}, k: {k}, Rotated: {nums_copy}, Expected: {expected}")
        assert nums_copy == expected, f"Test failed for {original_nums} with k={k}"

    # Test cases for slicing method
    print("\nSlicing Method (creates new list):")
    test_cases_slicing = [
        ([1, 2, 3, 4, 5, 6, 7], 3, [5, 6, 7, 1, 2, 3, 4]),
        ([-1, -100, 3, 99], 2, [3, 99, -1, -100]),
        ([1, 2], 1, [2, 1]),
        ([1], 0, [1]),
        ([1, 2, 3, 4, 5], 5, [1, 2, 3, 4, 5]), # k == n
        ([1, 2, 3, 4, 5], 6, [5, 1, 2, 3, 4])  # k > n
    ]

    for original_nums, k, expected in test_cases_slicing:
        rotated_nums = rotate_array_slicing(original_nums, k)
        print(f"Original: {original_nums}, k: {k}, Rotated: {rotated_nums}, Expected: {expected}")
        assert rotated_nums == expected, f"Test failed for {original_nums} with k={k}"