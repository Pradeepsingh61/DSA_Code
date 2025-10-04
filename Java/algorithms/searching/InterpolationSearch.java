import java.util.Arrays;

/**
 * Algorithm: Interpolation Search
 * Description: Position-aware search for sorted arrays that estimates the
 *              probable position of the target using linear interpolation.
 *              Works best on uniformly distributed data.
 *
 * Average Time Complexity: O(log log n) (uniform distribution)
 * Worst-case Time Complexity: O(n)
 * Space Complexity: O(1)
 */
public class InterpolationSearch {

    /**
     * Searches for target in a sorted array using interpolation.
     *
     * @param arr sorted array (ascending)
     * @param target value to search
     * @return index of target if found; otherwise -1
     * @throws IllegalArgumentException if arr is null
     */
    public static int search(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return -1;

        int low = 0, high = n - 1;

        // Loop while target is within the current range
        while (low <= high && target >= arr[low] && target <= arr[high]) {
            // Handle equal range to avoid division-by-zero
            if (arr[high] == arr[low]) {
                return (arr[low] == target) ? low : -1;
            }

            // Estimate position using linear interpolation
            int pos = low + (int)((long)(target - arr[low]) * (high - low) / (arr[high] - arr[low]));

            if (pos < low || pos > high) break; // safety bound

            if (arr[pos] == target) {
                return pos;
            } else if (arr[pos] < target) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        // Final check if while guard failed but boundaries might match
        if (low <= high && arr[low] == target) return low;
        if (low <= high && arr[high] == target) return high;
        return -1;
    }

    public static void main(String[] args) {
        // Uniformly distributed example
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80};
        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("search 10  -> " + search(arr, 10)); // 0
        System.out.println("search 80  -> " + search(arr, 80)); // 7
        System.out.println("search 55  -> " + search(arr, 55)); // -1

        // Edge cases
        int[] single = {42};
        System.out.println("single (42) search 42 -> " + search(single, 42)); // 0
        System.out.println("single (42) search 7  -> " + search(single, 7));  // -1

        int[] equalVals = {5, 5, 5, 5, 5};
        System.out.println("equalVals search 5  -> " + search(equalVals, 5)); // 0
        System.out.println("equalVals search 10 -> " + search(equalVals, 10)); // -1

        System.out.println("Average: O(log log n) uniform; Worst: O(n); Space: O(1)");
    }
}
