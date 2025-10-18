#include <iostream>
#include <vector>
#include <algorithm>

int lengthOfLIS(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::vector<int> dp(nums.size(), 1);
    int maxLen = 1;
    
    for (int i = 1; i < nums.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
        maxLen = std::max(maxLen, dp[i]);
    }
    
    return maxLen;
}

int main() {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << lengthOfLIS(nums) << std::endl;
    
    nums = {0, 1, 0, 3, 2, 3};
    std::cout << lengthOfLIS(nums) << std::endl;
    
    nums = {7, 7, 7, 7, 7, 7, 7};
    std::cout << lengthOfLIS(nums) << std::endl;
    
    return 0;
}