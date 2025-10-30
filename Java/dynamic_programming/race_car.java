/*
 * Title: Race Car (LeetCode #818)
 * Problem: 
 * The car starts at position 0 and speed +1. 
 * In each move, you can either:
 *   - "A": Accelerate -> position += speed; speed *= 2
 *   - "R": Reverse -> if speed > 0 then speed = -1 else speed = 1
 * Find the minimum number of instructions to reach the target position.
 *
 * Approach:
 * Dynamic Programming (DP)
 * - dp[i] stores the minimum number of steps required to reach position i.
 * - Use bit manipulation to find the smallest k such that (2^k - 1) >= i.
 * - Compute based on overshooting or undershooting target.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 *
 * Author: Mohammed Sufiyan Ahmed
 * Date: October 2025
 */

class Solution {
    public int racecar(int target) {
        int[] dp = new int[target + 1];

        for (int i = 1; i <= target; ++i) {
            int k = 32 - Integer.numberOfLeadingZeros(i);

            // Case 1: If target is exactly at position (2^k - 1)
            if (i == (1 << k) - 1) {
                dp[i] = k;
                continue;
            }

            // Case 2: Overshoot and then reverse
            dp[i] = dp[(1 << k) - 1 - i] + k + 1;

            // Case 3: Undershoot and reverse earlier
            for (int j = 0; j < k - 1; ++j) {
                dp[i] = Math.min(dp[i],
                        dp[i - (1 << (k - 1)) + (1 << j)] + k - 1 + j + 2);
            }
        }
        return dp[target];
    }

    // Example test case (for contributors)
    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Minimum instructions for target=3: " + sol.racecar(3));  // Output: 2
        System.out.println("Minimum instructions for target=6: " + sol.racecar(6));  // Output: 5
    }
}
