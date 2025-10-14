import java.util.Arrays;

/**
 * ## Dutch National Flag Problem (Sort Colors)
 *
 * This algorithm sorts an array containing only three distinct elements (0, 1, and 2) in-place.
 * It's a classic partitioning problem that is solved in a single pass.
 *
 * ### How it works:
 * 1. Use three pointers: `low`, `mid`, and `high`.
 * 2. `low` points to the boundary of the '0' section.
 * 3. `high` points to the boundary of the '2' section.
 * 4. `mid` is the current element being considered.
 * 5. If `nums[mid]` is 0, swap it with `nums[low]` and increment both `low` and `mid`.
 * 6. If `nums[mid]` is 1, it's in the correct place, so just increment `mid`.
 * 7. If `nums[mid]` is 2, swap it with `nums[high]` and decrement `high` (don't increment `mid` as the swapped element needs to be processed).
 *
 * ### Complexity
 * - **Time Complexity:** O(n), where 'n' is the number of elements, because we iterate through the array only once.
 * - **Space Complexity:** O(1), as the sorting is done in-place without using any extra data structures.
 */
public class DutchNationalFlagProblem {

    public static void sortColors(int[] nums) {
        if (nums == null || nums.length == 0) {
            return;
        }

        int low = 0;
        int mid = 0;
        int high = nums.length - 1;

        while (mid <= high) {
            switch (nums[mid]) {
                case 0:
                    // When the element is 0, swap it with the element at the low pointer
                    swap(nums, low, mid);
                    low++;
                    mid++;
                    break;
                case 1:
                    // When the element is 1, it's in its correct place
                    mid++;
                    break;
                case 2:
                    // When the element is 2, swap it with the element at the high pointer
                    swap(nums, mid, high);
                    high--;
                    // Do not increment mid, as the swapped element from high needs to be checked
                    break;
            }
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    /**
     * Main method for testing the Dutch National Flag Problem implementation.
     */
    public static void main(String[] args) {
        // Test Case 1: Mixed array
        int[] colors1 = {2, 0, 2, 1, 1, 0};
        System.out.println("Test Case 1:");
        System.out.println("Original: " + Arrays.toString(colors1));
        sortColors(colors1);
        System.out.println("Expected: [0, 0, 1, 1, 2, 2]");
        System.out.println("Actual:   " + Arrays.toString(colors1));
        System.out.println();

        // Test Case 2: Array is already sorted
        int[] colors2 = {0, 0, 1, 2, 2};
        System.out.println("Test Case 2:");
        System.out.println("Original: " + Arrays.toString(colors2));
        sortColors(colors2);
        System.out.println("Expected: [0, 0, 1, 2, 2]");
        System.out.println("Actual:   " + Arrays.toString(colors2));
        System.out.println();

        // Test Case 3: Array with only two kinds of elements
        int[] colors3 = {2, 1, 1, 0, 0};
        System.out.println("Test Case 3:");
        System.out.println("Original: " + Arrays.toString(colors3));
        sortColors(colors3);
        System.out.println("Expected: [0, 0, 1, 1, 2]");
        System.out.println("Actual:   " + Arrays.toString(colors3));
        System.out.println();
    }
}