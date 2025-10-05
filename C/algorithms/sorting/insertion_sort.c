/*
 * Algorithm Name:
 * Insertion Sort
 *
 * Programming Language:
 * C
 *
 * Category:
 * Sorting
 *
 * Difficulty Level:
 * Easy to Medium
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> Insertion Sort builds the final sorted array one element at a time by
 *       repeatedly taking elements from the unsorted portion and inserting them
 *       into their correct position in the sorted portion.
 *
 * 2. Approach / Idea:
 *    -> Start with the second element (index 1) as the first element is trivially sorted
 *    -> For each element, compare it with elements in the sorted portion (to its left)
 *    -> Shift larger elements to the right to make space
 *    -> Insert the current element in its correct position
 *    -> Repeat until all elements are processed
 *
 * 3. Complexity:
 *    Time: O(n²) worst case, O(n) best case (already sorted), O(n²) average case
 *    Space: O(1) - in-place sorting algorithm
 *
 * 4. Characteristics:
 *    -> Stable: Equal elements maintain their relative order
 *    -> In-place: Requires only O(1) extra memory
 *    -> Adaptive: Efficient for data sets that are already substantially sorted
 *    -> Online: Can sort a list as it receives it
 *
 * 5. Variants Implemented:
 *    -> Standard Insertion Sort
 *    -> Binary Insertion Sort (uses binary search for position finding)
 *    -> Recursive Insertion Sort
 *    -> Insertion Sort with Sentinel (optimization)
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes
void insertionSort(int arr[], int n);
void binaryInsertionSort(int arr[], int n);
void recursiveInsertionSort(int arr[], int n);
void sentinelInsertionSort(int arr[], int n);
int binarySearch(int arr[], int val, int start, int end);
void printArray(int arr[], int n, const char* label);
void copyArray(int source[], int dest[], int n);
double measureTime(void (*sortFunc)(int[], int), int arr[], int n);
void generateTestData(int arr[], int n, int type);

int main() {
    int choice, n, dataType;
    
    printf("=== Insertion Sort Algorithm Variants Demo ===\n\n");
    
    // Get array size
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }
    
    int *original = (int*)malloc(n * sizeof(int));
    int *arr1 = (int*)malloc(n * sizeof(int));
    int *arr2 = (int*)malloc(n * sizeof(int));
    int *arr3 = (int*)malloc(n * sizeof(int));
    int *arr4 = (int*)malloc(n * sizeof(int));
    
    if (!original || !arr1 || !arr2 || !arr3 || !arr4) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Choose data input method
    printf("\nChoose input method:\n");
    printf("1. Manual input\n");
    printf("2. Random data\n");
    printf("3. Nearly sorted data\n");
    printf("4. Reverse sorted data\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &dataType);
    
    if (dataType == 1) {
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &original[i]);
        }
    } else {
        generateTestData(original, n, dataType);
    }
    
    printf("\nOriginal Array: ");
    printArray(original, n, "");
    
    // Choose sorting variant
    printf("\nChoose Insertion Sort variant:\n");
    printf("1. Standard Insertion Sort\n");
    printf("2. Binary Insertion Sort\n");
    printf("3. Recursive Insertion Sort\n");
    printf("4. Sentinel Insertion Sort\n");
    printf("5. Compare All Variants\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);
    
    printf("\n=== Results ===\n");
    
    switch (choice) {
        case 1: {
            copyArray(original, arr1, n);
            double time = measureTime(insertionSort, arr1, n);
            printArray(arr1, n, "Standard Insertion Sort");
            printf("Time taken: %.6f seconds\n", time);
            break;
        }
        
        case 2: {
            copyArray(original, arr2, n);
            double time = measureTime(binaryInsertionSort, arr2, n);
            printArray(arr2, n, "Binary Insertion Sort");
            printf("Time taken: %.6f seconds\n", time);
            break;
        }
        
        case 3: {
            copyArray(original, arr3, n);
            clock_t start = clock();
            recursiveInsertionSort(arr3, n);
            clock_t end = clock();
            double time = ((double)(end - start)) / CLOCKS_PER_SEC;
            printArray(arr3, n, "Recursive Insertion Sort");
            printf("Time taken: %.6f seconds\n", time);
            break;
        }
        
        case 4: {
            copyArray(original, arr4, n);
            double time = measureTime(sentinelInsertionSort, arr4, n);
            printArray(arr4, n, "Sentinel Insertion Sort");
            printf("Time taken: %.6f seconds\n", time);
            break;
        }
        
        case 5: {
            printf("Comparing all variants:\n\n");
            
            copyArray(original, arr1, n);
            double time1 = measureTime(insertionSort, arr1, n);
            printf("1. Standard Insertion Sort: %.6f seconds\n", time1);
            
            copyArray(original, arr2, n);
            double time2 = measureTime(binaryInsertionSort, arr2, n);
            printf("2. Binary Insertion Sort: %.6f seconds\n", time2);
            
            copyArray(original, arr3, n);
            clock_t start = clock();
            recursiveInsertionSort(arr3, n);
            clock_t end = clock();
            double time3 = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("3. Recursive Insertion Sort: %.6f seconds\n", time3);
            
            copyArray(original, arr4, n);
            double time4 = measureTime(sentinelInsertionSort, arr4, n);
            printf("4. Sentinel Insertion Sort: %.6f seconds\n", time4);
            
            printf("\nFinal sorted array: ");
            printArray(arr1, n, "");
            break;
        }
        
        default:
            printf("Invalid choice!\n");
            free(original); free(arr1); free(arr2); free(arr3); free(arr4);
            return 1;
    }
    
    // Cleanup
    free(original);
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    
    return 0;
}

/**
 * Standard Insertion Sort
 * Classic implementation that shifts elements one by one
 * 
 * @param arr: Array to be sorted
 * @param n: Size of the array
 */
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert key at its correct position
        arr[j + 1] = key;
    }
}

