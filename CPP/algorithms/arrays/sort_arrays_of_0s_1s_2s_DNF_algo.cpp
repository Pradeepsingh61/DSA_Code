/**
 *
 * @author: Aryan Sisodiya (@InfinityxR9) (https://github.com/InfinityxR9)
 * @category: Algorithm
 * @date: 5 October, 2025
 * @name: Dutch National Flag Algorithm (DNF)
 * DIFFICULTY: Medium
 *
 * LeetCode Reference: https://leetcode.com/problems/sort-colors/description/
 * Constrains:
    - n == arr.length
    - 1 <= n <= 300
    - arr[i] is either 0, 1, or 2.
 *
 *
 *
 * DUTCH NATIONAL FLAG ALGORITHM (DNF ALGO)
    - Given an array of 0s, 1s and 2s. Symbolically, representing balls of colors Red, Blue and Black.
    - We have to sort the array such that the same color balls are adjacent. (Without using any in-built sort function)

 * Three Pass Approach (Brute Force):
    - We count the number of occurences of 0s, 1s and 2s
    - Redefine the array elements accordingly

 * DNF Three Pointers-Single Pass Approach:
    - We create three pointers, namely, low, mid, high
    - We assign the unsorted array part ranging from mid to high pointer values.
    - We sort until mid == high (i.e., the unsorted part vanishes)
    - The part of 0 to low - 1 is includes all the 0s, low to mid - 1 all the 1s, high + 1 to size - 1 all the 2s.
    - The remaining part of mid to high includes the unsorted elements, which ultimately vanishes. (Base condition)

    - Initialise low = 0, mid = 0, high = size - 1
    - If we encounter mid val = 0, swap(low val, mid val), low++, mid++
    - If we encounter mid val = 1, mid++
    - If we encounter mid val = 0, swap(high val, mid val), high--

 * Time Complexity:    O(n)
 * Space Complexity:   O(1)
 *
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>   

using namespace std;

/**
 * Core DNF Algorithm
 * @param arr Array of 0s, 1s and 2s to be sorted
 */
void dnf_sort(vector<int> &arr)
{
    // Input Validation
    for (int x : arr)
    {
        if (x != 0 && x != 1 && x != 2)
        {
            cout << "Invalid Input Array" << endl;
            return;
        }
    }

    int mid = 0, high = arr.size() - 1, low = 0;

    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[mid], arr[low]);
            mid++;
            low++;
        }
        else if (arr[mid] == 1)
            mid++;
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

/**
 * Running Single Test Case
 * @param input The array to be checked
 * @param expected The expected output
 * @param testName Test Case brief Description
 */
void run_test(vector<int> input, const vector<int> expected, const string testName)
{
    dnf_sort(input);
    if (input == expected)
    {
        cout << "[PASS] " << testName << endl;
    }
    else
    {
        cout << "[FAIL] " << testName << endl;
        cout << "  Expected: ";
        for (int x : expected)
            cout << x << " ";
        cout << "\n  Got:      ";
        for (int x : input)
            cout << x << " ";
        cout << "\n\n";
    }
}

/**
 * Utility function to Run all the test cases
 */
void test_cases()
{
    run_test({2, 0, 1, 2, 1, 0}, {0, 0, 1, 1, 2, 2}, "Random mix");
    run_test({}, {}, "Empty array");
    run_test({0}, {0}, "Single element 0");
    run_test({1}, {1}, "Single element 1");
    run_test({2}, {2}, "Single element 2");
    run_test({0, 0, 1, 1, 2, 2}, {0, 0, 1, 1, 2, 2}, "Already sorted");
    run_test({2, 2, 1, 1, 0, 0}, {0, 0, 1, 1, 2, 2}, "Reverse sorted");
    run_test({0, 0, 0}, {0, 0, 0}, "All zeros");
    run_test({1, 1, 1}, {1, 1, 1}, "All ones");
    run_test({2, 2, 2}, {2, 2, 2}, "All twos");
    run_test({0, 1, 2, 0, 1, 2, 0, 1, 2}, {0, 0, 0, 1, 1, 1, 2, 2, 2}, "Alternating Values");
    run_test({0, 2, 0, 2, 0, 2}, {0, 0, 0, 2, 2, 2}, "Only two values (0 and 2)");
    run_test({1, 2, 1, 2, 1, 2}, {1, 1, 1, 2, 2, 2}, "Only two values (1 and 2)");
    run_test({0, 0, 0, 0, 2}, {0, 0, 0, 0, 2}, "All elements same except one");

    // Large array test
    vector<int> large(300, 2);
    for (int i = 0; i < 100; ++i)
        large[i] = 0;
    for (int i = 100; i < 200; ++i)
        large[i] = 1;
    // Shuffle the array
    random_device rd;
    mt19937 g(rd());
    shuffle(large.begin(), large.end(), g);

    vector<int> large_expected(100, 0);
    large_expected.insert(large_expected.end(), 100, 1);
    large_expected.insert(large_expected.end(), 100, 2);
    run_test(large, large_expected, "Large array (n=300, randomized)");
}

// Main function
int main()
{
    // Running the test cases
    test_cases();

    return 0;
}