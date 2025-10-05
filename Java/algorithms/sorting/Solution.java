import java.util.*;

public class Solution {

    /**
     * Bucket sort for doubles in [0, 1).
     * Uses k buckets (default k = n) and insertion sort for each bucket.
     *
     * @param arr input array of doubles expected to lie in [0, 1)
     * @return a new sorted array (ascending)
     */
    public static double[] bucketSort1(double[] arr) {
        int n = arr.length;
        if (n <= 1) return Arrays.copyOf(arr, n);

        int k = n; // number of buckets
        ArrayList<ArrayList<Double>> buckets = new ArrayList<>(k);
        for (int i = 0; i < k; i++) buckets.add(new ArrayList<>());

        // Distribute values into buckets
        for (double x : arr) {
            if (x < 0.0 || x >= 1.0) {
                // For robustness: if outside [0,1), clamp into proper bucket via scaling
                // but it's better to use bucketSort2 for arbitrary ranges.
                int idx = (int)Math.floor(Math.min(Math.max(x, 0.0), 0.9999999) * k);
                buckets.get(idx).add(x);
            } else {
                int idx = (int)(x * k);
                if (idx == k) idx = k - 1; // safe-guard
                buckets.get(idx).add(x);
            }
        }

        // Sort each bucket using insertion sort (good for small sizes)
        for (ArrayList<Double> b : buckets) insertionSortList(b);

        // Concatenate buckets
        double[] out = new double[n];
        int pos = 0;
        for (ArrayList<Double> b : buckets) {
            for (double v : b) out[pos++] = v;
        }
        return out;
    }

    // insertion sort on ArrayList<Double>
    private static void insertionSortList(ArrayList<Double> list) {
        for (int i = 1; i < list.size(); i++) {
            double key = list.get(i);
            int j = i - 1;
            while (j >= 0 && list.get(j) > key) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, key);
        }
    }

    /**
     * Bucket sort for integers when you know the value range [minVal, maxVal].
     * This implementation maps integers into k buckets across the range and uses Collections.sort
     * for each bucket (which is typically TimSort, O(b log b) for bucket size b).
     *
     * @param arr input int array
     * @param minVal minimum possible value in arr
     * @param maxVal maximum possible value in arr
     * @return sorted int array
     */
    public static int[] bucketSort2(int[] arr, int minVal, int maxVal) {
        int n = arr.length;
        if (n <= 1) return Arrays.copyOf(arr, n);
        if (minVal > maxVal) throw new IllegalArgumentException("minVal > maxVal");

        // Choose number of buckets k (heuristic: k = min(n, range))
        int range = maxVal - minVal + 1;
        int k = Math.min(n, range);
        if (k <= 0) k = 1;

        ArrayList<ArrayList<Integer>> buckets = new ArrayList<>(k);
        for (int i = 0; i < k; i++) buckets.add(new ArrayList<>());

        // Map each value to bucket index
        for (int x : arr) {
            int idx = (int)((long)(x - minVal) * k / range); // scale into [0, k-1]
            if (idx < 0) idx = 0;
            else if (idx >= k) idx = k - 1;
            buckets.get(idx).add(x);
        }

        // Sort each bucket (Collections.sort uses TimSort)
        int[] out = new int[n];
        int pos = 0;
        for (ArrayList<Integer> b : buckets) {
            Collections.sort(b);
            for (int v : b) out[pos++] = v;
        }
        return out;
    }

    // ----------------------------
    // ✅ Test Cases / Examples
    // ----------------------------
    public static void main(String[] args) {
        // 1) Doubles in [0,1)
        double[] a1 = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
        System.out.println("Original (doubles): " + Arrays.toString(a1));
        double[] s1 = bucketSort1(a1);
        System.out.println("Sorted   (bucketSort1): " + Arrays.toString(s1));

        // 2) Integers with known small range
        int[] a2 = {29, 25, 3, 49, 9, 37, 21, 43};
        System.out.println("Original (ints): " + Arrays.toString(a2));
        int[] s2 = bucketSort2(a2, 0, 50);
        System.out.println("Sorted   (bucketSort2): " + Arrays.toString(s2));

        // 3) All equal elements (edge case)
        double[] a3 = {0.5, 0.5, 0.5, 0.5};
        System.out.println("All equal (doubles): " + Arrays.toString(a3));
        System.out.println("Sorted (bucketSort1): " + Arrays.toString(bucketSort1(a3)));

        // 4) Already sorted / reverse-sorted
        int[] a4 = {1,2,3,4,5,6,7,8,9};
        int[] a5 = {9,8,7,6,5,4,3,2,1};
        System.out.println("Already sorted (ints): " + Arrays.toString(bucketSort2(a4, 1, 9)));
        System.out.println("Reverse sorted (ints): " + Arrays.toString(bucketSort2(a5, 1, 9)));

        // 5) Large cluster in one bucket (worst-case demonstration)
        double[] a6 = new double[20];
        Arrays.fill(a6, 0.001); // all map to same bucket mostly
        System.out.println("Clustered (doubles): " + Arrays.toString(bucketSort1(a6))); // handles but degenerates to O(n^2)
    }
}
