/*
Problem Name: Count Distinct Subarrays Divisible by K in Sorted Array
Problem Link: https://leetcode.com/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array/
Platform: LeetCode
Language: C++
Author: Aditya Shimoga
Date: 30th October 2025

Description:
-----------------------------------
Given a sorted array nums and an integer k, find the number of distinct subarrays
whose sum is divisible by k.

Key Insight:
-----------------------------------
- For any subarray [l, r], sum(l..r) is divisible by k ⇔ prefixSum[r] % k == prefixSum[l-1] % k.
- To count valid subarrays efficiently, we maintain a frequency map of prefix sums modulo k.
- Since the array is sorted and may contain repeated elements, we process contiguous "blocks"
  of equal numbers separately. This ensures we don’t count identical subarrays multiple times.
- For each block:
  1. Calculate all valid subarrays ending in this block using prefix remainders from previous blocks.
  2. Update the remainder frequency map after processing the block.

Complexity:
-----------------------------------
Time Complexity: O(N*log(k))
Space Complexity: O(K) , depending on distinct remainders
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        long long divisor = 1LL * k;
        long long prefixSum = 0LL, resultCount = 0LL;
        int n = nums.size();

        map<int, int> remainderFreq;  // Tracks frequency of prefix sums modulo k

        int i = 0;
        while (i < n) {
            int j = i;
            int currentValue = nums[i];
            long long tempPrefixSum = prefixSum;

            // Step 1: Count valid subarrays ending within the current block
            while (j < n && nums[j] == currentValue) {
                prefixSum += nums[j];
                int remainder = prefixSum % divisor;

                // Subarray from start (remainder == 0)
                if (remainder == 0) resultCount++;

                // Subarray ending here matches an earlier prefix remainder
                if (remainderFreq.count(remainder))
                    resultCount += 1LL * remainderFreq[remainder];

                j++;
            }

            // Step 2: Update frequency map for this block
            j = i;
            while (j < n && nums[j] == currentValue) {
                tempPrefixSum += nums[j];
                int remainder = tempPrefixSum % divisor;
                remainderFreq[remainder]++;
                j++;
            }

            // Move to next distinct value block
            i = j;
        }

        return resultCount;
    }
};

/*
Example:
Input:
nums = [1,1,2,2,3], k = 3

Output:
Number of distinct subarrays divisible by 3 = 4

Explanation:
Subarrays divisible 3: [3], [1,2], [1,1,2,2],[1,1,2,2,3]
*/

int main() {
    Solution solver;

    // Test Case 1
    vector<int> nums1 = {1, 1, 2, 2, 3};
    int k1 = 3;
    long long result1 = solver.numGoodSubarrays(nums1, k1);
    cout << "Test Case 1:" << endl;
    cout << "Input: nums = [1,1,2,2,3], k = 3" << endl;
    cout << "Output: " << result1 << endl;
    cout << "Expected: 4" << endl << endl;

    // Test Case 2
    vector<int> nums2 = {2, 2, 2, 4, 4};
    int k2 = 4;
    long long result2 = solver.numGoodSubarrays(nums2, k2);
    cout << "Test Case 2:" << endl;
    cout << "Input: nums = [2,2,2,4,4], k = 4" << endl;
    cout << "Output: " << result2 << endl;
    cout << "Expected: 6" << endl;

    return 0;
}
