#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int maxSum = INT_MIN; // Stores the maximum sum found so far
        int currSum = 0;      // Stores the sum of the current subarray
        for(size_t i = 0; i < nums.size(); i++){
            currSum += nums[i];
            maxSum = std::max(currSum, maxSum);
            
            // If the current sum is negative, it won't contribute to a larger sum,
            // so we reset it to 0 to start a new subarray from the next element.
            if(currSum < 0){
                currSum = 0;
            }
        }

        return maxSum;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    int result = sol.maxSubArray(nums);
    
    std::cout << "The maximum subarray sum is: " << result << std::endl;
    
    return 0;
}