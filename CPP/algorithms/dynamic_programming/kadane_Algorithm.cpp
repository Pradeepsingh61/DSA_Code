/**
 * Kadane's Algorithm - Maximum Subarray Sum (C++)
 *
 * Description:
 * Finds the maximum possible sum of a contiguous subarray within a
 * one-dimensional array of integers. Handles arrays with all-negative
 * numbers as well. Provided are two variants:
 *  - kadane: classic approach with an all-negative safeguard
 *  - kadane_optimized: concise variant that naturally handles all-negative arrays
 *
 * Time Complexity:
 *  - O(n), where n is the number of elements in the array (single pass)
 *
 * Space Complexity:
 *  - O(1), constant extra space
 */

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

int kadane(std::vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int max_so_far = INT_MIN;
    int max_ending_here = 0;

    for (int num : nums)
    {
        max_ending_here = max_ending_here + num;

        if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
        }

        if (max_ending_here < 0)
        {
            max_ending_here = 0;
        }
    }

    if (max_so_far == INT_MIN)
    {
        int max_val = nums[0];
        for (size_t i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > max_val)
            {
                max_val = nums[i];
            }
        }
        return max_val;
    }

    return max_so_far;
}

// A slightly cleaner version that handles all-negative arrays without a separate check.
int kadane_optimized(std::vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int max_so_far = nums[0];
    int current_max = nums[0];

    for (size_t i = 1; i < nums.size(); ++i)
    {
        current_max = std::max(nums[i], current_max + nums[i]);
        max_so_far = std::max(max_so_far, current_max);
    }

    return max_so_far;
}

int main()
{
    // Test case 1: Mixed positive and negative numbers
    std::vector<int> arr1 = {-2, -3, 4, -1, -2, 1, 5, -3};
    std::cout << "Array 1: [-2, -3, 4, -1, -2, 1, 5, -3]" << std::endl;
    std::cout << "Maximum subarray sum (kadane): " << kadane(arr1) << std::endl;
    std::cout << "Maximum subarray sum (optimized): " << kadane_optimized(arr1) << std::endl;
    std::cout << std::endl;

    // Test case 2: All negative numbers
    std::vector<int> arr2 = {-5, -2, -8, -1};
    std::cout << "Array 2: [-5, -2, -8, -1]" << std::endl;
    std::cout << "Maximum subarray sum (kadane): " << kadane(arr2) << std::endl;
    std::cout << "Maximum subarray sum (optimized): " << kadane_optimized(arr2) << std::endl;
    std::cout << std::endl;

    // Test case 3: All positive numbers
    std::vector<int> arr3 = {1, 2, 3, 4, 5};
    std::cout << "Array 3: [1, 2, 3, 4, 5]" << std::endl;
    std::cout << "Maximum subarray sum (kadane): " << kadane(arr3) << std::endl;
    std::cout << "Maximum subarray sum (optimized): " << kadane_optimized(arr3) << std::endl;
    std::cout << std::endl;

    // Test case 4: Single element
    std::vector<int> arr4 = {-3};
    std::cout << "Array 4: [-3]" << std::endl;
    std::cout << "Maximum subarray sum (kadane): " << kadane(arr4) << std::endl;
    std::cout << "Maximum subarray sum (optimized): " << kadane_optimized(arr4) << std::endl;
    std::cout << std::endl;

    return 0;
}