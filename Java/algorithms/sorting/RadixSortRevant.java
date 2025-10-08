
/*
 * Algorithm Name:
 * Radix Sort
 *
 * Programming Language:
 * Java
 *
 * Category:
 * Sorting
 *
 * Difficulty Level:
 * Medium
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> Radix Sort is a non-comparative sorting algorithm that sorts integers by processing digits
 *       from least significant digit (LSD) to most significant digit (MSD).
 *
 * 2. Approach / Idea:
 *    -> Find the maximum number to know the number of digits.
 *    -> Do counting sort for every digit, starting from least significant to most significant.
 *    -> Counting sort is used as a subroutine to sort elements based on the current digit.
 *
 * 3. Complexity:
 *    Time: O(d * (n + k)), where n = number of elements, k = range of digits (0-9), d = number of digits
 *    Space: O(n + k)
 *
 * Author:
 * Revant Singh
 */
// package DSA_Code.Java.algorithms.sorting;
import java.util.Arrays;
import java.util.Scanner;

public class RadixSortRevant {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.println("Enter elements: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.println("Original Array: " + Arrays.toString(arr));

        radixSort(arr);

        System.out.println("Sorted Array:   " + Arrays.toString(arr));
    }

    // Radix Sort function
    static void radixSort(int[] arr) {
        int max = getMax(arr);

        // Apply counting sort for each digit
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }

    // Get maximum value in the array
    static int getMax(int[] arr) {
        int max = arr[0];
        for (int num : arr) {
            if (num > max) max = num;
        }
        return max;
    }

    // Counting sort based on digit represented by exp
    static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n]; // output array
        int[] count = new int[10]; // count array for digits 0-9

        // Count occurrences of each digit
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        // Transform count[i] so that it contains actual position
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        // Copy output to original array
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}
