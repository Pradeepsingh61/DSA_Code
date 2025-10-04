import java.util.Arrays;

/**
 * Algorithm: Fibonacci Search
 * Description: Searches for target in a sorted array using Fibonacci numbers
 *              to determine probe positions, reducing the search range similar
 *              to binary search but with Fibonacci offsets.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
public class FibonacciSearch {

    /**
     * Performs Fibonacci Search on a sorted array.
     *
     * @param arr sorted array in ascending order
     * @param target value to locate
     * @return index of target if found, otherwise -1
     * @throws IllegalArgumentException if arr is null
     */
    public static int search(int[] arr, int target) {
        if (arr == null) throw new IllegalArgumentException("Array cannot be null");
        int n = arr.length;
        if (n == 0) return -1;

        // Initialize fibonacci numbers: fibM = fib(k), fibMm1 = fib(k-1), fibMm2 = fib(k-2)
        int fibMm2 = 0; // F(0)
        int fibMm1 = 1; // F(1)
        int fibM = fibMm1 + fibMm2; // F(2)

        // Find the smallest Fibonacci number >= n
        while (fibM < n) {
            fibMm2 = fibMm1;
            fibMm1 = fibM;
            fibM = fibMm1 + fibMm2;
        }

        // Marks eliminated range from front
        int offset = -1;

        while (fibM > 1) {
            int i = Math.min(offset + fibMm2, n - 1);

            if (arr[i] < target) {
                // Move 1 Fibonacci down: cut subarray from offset to i
                fibM = fibMm1;
                fibMm1 = fibMm2;
                fibMm2 = fibM - fibMm1;
                offset = i;
            } else if (arr[i] > target) {
                // Move 2 Fibonacci down: cut subarray after i
                fibM = fibMm2;
                fibMm1 = fibMm1 - fibMm2;
                fibMm2 = fibM - fibMm1;
            } else {
                return i; // Found
            }
        }

        // Compare the last element
        if (fibMm1 == 1 && offset + 1 < n && arr[offset + 1] == target) {
            return offset + 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] arr = {1, 3, 5, 7, 9, 11, 13, 15};
        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("search 1  -> " + search(arr, 1));  // 0
        System.out.println("search 15 -> " + search(arr, 15)); // 7
        System.out.println("search 8  -> " + search(arr, 8));  // -1

        int[] single = {42};
        System.out.println("single 42 -> " + search(single, 42)); // 0
        System.out.println("single  7 -> " + search(single, 7));  // -1

        System.out.println("Time O(log n), Space O(1)");
    }
}
