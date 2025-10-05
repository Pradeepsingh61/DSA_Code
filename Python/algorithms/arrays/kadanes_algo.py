# ------------------------------------------------------------
#  PROBLEM: Maximum Subarray Sum (Kadane's Algorithm)
# ------------------------------------------------------------
# Given an integer array 'nums', find the contiguous subarray
# (containing at least one number) that has the largest sum,
# and return that sum.
#
# Example:
# Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
# Output: 6  (Because subarray [4, -1, 2, 1] gives max sum = 6)
# ------------------------------------------------------------

def max_subarray_sum(nums):
    # Edge case: if array is empty
    if not nums:
        return 0

    # Initialize:
    # current_sum → stores sum of current subarray
    # max_sum → stores maximum sum found so far
    current_sum = max_sum = nums[0]

    # Traverse array from 2nd element onwards
    for i in range(1, len(nums)):
        num = nums[i]

        # Either add current number to existing subarray
        # OR start a new subarray from current number
        current_sum = max(num, current_sum + num)

        # Update max_sum if we found a new maximum
        max_sum = max(max_sum, current_sum)

        # Debugging info (optional for understanding flow)
        # print(f"Step {i}: num={num}, current_sum={current_sum}, max_sum={max_sum}")

    return max_sum


# ------------------------------------------------------------
#  EXPLANATION:
# ------------------------------------------------------------
# - We iterate through the array once.
# - For each element, we decide:
#   (a) Continue the current subarray (add the element)
#   (b) Start a new subarray from this element
#
# - 'current_sum' keeps track of the best sum ending at current index.
# - 'max_sum' stores the global best sum seen so far.
#
# Example walkthrough:
# nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
# Output = 6  (from subarray [4, -1, 2, 1])
# ------------------------------------------------------------


# ------------------------------------------------------------
#  TIME COMPLEXITY:
# ------------------------------------------------------------
# O(n) → We traverse the array only once.
#
#  SPACE COMPLEXITY:
# O(1) → Uses constant extra space.
# ------------------------------------------------------------


# ------------------------------------------------------------
#  TEST CASES
# ------------------------------------------------------------
if __name__ == "__main__":
    nums1 = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    nums2 = [1]
    nums3 = [5, 4, -1, 7, 8]
    nums4 = [-1, -2, -3, -4]

    print("Test Case 1:", max_subarray_sum(nums1))  # Expected 6
    print("Test Case 2:", max_subarray_sum(nums2))  # Expected 1
    print("Test Case 3:", max_subarray_sum(nums3))  # Expected 23
    print("Test Case 4:", max_subarray_sum(nums4))  # Expected -1
