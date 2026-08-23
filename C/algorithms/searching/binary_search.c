 /*
 * Algorithm: Binary Search (Iterative and Recursive)
 * Description: An efficient algorithm used to find the position of a target value within a sorted array.
 * Time Complexity: O(log n)
 * Space Complexity: O(1) for Iterative, O(log n) for Recursive stack space
 * Author: ADIL AHMED
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Performs iterative binary search on a sorted array
 *
 * @param arr: Sorted array to process
 * @param size: Size of the array
 * @param target: Element to search for
 * @return: Index of target element if found, otherwise -1
 */
int Binary_search_iterative(int arr[], int size, int target) {
    // Input validation
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

/**
 * Performs recursive binary search helper on a sorted array
 *
 * @param arr: Sorted array to process
 * @param target: Element to search for
 * @param low: Lower bound index
 * @param high: Upper bound index
 * @return: Index of target element if found, otherwise -1
 */
int Binary_search_recursive(int arr[], int target, int low, int high) {
    if (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) return Binary_search_recursive(arr, target, low, mid - 1);
        else return Binary_search_recursive(arr, target, mid + 1, high);
    }
    return -1;
}


/**
 * Test function to demonstrate the algorithm
 */
void test_algorithm() {
    printf("Testing Algorithm...\n");

    // Test Case 1: Normal case
    int test_arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(test_arr1) / sizeof(test_arr1[0]);
    int target1=4;
    int result1 = Binary_search_iterative(test_arr1, size1,target1);
    printf("Test 1 - Input: {1,2,3,4,5}, Result: %d\n", result1);
    
    int result2 = Binary_search_recursive(test_arr1,target1,0,size1-1);
    printf("Test 1 - Input: {1,2,3,4,5}, Result: %d\n", result2);

    // Test Case 2: Edge case
    int *test_arr2 = NULL;
    int result3 = Binary_search_iterative(test_arr2, 0,target1);
    printf("Test 2 - Edge case handled: %d\n", result3);
}

int main() {
    test_algorithm();
    return 0;
}
