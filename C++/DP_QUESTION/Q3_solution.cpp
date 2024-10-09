class Solution {
public:
    // Memoization table to store the results of subproblems.
    // dp[{curr, lastswap}] stores the minimum number of swaps needed
    // from index 'curr' with the last swapped element at index 'lastswap'.
    map<pair<int, int>, int> dp;

    // Recursive function to compute the minimum number of swaps.
    // curr: current index in arr1 being considered.
    // lastswap: the index in arr2 representing the last swapped element, or -1 if no swap yet.
    // arr1: the first array.
    // arr2: the second array, sorted before calling this function.
    int recurse(int curr, int lastswap, vector<int>& arr1, vector<int>& arr2) {
        // Base case: If we have processed all elements of arr1, no more swaps are needed.
        if (curr >= arr1.size()) {
            return 0;
        }

        // Check if this subproblem has already been computed and stored in dp.
        if (dp.contains({curr, lastswap})) {
            return dp[{curr, lastswap}];
        }

        int n = arr2.size();  // Size of arr2
        int ans = 10000;      // Initialize ans with a large value (infinity equivalent).

        // Case 1: Last operation was a swap.
        if (lastswap != -1) {
            // Find the next greater element in arr2 after arr2[lastswap].
            auto idx = upper_bound(arr2.begin(), arr2.end(), arr2[lastswap]) - arr2.begin();

            // If a valid index is found in arr2, recurse with a swap (incrementing swap count).
            if (idx < n) {
                ans = min(ans, 1 + recurse(curr + 1, idx, arr1, arr2));
            }

            // Check if the current element in arr1 is greater than the last swapped element.
            // If true, recurse without swapping (i.e., proceed with no changes).
            if (arr1[curr] > arr2[lastswap]) {
                ans = min(ans, recurse(curr + 1, -1, arr1, arr2));
            }
        }
        // Case 2: No previous swap, process arr1[curr] directly.
        else {
            // If we are not at the first element, compare with the previous element in arr1.
            if (curr > 0) {
                // Find the next greater element in arr2 after arr1[curr-1].
                auto idx = upper_bound(arr2.begin(), arr2.end(), arr1[curr - 1]) - arr2.begin();

                // Recurse with a swap if a valid greater element in arr2 is found.
                if (idx < n) {
                    ans = min(ans, 1 + recurse(curr + 1, idx, arr1, arr2));
                }

                // If arr1[curr] is greater than arr1[curr-1], recurse without swapping.
                if (arr1[curr] > arr1[curr - 1]) {
                    ans = min(ans, recurse(curr + 1, -1, arr1, arr2));
                }
            }
            // If at the first element of arr1, we have the option to either swap or not swap.
            else {
                ans = min(ans, min(recurse(curr + 1, -1, arr1, arr2), 1 + recurse(curr + 1, 0, arr1, arr2)));
            }
        }

        // Store the result of this subproblem in dp.
        return dp[{curr, lastswap}] = ans;
    }

    // Main function to compute the minimum number of swaps to make arr1 strictly increasing.
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        // Sort arr2 to perform binary search using upper_bound in recursion.
        sort(arr2.begin(), arr2.end());

        // Start the recursion from the first element, with no previous swap (lastswap = -1).
        int ans = recurse(0, -1, arr1, arr2);

        // If ans is still large (infinity equivalent), return -1 (no valid solution found).
        if (ans >= 10000) {
            return -1;
        }

        // Otherwise, return the minimum number of swaps needed.
        return ans;
    }
};
