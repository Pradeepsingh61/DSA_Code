def two_sum(nums, target):
    """
    Finds the first pair of indices in `nums` whose values sum up to `target`.

    Args:
        nums (list of int): The input list of numbers.
        target (int): The target sum.

    Returns:
        list: A list containing the two indices of the numbers that add up to target.
              Returns an empty list if no such pair exists.
    """
    seen = {}  # Dictionary to store number -> index mapping

    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i

    return []  # Return empty list if no pair found
