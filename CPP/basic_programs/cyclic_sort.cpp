#include <iostream>
#include <vector>
using namespace std;

/*
-----------------------------------------------------
🌀 Cyclic Sort Algorithm
-----------------------------------------------------
📌 Description:
Cyclic Sort is an in-place algorithm used to sort an
array containing numbers in the range [1...n] (or [0...n-1])
without duplicates. The idea is to place each element
at its correct index (index = value - 1) by swapping
until the array is sorted.

📊 Complexity Analysis:
- Time Complexity: O(n)
  Each element is swapped at most once to its correct position.
- Space Complexity: O(1)
  No extra data structures are used, sorting is in-place.

✅ Applications:
- Sorting numbers in the range [1...n]
- Finding missing or duplicate numbers in arrays
- Common in coding interview problems
-----------------------------------------------------
*/

// Function to perform cyclic sort
void cyclicSort(vector<int>& nums) {
    int i = 0;
    int n = nums.size();
    while (i < n) {
        int correctIndex = nums[i] - 1; // correct index for current element

        // Swap only if element is in range and not at the right place
        if (nums[i] >= 1 && nums[i] <= n && nums[i] != nums[correctIndex]) {
            swap(nums[i], nums[correctIndex]);
        } else {
            i++; // move to next index if already in correct position
        }
    }
}

// Utility function to print array
void print(vector<int>& nums) {
    cout << "Sorted array is:" << endl;
    for (auto i : nums) {
        cout << i << " ";
    }
    cout << endl;
}

// Driver function
int main() {
    cout << "This is Cyclic Sort implementation." << endl;
    cout << "Cyclic Sort works efficiently when numbers are in the range [1...n] or [0...n-1] without duplicates." << endl;

    int n;
    cout << "Enter value of n: ";
    cin >> n;

    vector<int> nums(n, 0);
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cyclicSort(nums);
    print(nums);

    return 0;
}
