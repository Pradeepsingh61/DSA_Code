// Problem Statement: Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2⌋ times.
// This implementation uses the Boyer-Moore Voting Algorithm.

#include <iostream>
#include <vector>

class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        // Initialize candidate and a counter.
        int candidate = 0;
        int count = 0;

        // Iterate through the array to find a potential majority element.
        for (int num : nums) {
            // If count is 0, we set the current element as the new candidate.
            if (count == 0) {
                candidate = num;
            }
            
            // If the current element matches the candidate, increment count. Otherwise, decrement.
            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }

        // The algorithm guarantees that the remaining candidate is the majority element
        // because the majority element appears more than n/2 times.
        return candidate;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    
    int result = sol.majorityElement(nums);
    
    std::cout << "The majority element is: " << result << std::endl;
    
    return 0;
}