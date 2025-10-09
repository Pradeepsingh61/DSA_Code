/*************************************************************************
 * @author: Aryan Sisodiya (@InfinityxR9) (https://github.com/InfinityxR9)
 * @category: Problem
 * @date: 9 October, 2025
 * @name: Search in a 2D Matrix (Implemented as 2D STL Vector) - I
 * DIFFICULTY: Medium
 *
 * LeetCode Reference: https://leetcode.com/problems/search-a-2d-matrix/
 * Constrains:
 * * m == matrix.length
 * * n == matrix[i].length
 * * 1 <= m, n <= 100
 * * -104 <= matrix[i][j], target <= 104
 *
 * @details
 * You are given a m x n integer matrix with the following two properties:
 * * Each row is sorted in non-decreasing order.
 * * The first integer of each row is greater than the last integer of the previous row.
 *
 * Given an integer target, return true if target is in matrix or false otherwise.
 *
 * You must write a solution in O(log(m * n)) time complexity.
 *
 * @example
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 *
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * Output: false
 *
 * Approach: Using Binary Search Twice
 * * (1) We use binary search first to find out the target lies in which row
 *   (2) We use binary search second on that row to find out whether target lies in matrix or not.
 *
 * * The matrix is sorted in a zig-zag fashion.
 * * Hence, the Binary Search approach is very well applicable.
 *
 *
 * Time Complexity:     O(log (m * n))
 * Space Complexity:    O(1)
 *
 *
 */

// Necessary Header Files import
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

/**
 * Core Algorithm using Binary Search twice to find `target`
 * @param matrix The 2D Matrix (with specified properties), in which the `target` is to be searched
 * @param target The value to be searched in the `matrix`
 * @return Whether the `target` is present in the `matrix` or not
 */
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    // Variables Assignment to find the row
    int sRow = 0, eRow = matrix.size() - 1, sMid;

    while (sRow <= eRow)
    {
        sMid = sRow + (eRow - sRow) / 2;

        if (matrix[sMid][0] <= target &&
            matrix[sMid][matrix[sMid].size() - 1] >= target)
            break;
        else if (matrix[sMid][0] < target &&
                 matrix[sMid][matrix[sMid].size() - 1] < target)
            sRow = sMid + 1; // Search in right half
        else
            eRow = sMid - 1; // Search in left half
    }

    // Variables assignment for Binary Search in so found row
    int low = 0, high = matrix[sMid].size() - 1, mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (matrix[sMid][mid] == target)
            return true; // target found!
        else if (matrix[sMid][mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}

/**
 * Running Single Test Case
 * @param input The 2D Matrix with specified property
 * @param target The target value to be searched in the 2D Matrix
 * @param expected The expected output
 * @param testName Test Case brief Description
 */
void run_test(vector<vector<int>> input, const int target, const bool expected, const string testName)
{
    bool ans = searchMatrix(input, target);
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
 * Utility function to build a strictly-increasing flattened matrix with `rows` x `cols`.
 * @param rows Number of rows
 * @param cols Number of columns
 * @param start The start value `default = 1`
 * @param step The start value `default = 1`
 * @return The `matrix` so builded
 */
vector<vector<int>> build_increasing_matrix(int rows, int cols, int start = 1, int step = 1)
{
    vector<vector<int>> mat(rows, vector<int>());
    int val = start;
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            mat[r].push_back(val);
            val += step;
        }
    }
    return mat;
}

/**
 * Utility function to Run all the test cases
 */
