#include <bits/stdc++.h>
using namespace std;

/*
Algorithm Explanation:
We need to find all elements that appear more than ⌊ n/3 ⌋ times in the array.
Steps:
1. Use a frequency map (unordered_map) to count the occurrences of each number.
2. Compute the threshold = n / 3.
3. Traverse the frequency map and collect all elements with count > threshold.
4. Return the result as a vector.

This works because:
- At most 2 elements can appear more than n/3 times.
- Using a hashmap ensures we count efficiently.

->Time Complexity:
  O(n) -We iterate over the array once and then over the hashmap (at most n entries).

->Space Complexity:
  O(n) -In the worst case, all elements are unique, requiring n entries in the hashmap.
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> elementCountMap;

        // Count the occurrences of each element
        for (int num : nums) {
            elementCountMap[num]++;
        }

        vector<int> majorityElements;
        int threshold = nums.size() / 3;

        // Collect elements occurring more than threshold
        for (auto& pair : elementCountMap) {
            int element = pair.first;
            int count = pair.second;
            if (count > threshold) {
                majorityElements.push_back(element);
            }
        }
        return majorityElements;
    }
};

int main() {
    Solution sol;

    // Test Case 1:
    vector<int> nums1 = {3, 2, 3};
    vector<int> res1 = sol.majorityElement(nums1);
    cout << "Test Case 1 -> Input: [3,2,3] | Output: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    // Test Case 2:
    vector<int> nums2 = {1};
    vector<int> res2 = sol.majorityElement(nums2);
    cout << "Test Case 2 -> Input: [1] | Output: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    // Test Case 3: 
    vector<int> nums3 = {1,2};
    vector<int> res3 = sol.majorityElement(nums3);
    cout << "Test Case 3 -> Input: [1,2] | Output: ";
    for (int x : res3) cout << x << " ";
    cout << endl;

    return 0;
}

