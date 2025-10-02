/*
 * Longest Increasing Subsequence (LIS) Algorithm
 * 
 * Description:
 * The Longest Increasing Subsequence algorithm finds the length of the longest subsequence
 * of a given array such that all elements of the subsequence are sorted in increasing order.
 * 
 * This implementation uses dynamic programming with a 1D table to solve the problem:
 * 1. Create a table dp[] where dp[i] represents the length of LIS ending at index i
 * 2. Initialize all values in dp[] as 1 (minimum LIS length is 1)
 * 3. For each element arr[i], look for all elements arr[j] where j < i and arr[j] < arr[i]
 *    Update dp[i] = max(dp[i], dp[j] + 1)
 * 4. The maximum value in dp[] is the length of the LIS
 * 5. Reconstruct the actual subsequence using the dp[] array
 * 
 * Time Complexity: O(n²) where n is the length of the array
 * Space Complexity: O(n) for the DP table
 * 
 * Note: There is also an O(n log n) solution using binary search, but this implementation
 * focuses on the classic dynamic programming approach for clarity.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the length of LIS and the actual LIS
pair<int, vector<int>> longestIncreasingSubsequence(const vector<int>& arr) {
    int n = arr.size();
    
    // Base case
    if (n == 0) {
        return {0, {}};
    }
    
    // Create a table to store lengths of LIS ending at each index
    vector<int> dp(n, 1);  // Initialize with 1 as minimum LIS length is 1
    
    // To store the previous index for reconstructing the LIS
    vector<int> prev(n, -1);
    
    // Fill dp[] in bottom-up manner
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prev[i] = j;  // Store the previous index
            }
        }
    }
    
    // Find the maximum length and its index
    int maxLength = 0;
    int maxIndex = 0;
    
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i;
        }
    }
    
    // Reconstruct the LIS
    vector<int> lis;
    while (maxIndex != -1) {
        lis.push_back(arr[maxIndex]);
        maxIndex = prev[maxIndex];
    }
    
    // Reverse to get the correct order
    reverse(lis.begin(), lis.end());
    
    return {maxLength, lis};
}

// Function to print the DP table (for educational purposes)
void printDPTable(const vector<int>& arr, const vector<int>& dp) {
    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "DP:    ";
    for (int val : dp) {
        cout << val << " ";
    }
    cout << endl;
}

// Main function with test cases
int main() {
    // Test Case 1: Basic example
    cout << "Test Case 1:" << endl;
    vector<int> arr1 = {10, 22, 9, 33, 21, 50, 41, 60};
    cout << "Array: ";
    for (int num : arr1) {
        cout << num << " ";
    }
    cout << endl;
    
    auto result1 = longestIncreasingSubsequence(arr1);
    cout << "Length of LIS: " << result1.first << endl;
    cout << "LIS: ";
    for (int num : result1.second) {
        cout << num << " ";
    }
    cout << endl << endl;
    
    // Test Case 2: Array with decreasing elements
    cout << "Test Case 2:" << endl;
    vector<int> arr2 = {5, 4, 3, 2, 1};
    cout << "Array: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    auto result2 = longestIncreasingSubsequence(arr2);
    cout << "Length of LIS: " << result2.first << endl;
    cout << "LIS: ";
    for (int num : result2.second) {
        cout << num << " ";
    }
    cout << endl << endl;
    
    // Test Case 3: Array with all equal elements
    cout << "Test Case 3:" << endl;
    vector<int> arr3 = {7, 7, 7, 7, 7};
    cout << "Array: ";
    for (int num : arr3) {
        cout << num << " ";
    }
    cout << endl;
    
    auto result3 = longestIncreasingSubsequence(arr3);
    cout << "Length of LIS: " << result3.first << endl;
    cout << "LIS: ";
    for (int num : result3.second) {
        cout << num << " ";
    }
    cout << endl << endl;
    
    // Test Case 4: Array with alternating sequence
    cout << "Test Case 4:" << endl;
    vector<int> arr4 = {2, 5, 1, 8, 3};
    cout << "Array: ";
    for (int num : arr4) {
        cout << num << " ";
    }
    cout << endl;
    
    auto result4 = longestIncreasingSubsequence(arr4);
    cout << "Length of LIS: " << result4.first << endl;
    cout << "LIS: ";
    for (int num : result4.second) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
