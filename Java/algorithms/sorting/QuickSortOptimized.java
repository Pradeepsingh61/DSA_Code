import java.util.Arrays;

/**
 * Algorithm: Quick Sort (Optimized)
 * Description: In-place quicksort with median-of-three pivot selection,
 *              tail-recursion elimination (iterative partitioning), and
 *              insertion sort for small subarrays.
 *
 * Average Time Complexity: O(n log n)
 * Worst-case Time Complexity: O(n^2) (mitigated by pivot strategy)
 * Space Complexity: O(log n) (stack of subarray ranges)
 */
public class QuickSortOptimized {

    private static final int INSERTION_SORT_THRESHOLD = 16;

    /**
     * Public API to sort the array in ascending order.
     *
     * @param arr array to sort
     * @throws IllegalArgumentException if arr is null
     */
    public static void sort(int[] arr) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        if (arr.length <= 1) return;
        quickSort(arr, 0, arr.length - 1);
    }

    // Iterative quicksort using tail recursion elimination
    private static void quickSort(int[] arr, int left, int right) {
        while (left < right) {
            // Use insertion sort for tiny partitions
            if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
                insertionSort(arr, left, right);
                return;
            }

            // Median-of-three to choose a good pivot
            int pivotIndex = medianOfThree(arr, left, right);
            int pivot = arr[pivotIndex];

            // Partition around pivot
            int i = left - 1;
            int j = right + 1;
            while (true) {
                do { i++; } while (arr[i] < pivot);
                do { j--; } while (arr[j] > pivot);
                if (i >= j) break;
                swap(arr, i, j);
            }

            // Now j is the index separating the two partitions: [left..j], [j+1..right]
            // Recurse into the smaller partition first to keep stack depth O(log n)
            if (j - left < right - (j + 1)) {
                quickSort(arr, left, j);
                left = j + 1; // tail-recurse on the right side by adjusting bounds
            } else {
                quickSort(arr, j + 1, right);
                right = j; // tail-recurse on the left side by adjusting bounds
            }
        }
    }

    // Insertion sort for small ranges
    private static void insertionSort(int[] arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Median-of-three pivot selection: places median at middle index and returns it as pivot index
    private static int medianOfThree(int[] arr, int left, int right) {
        int mid = left + (right - left) / 2;
        if (arr[right] < arr[left]) swap(arr, left, right);
        if (arr[mid] < arr[left]) swap(arr, mid, left);
        if (arr[right] < arr[mid]) swap(arr, right, mid);
        // Place pivot at mid (already median); return mid
        return mid;
    }

    private static void swap(int[] arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    public static void main(String[] args) {
        int[] arr = {64, 34, 25, 12, 22, 11, 90, 5, 5, 102, -3, 0, 17};
        System.out.println("Original: " + Arrays.toString(arr));
        sort(arr);
        System.out.println("Sorted  : " + Arrays.toString(arr));

        int[] small = {3, 2, 1};
        sort(small);
        System.out.println("Small   : " + Arrays.toString(small));

        int[] already = {1, 2, 3, 4, 5, 6};
        sort(already);
        System.out.println("Already : " + Arrays.toString(already));

        System.out.println("Avg: O(n log n), Worst: O(n^2) mitigated by median-of-three & small-partition insertion sort; Space: O(log n)");
    }
}
