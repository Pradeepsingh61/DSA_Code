/*
File path (suggested): algorithms/sorting/RadixSort.java
(If you want to use a package, uncomment the package line below and place the file accordingly)
*/
// package algorithms.sorting;

import java.util.Arrays;

/**
 * Algorithm Name : Radix Sort
 * Programming Language: Java
 * Category: Sorting
 * Difficulty Level: Medium (Intermediate)
 *
 * Problem Statement:
 * Implement Radix Sort (LSD - least significant digit first) to sort an array
 * of non-negative integers. Use Counting Sort as a stable subroutine to sort
 * based on individual digit positions.
 *
 * Requirements:
 * - Input: array of non-negative integers
 * - Output: sorted array in ascending order
 *
 * Complexities:
 * - Time Complexity (Worst/Best/Average): O(d * (n + b))
 *     where d = number of digits in the maximum element,
 *           n = number of elements,
 *           b = base (10 for decimal)
 * - Space Complexity: O(n + b)
 *
 * Notes:
 * - This implementation assumes non-negative integers. To handle negative numbers,
 *   separate negatives and positives, radix-sort their absolute values, then merge.
 */
public class RadixSort {

    /**
     * Utility to get maximum value in arr[] — used to determine how many digits.
     */
    private static int getMax(int[] arr) {
        if (arr == null || arr.length == 0) return 0;
        int max = arr[0];
        for (int v : arr) {
            if (v > max) max = v;
        }
        return max;
    }

    /**
     * A stable Counting Sort that sorts arr[] according to the digit represented by exp.
     * exp = 1  -> sort by 1's digit
     * exp = 10 -> sort by 10's digit
     * exp = 100 -> sort by 100's digit, etc.
     *
     * Complexity of this subroutine: O(n + b) where b = 10 (digits 0..9)
     */
    private static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        if (n == 0) return;

        int[] output = new int[n];   // output array to store sorted order by current digit
        int[] count = new int[10];   // count array for digits 0..9 (base 10)

        // 1) Count occurrences of each digit in the given exp place
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        // 2) Convert count[] so that it contains actual positions (prefix sums)
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // 3) Build the output array from right to left to maintain stability
        //    (stable because elements with same digit appear in original relative order)
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            int pos = count[digit] - 1;   // index in output[]
            output[pos] = arr[i];
            count[digit]--;               // decrease count for this digit
        }

        // 4) Copy the output array back to arr[], so arr[] now contains numbers
        //    sorted by current digit (exp)
        System.arraycopy(output, 0, arr, 0, n);
    }

    /**
     * Main Radix Sort routine — sorts the array using digit-by-digit counting sort.
     */
    public static void radixSort(int[] arr) {
        if (arr == null || arr.length <= 1) return; // already sorted or nothing to do

        // Find the maximum number to know the number of digits
        int max = getMax(arr);

        // Do counting sort for every digit. Note that instead of passing the digit number,
        // exp is passed. exp is 10^i where i is current digit number (0 -> LSD).
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }

    /** Utility to print array in a readable form. */
    private static void printArray(String label, int[] arr) {
        System.out.println(label + Arrays.toString(arr));
    }

    /** Sample test cases covering: small arrays, repeated numbers, single-element array */
    public static void main(String[] args) {
        // Test case 1: Small array (classic example)
        int[] arr1 = {170, 45, 75, 90, 802, 24, 2, 66};
        printArray("Original arr1: ", arr1);
        radixSort(arr1);
        printArray("Sorted   arr1: ", arr1);
        System.out.println();

        // Test case 2: Array with repeated numbers
        int[] arr2 = {5, 3, 5, 2, 8, 5, 3};
        printArray("Original arr2: ", arr2);
        radixSort(arr2);
        printArray("Sorted   arr2: ", arr2);
        System.out.println();

        // Test case 3: Single-element array
        int[] arr3 = {42};
        printArray("Original arr3: ", arr3);
        radixSort(arr3);
        printArray("Sorted   arr3: ", arr3);
        System.out.println();

        // Optional: Empty array test
        int[] arr4 = {};
        printArray("Original arr4: ", arr4);
        radixSort(arr4);
        printArray("Sorted   arr4: ", arr4);
    }
}
