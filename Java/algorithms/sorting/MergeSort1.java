/**
 * Merge Sort Algorithm
 *
 * Description: Sorts an array using the divide-and-conquer approach. The array
 * is recursively divided into halves until each subarray has one element, then
 * merged in sorted order.
 *
 * Time Complexity: O(n log n) - array is split log n times, and each merge takes O(n)
 * Space Complexity: O(n) - uses additional arrays for merging
 */

import java.util.*;

class MergeSort1 {

    public static void main(String args[]) {
        int arr[] = {5, 4, 3, 2, 1};

        // Perform merge sort
        arr = mergeSort(arr);

        // Print sorted array
        System.out.println(Arrays.toString(arr));
    }

    /**
     * Recursively divides the array and sorts each half
     *
     * @param arr Array to be sorted
     * @return Sorted array
     */
    static int[] mergeSort(int arr[]) {
        if (arr.length == 1) {
            return arr; // Base case: single element is already sorted
        }

        int mid = arr.length / 2;

        // Recursively sort left and right halves
        int left[] = mergeSort(Arrays.copyOfRange(arr, 0, mid));
        int right[] = mergeSort(Arrays.copyOfRange(arr, mid, arr.length));

        // Merge sorted halves
        return merge(left, right);
    }

    /**
     * Merges two sorted arrays into a single sorted array
     *
     * @param first First sorted array
     * @param second Second sorted array
     * @return Merged sorted array
     */
    static int[] merge(int first[], int second[]) {
        int mix[] = new int[first.length + second.length];
        int i = 0, j = 0, k = 0;

        // Merge elements from both arrays in sorted order
        while (i < first.length && j < second.length) {
            if (first[i] < second[j]) {
                mix[k] = first[i];
                i++;
            } else {
                mix[k] = second[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements from first array
        while (i < first.length) {
            mix[k] = first[i];
            i++;
            k++;
        }

        // Copy remaining elements from second array
        while (j < second.length) {
            mix[k] = second[j];
            j++;
            k++;
        }

        return mix;
    }
}
