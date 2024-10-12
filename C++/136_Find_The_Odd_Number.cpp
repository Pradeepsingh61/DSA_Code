// https://leetcode.com/problems/single-number/description/

#include <bits/stdc++.h>

using namespace std;

int singleNumber(vector<int> &nums)
{
    if (nums.size() == 1)
    {
        return nums[0];
    }
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        ans = ans ^ nums[i];
    }
    return ans;
}

// TC:- O(1)
// SC:- O(1)