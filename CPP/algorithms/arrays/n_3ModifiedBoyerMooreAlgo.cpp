// Problem Statement: Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.	
// This implementation uses a modified Boyer-Moore Voting Algorithm.	

#include <iostream>	
#include <vector>	
#include <algorithm>	

class Solution {	
public:	
    std::vector<int> majorityElement(std::vector<int>& nums) {	
        // Initialize two candidates and their counters.	
        // At most, there can be two elements that appear more than n/3 times.	
        int el1 = 0, el2 = 0;	
        int ct1 = 0, ct2 = 0;	

        // First pass: Find the two potential candidates.	
        for (int num : nums) {	
            if (ct1 == 0 && num != el2) {	
                el1 = num;	
                ct1 = 1;	
            } else if (ct2 == 0 && num != el1) {	
                el2 = num;	
                ct2 = 1;	
            } else if (num == el1) {	
                ct1++;	
            } else if (num == el2) {	
                ct2++;	
            } else {	
                ct1--;	
                ct2--;	
            }	
        }	

        // Second pass: Verify if the candidates are majority elements.	
        ct1 = 0;	
        ct2 = 0;	
        for (int num : nums) {
            if (num == el1) {	
                ct1++;	
            } else if (num == el2) {	
                ct2++;	
            }	
        }	

        std::vector<int> ans;	
        int n = nums.size() / 3;	

        // Check if the counts are greater than n/3.	
        if (ct1 > n) {	
            ans.push_back(el1);	
        }	
        // Ensure el1 and el2 are distinct before adding el2.	
        if (el1 != el2 && ct2 > n) {	
            ans.push_back(el2);	
        }	

        // Sort the result for consistent output.	
        sort(ans.begin(), ans.end());	
        return ans;	
    }	
};	

int main() {	
    Solution sol;	
    std::vector<int> nums = {3, 2, 3};	

    std::vector<int> result = sol.majorityElement(nums);	

    std::cout << "The majority elements are: ";	
    for (int num : result) {	
        std::cout << num << " ";	
    }	
    std::cout << std::endl;	

    std::vector<int> nums2 = {1, 2};	
    result = sol.majorityElement(nums2);	

    std::cout << "The majority elements are: ";	
    for (int num : result) {	
        std::cout << num << " ";	
    }	
    std::cout << std::endl;	

    return 0;	
}