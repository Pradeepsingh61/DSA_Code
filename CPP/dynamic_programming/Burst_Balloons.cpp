/*
 * Burst Balloons (Dynamic Programming)
 *
 * Description:
 * You are given n balloons, each balloon has a number on it represented by an array nums[].
 * When you burst a balloon i, you gain coins equal to:
 *      nums[left] * nums[i] * nums[right]
 * where left and right are the adjacent balloons still remaining.
 * After bursting, balloon i is removed and the array shrinks.
 * Return the maximum coins you can collect by bursting balloons wisely.
 *
 * Approach:
 * - Add virtual balloons with value 1 at both ends for easier handling.
 * - Use Dynamic Programming (DP) on intervals.
 *   dp[i][j] = maximum coins obtainable by bursting balloons between index i and j (exclusive).
 * - For each range (i, j), consider every balloon k between i and j as the last balloon to burst:
 *       dp[i][j] = max(dp[i][j], nums[i]*nums[k]*nums[j] + dp[i][k] + dp[k][j])
 * - Final answer = dp[0][n-1]
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        // len is the distance between i and j
        for (int len = 2; len < n + 2; len++) {
            for (int i = 0; i + len < n + 2; i++) {
                int j = i + len;
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], nums[i]*nums[k]*nums[j] + dp[i][k] + dp[k][j]);
                }
            }
        }

        return dp[0][n + 1];
    }
};

int main() {
    Solution sol;

    // Test Case 1
    cout << "Test Case 1:" << endl;
    vector<int> nums1 = {3, 1, 5, 8};
    cout << "Balloons: [3, 1, 5, 8]" << endl;
    cout << "Max Coins: " << sol.maxCoins(nums1) << endl << endl; // 167

    // Test Case 2
    cout << "Test Case 2:" << endl;
    vector<int> nums2 = {1, 5};
    cout << "Balloons: [1, 5]" << endl;
    cout << "Max Coins: " << sol.maxCoins(nums2) << endl << endl; // 10

    // Test Case 3
    cout << "Test Case 3:" << endl;
    vector<int> nums3 = {9, 76, 64, 21};
    cout << "Balloons: [9, 76, 64, 21]" << endl;
    cout << "Max Coins: " << sol.maxCoins(nums3) << endl << endl;

    // Test Case 4 (Single balloon)
    cout << "Test Case 4:" << endl;
    vector<int> nums4 = {7};
    cout << "Balloons: [7]" << endl;
    cout << "Max Coins: " << sol.maxCoins(nums4) << endl << endl; // 7

    return 0;
}
