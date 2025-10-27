from typing import List

def max_subarray(nums: List[int]) -> int:
    """
    Return the maximum sum of a contiguous subarray using Kadane's algorithm.

    Args:
        nums: A non-empty list of integers.

    Returns:
        The maximum contiguous subarray sum (an int).

    Raises:
        ValueError: If `nums` is empty.

    Complexity:
        Time: O(n), single pass.
        Space: O(1), constant extra space.

    Example:
        >>> max_subarray([-2, 1, -3, 4, -1, 2, 1, -5, 4])
        6
    """
    if not nums:
        raise ValueError("nums must be a non-empty list")

    # cur_sum: maximum subarray sum ending at the current position
    # max_sum: maximum subarray sum found so far
    cur_sum = max_sum = nums[0]

    # iterate from second element to end
    for x in nums[1:]:
        # either extend the previous subarray or start fresh at current element
        cur_sum = x if x > cur_sum + x else cur_sum + x

        # update global maximum if current subarray is better
        if cur_sum > max_sum:
            max_sum = cur_sum

    return max_sum


if __name__ == "__main__":
    # quick manual tests / demonstration
    examples = [
        ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
        ([1, 2, 3], 6),
        ([-3, -2, -5], -2),
        ([5], 5),
    ]
    for arr, expected in examples:
        print(f"{arr} -> {max_subarray(arr)} (expected {expected})")
