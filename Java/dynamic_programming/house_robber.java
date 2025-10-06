
/*
    Description: House Robber

    You are a robber planning to rob houses along a street. 
    Each house has some amount of money. All houses are in a line.

    Constraint: You cannot rob two adjacent houses.

    Find the maximum amount of money you can rob.

    Example:
        Input: nums = [2,7,9,3,1]
        Output: 12
        Explanation: Rob houses 1, 3, 5 → 2 + 9 + 1 = 12
*/

public class house_robber {

    // -----------------------------------------------------------
    //  1. BRUTE FORCE RECURSION
    // -----------------------------------------------------------
    // Idea:
    // For each house, choose to either:
    //   1️. Rob it → skip next house (i+2)
    //   2️. Skip it → consider next house (i+1)
    //
    // Recurrence:
    //   maxMoney(i) = max(nums[i] + maxMoney(i+2), maxMoney(i+1))
    //
    // Time Complexity: O(2^n) — exponential
    // Space Complexity: O(n) — recursion stack
    public static int robBrute(int[] nums, int index) {
        if (index >= nums.length) return 0;
        // Rob current house or skip it
        int rob = nums[index] + robBrute(nums, index + 2);
        int skip = robBrute(nums, index + 1);
        return Math.max(rob, skip);
    }

    // -----------------------------------------------------------
    //  2. DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------
    // Idea:
    // dp[i] = maximum money that can be robbed from house i to end
    //
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static int robDP(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        int n = nums.length;
        int[] dp = new int[n + 2]; // dp[n] = dp[n+1] = 0 (base case)

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = Math.max(nums[i] + dp[i + 2], dp[i + 1]);
        }

        return dp[0];
    }

    // -----------------------------------------------------------
    //  3. SPACE-OPTIMIZED DP
    // -----------------------------------------------------------
    // Observation:
    // We only need last two values at each step.
    //
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public static int robOptimized(int[] nums) {
        int prev1 = 0; // dp[i+1]
        int prev2 = 0; // dp[i+2]

        for (int i = nums.length - 1; i >= 0; i--) {
            int current = Math.max(nums[i] + prev2, prev1);
            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }

    // -----------------------------------------------------------
    //  MAIN METHOD (Test all versions)
    // -----------------------------------------------------------
    public static void main(String[] args) {
        int[] nums = {2, 7, 9, 3, 1};

        System.out.println("Brute Force Result: " + robBrute(nums, 0));
        System.out.println("DP Result: " + robDP(nums));
        System.out.println("Optimized Result: " + robOptimized(nums));
    }
}
