/**
 * Stalin Sort Algorithm
 *
 * Description:
 * Stalin Sort is a humorous and simple sorting algorithm that removes elements from the list if they
 * are smaller than the previous one. This results in a list of elements where each element is greater 
 * than or equal to the one before it. The goal of this algorithm is not to sort all elements but to
 * remove elements that break the "non-decreasing" sequence.
 *
 * Approach:
 * - The algorithm iterates through the input array from the second element onwards.
 * - For each element, if it is greater than or equal to the last valid element (tracked by an index),
 *   it is kept; otherwise, it is discarded.
 * - The elements are placed in the array in such a way that the valid elements are at the front, and 
 *   the invalid ones are ignored.
 * - The result is a subsequence where the elements are in non-decreasing order.
 *
 * Use Cases:
 * - **Data Cleaning**: This algorithm could be used for cleaning data where you need to remove values
 *   that are smaller than the ones before them (e.g., in sensor data where the data should be increasing).
 * - **Simplified Sorting**: Useful in situations where you only care about retaining values that 
 *   create a non-decreasing sequence.
 *
 * Time Complexity:
 * - O(n) where n is the number of elements in the array.
 * - The algorithm only traverses the array once, making a constant-time comparison for each element.
 *
 * Space Complexity:
 * - O(1), as it modifies the input array in place and uses a constant amount of extra space (only a few variables).
 *
 * Algorithm Steps:
 * 1. Initialize `index` to track the position of the last valid element.
 * 2. Iterate through the array, starting from the second element.
 * 3. If the current element is greater than or equal to the last valid element, place it in the valid part.
 * 4. Finally, print the result array containing only valid elements.
 */
public class StalinSort {

    /**
     * Stalin Sort function that modifies the input array in place.
     * 
     * @param nums The array of integers to be processed.
     */
    public static void stalinSort(int[] nums) {
        // The index of the last valid element (elements in non-decreasing order)
        int index = 0; 

        // Iterate through the array starting from the second element
        for (int i = 1; i < nums.length; i++) {
            // If the current element is greater than or equal to the last valid element
            if (nums[i] >= nums[index]) {
                index++;  // Move index forward to accept the current element
                nums[index] = nums[i]; // Place the element in the "valid" part of the array
            }
        }

        // Print the "sorted" part of the array, which is the valid subsequence
        System.out.print("Sorted array: ");
        for (int i = 0; i <= index; i++) {
            System.out.print(nums[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        // Test case: Initial unsorted array
        int[] nums = {3, 1, 4, 2, 5, 6, 3, 8};
        stalinSort(nums);  // Sort using Stalin Sort

        // Additional test cases:
        int[] nums2 = {1, 2, 3, 4, 5};
        stalinSort(nums2);  // Already sorted, should print all elements.

        int[] nums3 = {5, 4, 3, 2, 1};
        stalinSort(nums3);  // Decreasing sequence, only the first element (5) will be kept.

        int[] nums4 = {10, 20, 10, 30, 25, 35, 30};
        stalinSort(nums4);  // Mixed sequence, will keep 10, 20, 30, 35.
    }
}
