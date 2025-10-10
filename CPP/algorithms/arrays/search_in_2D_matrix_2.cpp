/*************************************************************************
 * @author: Aryan Sisodiya (@InfinityxR9) (https://github.com/InfinityxR9)
 * @category: Problem
 * @date: 9 October, 2025
 * @name: Search in a 2D Matrix (Implemented as 2D STL Vector) - II
 * DIFFICULTY: Medium
 *
 * LeetCode Reference: https://leetcode.com/problems/search-a-2d-matrix-ii/
 *
 * CONSTRAINS:
 * * m == matrix.length
 * * n == matrix[i].length
 * * 1 <= n, m <= 300
 * * -109 <= matrix[i][j] <= 109
 * * All the integers in each row are sorted in ascending order.
 * * All the integers in each column are sorted in ascending order.
 * * -109 <= target <= 109
 *
 * @details
 * Write an efficient algorithm that searches for a value target in an m x n integer matrix.
 *
 * This matrix has the following properties:
 * * Integers in each row are sorted in ascending from left to right.
 * * Integers in each column are sorted in ascending from top to bottom.
 *
 * @example
 * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]
 * target = 5
 * Output: true
 *
 * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]
 * target = 20
 * Output: false
 *
 * APPROACH: Using Two Pointers
 * * Create two pointers, say, row, pointing at the first row (0) and col, pointing to last column
 * * If, the target is less than the element, we need to search for a smaller number.
 * * Shift to left side (col--)
 * * If, the target is greater than the element, we need to search for a greater number.
 * * Shift to bottom side (row++)
 *
 * @note:
 * * This Algorithm can also be applied to the Search in 2D Matrix I also
 * * Since, we traverse only once until we reach to the target, we have linear TC
 *
 *
 *
 * Time Complexity:     O(m + n)
 * Space Complexity:    O(1)
 *
 *
 */

// Necessary Header Files import
#include <iostream>
#include <vector>
#include <random>

using namespace std;

/**
 * @brief Algorithm to find `target` in the `matrix`
 * @param matrix The 2D Matrix (with specified properties), in which the `target` is to be searched
 * @param target The value to be searched in the `matrix`
 * @return Whether the `target` is present in the `matrix` or not
 */
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if(matrix.empty() || matrix[0].empty()) return false;

    int row = 0, col = matrix[0].size() - 1;

    while (row < matrix.size() && col >= 0)
    {
        if (matrix[row][col] == target)
            return true; // Target is found
        if (matrix[row][col] > target)
            col--; // Shift to left
        else
            row++; // Shift to bottom
    }

    return false;
}

/**
 * @brief Single Test Case
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
 * @brief function to Build strictly increasing 2D matrix (row & column sorted)
 * @param rows Number of rows
 * @param cols Number of columns
 * @param start The start value `default = 1`
 * @param step The start value `default = 1`
 * @return The `matrix` so builded
 */
vector<vector<int>> build_increasing_matrix(int rows, int cols, int start = 1, int step = 1)
{
    vector<vector<int>> mat(rows, vector<int>(cols));
    int val = start;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            mat[r][c] = val;
            val += step;
        }
    return mat;
}

/**
 * @brief function to Run all the test cases
 */
