/**
 * Binary Search Algorithm
 *
 * Description:
 * Binary Search is a divide-and-conquer algorithm that efficiently searches 
 * for a target value in a sorted array by repeatedly dividing the search 
 * interval in half.
 *
 * Approach:
 * - Start with two pointers (left and right).
 * - Find the middle element.
 * - If the middle element is the target, return its index.
 * - If the target is smaller, search the left half.
 * - If the target is larger, search the right half.
 * - Repeat until the element is found or the interval is empty.
 *
 * Time Complexity: O(log n) - halves the search space each step
 * Space Complexity: O(1) - uses only constant extra space
 *
 * Use Cases:
 * - Searching in sorted lists/arrays
 * - Used in libraries (like Arrays.binarySearch in Java)
 * - Applied in optimization problems (searching answer space)
 */

import java.util.Arrays;

public class BinarySearch {

    // Iterative Binary Search
    public static int binarySearch(int[] arr, int target) {
        int left = 0, right = arr.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;  // avoid overflow

            // Check if target found
            if (arr[mid] == target) {
                return mid;
            }
            // If target greater, ignore left half
            else if (arr[mid] < target) {
                left = mid + 1;
            }
            // If target smaller, ignore right half
            else {
                right = mid - 1;
            }
        }
        return -1; // target not found
    }

    // Test cases
    public static void main(String[] args) {
        int[] testArr = {1, 3, 5, 7, 9, 11};

        System.out.println("Array: " + Arrays.toString(testArr));

        // Example tests
        int target1 = 5;
        System.out.println("Searching for " + target1 + ": Index = " +
                binarySearch(testArr, target1)); // Expected 2

        int target2 = 6;
        System.out.println("Searching for " + target2 + ": Index = " +
                binarySearch(testArr, target2)); // Expected -1 (not found)

        int target3 = 11;
        System.out.println("Searching for " + target3 + ": Index = " +
                binarySearch(testArr, target3)); // Expected 5
    }
}
