/*
 * Problem Name:
 * Trapping Rain Water
 *
 * Programming Language:
 * C++
 *
 * Category:
 * Arrays / Two Pointer Technique
 *
 * Difficulty Level:
 * Hard
 *
 * Problem Description:
 * Given an array `arr[]` representing the elevation map where the width of each bar is 1,
 * compute how much water it can trap after raining.
 *
 * Example:
 * Input: arr = [4,2,0,3,2,5]
 * Output: 9
 * Explanation: Water trapped = (1+3+1+0+4) = 9
 *
 * Algorithm (Two Pointer Approach):
 * 1. Initialize two pointers — `l` (left) at 0 and `r` (right) at n-1.
 * 2. Maintain two variables:
 *    - `lmax` = maximum height seen so far from the left.
 *    - `rmax` = maximum height seen so far from the right.
 * 3. Move the pointer which has the smaller current height:
 *    - If `arr[l] <= arr[r]`:
 *        - If `lmax > arr[l]`, then water trapped = `lmax - arr[l]`.
 *        - Else, update `lmax = arr[l]`.
 *        - Move `l` forward.
 *    - Else:
 *        - If `rmax > arr[r]`, then water trapped = `rmax - arr[r]`.
 *        - Else, update `rmax = arr[r]`.
 *        - Move `r` backward.
 * 4. Continue until `l` meets `r`.
 * 5. Return the total trapped water.
 *
 * Time Complexity: O(N)  — Each element is processed at most once.
 * Space Complexity: O(1) — Constant extra space used.
 *
 * Author:
 * Apurva Jain
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        int lmax = 0, rmax = 0, total = 0;

        while (l < r) {
            if (arr[l] <= arr[r]) {
                if (lmax > arr[l]) {
                    total += lmax - arr[l];
                } else {
                    lmax = arr[l];
                }
                l++;
            } else {
                if (rmax > arr[r]) {
                    total += rmax - arr[r];
                } else {
                    rmax = arr[r];
                }
                r--;
            }
        }
        return total;
    }
};

// Driver Code for testing
int main() {
    Solution sol;
    vector<int> height = {4, 2, 0, 3, 2, 5};
    cout << "Trapped Rain Water: " << sol.trap(height) << endl;
    return 0;
}
