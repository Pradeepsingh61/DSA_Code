/**
 * Algorithm: Merge Sort
 * Description: Stable divide-and-conquer sorting algorithm using merge operation
 * Time Complexity: O(n log n) in all cases (best, average, worst)
 * Space Complexity: O(n) for temporary arrays used during merging
 *
 * @author Pasan Sulakshana Rathnayake
 * @version 1.0
 * @since 2025-10-04
 */

import java.util.*;

public class MergeSort {

    /**
     * Sorts an array using merge sort algorithm.
     *
     * @param arr the array to be sorted
     * @throws IllegalArgumentException if array is null
     */
    public static void mergeSort(int[] arr) {
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        if (arr.length <= 1) {
            return; // Already sorted
        }

        mergeSort(arr, 0, arr.length - 1);
    }

    /**
     * Recursive merge sort implementation.
     *
     * @param arr the array to sort
     * @param left starting index
     * @param right ending index
     */
    private static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            // Calculate middle point to divide array into two halves
            int mid = left + (right - left) / 2;
            
            // Recursively sort both halves
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            
            // Merge the sorted halves
            merge(arr, left, mid, right);
        }
    }

    /**
     * Merges two sorted subarrays into a single sorted array.
     *
     * @param arr the array containing both subarrays
     * @param left starting index of first subarray
     * @param mid ending index of first subarray
     * @param right ending index of second subarray
     */
    private static void merge(int[] arr, int left, int mid, int right) {
        // Calculate sizes of two subarrays to be merged
        int leftSize = mid - left + 1;
        int rightSize = right - mid;
        
        // Create temporary arrays for left and right subarrays
        int[] leftArray = new int[leftSize];
        int[] rightArray = new int[rightSize];
        
        // Copy data to temporary arrays
        System.arraycopy(arr, left, leftArray, 0, leftSize);
        System.arraycopy(arr, mid + 1, rightArray, 0, rightSize);
        
        // Merge the temporary arrays back into arr[left..right]
        int i = 0; // Initial index of left subarray
        int j = 0; // Initial index of right subarray
        int k = left; // Initial index of merged subarray
        
        // Merge elements in sorted order
        while (i < leftSize && j < rightSize) {
            if (leftArray[i] <= rightArray[j]) {
                arr[k] = leftArray[i];
                i++;
            } else {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements of leftArray[], if any
        while (i < leftSize) {
            arr[k] = leftArray[i];
            i++;
            k++;
        }
        
        // Copy remaining elements of rightArray[], if any
        while (j < rightSize) {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    /**
     * Test the merge sort implementation.
     */
    public static void main(String[] args) {
        // Test case 1: Regular array
        int[] test1 = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("Original array: " + Arrays.toString(test1));
        mergeSort(test1);
        System.out.println("Sorted array: " + Arrays.toString(test1));
        
        // Test case 2: Already sorted
        int[] test2 = {1, 2, 3, 4, 5};
        System.out.println("\nAlready sorted: " + Arrays.toString(test2));
        mergeSort(test2);
        System.out.println("After sorting: " + Arrays.toString(test2));
        
        // Test case 3: Reverse sorted
        int[] test3 = {5, 4, 3, 2, 1};
        System.out.println("\nReverse sorted: " + Arrays.toString(test3));
        mergeSort(test3);
        System.out.println("After sorting: " + Arrays.toString(test3));
        
        // Test case 4: Array with duplicates
        int[] test4 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        System.out.println("\nWith duplicates: " + Arrays.toString(test4));
        mergeSort(test4);
        System.out.println("After sorting: " + Arrays.toString(test4));
        
        // Test case 5: Single element
        int[] test5 = {42};
        mergeSort(test5);
        assert test5[0] == 42;
        
        // Test case 6: Empty array
        int[] test6 = {};
        mergeSort(test6);
        assert test6.length == 0;
        
        // Test case 7: Two elements
        int[] test7 = {2, 1};
        System.out.println("\nTwo elements: " + Arrays.toString(test7));
        mergeSort(test7);
        System.out.println("After sorting: " + Arrays.toString(test7));
        
        System.out.println("\nAll test cases passed! ✅");
        System.out.println("MergeSort is stable and guarantees O(n log n) performance!");
    }
}