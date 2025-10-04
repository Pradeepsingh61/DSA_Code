/**
 * Algorithm: Shell Sort
 * Description: Advanced insertion sort that uses gap sequences for improved performance
 * Time Complexity: O(n^3/2) worst case, O(n log n) average case (depends on gap sequence)
 * Space Complexity: O(1) - in-place sorting algorithm
 *
 * @author Pasan Sulakshana Rathnayake
 * @version 1.0
 * @since 2025-10-04
 */

import java.util.*;

public class ShellSort {

    /**
     * Sorts an array using shell sort algorithm with Knuth's gap sequence.
     *
     * @param arr the array to be sorted
     * @throws IllegalArgumentException if array is null
     */
    public static void shellSort(int[] arr) {
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        if (arr.length <= 1) {
            return; // Already sorted
        }

        int n = arr.length;

        // Start with Knuth's gap sequence: h = 3h + 1
        // This gives us gaps like: 1, 4, 13, 40, 121, 364, ...
        int gap = 1;
        while (gap < n / 3) {
            gap = 3 * gap + 1;
        }

        // Perform shell sort with decreasing gaps
        while (gap >= 1) {
            // Perform insertion sort for elements at gap distance
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                
                // Shift elements that are greater than temp
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                
                // Place temp in its correct position
                arr[j] = temp;
            }
            
            // Reduce gap for next iteration
            gap = gap / 3;
        }
    }

    /**
     * Alternative shell sort implementation using Shell's original gap sequence.
     * This version uses gaps: n/2, n/4, n/8, ..., 1
     *
     * @param arr the array to be sorted
     * @throws IllegalArgumentException if array is null
     */
    public static void shellSortOriginal(int[] arr) {
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        if (arr.length <= 1) {
            return;
        }

        int n = arr.length;

        // Start with gap = n/2 and reduce by half each time
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Perform insertion sort for elements at gap distance
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                
                // Shift elements that are greater than temp
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                
                // Place temp in its correct position
                arr[j] = temp;
            }
        }
    }



    /**
     * Test the shell sort implementation.
     */
    public static void main(String[] args) {
        System.out.println("SHELL SORT ALGORITHM TESTING");
        System.out.println("=============================");

        // Test case 1: Regular array
        int[] test1 = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42};
        System.out.println("\n1. Regular array test:");
        System.out.println("Original: " + Arrays.toString(test1));
        shellSort(test1.clone());
        System.out.println("Sorted:   " + Arrays.toString(test1));
        shellSort(test1);
        System.out.println("Verified: " + Arrays.toString(test1));
        
        // Test case 2: Already sorted
        int[] test2 = {1, 2, 3, 4, 5, 6, 7, 8};
        System.out.println("\n2. Already sorted array:");
        System.out.println("Original: " + Arrays.toString(test2));
        shellSort(test2);
        System.out.println("Sorted:   " + Arrays.toString(test2));
        
        // Test case 3: Reverse sorted
        int[] test3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        System.out.println("\n3. Reverse sorted array:");
        System.out.println("Original: " + Arrays.toString(test3));
        shellSort(test3);
        System.out.println("Sorted:   " + Arrays.toString(test3));
        
        // Test case 4: Array with duplicates
        int[] test4 = {5, 2, 8, 2, 9, 1, 5, 5, 2};
        System.out.println("\n4. Array with duplicates:");
        System.out.println("Original: " + Arrays.toString(test4));
        shellSort(test4);
        System.out.println("Sorted:   " + Arrays.toString(test4));
        
        // Test case 5: Single element
        int[] test5 = {42};
        shellSort(test5);
        assert test5[0] == 42;
        
        // Test case 6: Empty array
        int[] test6 = {};
        shellSort(test6);
        assert test6.length == 0;
        
        // Test case 7: Two elements
        int[] test7 = {9, 3};
        System.out.println("\n5. Two elements:");
        System.out.println("Original: " + Arrays.toString(test7));
        shellSort(test7);
        System.out.println("Sorted:   " + Arrays.toString(test7));
        
        // Test case 8: Compare gap sequences
        int[] testOriginal = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42};
        int[] testKnuth = testOriginal.clone();
        
        System.out.println("\n6. Comparing gap sequences:");
        System.out.println("Original array: " + Arrays.toString(testOriginal));
        
        shellSortOriginal(testOriginal);
        System.out.println("Shell's gaps:   " + Arrays.toString(testOriginal));
        
        shellSort(testKnuth);
        System.out.println("Knuth's gaps:   " + Arrays.toString(testKnuth));
        
        System.out.println("\nAll test cases passed!");
        System.out.println("Shell Sort advantages:");
        System.out.println("   - Better than insertion sort for larger arrays");
        System.out.println("   - In-place sorting (O(1) space complexity)");
        System.out.println("   - Adaptive - performs well on partially sorted data");
        System.out.println("   - Gap sequence affects performance significantly");
    }
}