#include<iostream>
#include<vector>
#include<climits>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN; // Stores the maximum sum found so far
        int currSum = 0;      // Stores the sum of the current subarray
        for(int i = 0; i < nums.size(); i++){
            currSum += nums[i];
            maxSum = max(currSum, maxSum);
            
            // If the current sum is negative, it won't contribute to a larger sum,
            // so we reset it to 0 to start a new subarray from the next element.
            if(currSum < 0){
                currSum = 0;
            }
        }

        return maxSum;
    }
};