void test_cases()
{
    // 1-2: Given examples
    run_test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3, true, "Example Case 1: Found (middle row)");
    run_test({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 13, false, "Example Case 2: Not present");

    // 3-4: Single element
    run_test({{5}}, 5, true, "Single element present");
    run_test({{5}}, -5, false, "Single element absent");

    // 5-8: Single row
    run_test({{1, 3, 5, 7, 9}}, 7, true, "Single row: present (middle)");
    run_test({{1, 3, 5, 7, 9}}, 2, false, "Single row: absent (between)");
    run_test({{1, 3, 5, 7, 9}}, 1, true, "Single row: first element");
    run_test({{1, 3, 5, 7, 9}}, 9, true, "Single row: last element");

    // 9-10: Single column
    run_test({{1}, {3}, {5}, {7}, {9}}, 5, true, "Single column: middle present");
    run_test({{1}, {3}, {5}, {7}, {9}}, 4, false, "Single column: absent between rows");

    // 11-13: Multi-row: first, last, between
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 1, true, "Multi-row: first element");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 22, true, "Multi-row: last element");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 15, false, "Multi-row: value between rows");

    // 14-15: Large gaps
    run_test({{1, 2, 3}, {100, 200, 300}, {1000, 2000, 3000}}, 200, true, "Large gap: present");
    run_test({{1, 2, 3}, {100, 200, 300}, {1000, 2000, 3000}}, 250, false, "Large gap: absent");

    // 16-17: Negatives
    run_test({{-10, -5, -2}, {0, 2, 4}, {10, 20, 30}}, -5, true, "Negative number present");
    run_test({{-10, -5, -2}, {0, 2, 4}, {10, 20, 30}}, -6, false, "Negative number absent");

    // 18-19: Mix negatives and positives
    run_test({{-100, -50, -10}, {0, 1, 2}, {10, 20, 30}}, 0, true, "Zero present (row boundary)");
    run_test({{-100, -50, -10}, {0, 1, 2}, {10, 20, 30}}, 3, false, "Positive absent across rows");

    // 20-21: Outside range
    run_test({{5, 10, 15}, {20, 25, 30}}, 1, false, "Target smaller than min");
    run_test({{5, 10, 15}, {20, 25, 30}}, 35, false, "Target larger than max");

    // 22-23: 2x2
    run_test({{1, 2}, {3, 4}}, 3, true, "2x2 present");
    run_test({{1, 2}, {3, 4}}, 5, false, "2x2 absent");

    // 24-25: 3x1 column
    run_test({{2}, {4}, {6}}, 4, true, "3x1 column present");
    run_test({{2}, {4}, {6}}, 5, false, "3x1 column absent");

    // 26-27: Random small valid matrices
    run_test({{1, 4, 7}, {10, 14, 18}, {25, 30, 35}}, 30, true, "Random small: present");
    run_test({{1, 4, 7}, {10, 14, 18}, {25, 30, 35}}, 26, false, "Random small: absent");

    // 28-29: 4x4
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 22, true, "4x4 present");
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 19, false, "4x4 absent (gap)");

    // 30-32: Boundary extremes (constraints: -10^4 .. 10^4)
    run_test({{-10000, -9999, -9998}, {0, 1, 2}, {9998, 9999, 10000}}, -10000, true, "Boundary min present");
    run_test({{-10000, -9999, -9998}, {0, 1, 2}, {9998, 9999, 10000}}, 10000, true, "Boundary max present");
    run_test({{-10000, -9999, -9998}, {0, 1, 2}, {9998, 9999, 10000}}, 5000, false, "Boundary mid absent");

    // 33-34: Larger random-like
    run_test({{1, 3, 5, 7, 9, 11}, {20, 22, 24, 26, 28, 30}, {40, 42, 44, 46, 48, 50}}, 28, true, "Larger random: present");
    run_test({{1, 3, 5, 7, 9, 11}, {20, 22, 24, 26, 28, 30}, {40, 42, 44, 46, 48, 50}}, 29, false, "Larger random: absent");

    // 35-36: Sequential 1..9
    run_test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 8, true, "Sequential present");
    run_test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 10, false, "Sequential absent");

    // 37-38: Rectangular 2x5
    run_test({{1, 2, 3, 4, 5}, {10, 11, 12, 13, 14}}, 12, true, "Rectangular 2x5 present");
    run_test({{1, 2, 3, 4, 5}, {10, 11, 12, 13, 14}}, 9, false, "Rectangular 2x5 absent");

    // 39-40: Row transitions
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 10, true, "Row transition: first element of middle row");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 12, true, "Row transition: last element of middle row");

    // 41-42: Mixed intervals
    run_test({{2, 4, 6, 8}, {15, 20, 25, 30}, {100, 200, 300, 400}}, 300, true, "Mixed intervals: present");
    run_test({{2, 4, 6, 8}, {15, 20, 25, 30}, {100, 200, 300, 400}}, 99, false, "Mixed intervals: absent");

    // 43-44: Repeated values inside rows (allowed) but strict across rows
    run_test({{1, 1, 1, 2}, {3, 3, 3, 4}}, 1, true, "Repeateds in row: find repeat value");
    run_test({{1, 1, 1, 2}, {3, 3, 3, 4}}, 3, true, "Repeateds in next row: find repeat value");

    // 45: All-equal single row
    run_test({{2, 2, 2, 2}}, 2, true, "Single row all-equal: present");

    // 46: Varying row lengths
    run_test({{1, 2}, {3, 4, 5}, {6}}, 5, true, "Varying row lengths: present");

    // 47: Absent just after first row
    run_test({{1, 2, 3}, {10, 11, 12}}, 4, false, "Absent just after first row (gap)");

    // 48: Negative to zero transition with duplicates
    run_test({{-3, -2, -1}, {0, 0, 1}}, 0, true, "Negative->Zero with duplicates: present");

    // 49: Long single row (n = 100) - generated
    {
        vector<int> longRow;
        longRow.reserve(100);
        for (int i = 0; i < 100; ++i)
            longRow.push_back(i * 2 + 1); // odd numbers 1..199
        run_test({longRow}, 199, true, "Long single row (n=100): last element present");
        run_test({longRow}, 100, false, "Long single row (n=100): absent even number");
    }

    // 50-52: Programmatic, deterministic random-ish matrices (fixed seed)
    {
        mt19937 rng(42);
        for (int t = 0; t < 3; ++t)
        {
            int rows = 1 + (rng() % 6);      // 1..6 rows
            int cols = 1 + (rng() % 8);      // 1..8 cols
            int start = -50 + (rng() % 101); // -50..50
            int step = 1 + (rng() % 5);      // 1..5
            auto M = build_increasing_matrix(rows, cols, start, step);

            // pick a random cell to be the target (should be present)
            int rr = rng() % rows;
            int cc = rng() % cols;
            int target_present = M[rr][cc];
            run_test(M, target_present, true, "GenMatrix present (deterministic seed)");

            // pick a value guaranteed absent: take last element and add 1
            int last = M[rows - 1][cols - 1];
            int target_absent = last + 1;
            run_test(M, target_absent, false, "GenMatrix absent (just above last)");
        }
    }
}

// Main function
int main()
{
    // Running the test cases
    test_cases();

    return 0;
}
