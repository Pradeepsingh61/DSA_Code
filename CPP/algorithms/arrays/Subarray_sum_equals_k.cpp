#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Given an array and an integer k, count the total number of subarrays whose sum equals k.

Algorithm:
1. Build a prefix sum array:
   - prefix[i] = sum of elements from arr[0] to arr[i].
2. Traverse the prefix array:
   - If prefix[i] == k → increment count (subarray from start).
   - If (prefix[i] - k) exists in map → add its frequency to answer.
   - Store prefix[i] in map.
3. Return the total count.

Time Complexity:
- O(n) → One traversal + hash map lookups.

Space Complexity:
- O(n) → Hash map storing prefix sums.
*/

class Solution {
public:
    int subarraySum(vector<int>& arr, int k) {
        int n = arr.size();
        
        // Step 1: Create prefix sum array
        int prefix[n];
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = arr[i] + prefix[i - 1];
        }
        
        unordered_map<int,int> mp; // prefix sum frequencies
        int ans = 0;
        
        // Step 2: Traverse prefix array
        for (int i = 0; i < n; i++) {
            if (prefix[i] == k) // subarray from start
                ans++;
            
            if (mp.find(prefix[i] - k) != mp.end()) {
                ans += mp[prefix[i] - k];
            }
            
            mp[prefix[i]]++;
        }
        
        return ans;
    }
};

// ✅ Driver Code with Multiple Test Cases
int main() {
    Solution s;
    
    vector<vector<int>> testArrays = {
        {1, 2, 3, 1, 1, 1},    // Example 1
        {1, 1, 1},             // Example 2
        {3, 4, 7, 2, -3, 1, 4, 2}, // Example 3 with negatives
        {1, -1, 0},            // Edge case with zero and negatives
        {2, 2, 2, 2}           // Repeated numbers
    };
    
    vector<int> ks = {3, 2, 7, 0, 4};
    
    for (int i = 0; i < testArrays.size(); i++) {
        cout << "Test Case " << i+1 << ": ";
        cout << "Number of subarrays with sum " << ks[i] << " = "
             << s.subarraySum(testArrays[i], ks[i]) << endl;
    }
    
    return 0;
}
