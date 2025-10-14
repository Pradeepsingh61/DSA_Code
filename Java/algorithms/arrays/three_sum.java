import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * ## 3 Sum Problem
 *
 * This algorithm finds all unique triplets in an array of integers that sum up to zero.
 * It uses a two-pointer approach on a sorted version of the array to efficiently find the triplets.
 *
 * ### Complexity
 * - **Time Complexity:** O(n^2), where n is the number of elements in the array.
 * The array sort takes O(n log n), but the nested loop structure (one `for` loop and one `while` loop) dominates, resulting in O(n^2).
 * - **Space Complexity:** O(1), as we are not using any extra space other than for the output list.
 * The sorting is done in-place.
 */
public class three_sum {

    public static List<List<Integer>> findTriplets(int[] nums) {
        // Sort the array to enable the two-pointer approach
        Arrays.sort(nums);
        List<List<Integer>> result = new ArrayList<>();

        // Iterate through the array. We only need to go up to the third-to-last element.
        for (int i = 0; i < nums.length - 2; i++) {
            // Skip duplicate elements to avoid duplicate triplets in the result.
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Use two pointers, one starting from the element after `i` and one from the end.
            int left = i + 1;
            int right = nums.length - 1;

            while (left < right) {
                int currentSum = nums[i] + nums[left] + nums[right];

                if (currentSum == 0) {
                    // Found a triplet! Add it to the result.
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));

                    // Move pointers and skip duplicates for the other two elements.
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }

                    // Move to the next unique pair.
                    left++;
                    right--;
                } else if (currentSum < 0) {
                    // If the sum is too small, move the left pointer to the right to increase it.
                    left++;
                } else {
                    // If the sum is too large, move the right pointer to the left to decrease it.
                    right--;
                }
            }
        }
        return result;
    }

    /**
     * Main method for testing the three_sum implementation.
     */
    public static void main(String[] args) {
        // Test Case 1: Standard case with positive and negative numbers
        int[] nums1 = {-1, 0, 1, 2, -1, -4};
        System.out.println("Test Case 1:");
        System.out.println("Input: " + Arrays.toString(nums1));
        System.out.println("Output: " + findTriplets(nums1)); // Expected: [[-1, -1, 2], [-1, 0, 1]]
        System.out.println();

        // Test Case 2: Array with all zeros
        int[] nums2 = {0, 0, 0, 0};
        System.out.println("Test Case 2:");
        System.out.println("Input: " + Arrays.toString(nums2));
        System.out.println("Output: " + findTriplets(nums2)); // Expected: [[0, 0, 0]]
        System.out.println();

        // Test Case 3: Array with no solution
        int[] nums3 = {1, 2, 3, 4, 5};
        System.out.println("Test Case 3:");
        System.out.println("Input: " + Arrays.toString(nums3));
        System.out.println("Output: " + findTriplets(nums3)); // Expected: []
        System.out.println();
    }
}