
/*
    Problem: Climbing Stairs
    You are climbing a staircase. It takes n steps to reach the top.
    Each time you can climb either 1 step or 2 steps.
    Find how many distinct ways you can climb to the top.
*/

public class climbing_stairs {

    // -----------------------------------------------------------
    //  1. BRUTE FORCE (Recursive)
    // -----------------------------------------------------------
    // Idea:
    //   At each step, you can take 1 or 2 steps.
    //   So total ways = f(n-1) + f(n-2)
    //
    // Time Complexity: O(2^n)  (exponential)
    // Space Complexity: O(n)   (recursion call stack)
    public static int climbStairsBrute(int n) {
        if (n <= 2) return n; // base cases
        return climbStairsBrute(n - 1) + climbStairsBrute(n - 2);
    }


    // -----------------------------------------------------------
    //  2. OPTIMIZED DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static int climbStairsDP(int n) {
        if (n <= 2) return n;
        int[] dp = new int[n + 1];
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }


    // -----------------------------------------------------------
    //  3. OPTIMIZED (Space-Optimized DP)
    // -----------------------------------------------------------
    // We only need the last two results at any time.
    //
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public static int climbStairsOptimized(int n) {
        if (n <= 2) return n;
        int first = 1, second = 2;
        for (int i = 3; i <= n; i++) {
            int third = first + second;
            first = second;
            second = third;
        }
        return second;
    }


    // -----------------------------------------------------------
    //  MAIN METHOD (Test all versions)
    // -----------------------------------------------------------
    public static void main(String[] args) {
        int n = 5;  // example: 5 stairs

        System.out.println("Brute Force Result: " + climbStairsBrute(n));
        System.out.println("DP Result: " + climbStairsDP(n));
        System.out.println("Optimized Result: " + climbStairsOptimized(n));
    }
}
