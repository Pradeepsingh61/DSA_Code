// LeetCode Problem 31
// https://leetcode.com/problems/next-permutation/

// Problem-Description
// A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
// For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
// The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
// For example, the next permutation of arr = [1,2,3] is [1,3,2].
// Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
// While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
// Given an array of integers nums, find the next permutation of nums.
// The replacement must be in place and use only constant extra memory.
// Example 1:
// Input: nums = [1,2,3]
// Output: [1,3,2]


// Intuition
// Idea is to iterate through the end as highlighted in the comments and check for the next greater integer on the right of pivot point.
// Here, pivot point is the index where the increasing order ends (from the ending). If the pivot point reaches the first position that means our entire array is in decreasing order (from start) and thus next iteration will be sorted version of it.


// Complexity
// Time complexity:O(NlogN)
// Space complexity: O(1)


// Author ADITYATIWARI
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();
        int piv=-1;
        int jg=-1;
        for(int i=n-1;i>0;i--){
            if(nums[i]>nums[i-1]){
                piv=i-1;
                break;
            }
        }
        if(piv==-1){
            sort(nums.begin(),nums.end());
            return;
        }

            reverse(nums.begin()+piv+1,nums.end());
            for(int i=piv;i<n;i++){
                if(nums[i]>nums[piv]){
                    jg=i;
                    break;
                }
            }
            swap(nums[piv],nums[jg]);
            return;
    }
};