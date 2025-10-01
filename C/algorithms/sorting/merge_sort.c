/*
 * Algorithm: Merge Sort
 * Description: Divide-and-conquer sorting algorithm that divides array into halves,
 *              sorts them separately, and merges them back together
 * Time Complexity: O(n log n) for all cases
 * Space Complexity: O(n) for temporary arrays
 * Author: Abhijit
 * Date: October 2025
 * Hacktoberfest 2025
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Merges two subarrays of arr[]
 * First subarray is arr[left..mid]
 * Second subarray is arr[mid+1..right]
 */
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int *leftArray = (int*)malloc(n1 * sizeof(int));
    int *rightArray = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(leftArray);
    free(rightArray);
}

/**
 * Main function that sorts arr[left..right] using merge sort
 */
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point to divide the array into two halves
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

/**
 * Utility function to print array elements
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    // Prompt the user for the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input! Number of elements must be positive.\n");
        return 1;
    }

    int arr[n]; // Declare an array of size n

    // Read the elements from the user
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nOriginal array: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("Sorted array:   ");
    printArray(arr, n);

    printf("\nAlgorithm Information:\n");
    printf("- Time Complexity: O(n log n) for all cases\n");
    printf("- Space Complexity: O(n) for temporary arrays\n");
    printf("- Stable sorting algorithm\n");
    printf("- Divide-and-conquer approach\n");

    return 0;
}