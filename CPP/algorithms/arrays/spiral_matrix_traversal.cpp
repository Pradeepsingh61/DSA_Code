/*************************************************************************
 * @author: Aryan Sisodiya (@InfinityxR9) (https://github.com/InfinityxR9)
 * @category: Algorithm
 * @date: 9 October, 2025
 * @name: Spiral Matrix Traversal
 * DIFFICULTY: Medium
 *
 * LeetCode Reference: https://leetcode.com/problems/spiral-matrix/
 *
 * CONSTRAINS:
 * * m == matrix.length
 * * n == matrix[i].length
 * * 1 <= m, n <= 10
 * * -100 <= matrix[i][j] <= 100
 *
 * @details
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * @example
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 * Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * APPROACH:
 * * Create 4 pointers, initially, pointing to first row, last row, first column, last column
 * * (Or the 4 boundaries)
 * * We'll traverse the matrix boundary wise, first, the top row boundary, then the right boundary,
 *   then bottom boundary and at last, the left boundary
 * * Update the boundary values to shrink the matrix
 * * Repeat the process to traverse the complete matrix in spiral fashion
 *
 * @note Edge Cases:
 * * When the conditions meets when the top and bottom boundaries are equal,
 *   that particular row would be traversed twice.
 * * To tackle this, if both the boundaries are equal, we traverse only once.
 * * Same goes for the columnar boundaries too
 *
 * @note Extra Space:
 * * The vector<int> created to store the traversal will not be considered in space complexity
 *   as it is a demand of the problem and no auxillary space is used
 *
 *
 *
 * Time Complexity:     O(m * n)
 * Space Complexity:    O(1)
 *
 *
 */

// Necessary Header Files import
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

/**
 * @brief Algorithm to traverse the `matrix` in Spiral Fashion
 * @param matrix The 2D Matrix to be traversed
 * @return The spiral traversal of `matrix`
 */
vector<int> spiral_order(const vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    int srow = 0, erow = m - 1, scol = 0, ecol = n - 1;
    vector<int> trav;

    while (srow <= erow && scol <= ecol)
    {
        for (int i = scol; i <= ecol; i++)
            trav.push_back(matrix[srow][i]);
        for (int i = srow + 1; i < erow; i++)
            trav.push_back(matrix[i][ecol]);
        if (srow != erow)
        {
            for (int i = ecol; i >= scol; i--)
                trav.push_back(matrix[erow][i]);
        }
        if (scol != ecol)
        {
            for (int i = erow - 1; i > srow; i--)
                trav.push_back(matrix[i][scol]);
        }

        scol++;
        ecol--;
        srow++;
        erow--;
    }

    return trav;
}

/**
 * @brief Single Test Case
 * @param input The 2D Matrix to be traversed Spirally
 * @param expected The expected output
 * @param testName Test Case brief Description
 */
void run_test(vector<vector<int>> input, const vector<int> expected, const string testName)
{
    vector<int> ans = spiral_order(input);
    if (ans == expected)
    {
        cout << "[PASS] " << testName << endl;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        cout << "  Expected: ";
        cout << "[";
        for (int i : expected)
        {
            cout << i << " ";
        }
        cout << "]";
        cout << "\n  Got: ";
        cout << "[";
        for (int i : ans)
        {
            cout << i << " ";
        }
        cout << "]";
        cout << "\n\n";
    }
}

/**
 * @brief Build a 2D matrix for test cases *
 * @param rows Number of rows
 * @param cols Number of columns
 * @param start Starting number (default = 1)
 * @param step Step increment (default = 1)
 * @param duplicates If true, all values in a row are duplicated (default = false)
 * @param randomize If true, values are random (default = false)
 * @param minVal Minimum value for random (only used if randomize=true)
 * @param maxVal Maximum value for random (only used if randomize=true)
 * @return vector<vector<int>> The built matrix
 */
vector<vector<int>> build_matrix(int rows, int cols, int start = 1, int step = 1,
                                 bool duplicates = false, bool randomize = false,
                                 int minVal = -100, int maxVal = 100)
{
    vector<vector<int>> mat(rows, vector<int>(cols));
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int val = start;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (randomize)
            {
                mat[r][c] = minVal + rng() % (maxVal - minVal + 1);
            }
            else if (duplicates)
            {
                mat[r][c] = val;
            }
            else
            {
                mat[r][c] = val;
                val += step;
            }
        }
        if (duplicates && !randomize)
            val += step;
    }
    return mat;
}

/**
 * @brief function to Run all the test cases
 */
