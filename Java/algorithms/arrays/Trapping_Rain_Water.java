/*
Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
*/

class Solution {
    public int trap(int[] arr) {
        int n = arr.length;

        // Edge case: If there are less than 3 bars, no water can be trapped
        if (n < 3) return 0;

        // ----------------------------
        // Step 1: Create left max array
        // ----------------------------
        // left[i] stores the maximum height of bar from index 0 to i.
        int[] left = new int[n];
        left[0] = arr[0];
        for (int i = 1; i < n; i++) {
            left[i] = Math.max(left[i - 1], arr[i]);
        }

        // -----------------------------
        // Step 2: Create right max array
        // -----------------------------
        // right[i] stores the maximum height of bar from index i to n-1.
        int[] right = new int[n];
        right[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            right[i] = Math.max(right[i + 1], arr[i]);
        }

        // -------------------------------------
        // Step 3: Calculate trapped water at each index
        // -------------------------------------
        // The water trapped at each position depends on:
        // min(max height on left, max height on right) - current height
        int totalWater = 0;
        for (int i = 0; i < n; i++) {
            totalWater += Math.min(left[i], right[i]) - arr[i];
        }

        // Step 4: Return the total water trapped
        return totalWater;
    }
}
