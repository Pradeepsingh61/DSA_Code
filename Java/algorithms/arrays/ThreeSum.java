import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * ## 3 Sum Problem
 *
 * This algorithm finds all unique triplets in an array of integers that sum up to zero.
 * It uses a two-pointer approach on a sorted version of the array to efficiently find the triplets.
 *
 * ### How it works:
 * 1. The input array is sorted to enable the two-pointer approach and to handle duplicates easily.
 * 2. We iterate through the array with a single pointer `i`.
 * 3. For each element `nums[i]`, we use two more pointers, `left` (starting at `i+1`) and `right` (starting at the end of the array).
 * 4. We calculate the sum of the three elements. If the sum is zero, we've found a triplet. If it's less than zero, we move `left` forward. If it's greater, we move `right` backward.
 * 5. Duplicates are skipped to ensure that each unique triplet is only added once.
 *
 * ### Complexity
 * - **Time Complexity:** O(n^2), where 'n' is the number of elements. The array sort is O(n log n), but the nested loop structure (a `for` loop and a `while` loop) dominates.
 * - **Space Complexity:** O(1) for the algorithm itself (if we don't count the space for the output list). Sorting is done in-place.
 */
public class ThreeSum {

    public static List<List<Integer>> findTriplets(int[] nums) {
        // Sort the array to enable the two-pointer approach
        Arrays.sort(nums);
        List<List<Integer>> result = new ArrayList<>();

        // Iterate through the array. We only need to go up to the third-to-last element.
        for (int i = 0; i < nums.length - 2; i++) {
            // Skip duplicate elements for the first element of the triplet to avoid duplicate results.
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = nums.length - 1;
            while (left < right) {
                int currentSum = nums[i] + nums[left] + nums[right];
                if (currentSum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    // Skip duplicates for the second and third elements.
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (currentSum < 0) {
                    left++; // Sum is too small, need a larger number.
                } else {
                    right--; // Sum is too large, need a smaller number.
                }
            }
        }
        return result;
    }

    /**
     * Main method for testing the ThreeSum implementation.
     */
    public static void main(String[] args) {
        // Test Case 1: Standard case with multiple solutions
        int[] nums1 = {-1, 0, 1, 2, -1, -4};
        System.out.println("Test Case 1:");
        System.out.println("Input: " + Arrays.toString(nums1));
        System.out.println("Expected: [[-1, -1, 2], [-1, 0, 1]]");
        System.out.println("Actual: " + findTriplets(nums1));
        System.out.println();

        // Test Case 2: Array with no solution
        int[] nums2 = {1, 2, 3};
        System.out.println("Test Case 2:");
        System.out.println("Input: " + Arrays.toString(nums2));
        System.out.println("Expected: []");
        System.out.println("Actual: " + findTriplets(nums2));
        System.out.println();

        // Test Case 3: Array with all zeros
        int[] nums3 = {0, 0, 0, 0};
        System.out.println("Test Case 3:");
        System.out.println("Input: " + Arrays.toString(nums3));
        System.out.println("Expected: [[0, 0, 0]]");
        System.out.println("Actual: " + findTriplets(nums3));
        System.out.println();
    }
}