/**
 * Pascal's Triangle Row Generator
 *
 * Description: Generates the nth row of Pascal's Triangle using the 
 * combinatorial formula nCr = n! / (r! * (n-r)!).
 *
 * Time Complexity: O(n^2) in worst case for computing factorial-based combinations.
 * Space Complexity: O(n) - stores the nth row in a list.
 */

import java.util.*;
class PascalsTriangle {
    public static void main(String[] args) {
        int n = 5; 
        List<Integer> list = new ArrayList<>();

        for (int c = 1; c <= n; c++) {
            list.add(nCr(n - 1, c - 1));
        }
        System.out.println(list.toString());
    }

    /**
     * Computes nCr (combinations) using an iterative approach to avoid large factorials.
     *
     * @param r Total items (n-1 for zero-based row)
     * @param c Items chosen (c-1 for zero-based column)
     * @return The value of nCr
     */
    static int nCr(int r, int c) {
        int result = 1;
        for (int i = 0; i < c; i++) {
            result = result * (r - i);
            result = result / (i + 1);
        }
        return result;
    }
}
