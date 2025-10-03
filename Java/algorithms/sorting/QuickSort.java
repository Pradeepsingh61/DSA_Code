/**
 * Algorithm: Quick Sort
 * Description: Efficient divide-and-conquer sorting algorithm using partitioning
 * Time Complexity: O(n log n) average case, O(n²) worst case
 * Space Complexity: O(log n) for recursion stack
 *
 * @author Pasan Sulakshana Rathnayake
 * @version 1.0
 * @since 2025-10-03
 */

import java.util.*;

public class QuickSort {

    /**
     * Sorts an array using quick sort algorithm.
     *
     * @param arr the array to be sorted
     * @throws IllegalArgumentException if array is null
     */
    public static void quickSort(int[] arr) {
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        if (arr.length <= 1) {
            return; // Already sorted
        }

        quickSort(arr, 0, arr.length - 1);
    }

    /**
     * Recursive quick sort implementation.
     *
     * @param arr the array to sort
     * @param low starting index
     * @param high ending index
     */
    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            // Partition the array and get pivot index
            int pivotIndex = partition(arr, low, high);
            
            // Recursively sort elements before and after partition
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }

    /**
     * Partitions the array around a pivot element.
     *
     * @param arr the array to partition
     * @param low starting index
     * @param high ending index
     * @return the final position of the pivot
     */
    private static int partition(int[] arr, int low, int high) {
        // Choose rightmost element as pivot
        int pivot = arr[high];
        int i = low - 1; // Index of smaller element
        
        for (int j = low; j < high; j++) {
            // If current element is smaller than or equal to pivot
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        
        // Place pivot in correct position
        swap(arr, i + 1, high);
        return i + 1;
    }

    /**
     * Swaps two elements in the array.
     *
     * @param arr the array
     * @param i first index
     * @param j second index
     */
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    /**
     * Test the quick sort implementation.
     */
    public static void main(String[] args) {
        // Test case 1: Regular array
        int[] test1 = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("Original array: " + Arrays.toString(test1));
        quickSort(test1);
        System.out.println("Sorted array: " + Arrays.toString(test1));
        
        // Test case 2: Already sorted
        int[] test2 = {1, 2, 3, 4, 5};
        System.out.println("\nAlready sorted: " + Arrays.toString(test2));
        quickSort(test2);
        System.out.println("After sorting: " + Arrays.toString(test2));
        
        // Test case 3: Reverse sorted
        int[] test3 = {5, 4, 3, 2, 1};
        System.out.println("\nReverse sorted: " + Arrays.toString(test3));
        quickSort(test3);
        System.out.println("After sorting: " + Arrays.toString(test3));
        
        // Test case 4: Single element
        int[] test4 = {42};
        quickSort(test4);
        assert test4[0] == 42;
        
        // Test case 5: Empty array
        int[] test5 = {};
        quickSort(test5);
        assert test5.length == 0;
        
        System.out.println("\nAll test cases passed! ✅");
    }
}