/*
 * Algorithm: Heap Sort
 * Description: In-place comparison-based sorting algorithm using a binary heap (max-heap).
 * Time Complexity: O(n log n) for all cases
 * Space Complexity: O(1) auxiliary (in-place)
 * Author: rishanmenezes
 * Date: 2025-10-05
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Sifts an element down the heap to maintain max-heap property.
 * @param arr: Array representing the heap
 * @param n: Current heap size
 * @param i: Index to heapify at
 */
static void heapify(int arr[], int n, int i) {
    // Input validation: indexes within bounds
    if (arr == NULL || n <= 0 || i < 0 || i >= n) {
        return; // Nothing to do for invalid input
    }

    int largest = i;            // Assume current node is largest
    int left = 2 * i + 1;       // Left child
    int right = 2 * i + 2;      // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

/**
 * Builds a max-heap from an unsorted array in O(n) time.
 */
static void build_max_heap(int arr[], int n) {
    if (arr == NULL || n <= 1) return;

    // Start from last internal node and heapify downwards
    for (int i = (n / 2) - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
}

/**
 * Sorts the array in ascending order using heap sort.
 * @param arr: Array to sort (modified in place)
 * @param n: Number of elements in arr
 * @return: 0 on success, -1 for invalid input
 */
int heap_sort(int arr[], int n) {
    // Input validation
    if (arr == NULL || n < 0) {
        fprintf(stderr, "Error: Invalid input to heap_sort()\n");
        return -1;
    }
    if (n <= 1) {
        return 0; // Already sorted or nothing to do
    }

    // Step 1: Build max-heap
    build_max_heap(arr, n);

    // Step 2: Repeatedly extract the maximum to the end
    for (int end = n - 1; end > 0; --end) {
        // Move current root (max) to end
        int tmp = arr[0];
        arr[0] = arr[end];
        arr[end] = tmp;

        // Heapify reduced heap
        heapify(arr, end, 0);
    }

    return 0;
}

/* -------------------------- Test Utilities --------------------------- */

static void print_array(const char* label, const int arr[], int n) {
    printf("%s[", label);
    for (int i = 0; i < n; ++i) {
        printf("%d%s", arr[i], (i + 1 == n) ? "" : ", ");
    }
    printf("]\n");
}

static bool is_sorted_non_decreasing(const int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

static void run_test_case(const char* name, int input[], int n) {
    printf("\n== %s ==\n", name);
    print_array("Input: ", input, n);
    int rc = heap_sort(input, n);
    if (rc != 0) {
        printf("heap_sort returned error code %d\n", rc);
        return;
    }
    print_array("Sorted: ", input, n);
    printf("Correct: %s\n", is_sorted_non_decreasing(input, n) ? "true" : "false");
}

int main(void) {
    // Test 1: Typical unsorted array
    int a1[] = {64, 34, 25, 12, 22, 11, 90};
    run_test_case("Typical", a1, (int)(sizeof(a1) / sizeof(a1[0])));

    // Test 2: Already sorted array
    int a2[] = {1, 2, 3, 4, 5, 6};
    run_test_case("Already Sorted", a2, (int)(sizeof(a2) / sizeof(a2[0])));

    // Test 3: Reverse sorted array
    int a3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    run_test_case("Reverse Sorted", a3, (int)(sizeof(a3) / sizeof(a3[0])));

    // Test 4: Duplicates and negatives
    int a4[] = {5, -1, 3, 5, 2, 2, -3, 0};
    run_test_case("Duplicates & Negatives", a4, (int)(sizeof(a4) / sizeof(a4[0])));

    // Test 5: Single element
    int a5[] = {42};
    run_test_case("Single Element", a5, (int)(sizeof(a5) / sizeof(a5[0])));

    // Test 6: Empty array (n = 0) - should be a no-op
    int a6[] = {};
    run_test_case("Empty Array", a6, 0);

    return 0;
}
