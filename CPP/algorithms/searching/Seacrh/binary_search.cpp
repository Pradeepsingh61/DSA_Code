#include <stdio.h>

/*
======================================================
Binary Search Algorithm
======================================================
Description:
Binary Search is an efficient algorithm to find the position of a target value
in a sorted array. It repeatedly divides the search interval in half. 

Key Idea:
1. Start with the entire array as the search interval.
2. Find the middle element.
3. If the middle element is equal to the target, return its index.
4. If the target is smaller, search the left half.
5. If the target is larger, search the right half.
6. Repeat until the target is found or interval is empty.

Time Complexity: O(log n)
Space Complexity: O(1) for iterative implementation
======================================================
*/

// Iterative Binary Search function
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // prevents overflow

        if (arr[mid] == target) {
            return mid; // Target found
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Search in right half
        }
        else {
            right = mid - 1; // Search in left half
        }
    }

    return -1; // Target not found
}

int main() {
    int n, target;

    // Input the size of the array
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements in sorted order: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Input the target value
    printf("Enter the target value: ");
    scanf("%d", &target);

    // Call Binary Search
    int result = binarySearch(arr, n, target);

    if (result != -1) {
        printf("Target %d found at index %d.\n", target, result);
    } else {
        printf("Target %d not found in the array.\n", target);
    }

    return 0;
}
