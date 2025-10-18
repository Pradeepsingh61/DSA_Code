/*
 * Algorithm Name:
 * Linear Search (Sequential Search)
 *
 * Programming Language:
 * C
 *
 * Category:
 * Searching
 *
 * Difficulty Level:
 * Easy
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> Linear Search finds the position of a target element in an array by checking
 *       each element sequentially from the beginning until the target is found or
 *       the end of the array is reached.
 *
 * 2. Approach / Idea:
 *    -> Start from the first element of the array
 *    -> Compare each element with the target value
 *    -> If match found, return the index
 *    -> If end of array reached without finding target, return -1
 *    -> Works on both sorted and unsorted arrays
 *
 * 3. Complexity:
 *    Time: O(n) - worst case when element is at end or not present
 *    Space: O(1) - constant extra space
 *
 * 4. Variants Implemented:
 *    -> Basic Linear Search
 *    -> Linear Search with All Occurrences
 *    -> Recursive Linear Search
 *    -> Linear Search from End (Reverse)
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int linearSearch(int arr[], int n, int target);
int* linearSearchAllOccurrences(int arr[], int n, int target, int* count);
int linearSearchRecursive(int arr[], int n, int target, int index);
int linearSearchReverse(int arr[], int n, int target);
void printArray(int arr[], int n);

int main() {
    int choice, n, target, result;
    
    printf("=== Linear Search Algorithm Demo ===\n\n");
    
    // Get array size
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }
    
    int arr[n];
    
    // Input array elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("\nArray: ");
    printArray(arr, n);
    
    printf("\nEnter the element to search: ");
    scanf("%d", &target);
    
    // Menu for different search variants
    printf("\nChoose search variant:\n");
    printf("1. Basic Linear Search\n");
    printf("2. Find All Occurrences\n");
    printf("3. Recursive Linear Search\n");
    printf("4. Reverse Linear Search\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    
    printf("\n=== Results ===\n");
    
    switch (choice) {
        case 1: {
            result = linearSearch(arr, n, target);
            if (result != -1) {
                printf("Element %d found at index %d (position %d)\n", target, result, result + 1);
            } else {
                printf("Element %d not found in the array\n", target);
            }
            break;
        }
        
        case 2: {
            int count = 0;
            int* indices = linearSearchAllOccurrences(arr, n, target, &count);
            
            if (count > 0) {
                printf("Element %d found %d time(s) at indices: ", target, count);
                for (int i = 0; i < count; i++) {
                    printf("%d", indices[i]);
                    if (i < count - 1) printf(", ");
                }
                printf("\n");
                free(indices);
            } else {
                printf("Element %d not found in the array\n", target);
            }
            break;
        }
        
        case 3: {
            result = linearSearchRecursive(arr, n, target, 0);
            if (result != -1) {
                printf("Element %d found at index %d (position %d) using recursion\n", target, result, result + 1);
            } else {
                printf("Element %d not found in the array using recursion\n", target);
            }
            break;
        }
        
        case 4: {
            result = linearSearchReverse(arr, n, target);
            if (result != -1) {
                printf("Element %d found at index %d (position %d) searching from end\n", target, result, result + 1);
            } else {
                printf("Element %d not found in the array searching from end\n", target);
            }
            break;
        }
        
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    return 0;
}

/**
 * Basic Linear Search
 * Searches for target element from beginning to end
 * 
 * @param arr: Array to search in
 * @param n: Size of the array
 * @param target: Element to search for
 * @return: Index of element if found, -1 otherwise
 */
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Return index where element is found
        }
    }
    return -1;  // Element not found
}

/**
 * Linear Search - Find All Occurrences
 * Finds all positions where target element appears
 * 
 * @param arr: Array to search in
 * @param n: Size of the array
 * @param target: Element to search for
 * @param count: Pointer to store number of occurrences found
 * @return: Dynamically allocated array of indices where element is found
 */
int* linearSearchAllOccurrences(int arr[], int n, int target, int* count) {
    int* indices = (int*)malloc(n * sizeof(int));  // Worst case: all elements match
    *count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            indices[*count] = i;
            (*count)++;
        }
    }
    
    if (*count == 0) {
        free(indices);
        return NULL;
    }
    
    // Resize array to actual count to save memory
    indices = (int*)realloc(indices, (*count) * sizeof(int));
    return indices;
}

/**
 * Recursive Linear Search
 * Implements linear search using recursion
 * 
 * @param arr: Array to search in
 * @param n: Size of the array
 * @param target: Element to search for
 * @param index: Current index being checked (starts from 0)
 * @return: Index of element if found, -1 otherwise
 */
int linearSearchRecursive(int arr[], int n, int target, int index) {
    // Base case: reached end of array
    if (index >= n) {
        return -1;
    }
    
    // Base case: element found
    if (arr[index] == target) {
        return index;
    }
    
    // Recursive case: search in remaining array
    return linearSearchRecursive(arr, n, target, index + 1);
}

/**
 * Reverse Linear Search
 * Searches for target element from end to beginning
 * Useful when target is more likely to be at the end
 * 
 * @param arr: Array to search in
 * @param n: Size of the array
 * @param target: Element to search for
 * @return: Index of element if found, -1 otherwise
 */
int linearSearchReverse(int arr[], int n, int target) {
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == target) {
            return i;  // Return index where element is found
        }
    }
    return -1;  // Element not found
}

/**
 * Utility function to print array elements
 * 
 * @param arr: Array to print
 * @param n: Size of the array
 */
void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
