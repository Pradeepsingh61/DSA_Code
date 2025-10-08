import java.util.Arrays;

public class BinomialCoefficient {

    /**
     * Calculates the Binomial Coefficient C(n, k), also known as "n choose k",
     * using Dynamic Programming.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * The binomial coefficient C(n, k) represents the number of ways to choose k elements
     * from a set of n distinct elements. It can be computed using a recurrence relation that
     * forms the basis of Pascal's Triangle.
     *
     * Recurrence Relation:
     * C(n, k) = C(n-1, k-1) + C(n-1, k)
     *
     * Base Cases:
     * C(n, 0) = 1 (There's one way to choose zero elements: the empty set)
     * C(n, n) = 1 (There's one way to choose all n elements: the entire set)
     *
     * DYNAMIC PROGRAMMING APPROACH:
     * We can solve this efficiently by building a 2D DP table (let's call it `dp`) to store
     * the results of subproblems, effectively constructing a part of Pascal's Triangle.
     *
     * State Definition:
     * `dp[i][j]` will store the value of C(i, j).
     *
     * Table Filling:
     * We fill the table row by row, from i=0 to n. For each row `i`, we calculate the
     * coefficients for `j` from 0 up to `k`.
     * - The value `dp[i][j]` is calculated using the values from the previous row:
     * `dp[i-1][j-1]` and `dp[i-1][j]`.
     * - The base cases `C(i, 0) = 1` and `C(i, i) = 1` are used to initialize the values
     * in each row.
     *
     * The final answer is the value stored at `dp[n][k]`.
     *
     * OPTIMIZATION:
     * A useful property of binomial coefficients is that C(n, k) = C(n, n-k).
     * To save computation, we can choose the smaller of k and n-k. For example,
     * C(10, 8) is the same as C(10, 2), and calculating the latter is faster.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Time Complexity: O(n * k)
     * We fill a 2D table of size (n+1) x (k+1). Each entry takes constant time to compute,
     * leading to a complexity proportional to the size of the table.
     *
     * Space Complexity: O(n * k)
     * This is the space required to store the 2D DP table.
     * (Note: This can be optimized to O(k) space because computing row `i` only requires
     * values from the previous row `i-1`. A 1D array could be used to store the previous
     * row's results and update it in place to get the current row's results).
     *
     * @param n The total number of items.
     * @param k The number of items to choose.
     * @return The value of C(n, k). Returns -1 for invalid input.
     */
    public long calculateNcr(int n, int k) {
        // Step 1: Handle invalid input cases.
        // k cannot be greater than n, and both must be non-negative.
        if (k < 0 || n < 0 || k > n) {
            return -1; // Or throw an exception
        }

        // Step 2: Apply the optimization C(n, k) = C(n, n-k).
        // We choose the smaller value between k and n-k to reduce computation.
        if (k > n - k) {
            k = n - k;
        }

        // Base case: C(n, 0) is always 1.
        if (k == 0) {
            return 1;
        }

        // Step 3: Create the DP table to store results of subproblems.
        // Using long to prevent overflow as C(n, k) can grow very large.
        // The table size is (n+1) x (k+1).
        long[][] dp = new long[n + 1][k + 1];

        // Step 4: Fill the DP table in a bottom-up manner.
        for (int i = 0; i <= n; i++) {
            // We only need to compute up to min(i, k) for each row 'i',
            // because C(i, j) is 0 if j > i.
            for (int j = 0; j <= Math.min(i, k); j++) {
                // Step 5: Apply the base cases.
                // C(i, 0) = 1 and C(i, i) = 1.
                if (j == 0 || j == i) {
                    dp[i][j] = 1;
                } else {
                    // Step 6: Use the recurrence relation to compute other values.
                    // C(i, j) = C(i-1, j-1) + C(i-1, j)
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
            }
        }

        // Step 7: The final answer is at the bottom-right corner of our computed table.
        return dp[n][k];
    }

    public static void main(String[] args) {
        BinomialCoefficient bc = new BinomialCoefficient();

        int n1 = 5, k1 = 2;
        System.out.println("C(" + n1 + ", " + k1 + ") = " + bc.calculateNcr(n1, k1)); // Expected: 10

        int n2 = 10, k2 = 5;
        System.out.println("C(" + n2 + ", " + k2 + ") = " + bc.calculateNcr(n2, k2)); // Expected: 252
        
        // Using the optimization C(10, 8) = C(10, 2)
        int n3 = 10, k3 = 8;
        System.out.println("C(" + n3 + ", " + k3 + ") = " + bc.calculateNcr(n3, k3)); // Expected: 45

        int n4 = 52, k4 = 5;
        System.out.println("C(" + n4 + ", " + k4 + ") = " + bc.calculateNcr(n4, k4)); // Expected: 2598960
        
        // Invalid input
        int n5 = 5, k5 = 6;
        System.out.println("C(" + n5 + ", " + k5 + ") = " + bc.calculateNcr(n5, k5)); // Expected: -1
    }
}