/*
 * Bucket Sort Algorithm in Java
 * 
 * Description:
 *   Bucket Sort works by distributing elements into buckets,
 *   sorting each bucket individually, then concatenating them.
 *
 * Time Complexity:
 *   Best: O(n+k), Average: O(n+k), Worst: O(n^2)
 * Space Complexity:
 *   O(n + k) where k is number of buckets
 */

import java.util.*;

public class BucketSort {
    public static void bucketSort(float[] arr) {
        int n = arr.length;
        if (n <= 0) return;

        // 1) Create buckets
        @SuppressWarnings("unchecked")
        ArrayList<Float>[] buckets = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            buckets[i] = new ArrayList<Float>();
        }

        // 2) Distribute array elements into buckets
        for (float num : arr) {
            int index = (int) (num * n);
            buckets[index].add(num);
        }

        // 3) Sort individual buckets
        for (ArrayList<Float> bucket : buckets) {
            Collections.sort(bucket);
        }

        // 4) Concatenate buckets back into original array
        int idx = 0;
        for (ArrayList<Float> bucket : buckets) {
            for (float num : bucket) {
                arr[idx++] = num;
            }
        }
    }

    // Test code
    public static void main(String[] args) {
        float[] arr = {0.42f, 0.32f, 0.23f, 0.52f, 0.25f, 0.47f, 0.51f};
        bucketSort(arr);
        System.out.println(Arrays.toString(arr));
    }
}
