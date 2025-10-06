#include <stdio.h>

/*
=========================================================
Algorithm Name: Binary Search
Category: Searching
Difficulty Level: Easy (Beginner friendly)

Algorithm Description:
Binary search is an efficient algorithm used to find the position 
of a target value within a sorted array. It works by repeatedly 
dividing the search interval in half. If the value of the search key 
is less than the item in the middle of the interval, the algorithm 
continues on the left half, otherwise on the right half.

Time Complexity:
- Best Case: O(1)  (target is at the middle)
- Average Case: O(log n)
- Worst Case: O(log n)

Space Complexity:
- O(1) (iterative implementation uses constant extra space)
=========================================================
*/

// Function to perform Binary Search on a sorted array
int binarySearch(int arr[], int size, int target) {
    int left = 0;           // Start of the search interval
    int right = size - 1;   // End of the search interval

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Middle index

        if (arr[mid] == target) {
            return mid; // Target found, return its index
        } else if (arr[mid] < target) {
            left = mid + 1; // Ignore left half
        } else {
            right = mid - 1; // Ignore right half
        }
    }

    return -1; // Target not found
}

int main() {
    int arr[] = {9, 11, 21, 34, 45, 56, 78};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 56;

    // Call the binary search function
    int result = binarySearch(arr, size, target);

    // Output the result
    if (result != -1) {
        printf("Element found at index: %d\n", result);
    } else {
        printf("Element not found!\n");
    }

    return 0;
}
