import java.util.Arrays;

public class BinarySearchVariants {

    /**
     * Algorithm: Binary Search (Iterative)
     * Description: Searches for a target value in a sorted array using
     *              divide-and-conquer to achieve logarithmic time.
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    public static int binarySearch(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int left = 0, right = arr.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2; // avoids overflow
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) left = mid + 1; else right = mid - 1;
        }
        return -1;
    }

    /**
     * Algorithm: Binary Search (Recursive)
     * Time Complexity: O(log n)
     * Space Complexity: O(log n) due to recursion stack
     */
    public static int binarySearchRecursive(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        return bsRec(arr, 0, arr.length - 1, target);
    }

    private static int bsRec(int[] arr, int left, int right, int target) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) return bsRec(arr, mid + 1, right, target);
        return bsRec(arr, left, mid - 1, target);
    }

    /**
     * Returns the first index of target in a sorted array with duplicates, or -1 if not found.
     * Time: O(log n), Space: O(1)
     */
    public static int firstOccurrence(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int left = 0, right = arr.length - 1, ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= target) {
                if (arr[mid] == target) ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    /**
     * Returns the last index of target in a sorted array with duplicates, or -1 if not found.
     * Time: O(log n), Space: O(1)
     */
    public static int lastOccurrence(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int left = 0, right = arr.length - 1, ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) {
                if (arr[mid] == target) ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }

    /**
     * Lower bound: first index i such that arr[i] >= target. If all elements < target, returns arr.length.
     * Time: O(log n), Space: O(1)
     */
    public static int lowerBound(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int left = 0, right = arr.length; // right is exclusive
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) left = mid + 1; else right = mid;
        }
        return left;
    }

    /**
     * Upper bound: first index i such that arr[i] > target. If all elements <= target, returns arr.length.
     * Time: O(log n), Space: O(1)
     */
    public static int upperBound(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int left = 0, right = arr.length; // right is exclusive
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) left = mid + 1; else right = mid;
        }
        return left;
    }

    // Helper to verify sortedness (optional debug)
    private static boolean isSorted(int[] arr) {
        for (int i = 1; i < arr.length; i++) if (arr[i] < arr[i - 1]) return false;
        return true;
    }

    public static void main(String[] args) {
        // Demonstration and tests
        int[] arr = {1, 3, 3, 3, 5, 7, 9, 11, 15};
        System.out.println("Array: " + Arrays.toString(arr));

        // Basic searches
        System.out.println("binarySearch 7  -> " + binarySearch(arr, 7));
        System.out.println("binarySearch 2  -> " + binarySearch(arr, 2));
        System.out.println("binarySearchRecursive 9 -> " + binarySearchRecursive(arr, 9));

        // Occurrence variants
        System.out.println("firstOccurrence 3 -> " + firstOccurrence(arr, 3)); // expected 1
        System.out.println("lastOccurrence 3  -> " + lastOccurrence(arr, 3));  // expected 3

        // Bounds
        System.out.println("lowerBound 4 -> " + lowerBound(arr, 4)); // first >= 4 => index 4 (value 5)
        System.out.println("upperBound 3 -> " + upperBound(arr, 3)); // first > 3  => index 4
        System.out.println("lowerBound 100 -> " + lowerBound(arr, 100)); // arr.length
        System.out.println("upperBound -10 -> " + upperBound(arr, -10)); // 0

        // Complexity notes
        System.out.println("All methods: Time O(log n), Space O(1) except recursive O(log n) stack");

        // Optional sortedness assertion (disabled by default)
        // if (!isSorted(arr)) throw new IllegalArgumentException("Array must be sorted");
    }
}