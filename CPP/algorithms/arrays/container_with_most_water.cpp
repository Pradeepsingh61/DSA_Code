/**
 * @author: Aryan Sisodiya (@InfinityxR9) (https://github.com/InfinityxR9)
 * @category: Problem
 * @date: 6 October, 2025
 * @name: Container With Most Water
 * DIFFICULTY: Medium
 *
 * LeetCode Reference: https://leetcode.com/problems/container-with-most-water/
 * Constrains:
 * * n == height.length
 * * 2 <= n <= 105
 * * 0 <= height[i] <= 104
 *
 * @details
 * You are given an integer array height of length n.
 * There are n vertical lines drawn such that the two endpoints of the ith line
 * are (i, 0) and (i, height[i]).
 *
 * Find two lines that together with the x-axis form a container,
 * such that the container contains the most water.
 *
 * Return the maximum amount of water a container can store.
 *
 * Notice that you may not slant the container.
 *
 * @example
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7].
 * In this case, the max area of water (blue section) the container can contain is 49.
 *
 * Input: height = [1,1]
 * Output: 1
 *
 * Approach: Using Two Pointers Approach
 * * You create two pointers at the first position (i) and end position of the array (j)
 * * You find the base length by subtracting the values at i and j
 * * Since minimum of those two heights (height[i] and height[j]) will be used for container height
 * * You find the container height and multiply it by the base to get the area
 * * You keep on calculating the current area and take max with the existing proposed maximum Area
 * * You move the pointer which is at the less height position.
 * (Since min of height determine the actual height)
 * * You keep of doing it until i and j pointers overlap each other.
 * * Return the max Area at the end.
 *
 * Time Complexity:     O(n)
 * Space Complexity:    O(1)
 *
 *
 */

// Necessary Header Files import
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>

using namespace std;

/**
 * Core Algorithm using Two Pointers Approach to find the container with most water
 * @param height The array container the height of vertical lines
 * @returns The maximum possible water area of the biggest container
 */
int max_area(vector<int> &height)
{
    // Pointers Assignment
    int i = 0;
    int j = height.size() - 1;

    // Utility Variables Assignment
    int max_area = INT_MIN;
    int base;
    int min_height;
    int curr_area;

    while (i < j)
    {
        min_height = min(height[i], height[j]);
        base = j - i;

        curr_area = base * min_height;
        max_area = max(curr_area, max_area);

        if (height[i] > height[j])
            j--;
        else
            i++;
    }

    return max_area;
}

/**
 * Running Single Test Case
 * @param input The array with the height of verticle lines
 * @param expected The expected output
 * @param testName Test Case brief Description
 */
void run_test(vector<int> input, const int expected, const string testName)
{
    const int ans = max_area(input);
    if (ans == expected)
    {
        cout << "[PASS] " << testName << endl;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        cout << "  Expected: " << expected;
        cout << "\n  Got:      " << ans;
        cout << "\n\n";
    }
}

/**
 * Utility function to Run all the test cases
 */
void test_cases()
{
    // Basic cases from LeetCode
    run_test({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49, "Random mix (LeetCode example)");
    run_test({1, 1}, 1, "Two lines, same height");
    run_test({1, 2}, 1, "Two lines, different height");

    // Edge cases
    run_test({0, 0}, 0, "Two lines, both zero");
    run_test({0, 1}, 0, "One zero, one non-zero");
    run_test({10000, 10000}, 10000, "Max height, two lines");

    // All zeros
    run_test({0, 0, 0, 0, 0}, 0, "All zeros");

    // All ones
    run_test({1, 1, 1, 1, 1}, 4, "All ones");

    // Increasing heights
    run_test({1, 2, 3, 4, 5}, 6, "Strictly increasing heights");

    // Decreasing heights
    run_test({5, 4, 3, 2, 1}, 6, "Strictly decreasing heights");

    // Alternating pattern
    run_test({1, 10000, 1, 10000, 1}, 20000, "Alternating max/min heights");

    // Large random array (n=300, values 0-10000)
    vector<int> large(300);
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> dist(0, 10000);
    for (int &x : large)
        x = dist(g);
    // For random, we can't know expected, so just print result
    cout << "[INFO] Large random array (n=300): Max area = " << max_area(large) << endl;

    // Minimum constraint (n=2)
    run_test({2, 3}, 2, "Minimum constraint (n=2)");

    // Maximum constraint (n=100000, all max height)
    vector<int> max_large(100000, 10000);
    // Expected area: (n-1) * 10000
    run_test(max_large, (100000 - 1) * 10000, "Maximum constraint (n=100000, all max height)");

    // Zigzag pattern
    run_test({1, 10000, 1, 10000, 1, 10000, 1}, 40000, "Zigzag pattern");

    // Single peak in the middle
    run_test({1, 2, 10000, 2, 1}, 4, "Single peak in the middle");

    // Plateau
    run_test({5, 5, 5, 5, 5}, 20, "Plateau");

    // Valley
    run_test({10000, 1, 10000}, 20000, "Valley");

    // Sparse non-zero
    run_test({0, 0, 0, 10000, 0, 0, 0}, 0, "Sparse non-zero");

    // Two distant tall lines
    run_test({10000, 0, 0, 0, 10000}, 40000, "Two distant tall lines");

    // Random mix, small
    run_test({3, 1, 2, 4, 5}, 12, "Random mix, small");

    // All different heights
    run_test({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 25, "All different heights");

    // Large array, increasing then decreasing
    vector<int> inc_dec(1000);
    for (int i = 0; i < 500; ++i)
        inc_dec[i] = i + 1;
    for (int i = 500; i < 1000; ++i)
        inc_dec[i] = 1000 - i;
    cout << "[INFO] Large inc/dec array (n=1000): Max area = " << max_area(inc_dec) << endl;

    // Tallest lines at both ends, with small values in between
    run_test({10000, 1, 1, 1, 10000}, 40000, "Tallest lines at both ends, small middle");

    // Only one non-zero at the start
    run_test({10000, 0, 0, 0, 0}, 0, "Only one non-zero at start");

    // Only one non-zero at the end
    run_test({0, 0, 0, 0, 10000}, 0, "Only one non-zero at end");

    // Two non-zero lines next to each other
    run_test({0, 10000, 10000, 0}, 10000, "Two non-zero lines next to each other");

    // Heights with plateau in the middle
    run_test({1, 5, 5, 5, 1}, 10, "Plateau in the middle");

    // Heights with valley in the middle
    run_test({5, 1, 5}, 10, "Valley in the middle");

    // All heights are the same except one
    run_test({5, 5, 5, 1, 5, 5, 5}, 30, "All same except one");

    // Increasing then plateau
    run_test({1, 2, 3, 3, 3}, 6, "Increasing then plateau");

    // Plateau then decreasing
    run_test({3, 3, 3, 2, 1}, 6, "Plateau then decreasing");
}

// Main function
int main()
{
    // Running the test cases
    test_cases();

    return 0;
}