void test_cases()
{
    mt19937 rng(42); // deterministic random for test repeatability

    // ---------------- Tiny matrices ----------------
    run_test({{1}}, {1}, "1x1 single element");
    run_test({{1, 2}}, {1, 2}, "1x2 row");
    run_test({{1}, {2}}, {1, 2}, "2x1 col");
    run_test({{1, 2}, {3, 4}}, {1, 2, 4, 3}, "2x2 square");

    // ---------------- Rectangular matrices ----------------
    run_test({{1, 2, 3}, {4, 5, 6}}, {1, 2, 3, 6, 5, 4}, "2x3 rectangle");
    run_test({{1, 2}, {3, 4}, {5, 6}}, {1, 2, 4, 6, 5, 3}, "3x2 rectangle");

    // ---------------- Negative numbers ----------------
    run_test({{-3, -2, -1}, {0, 1, 2}, {3, 4, 5}}, {-3, -2, -1, 2, 5, 4, 3, 0, 1}, "3x3 negatives mixed");

    // ---------------- Duplicates ----------------
    run_test({{1, 1, 2}, {2, 2, 3}, {3, 3, 3}}, {1, 1, 2, 3, 3, 3, 3, 2, 2}, "3x3 duplicates");

    // ---------------- Sequential 3x3 ----------------
    run_test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {1, 2, 3, 6, 9, 8, 7, 4, 5}, "3x3 sequential");

    // ---------------- 4x4 ----------------
    run_test({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
             {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10}, "4x4 sequential");

    // ---------------- Single row ----------------
    run_test({{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, "1x10 single row");

    // ---------------- Single column ----------------
    run_test({{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, "10x1 single col");

    // ---------------- Longest allowed (10x10) ----------------
    auto mat10x10 = build_matrix(10, 10);
    run_test(mat10x10, spiral_order(mat10x10), "10x10 increasing");

    // ---------------- Random matrices ----------------
    for (int t = 0; t < 5; t++)
    {
        int r = 1 + rng() % 10;
        int c = 1 + rng() % 10;
        auto mat = build_matrix(r, c, 0, 1, false, true, -50, 50);
        run_test(mat, spiral_order(mat), "Random " + to_string(r) + "x" + to_string(c));
    }

    // ---------------- Large gaps ----------------
    run_test({{1, 100, 200}, {300, 400, 500}}, {1, 100, 200, 500, 400, 300}, "Large gaps 2x3");
    run_test({{1, 2, 3}, {100, 200, 300}, {1000, 2000, 3000}}, {1, 2, 3, 300, 3000, 2000, 1000, 100, 200}, "Large gaps 3x3");

    // ---------------- Edge cases ----------------
    run_test({{1, 2, 3, 4}}, {1, 2, 3, 4}, "1x4 single row edge");
    run_test({{1}, {2}, {3}, {4}}, {1, 2, 3, 4}, "4x1 single col edge");

    // ---------------- All duplicates ----------------
    auto mat5x5 = build_matrix(5, 5, 7, 0, true);
    run_test(mat5x5, spiral_order(mat5x5), "5x5 all duplicates");

    // ---------------- Increasing by 2 ----------------
    auto mat4x4_step2 = build_matrix(4, 4, 1, 2);
    run_test(mat4x4_step2, {1, 3, 5, 7, 15, 23, 31, 29, 27, 25, 17, 9, 11, 13, 21, 19}, "4x4 step 2");

    // ---------------- Negative start ----------------
    auto mat3x3_neg = build_matrix(3, 3, -5, 2);
    run_test(mat3x3_neg, {-5, -3, -1, 5, 11, 9, 7, 1, 3}, "3x3 negative start");

    // ---------------- 1xN and Nx1 extremes ----------------
    auto mat1x10 = build_matrix(1, 10);
    run_test(mat1x10, spiral_order(mat1x10), "1x10 row extreme");

    auto mat10x1 = build_matrix(10, 1);
    run_test(mat10x1, spiral_order(mat10x1), "10x1 col extreme");

    // ---------------- Random small matrices ----------------
    for (int t = 0; t < 5; t++)
    {
        int r = 1 + rng() % 5;
        int c = 1 + rng() % 5;
        auto mat = build_matrix(r, c, 0, 1, false, true, -10, 10);
        run_test(mat, spiral_order(mat), "Random small " + to_string(r) + "x" + to_string(c));
    }

    // ---------------- Random duplicates ----------------
    for (int t = 0; t < 5; t++)
    {
        int r = 2 + rng() % 5;
        int c = 2 + rng() % 5;
        auto mat = build_matrix(r, c, 5, 0, true);
        run_test(mat, spiral_order(mat), "Random duplicates " + to_string(r) + "x" + to_string(c));
    }

    // ---------------- Stress Test ----------------
    auto stress_mat = build_matrix(10, 10, 1, 1, false, true, -100, 100);
    auto expected_stress = spiral_order(stress_mat);
    run_test(stress_mat, expected_stress, "Stress Test 10x10 Random");

    cout << "---- All Test Cases run successfully ----" << endl;
}

// Main function
int main()
{
    // Running the test cases
    test_cases();

    return 0;
}
