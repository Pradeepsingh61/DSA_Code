import java.util.Arrays;

public class CountingSort {
    public static void countingSort(int[] arr) {
        int max = Arrays.stream(arr).max().getAsInt();
        int[] count = new int[max + 1];

        // Count the occurrences of each element
        for (int num : arr) {
            count[num]++;
        }

        // Modify the count array to store the cumulative sum
        for (int i = 1; i < count.length; i++) {
            count[i] += count[i - 1];
        }

        // Sort the original array using the count array
        int[] output = new int[arr.length];
        for (int i = arr.length - 1; i >= 0; i--) {
            output[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }

        System.arraycopy(output, 0, arr, 0, arr.length);
    }
}