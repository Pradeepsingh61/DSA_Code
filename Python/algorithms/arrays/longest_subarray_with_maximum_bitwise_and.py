"""
2419. Longest Subarray With Maximum Bitwise AND
Solved
Medium
Topics
Companies
Hint
You are given an integer array nums of size n.

Consider a non-empty subarray from nums that has the maximum possible bitwise AND.

In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then, only subarrays with a bitwise AND equal to k should be considered.
Return the length of the longest such subarray.

The bitwise AND of an array is the bitwise AND of all the numbers in it.

A subarray is a contiguous sequence of elements within an array.

 

Example 1:

Input: nums = [1,2,3,3,2,2]
Output: 2
Explanation:
The maximum possible bitwise AND of a subarray is 3.
The longest subarray with that value is [3,3], so we return 2.
Example 2:

Input: nums = [1,2,3,4]
Output: 1
Explanation:
The maximum possible bitwise AND of a subarray is 4.
The longest subarray with that value is [4], so we return 1.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 106
"""
from typing import List

class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        max_val = nums[0]
        max_len = 1
        current_len = 1
        for i in range(1, len(nums)):
            if nums[i] > max_val:
                max_val = nums[i]
                max_len = 1
                current_len = 1
            elif nums[i] == max_val:
                current_len += 1
                max_len = max(max_len, current_len)
            else:
                current_len = 0
        return max_len
    
# Test cases

test = Solution()
assert test.longestSubarray([1,2,3,3,2,2]) == 2
assert test.longestSubarray([1,2,3,4]) == 1
assert test.longestSubarray([1,2,3,4,4,4]) == 3

print("All tests passed")