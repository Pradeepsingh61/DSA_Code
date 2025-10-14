import java.util.Arrays;

/**
 * Algorithm: Jump Search
 * Description: Searches for a target in a sorted array by jumping blocks of size ≈ sqrt(n),
 *              then performing a linear scan within the found block.
 *
 * Time Complexity: O(\u221An)
 * Space Complexity: O(1)
 */
public class JumpSearch {

    /**
     * Performs jump search on a sorted array.
     *
     * @param arr sorted array in ascending order
     * @param target value to find
     * @return index of target if found, otherwise -1
     * @throws IllegalArgumentException if arr is null
     */
    public static int search(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return -1;

        int step = (int) Math.floor(Math.sqrt(n));
        if (step == 0) step = 1; // safeguard

        int prev = 0;
        int curr = Math.min(step, n) - 1;

        // Jump in blocks until the block end is >= target or end of array
        while (arr[curr] < target) {
            prev = curr + 1;
            if (prev >= n) return -1;
            curr = Math.min(prev + step - 1, n - 1);
        }

        // Linear scan within the block [prev, curr]
        for (int i = prev; i <= curr; i++) {
            if (arr[i] == target) return i;
            if (arr[i] > target) return -1; // early exit
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("search 1  -> " + search(arr, 1));   // 0
        System.out.println("search 19 -> " + search(arr, 19));  // 9
        System.out.println("search 8  -> " + search(arr, 8));   // -1

        // Edge cases
        int[] one = {42};
        System.out.println("one 42 -> " + search(one, 42)); // 0
        System.out.println("one  7 -> " + search(one, 7));  // -1

        System.out.println("Time O(√n), Space O(1)");
    }
}
