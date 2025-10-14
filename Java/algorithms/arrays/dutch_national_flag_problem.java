import java.util.Arrays;

/**
 * ## Dutch National Flag Problem (Sort Colors)
 *
 * This algorithm sorts an array containing only 0s, 1s, and 2s in a single pass.
 * It uses three pointers (`low`, `mid`, and `high`) to partition the array into three sections:
 * 0s at the beginning, 1s in the middle, and 2s at the end.
 *
 * ### Complexity
 * - **Time Complexity:** O(n), where n is the number of elements. We iterate through the array only once.
 * - **Space Complexity:** O(1), as the sorting is done in-place without using any extra data structures.
 */
public class dutch_national_flag_problem {

    public static void sortColors(int[] nums) {
        if (nums == null || nums.length == 0) {
            return;
        }

        int low = 0;          // Points to the position where the next 0 should go.
        int mid = 0;          // The current element being processed.
        int high = nums.length - 1; // Points to the position where the next 2 should go.

        // The loop continues as long as the 'mid' pointer has not surpassed the 'high' pointer.
        while (mid <= high) {
            switch (nums[mid]) {
                case 0:
                    // If the middle element is 0, swap it with the element at the 'low' pointer.
                    swap(nums, low, mid);
                    low++;
                    mid++;
                    break;
                case 1:
                    // If the middle element is 1, it's in the correct place, so just move 'mid'.
                    mid++;
                    break;
                case 2:
                    // If the middle element is 2, swap it with the element at the 'high' pointer.
                    swap(nums, mid, high);
                    high--;
                    // Note: We don't increment 'mid' here because the element swapped from 'high'
                    // could be a 0, which needs to be processed again.
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
        System.out.println("Original array: " + Arrays.toString(colors1));
        sortColors(colors1);
        System.out.println("Sorted array:   " + Arrays.toString(colors1)); // Expected: [0, 0, 1, 1, 2, 2]
        System.out.println();

        // Test Case 2: Array already sorted
        int[] colors2 = {0, 1, 2};
        System.out.println("Test Case 2:");
        System.out.println("Original array: " + Arrays.toString(colors2));
        sortColors(colors2);
        System.out.println("Sorted array:   " + Arrays.toString(colors2)); // Expected: [0, 1, 2]
        System.out.println();

        // Test Case 3: Array with only 2s and 1s
        int[] colors3 = {2, 1, 2, 1};
        System.out.println("Test Case 3:");
        System.out.println("Original array: " + Arrays.toString(colors3));
        sortColors(colors3);
        System.out.println("Sorted array:   " + Arrays.toString(colors3)); // Expected: [1, 1, 2, 2]
        System.out.println();
    }import java.util.Arrays;

/**
 * ## Dutch National Flag Problem (Sort Colors)
 *
 * This algorithm sorts an array containing only 0s, 1s, and 2s in a single pass.
 * It uses three pointers (`low`, `mid`, and `high`) to partition the array into three sections:
 * 0s at the beginning, 1s in the middle, and 2s at the end.
 *
 * ### Complexity
 * - **Time Complexity:** O(n), where n is the number of elements. We iterate through the array only once.
 * - **Space Complexity:** O(1), as the sorting is done in-place without using any extra data structures.
 */
public class dutch_national_flag_problem {

    public static void sortColors(int[] nums) {
        if (nums == null || nums.length == 0) {
            return;
        }

        int low = 0;          // Points to the position where the next 0 should go.
        int mid = 0;          // The current element being processed.
        int high = nums.length - 1; // Points to the position where the next 2 should go.

        // The loop continues as long as the 'mid' pointer has not surpassed the 'high' pointer.
        while (mid <= high) {
            switch (nums[mid]) {
                case 0:
                    // If the middle element is 0, swap it with the element at the 'low' pointer.
                    swap(nums, low, mid);
                    low++;
                    mid++;
                    break;
                case 1:
                    // If the middle element is 1, it's in the correct place, so just move 'mid'.
                    mid++;
                    break;
                case 2:
                    // If the middle element is 2, swap it with the element at the 'high' pointer.
                    swap(nums, mid, high);
                    high--;
                    // Note: We don't increment 'mid' here because the element swapped from 'high'
                    // could be a 0, which needs to be processed again.
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
        System.out.println("Original array: " + Arrays.toString(colors1));
        sortColors(colors1);
        System.out.println("Sorted array:   " + Arrays.toString(colors1)); // Expected: [0, 0, 1, 1, 2, 2]
        System.out.println();

        // Test Case 2: Array already sorted
        int[] colors2 = {0, 1, 2};
        System.out.println("Test Case 2:");
        System.out.println("Original array: " + Arrays.toString(colors2));
        sortColors(colors2);
        System.out.println("Sorted array:   " + Arrays.toString(colors2)); // Expected: [0, 1, 2]
        System.out.println();

        // Test Case 3: Array with only 2s and 1s
        int[] colors3 = {2, 1, 2, 1};
        System.out.println("Test Case 3:");
        System.out.println("Original array: " + Arrays.toString(colors3));
        sortColors(colors3);
        System.out.println("Sorted array:   " + Arrays.toString(colors3)); // Expected: [1, 1, 2, 2]
        System.out.println();
    }
}
}