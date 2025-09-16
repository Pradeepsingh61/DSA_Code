class Solution {
public:
    // Memoization table to store results of subproblems
    // dp[{curr, lastswap}] keeps the minimum swaps needed for the subarray starting at index `curr`
    // with the last swapped element located at index `lastswap` in arr2
    map<pair<int, int>, int> dp;

    // Recursive function to calculate the minimum number of swaps
    // curr: current index of arr1 being processed
    // lastswap: index in arr2 for the last swapped element or -1 if no swap has occurred
    // arr1: the first array (which we need to make strictly increasing)
    // arr2: the second array, which will be sorted before use
    int recurse(int curr, int lastswap, vector<int>& arr1, vector<int>& arr2) {
        // Base case: If we've processed all elements of arr1, no more swaps are required
        if (curr >= arr1.size()) {
            return 0;  // No more elements to process
        }

        // If this subproblem has already been solved, return the stored result from dp
        if (dp.contains({curr, lastswap})) {
            return dp[{curr, lastswap}];
        }

        int n = arr2.size();   // Size of arr2
        int ans = 10000;       // Initialize answer to a large value (acting as infinity)

        // Case 1: If the last operation involved a swap (lastswap != -1)
        if (lastswap != -1) {
            // Find the first element in arr2 that is strictly greater than arr2[lastswap]
            auto idx = upper_bound(arr2.begin(), arr2.end(), arr2[lastswap]) - arr2.begin();
            
            // If a valid index in arr2 is found, we can swap arr1[curr] with arr2[idx] and recurse
            if (idx < n) {
                ans = min(ans, 1 + recurse(curr + 1, idx, arr1, arr2));  // Recurse with a swap (increment swap count by 1)
            }

            // If arr1[curr] is greater than the last swapped element arr2[lastswap], recurse without swapping
            if (arr1[curr] > arr2[lastswap]) {
                ans = min(ans, recurse(curr + 1, -1, arr1, arr2));  // Recurse without swapping
            }
        }
        // Case 2: If no previous swap (lastswap == -1)
        else {
            // If we are not at the first element in arr1, we can compare arr1[curr] with arr1[curr-1]
            if (curr > 0) {
                // Find the first element in arr2 that is strictly greater than arr1[curr-1]
                auto idx = upper_bound(arr2.begin(), arr2.end(), arr1[curr - 1]) - arr2.begin();
                
                // If a valid index in arr2 is found, we can swap arr1[curr] and recurse
                if (idx < n) {
                    ans = min(ans, 1 + recurse(curr + 1, idx, arr1, arr2));  // Recurse with swap
                }

                // If arr1[curr] is greater than arr1[curr-1], we can recurse without swapping
                if (arr1[curr] > arr1[curr - 1]) {
                    ans = min(ans, recurse(curr + 1, -1, arr1, arr2));  // Recurse without swap
                }
            }
            // If we are at the first element (curr == 0), we can either swap or not swap
            else {
                // Try both options: recurse without swap or recurse with swap
                ans = min(ans, min(recurse(curr + 1, -1, arr1, arr2), 1 + recurse(curr + 1, 0, arr1, arr2)));
            }
        }

        // Store the result of the current subproblem in dp and return it
        return dp[{curr, lastswap}] = ans;
    }

    // Main function to make arr1 strictly increasing with the minimum number of swaps using elements from arr2
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        // Sort arr2 to use binary search (upper_bound) during recursion
        sort(arr2.begin(), arr2.end());

        // Start recursion from index 0 of arr1 with no previous swap (-1 for lastswap)
        int ans = recurse(0, -1, arr1, arr2);

        // If ans is still large (indicating no valid solution), return -1
        if (ans >= 10000) {
            return -1;  // No way to make arr1 strictly increasing
        }

        // Return the minimum number of swaps needed
        return ans;
    }
};
