/*
 * Algorithm: Search in Rotated Sorted Array
 * Language: C++
 * Description: 
 * Searches for an integer 'target' in a sorted array 'nums' that has been 
 * left-rotated at an unknown pivot point 'k'. The algorithm must achieve 
 * O(log n) runtime complexity, which requires a modified Binary Search.
 * * Problem Constraints:
 * - nums is sorted ascendingly with distinct values.
 * - The array structure is [nums[k], ..., nums[n-1], nums[0], ..., nums[k-1]].
 * - Example: [4,5,6,7,0,1,2] (rotated at k=4 from [0,1,2,4,5,6,7]).
 * * Time Complexity: O(log n) // Achieved via single-pass Binary Search
 * Space Complexity: O(1)   // In-place search using only a few pointers
 * Author: Adi-3108
 
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Searches for a target value in a possibly rotated sorted array using O(log n) time.
 * * The core idea is that in a rotated sorted array, at least one half (left or right) 
 * defined by the 'mid' point MUST be sorted. We identify the sorted half and check 
 * if the 'target' falls within that sorted range. If it does, we move our search 
 * boundary (low/high) into that sorted half. Otherwise, the target must be in the 
 * unsorted/rotated half, and we move the search there.
 * * @param nums The rotated sorted array of unique integers.
 * @param target The integer value to search for.
 * @return int The index of the target if found, or -1 otherwise.
 */
int searchRotatedSortedArray(const std::vector<int>& nums, int target) {
    // Input validation (Constraint: nums.length >= 1, but safe to check)
    if (nums.empty()) {
        return -1;
    }

    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        // --- Core Binary Search Logic ---

        // 1. Check if the left half is sorted (comparison between the extremes)
        if (nums[low] <= nums[mid]) {
            // Left half [low...mid] is sorted.
            
            // Check if the target is within the sorted left half
            if (target >= nums[low] && target < nums[mid]) {
                // Target is in the sorted left half; search there.
                high = mid - 1;
            } else {
                // Target must be in the rotated right half; search there.
                low = mid + 1;
            }
        } 
        
        // 2. Otherwise, the right half must be sorted (from nums[mid] to nums[high])
        else {
            // Right half [mid...high] is sorted.

            // Check if the target is within the sorted right half
            if (target > nums[mid] && target <= nums[high]) {
                // Target is in the sorted right half; search there.
                low = mid + 1;
            } else {
                // Target must be in the rotated left half; search there.
                high = mid - 1;
            }
        }
    }

    // Target not found after exhausting the array.
    return -1;
}

// Test Function
void testSearchRotatedSortedArray() {
    std::cout << "--- Testing Search in Rotated Sorted Array ---\n";

    // Example 1: Input: [4,5,6,7,0,1,2], target = 0, Output: 4
    std::vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    int expected1 = 4;
    int result1 = searchRotatedSortedArray(nums1, target1);
    std::cout << "Test 1: Input: [4,5,6,7,0,1,2], Target: 0\n";
    std::cout << "Expected: " << expected1 << ", Actual: " << result1 << " | " 
              << (result1 == expected1 ? "PASS" : "FAIL") << std::endl;

    // Example 2: Input: [4,5,6,7,0,1,2], target = 3, Output: -1
    std::vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    int expected2 = -1;
    int result2 = searchRotatedSortedArray(nums2, target2);
    std::cout << "Test 2: Input: [4,5,6,7,0,1,2], Target: 3\n";
    std::cout << "Expected: " << expected2 << ", Actual: " << result2 << " | "
              << (result2 == expected2 ? "PASS" : "FAIL") << std::endl;

    // Example 3: Input: [1], target = 0, Output: -1
    std::vector<int> nums3 = {1};
    int target3 = 0;
    int expected3 = -1;
    int result3 = searchRotatedSortedArray(nums3, target3);
    std::cout << "Test 3: Input: [1], Target: 0\n";
    std::cout << "Expected: " << expected3 << ", Actual: " << result3 << " | "
              << (result3 == expected3 ? "PASS" : "FAIL") << std::endl;

    // Edge Case: No rotation (Target found)
    std::vector<int> nums4 = {1, 2, 3, 4, 5};
    int target4 = 4;
    int expected4 = 3;
    int result4 = searchRotatedSortedArray(nums4, target4);
    std::cout << "Test 4: Input: [1,2,3,4,5], Target: 4\n";
    std::cout << "Expected: " << expected4 << ", Actual: " << result4 << " | "
              << (result4 == expected4 ? "PASS" : "FAIL") << std::endl;
}

int main() {
    testSearchRotatedSortedArray();
    return 0;
}