/**
 * Binary Insertion Sort
 * Uses binary search to find the correct position for insertion
 * Reduces comparisons from O(n) to O(log n) per element
 * 
 * @param arr: Array to be sorted
 * @param n: Size of the array
 */
void binaryInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Find location to insert using binary search
        int loc = binarySearch(arr, key, 0, j);
        
        // Shift elements to make space
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert key at found location
        arr[j + 1] = key;
    }
}

/**
 * Recursive Insertion Sort
 * Implements insertion sort using recursion
 * 
 * @param arr: Array to be sorted
 * @param n: Size of the array (number of elements to sort)
 */
void recursiveInsertionSort(int arr[], int n) {
    // Base case: if array has 1 or no elements
    if (n <= 1) {
        return;
    }
    
    // Sort first n-1 elements
    recursiveInsertionSort(arr, n - 1);
    
    // Insert the nth element at its correct position
    int last = arr[n - 1];
    int j = n - 2;
    
    // Move elements greater than last to one position ahead
    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    
    // Insert last element at its correct position
    arr[j + 1] = last;
}

/**
 * Sentinel Insertion Sort
 * Optimization that eliminates the boundary check in the inner loop
 * Places the minimum element at the beginning as a sentinel
 * 
 * @param arr: Array to be sorted
 * @param n: Size of the array
 */
void sentinelInsertionSort(int arr[], int n) {
    if (n <= 1) return;
    
    // Find minimum element and place it at the beginning
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) {
            minIdx = i;
        }
    }
    
    // Swap minimum element with first element
    if (minIdx != 0) {
        int temp = arr[0];
        arr[0] = arr[minIdx];
        arr[minIdx] = temp;
    }
    
    // Now perform insertion sort without boundary check
    for (int i = 2; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // No need to check j >= 0 because arr[0] is the minimum
        while (arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

/**
 * Binary Search for finding insertion position
 * Finds the correct position to insert val in sorted array arr[start...end]
 * 
 * @param arr: Sorted array
 * @param val: Value to be inserted
 * @param start: Starting index
 * @param end: Ending index
 * @return: Position where val should be inserted
 */
int binarySearch(int arr[], int val, int start, int end) {
    if (start == end) {
        return (arr[start] > val) ? start : start + 1;
    }
    
    if (start > end) {
        return start;
    }
    
    int mid = (start + end) / 2;
    
    if (arr[mid] < val) {
        return binarySearch(arr, val, mid + 1, end);
    } else if (arr[mid] > val) {
        return binarySearch(arr, val, start, mid - 1);
    } else {
        return mid;
    }
}

/**
 * Utility function to print array elements
 * 
 * @param arr: Array to print
 * @param n: Size of the array
 * @param label: Label to print before array
 */
void printArray(int arr[], int n, const char* label) {
    if (strlen(label) > 0) {
        printf("%s: ", label);
    }
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * Copy array elements from source to destination
 * 
 * @param source: Source array
 * @param dest: Destination array
 * @param n: Number of elements to copy
 */
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

/**
 * Measure execution time of a sorting function
 * 
 * @param sortFunc: Pointer to sorting function
 * @param arr: Array to be sorted
 * @param n: Size of the array
 * @return: Time taken in seconds
 */
double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/**
 * Generate test data based on type
 * 
 * @param arr: Array to fill with test data
 * @param n: Size of the array
 * @param type: Type of data (2=random, 3=nearly sorted, 4=reverse sorted)
 */
void generateTestData(int arr[], int n, int type) {
    srand(time(NULL));
    
    switch (type) {
        case 2: // Random data
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 1000;
            }
            break;
            
        case 3: // Nearly sorted data
            for (int i = 0; i < n; i++) {
                arr[i] = i + (rand() % 3 - 1); // Add small random variation
            }
            break;
            
        case 4: // Reverse sorted data
            for (int i = 0; i < n; i++) {
                arr[i] = n - i;
            }
            break;
    }
}
