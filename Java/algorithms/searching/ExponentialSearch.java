import java.util.Arrays;

/**
 * Algorithm: Exponential Search
 * Description: Quickly finds a range where the target may reside by
 *              exponentially increasing the index (1, 2, 4, 8, ...),
 *              then performs binary search within that range.
 *
 * Use cases: Efficient when the target is near the beginning or when
 *             the array size is unbounded/unknown ahead of time.
 *
 * Time Complexity: O(log i) where i is the index of the target
 * Space Complexity: O(1)
 */
public class ExponentialSearch {

    /**
     * Performs exponential search on a sorted array.
     *
     * @param arr sorted input array
     * @param target value to search for
     * @return index of target if found, otherwise -1
     * @throws IllegalArgumentException if arr is null
     */
    public static int search(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return -1;

        // If the first element is the target
        if (arr[0] == target) return 0;

        // Find range for binary search by repeated doubling
        int bound = 1;
        while (bound < n && arr[bound] < target) {
            bound *= 2;
        }

        // Define the search boundaries
        int left = bound / 2;
        int right = Math.min(bound, n - 1);

        // Binary search within [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) left = mid + 1; else right = mid - 1;
        }

        return -1;
    }

    /**
     * Lower bound within exponential search context: first index i with arr[i] >= target.
     * Returns arr.length if all elements are < target.
     */
    public static int lowerBound(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return 0;

        // Exponentially grow until arr[bound] >= target or end
        int bound = 1;
        while (bound < n && arr[bound] < target) bound <<= 1;

        int left = bound >> 1;
        int right = Math.min(bound, n);
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) left = mid + 1; else right = mid;
        }
        return left;
    }

    /**
     * Upper bound within exponential search context: first index i with arr[i] > target.
     * Returns arr.length if all elements are <= target.
     */
    public static int upperBound(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return 0;

        int bound = 1;
        while (bound < n && arr[bound] <= target) bound <<= 1;

        int left = bound >> 1;
        int right = Math.min(bound, n);
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) left = mid + 1; else right = mid;
        }
        return left;
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        System.out.println("Array: " + Arrays.toString(arr));

        // Basic searches
        System.out.println("search 1   -> " + search(arr, 1));   // 0
        System.out.println("search 34  -> " + search(arr, 34));  // 7
        System.out.println("search 100 -> " + search(arr, 100)); // -1

        // Bounds
        System.out.println("lowerBound 4  -> " + lowerBound(arr, 4));  // 3 (value 5)
        System.out.println("upperBound 34 -> " + upperBound(arr, 34)); // 8 (value 55)

        // Complexity notes
        System.out.println("Time O(log i), Space O(1), where i is index of target.");
    }
}
