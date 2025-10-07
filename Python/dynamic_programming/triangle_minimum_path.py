"""
Triangle Minimum Path Sum

Problem:
Given a triangle array, return the minimum path sum from top to bottom.
Each step you may move to adjacent numbers on the row below.

Approach:
Use dynamic programming to update the triangle in-place.
Each element in the row is updated by adding the minimum of the adjacent elements above.

Time Complexity: O(n^2), where n is number of rows.
Space Complexity: O(1) - in-place modification.

Example:
Input: [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
"""

from typing import List

class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        for i in range(1, n):
            triangle[i][0] += triangle[i-1][0]
            triangle[i][i] += triangle[i-1][i-1]
            for j in range(1, i):
                triangle[i][j] += min(triangle[i-1][j], triangle[i-1][j-1])
        return min(triangle[-1])


# Sample test cases
if __name__ == "__main__":
    sol = Solution()
    assert sol.minimumTotal([[2],[3,4],[6,5,7],[4,1,8,3]]) == 11
    assert sol.minimumTotal([[-10]]) == -10
    print("All test cases passed!")
