/**
 * Shell_Sort.cpp
 *
 * Shell Sort Algorithm
 *
 * Description:
 *  Shell Sort is an in-place comparison sort which generalizes insertion sort
 *  by allowing exchanges of elements that are far apart. The idea is to
 *  arrange the list of elements so that, starting anywhere, taking every h-th
 *  element (for some gap h) yields a sorted list. Such a list is said to be
 *  h-sorted. By h-sorting the list for a decreasing sequence of gaps (ending
 *  with 1), the array gets closer to fully sorted and the final insertion sort
 *  (gap = 1) is fast because the array is already mostly sorted.
 *
 * Approach / Methodology:
 *  - Use a sequence of gaps (here the simple sequence gap = n/2, gap /= 2).
 *  - For each gap, perform a "gapped insertion sort": treat each subarray formed
 *    by elements at indices i, i+gap, i+2*gap, ... as an insertion-sorted list.
 *  - Reduce the gap until it becomes 1 (a normal insertion sort finishes the job).
 *
 * Use cases:
 *  - Good for medium-sized arrays.
 *  - Often used as an educational example of diminishing increment sorting.
 *  - Faster than plain insertion sort for arrays that are not too large and/or
 *    partially sorted.
 *
 * Complexity Analysis:
 *  - Time complexity:
 *      * Depends strongly on the gap sequence.
 *      * With the simple gap sequence (gap = n/2, gap /= 2) the worst-case
 *        time complexity can be O(n^2).
 *      * With better gap sequences (e.g., Knuth, Tokuda) practical performance
 *        is considerably improved.
 *  - Space complexity: O(1) (in-place sorting, only a few extra variables).
 *
 * Notes:
 *  - This implementation uses the simple gap sequence (n/2, n/4, ..., 1).
 *  - For production or performance-sensitive code, consider using a better gap
 *    sequence (Knuth's sequence: gap = gap*3 + 1).
 *
 * Author: Shubham Khetan (https://github.com/Shubham-Khetan-2005)
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * shellSort
 * -----------
 * Sorts the vector `arr` in ascending order using Shell Sort.
 *
 * Parameters:
 *  - arr : reference to a vector<int> that will be sorted in-place.
 *
 * Returns:
 *  - void (the input vector is modified directly)
 */
void shellSort(vector<int> &arr) {
    int n = static_cast<int>(arr.size());

    // Start with a big gap, then reduce the gap
    // Here gap sequence: n/2, n/4, ..., 1 (Shell's original sequence)
    for (int gap = n / 2; gap > 0; gap /= 2) {

        // Perform a gapped insertion sort for this gap size.
        // The elements arr[i], arr[i-gap], arr[i-2*gap], ... are compared and shifted.
        for (int i = gap; i < n; ++i) {
            int temp = arr[i]; // Element to be inserted in the sorted subarray
            int j = i;

            // Shift earlier gap-sorted elements up until the correct location for temp is found
            // We compare arr[j - gap] with temp and shift arr[j - gap] to arr[j] if it's greater.
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            // Place temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

/* Utility function to print a vector nicely */
void printVector(const vector<int> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

/* Test harness that demonstrates the algorithm with multiple test cases */
void run_tests() {
    cout << "Shell Sort - Demo Test Cases\n\n";

    // Test case 1: random numbers
    vector<int> t1 = {12, 34, 54, 2, 3, 7};
    cout << "Test 1 (random):\nBefore: ";
    printVector(t1);
    shellSort(t1);
    cout << "After : ";
    printVector(t1);
    cout << "Expected: 2 3 7 12 34 54\n\n";

    // Test case 2: already sorted (best case for insertion-like sorts)
    vector<int> t2 = {1, 2, 3, 4, 5, 6};
    cout << "Test 2 (already sorted):\nBefore: ";
    printVector(t2);
    shellSort(t2);
    cout << "After : ";
    printVector(t2);
    cout << "Expected: 1 2 3 4 5 6\n\n";

    // Test case 3: reverse sorted (worst-ish case)
    vector<int> t3 = {9, 8, 7, 6, 5, 4, 3};
    cout << "Test 3 (reverse sorted):\nBefore: ";
    printVector(t3);
    shellSort(t3);
    cout << "After : ";
    printVector(t3);
    cout << "Expected: 3 4 5 6 7 8 9\n\n";

    // Test case 4: contains duplicates
    vector<int> t4 = {5, 3, 8, 5, 2, 9, 5};
    cout << "Test 4 (duplicates):\nBefore: ";
    printVector(t4);
    shellSort(t4);
    cout << "After : ";
    printVector(t4);
    cout << "Expected: 2 3 5 5 5 8 9\n\n";

    // Test case 5: edge cases - empty and single-element arrays
    vector<int> t5 = {};
    vector<int> t6 = {42};
    cout << "Test 5 (empty):\nBefore: ";
    printVector(t5);
    shellSort(t5);
    cout << "After : ";
    printVector(t5);
    cout << "Expected: (empty line)\n\n";

    cout << "Test 6 (single element):\nBefore: ";
    printVector(t6);
    shellSort(t6);
    cout << "After : ";
    printVector(t6);
    cout << "Expected: 42\n\n";

    cout << "All demo tests finished.\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // NOTE:
    // This file includes a demonstration test harness (`run_tests()`).
    // If you want to use this program to sort custom input, comment out run_tests()
    // and uncomment the interactive input block below.

    run_tests();

    /* Interactive / competitive programming style input:
     * Uncomment this block to enable stdin-based input:
     *
     * Example input:
     * 6
     * 12 34 54 2 3 7
     *
     * Expected output:
     * 2 3 7 12 34 54
     */

    /*
    int n;
    if (!(cin >> n)) return 0; // read n; exit if no input provided
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    shellSort(arr);

    for (int x : arr) cout << x << ' ';
    cout << '\n';
    */

    return 0;
}
