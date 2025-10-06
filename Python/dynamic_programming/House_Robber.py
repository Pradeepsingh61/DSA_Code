from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        """
        Problem:
        Given an integer array `nums` representing the amount of money in each house,
        return the maximum amount of money you can rob without alerting the police.
        (You cannot rob two adjacent houses.)

        Approach:
        Use Dynamic Programming (DP) with tabulation.

        Recurrence:
            dp[i] = max(dp[i-1], dp[i-2] + nums[i])
            - dp[i-1]: skip current house
            - dp[i-2] + nums[i]: rob current house

        Base Cases:
            dp[0] = nums[0]                        # only one house
            dp[1] = max(nums[0], nums[1])          # choose the better of the first two

        Time Complexity:  O(n)
        Space Complexity: O(n)  → can be optimized to O(1)
        """
        n = len(nums)
        if n == 0:
            return 0
        if n == 1:
            return nums[0]

        dp = [0] * n
        dp[0] = nums[0]
        dp[1] = max(nums[0], nums[1])

        for i in range(2, n):
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])

        return dp[-1]


# -------------------------------
# Test Cases
# -------------------------------
if __name__ == "__main__":
    solution = Solution()
    
    test_cases = [
        ([1, 2, 3, 1], 4),
        ([2, 7, 9, 3, 1], 12),
        ([2, 1, 1, 2], 4),
        ([10], 10),
        ([5, 3, 4, 11, 2], 16)
    ]
    
    for nums, expected in test_cases:
        result = solution.rob(nums)
        print(f"Houses: {nums} => Max Rob: {result} | Expected: {expected}")
