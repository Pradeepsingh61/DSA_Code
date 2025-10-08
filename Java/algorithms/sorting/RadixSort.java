/**
 * Algorithm: Radix Sort
 * Description: Non-comparison based integer sorting algorithm that processes 
 *              digits from least significant to most significant digit using 
 *              counting sort as a subroutine. Works efficiently for integers
 *              and strings with fixed-length keys.
 * 
 * Time Complexity: O(d * (n + k)) where d = number of digits, n = array size, k = range of digits (0-9)
 * Space Complexity: O(n + k) for the counting array and output array
 * 
 * Advantages:
 * - Linear time complexity for fixed number of digits
 * - Stable sorting algorithm (maintains relative order of equal elements)
 * - Can be faster than comparison-based sorts for certain data types
 * 
 * Use Cases:
 * - Sorting integers with limited digit count
 * - Sorting strings with fixed length
 * - Parallel processing scenarios
 * - When comparison operations are expensive
 *
 * @author DSA_Code Contributors
 * @version 1.0
 * @since 2025-10-09
 */

import java.util.Arrays;

public class RadixSort {

    /**
     * Sorts an array of non-negative integers using Radix Sort algorithm.
     * Processes digits from least significant to most significant using counting sort.
     *
     * @param arr the array to be sorted (must contain non-negative integers)
     * @throws IllegalArgumentException if array is null or contains negative numbers
     */
    public static void radixSort(int[] arr) {
        // Input validation - check for null array
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        // Empty or single element arrays are already sorted
        if (arr.length <= 1) {
            return;
        }

        // Check for negative numbers - Radix sort handles only non-negative integers
        for (int num : arr) {
            if (num < 0) {
                throw new IllegalArgumentException(
                    "Radix sort only works with non-negative integers. Found: " + num
                );
            }
        }

        // Find the maximum number to determine number of digits to process
        int max = getMax(arr);

        // Perform counting sort for each digit position
        // Start from least significant digit (exp = 1) to most significant
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }

    /**
     * Finds the maximum element in the array.
     * Used to determine the number of digits to process in radix sort.
     *
     * @param arr the input array
     * @return the maximum element in the array
     */
    private static int getMax(int[] arr) {
        int max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    /**
     * Performs counting sort on array based on the digit at given position.
     * This is a stable sort, maintaining relative order of elements with same digit.
     *
     * @param arr the array to be sorted
     * @param exp the digit position (1 for units, 10 for tens, 100 for hundreds, etc.)
     */
    private static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n]; // Output array to store sorted elements
        int[] count = new int[10]; // Count array for digits 0-9

        // Initialize count array with zeros (though Java does this by default)
        Arrays.fill(count, 0);

        // Store count of occurrences of each digit
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        // Change count[i] to contain actual position of this digit in output array
        // This creates a cumulative count that represents the position
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array by placing elements in correct position
        // Process from right to left to maintain stability
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Copy the sorted elements back to original array
        System.arraycopy(output, 0, arr, 0, n);
    }

    /**
     * Prints an array with a label.
     *
     * @param label description of the array
     * @param arr the array to print
     */
    private static void printArray(String label, int[] arr) {
        System.out.print(label + ": ");
        System.out.println(Arrays.toString(arr));
    }

    /**
     * Verifies if an array is sorted in ascending order.
     *
     * @param arr the array to check
     * @return true if array is sorted, false otherwise
     */
    private static boolean isSorted(int[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Test cases demonstrating various scenarios for Radix Sort.
     */
    public static void main(String[] args) {
        System.out.println("=== Radix Sort Implementation ===\n");

        // Test Case 1: Standard unsorted array
        System.out.println("Test Case 1: Standard Array");
        int[] test1 = {170, 45, 75, 90, 802, 24, 2, 66};
        printArray("Original", test1);
        radixSort(test1);
        printArray("Sorted  ", test1);
        System.out.println("Is sorted: " + isSorted(test1));
        System.out.println();

        // Test Case 2: Already sorted array
        System.out.println("Test Case 2: Already Sorted Array");
        int[] test2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        printArray("Original", test2);
        radixSort(test2);
        printArray("Sorted  ", test2);
        System.out.println("Is sorted: " + isSorted(test2));
        System.out.println();

        // Test Case 3: Reverse sorted array
        System.out.println("Test Case 3: Reverse Sorted Array");
        int[] test3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        printArray("Original", test3);
        radixSort(test3);
        printArray("Sorted  ", test3);
        System.out.println("Is sorted: " + isSorted(test3));
        System.out.println();

        // Test Case 4: Array with duplicate values
        System.out.println("Test Case 4: Array with Duplicates");
        int[] test4 = {5, 2, 8, 2, 9, 1, 5, 5};
        printArray("Original", test4);
        radixSort(test4);
        printArray("Sorted  ", test4);
        System.out.println("Is sorted: " + isSorted(test4));
        System.out.println();

        // Test Case 5: Array with same elements
        System.out.println("Test Case 5: All Same Elements");
        int[] test5 = {7, 7, 7, 7, 7};
        printArray("Original", test5);
        radixSort(test5);
        printArray("Sorted  ", test5);
        System.out.println("Is sorted: " + isSorted(test5));
        System.out.println();

        // Test Case 6: Single element array
        System.out.println("Test Case 6: Single Element");
        int[] test6 = {42};
        printArray("Original", test6);
        radixSort(test6);
        printArray("Sorted  ", test6);
        System.out.println("Is sorted: " + isSorted(test6));
        System.out.println();

        // Test Case 7: Empty array
        System.out.println("Test Case 7: Empty Array");
        int[] test7 = {};
        printArray("Original", test7);
        radixSort(test7);
        printArray("Sorted  ", test7);
        System.out.println("Is sorted: " + (test7.length == 0 || isSorted(test7)));
        System.out.println();

        // Test Case 8: Large numbers with varying digit counts
        System.out.println("Test Case 8: Large Numbers");
        int[] test8 = {999, 1, 100, 50, 9999, 500, 10, 5000};
        printArray("Original", test8);
        radixSort(test8);
        printArray("Sorted  ", test8);
        System.out.println("Is sorted: " + isSorted(test8));
        System.out.println();

        // Test Case 9: Error handling - null array
        System.out.println("Test Case 9: Error Handling (Null Array)");
        try {
            radixSort(null);
            System.out.println("ERROR: Should have thrown exception!");
        } catch (IllegalArgumentException e) {
            System.out.println("Correctly caught exception: " + e.getMessage());
        }
        System.out.println();

        // Test Case 10: Error handling - negative numbers
        System.out.println("Test Case 10: Error Handling (Negative Numbers)");
        try {
            int[] test10 = {5, -3, 8, 2};
            radixSort(test10);
            System.out.println("ERROR: Should have thrown exception!");
        } catch (IllegalArgumentException e) {
            System.out.println("Correctly caught exception: " + e.getMessage());
        }
        System.out.println();

        System.out.println("=== All tests completed successfully! ===");
    }
}