void test_cases()
{
    // --- Tiny matrices ---
    run_test({{5}}, 5, true, "1x1 present");
    run_test({{5}}, 0, false, "1x1 absent");
    run_test({{1, 2, 3, 4, 5}}, 1, true, "1x5 row: first");
    run_test({{1, 2, 3, 4, 5}}, 5, true, "1x5 row: last");
    run_test({{1, 2, 3, 4, 5}}, 3, true, "1x5 row: middle");
    run_test({{1, 2, 3, 4, 5}}, 6, false, "1x5 row: absent");
    run_test({{1}, {2}, {3}, {4}, {5}}, 1, true, "5x1 col: first");
    run_test({{1}, {2}, {3}, {4}, {5}}, 5, true, "5x1 col: last");
    run_test({{1}, {2}, {3}, {4}, {5}}, 3, true, "5x1 col: middle");
    run_test({{1}, {2}, {3}, {4}, {5}}, 6, false, "5x1 col: absent");

    // --- 2x2 ---
    run_test({{1, 2}, {3, 4}}, 1, true, "2x2 top-left present");
    run_test({{1, 2}, {3, 4}}, 4, true, "2x2 bottom-right present");
    run_test({{1, 2}, {3, 4}}, 3, true, "2x2 bottom-left present");
    run_test({{1, 2}, {3, 4}}, 5, false, "2x2 absent");

    // --- Negative numbers ---
    run_test({{-10, -5, -2}, {0, 2, 4}, {10, 20, 30}}, -5, true, "Negative present");
    run_test({{-10, -5, -2}, {0, 2, 4}, {10, 20, 30}}, -6, false, "Negative absent");
    run_test({{-3, -2, -1}, {0, 0, 1}}, 0, true, "Zero present");
    run_test({{-3, -2, -1}, {0, 0, 1}}, 2, false, "Zero absent");

    // --- Multi-row ---
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 1, true, "Multi-row: first element");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 22, true, "Multi-row: last element");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 15, false, "Multi-row: absent middle");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 10, true, "Row transition: first middle row");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 12, true, "Row transition: last middle row");
    run_test({{1, 2, 3}, {10, 11, 12}, {20, 21, 22}}, 4, false, "Absent just after first row");

    // --- Sequential 3x3 ---
    run_test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 8, true, "Sequential 3x3: present");
    run_test({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 10, false, "Sequential 3x3: absent");

    // --- 4x4 matrix ---
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 22, true, "4x4 present");
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 19, false, "4x4 absent");
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 1, true, "4x4 top-left");
    run_test({{1, 2, 3, 4}, {10, 11, 12, 13}, {20, 21, 22, 23}, {30, 31, 32, 33}}, 33, true, "4x4 bottom-right");

    // --- Duplicates inside rows ---
    run_test({{1, 1, 2}, {2, 3, 3}, {3, 4, 5}}, 2, true, "Duplicates present");
    run_test({{1, 1, 2}, {2, 3, 3}, {3, 4, 5}}, 6, false, "Duplicates absent");
    run_test({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}}, 1, true, "All duplicates row middle present");
    run_test({{0, 0, 0}, {1, 1, 1}, {2, 2, 2}}, 3, false, "All duplicates row middle absent");

    // --- Large gaps ---
    run_test({{1, 2, 3}, {100, 200, 300}, {1000, 2000, 3000}}, 200, true, "Large gap present");
    run_test({{1, 2, 3}, {100, 200, 300}, {1000, 2000, 3000}}, 250, false, "Large gap absent");

    // --- Mixed intervals ---
    run_test({{1, 5, 9}, {20, 25, 30}, {100, 200, 300}}, 25, true, "Random intervals present");
    run_test({{1, 5, 9}, {20, 25, 30}, {100, 200, 300}}, 50, false, "Random intervals absent");

    // --- Outside range ---
    run_test({{5, 10, 15}, {20, 25, 30}}, 1, false, "Target smaller than min");
    run_test({{5, 10, 15}, {20, 25, 30}}, 35, false, "Target larger than max");
    run_test({{-100, -50, 0}, {1, 50, 100}}, -200, false, "Below min negative");
    run_test({{-100, -50, 0}, {1, 50, 100}}, 200, false, "Above max positive");

    // --- Programmatic matrices ---
    mt19937 rng(42);
    for (int t = 0; t < 5; t++)
    {
        int rows = 1 + rng() % 6;
        int cols = 1 + rng() % 6;
        auto M = build_increasing_matrix(rows, cols, -50, 3);
        int target_present = M[rng() % rows][rng() % cols];
        run_test(M, target_present, true, "Random matrix present Test " + to_string(t + 1));
        int target_absent = M[rows - 1][cols - 1] + 1;
        run_test(M, target_absent, false, "Random matrix absent Test " + to_string(t + 1));
    }

    // --- Long row / column ---
    vector<int> longRow(300);
    for (int i = 0; i < 300; i++)
        longRow[i] = i * 2;
    run_test({longRow}, 598, true, "Long row last element present");
    run_test({longRow}, 599, false, "Long row absent");
    vector<vector<int>> longCol(300, vector<int>(1));
    for (int i = 0; i < 300; i++)
        longCol[i][0] = i * 3;
    run_test(longCol, 150, true, "Long column present");
    run_test(longCol, 151, false, "Long column absent");

    // --- Stress 300x300 maximum constraints ---
    vector<vector<int>> maxMat(300, vector<int>(300));
    int val = -1e9;
    for (int i = 0; i < 300; i++)
        for (int j = 0; j < 300; j++)
            maxMat[i][j] = val++;
    run_test(maxMat, -1e9, true, "Stress min boundary 300x300");
    run_test(maxMat, val - 1, true, "Stress max boundary 300x300");
    run_test(maxMat, 1e9, false, "Stress absent positive 300x300");
    run_test(maxMat, -1e9 - 1, false, "Stress absent negative 300x300");

    cout << "---- All Test Cases run successfully ----" << endl;
}

// Main function
int main()
{
    // Running the test cases
    test_cases();

    return 0;
}
