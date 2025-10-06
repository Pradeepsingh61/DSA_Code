/*
 * Cycle Sort — Two Variants
 * =========================
 * 
 * 1️⃣ Original Cycle Sort (General Arrays)
 * --------------------------------------
 * ✍️ Description
 * - Works for any unsorted array (even with duplicates).
 * - Places each element directly into its correct position
 *   by counting how many elements are smaller (its rank).
 * - Completes cycles of misplaced elements by rotating until closed.
 *
 * 📊 Complexity
 * - Time:  O(n^2) — each "count smaller elements" scan takes O(n).
 * - Writes: O(n)  — each element is written once into final place.
 * - Space: O(1)   — in-place.
 *
 * 💡 Notes
 * - Minimizes number of writes → useful where writes are expensive
 *   (e.g., Flash/EEPROM).
 * - Not stable (order of duplicates may change).
 *
 * 2️⃣ Cycle Sort for Range 1..n (Permutation Case)
 * -----------------------------------------------
 * ✍️ Description
 * - Special optimization when the array is a permutation of [1..n].
 * - Correct index of value v is v-1. Repeatedly swap elements
 *   into their correct positions until all are placed.
 *
 * 📊 Complexity
 * - Time:  O(n)   — each element swapped at most once into place.
 * - Writes: O(n)  — total swaps ≤ n.
 * - Space: O(1).
 *
 * 💡 Notes
 * - Only works when array contains numbers 1..n exactly once each.
 * - Used in problems like "find missing numbers" or "find duplicates".
 */

 import java.util.*;

 class CycleSortAll {
 
     // 🔹 1. Original Cycle Sort (general case, O(n^2))
     public static void cycleSortGeneral(int[] a) {
         int n = a.length;
         for (int start = 0; start <= n - 2; start++) {
             int item = a[start];
 
             // Find correct position of this item
             int pos = start;
             for (int i = start + 1; i < n; i++) {
                 if (a[i] < item) pos++;
             }
 
             if (pos == start) continue;
             while (item == a[pos]) pos++;
 
             if (pos != start) {
                 int tmp = a[pos];
                 a[pos] = item;
                 item = tmp;
             }
 
             // Rotate cycle
             while (pos != start) {
                 pos = start;
                 for (int i = start + 1; i < n; i++) {
                     if (a[i] < item) pos++;
                 }
                 while (item == a[pos]) pos++;
 
                 int tmp = a[pos];
                 a[pos] = item;
                 item = tmp;
             }
         }
     }
 
     // 🔹 2. Cycle Sort for permutation of 1..n (O(n))
     public static void cycleSortPermutation(int[] arr) {
         int i = 0;
         while (i < arr.length) {
             int correct = arr[i] - 1; // correct index
             if (arr[i] != arr[correct]) {
                 int tmp = arr[i];
                 arr[i] = arr[correct];
                 arr[correct] = tmp;
             } else {
                 i++;
             }
         }
     }
 
     // ----------------------------
     // ✅ Test Cases
     // ----------------------------
     public static void main(String[] args) {
         // Case 1: General Cycle Sort
         int[] arr1 = {3, 1, 2, 3, 2, 1, 3};
         cycleSortGeneral(arr1);
         System.out.println("General Cycle Sort (with duplicates): " + Arrays.toString(arr1));
         // Expect: [1, 1, 2, 2, 3, 3, 3]
 
         int[] arr2 = {5, 4, 3, 2, 1};
         cycleSortGeneral(arr2);
         System.out.println("General Cycle Sort (reverse): " + Arrays.toString(arr2));
         // Expect: [1, 2, 3, 4, 5]
 
         // Case 2: Permutation 1..n
         int[] arr3 = {3, 5, 2, 1, 4};
         cycleSortPermutation(arr3);
         System.out.println("Cycle Sort Permutation 1..n: " + Arrays.toString(arr3));
         // Expect: [1, 2, 3, 4, 5]
 
         int[] arr4 = {2, 3, 1, 5, 4};
         cycleSortPermutation(arr4);
         System.out.println("Cycle Sort Permutation 1..n: " + Arrays.toString(arr4));
         // Expect: [1, 2, 3, 4, 5]
     }
 }
 