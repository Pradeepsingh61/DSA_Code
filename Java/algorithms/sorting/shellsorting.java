/*
📘 Shell Sort Algorithm

✍️ Description:
Shell Sort is an optimization over Insertion Sort that allows the exchange of far-apart elements.
It works by sorting elements that are a certain 'gap' apart, reducing the gap in each iteration until it becomes 1.
At that point, the algorithm becomes a regular Insertion Sort, but since the array is already mostly sorted,
it performs much faster.

💡 Use Cases / Applications:
- Useful for medium-sized datasets
- Works well when memory is limited (in-place sorting)
- Suitable when a simple but efficient improvement over insertion sort is needed

📊 Complexity Analysis:
Time Complexity:
    • Best Case: O(n log n)
    • Average Case: O(n^(3/2))
    • Worst Case: O(n²)
Space Complexity: O(1)
    • Only a few temporary variables are used — no extra data structures.

*/

#include <iostream>
#include <vector>
using namespace std;

/*
🔹 Function: shellSort
🔹 Parameters:
    arr — reference to the vector of integers to be sorted
🔹 Description:
    Performs Shell Sort on the input array.
*/
void shellSort(vector<int> &arr) {
    int n = arr.size();

    // Start with a large gap and reduce it each iteration
    for (int gap = n / 2; gap > 0; gap /= 2) {

        // Perform a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements until correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap]; // Move element ahead by gap
            }

            arr[j] = temp; // Insert temp at correct position
        }
    }
}

/*
✅ Test Cases / Examples
Demonstrates sorting functionality on multiple inputs
*/
int main() {
    // Example 1: Random elements
    vector<int> arr1 = {12, 34, 54, 2, 3};
    shellSort(arr1);
    cout << "Sorted Array 1: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // Example 2: Already sorted array
    vector<int> arr2 = {1, 2, 3, 4, 5};
    shellSort(arr2);
    cout << "Sorted Array 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // Example 3: Reverse order
    vector<int> arr3 = {9, 8, 7, 6, 5};
    shellSort(arr3);
    cout << "Sorted Array 3: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;

    // Example 4: Single element (edge case)
    vector<int> arr4 = {42};
    shellSort(arr4);
    cout << "Sorted Array 4: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;

    return 0;
}
