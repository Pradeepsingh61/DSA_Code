/*
Bubble Sort Algorithm

Description:
Bubble Sort is a simple comparison-based sorting algorithm.
It repeatedly steps through the array, compares adjacent elements,
and swaps them if they are in the wrong order. This process is repeated
until the array is completely sorted. The largest element "bubbles up"
to the end of the array with each pass.

Approach:
- Compare adjacent elements and swap if needed.
- After each iteration, the largest unsorted element is moved to its correct position.
- Repeat the process until no swaps are needed (optimized version).

Use Cases:
- Small datasets
- Educational purposes for learning sorting concepts

Time Complexity:
- Best Case: O(n) when the array is already sorted
- Average Case: O(n²)
- Worst Case: O(n²)
Reason: Two nested loops — outer loop runs n times, inner loop runs (n - i - 1) times.

Space Complexity:
- O(1): Uses only a few extra variables for swapping and flags.
*/

#include <stdio.h>

// Function prototypes
void inputArray(int arr[], int size);
void displayArray(int arr[], int size);
void bubbleSort(int arr[], int size);

int main() {
    int size;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int arr[size];

    // Input elements
    inputArray(arr, size);

    printf("\nOriginal array:\n");
    displayArray(arr, size);

    // Sort array
    bubbleSort(arr, size);

    printf("\nSorted array in ascending order:\n");
    displayArray(arr, size);

    // Example test cases (demonstration)
    // Input:  [5, 2, 9, 1, 5, 6]
    // Output: [1, 2, 5, 5, 6, 9]
    // Edge Case: Single element or already sorted array

    return 0;
}

// Reads 'size' number of elements into the array
void inputArray(int arr[], int size) {
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

// Displays the contents of the array
void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Performs Bubble Sort on the array
void bubbleSort(int arr[], int size) {
    int temp, swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = 0;

        // Compare adjacent elements
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // Optimization: Stop if no swaps occurred
        if (!swapped)
            break;
    }
}
