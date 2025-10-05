/*
 * Algorithm Name
Longest Increasing Subsequence (LIS) using Dynamic Programming

Programming Language
Java

Category
Dynamic Programming / Array

Difficulty Level
Medium

* Algorithm Description : 

1. Problem it solves:
-> Finds the length of the longest subsequence in an array such that all elements of the subsequence are strictly increasing.

2. Approach / Idea:
-> Uses a DP array where dp[i] represents the length of the LIS ending at index i.
-> Initialize all dp[i] = 1 (each element itself is a subsequence of length 1).
-> For every element nums[i], check all previous elements nums[j] where j < i:
     - If nums[i] > nums[j], update dp[i] = max(dp[i], dp[j] + 1)
-> The final answer is the maximum value in the dp array.

3. Complexity:
Time: O(n²), due to two nested loops.
Space: O(n), for the dp array.

* Author : Surya Pratap Singh
*/

// Time Complexity: O(n^2)
// Space Complexity: O(n)

import java.util.*;

public class LIS {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // take input size
        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        
        int[] nums = new int[n];
        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            nums[i] = sc.nextInt();
        }
        
        int lis = lengthOfLIS(nums);
        System.out.println("Length of Longest Increasing Subsequence: " + lis);
        
        sc.close();
    }
    
    public static int lengthOfLIS(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        
        // each element is at least length 1
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
        }
        
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
            maxLen = Math.max(maxLen, dp[i]);
        }
        
        return maxLen;
    }
}