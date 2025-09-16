#include <iostream>
using namespace std;

// Function to perform Binary Search
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate mid index

        // Check if the target is at mid
        if (arr[mid] == target) {
            return mid; // Return the index if found
        }

        // If target is greater, ignore the left half
        if (arr[mid] < target) {
            left = mid + 1;
        } 
        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    return -1; // Return -1 if the target is not found
}

int main() {
    int arr[] = {9, 11, 21, 34, 45, 56, 78};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 56;

    // Call the binary search function
    int result = binarySearch(arr, size, target);

    // Output the result
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found!" << endl;
    }

    return 0;
}
