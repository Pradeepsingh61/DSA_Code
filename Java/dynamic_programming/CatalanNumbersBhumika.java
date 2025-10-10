public class CatalanNumbersBhumika {

    /**
     * Calculates the nth Catalan number using Dynamic Programming.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * Catalan numbers are a sequence of natural numbers that occur in various counting
     * problems in combinatorics. The nth Catalan number is denoted as C(n).
     *
     * Examples of problems solved by Catalan numbers:
     * 1. The number of correctly matched sequences of n pairs of parentheses (e.g., for n=3: ((())), ()()(), ()(()), (())(), (()())).
     * 2. The number of possible Binary Search Trees (BSTs) with n keys.
     * 3. The number of ways a convex polygon with n+2 sides can be cut into triangles.
     * 4. The number of paths on a grid from (0,0) to (n,n) that do not go above the main diagonal.
     *
     * DYNAMIC PROGRAMMING APPROACH:
     * We can compute Catalan numbers using the following recursive formula:
     * C(n) = C(0)*C(n-1) + C(1)*C(n-2) + ... + C(n-1)*C(0)
     * which can be written as a summation: C(n) = Σ [from i=0 to n-1] ( C(i) * C(n-1-i) )
     *
     * The base case is C(0) = 1.
     *
     * We use a 1D DP array, let's call it `catalan`, to store the computed values.
     *
     * State Definition:
     * `catalan[i]` will store the value of the ith Catalan number, C(i).
     *
     * Logic:
     * - We initialize the base case: `catalan[0] = 1`.
     * - We then iteratively compute `catalan[i]` for i from 1 to n.
     * - To compute `catalan[i]`, we use an inner loop that applies the summation formula,
     * relying on the previously computed values (C(0) through C(i-1)) that are already
     * stored in our `catalan` array.
     *
     * The final answer is the value stored at `catalan[n]`.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Let N be the input number.
     *
     * Time Complexity: O(N^2)
     * We have two nested loops. The outer loop runs from i=1 to N. The inner loop runs i times.
     * The total number of operations is roughly 1 + 2 + 3 + ... + N, which is N*(N+1)/2.
     * This gives a quadratic time complexity.
     *
     * Space Complexity: O(N)
     * We use a DP array of size N+1 to store the Catalan numbers up to N.
     *
     * @param n The index of the Catalan number to compute (must be non-negative).
     * @return The nth Catalan number. Returns -1 for invalid input.
     */
    public long findCatalan(int n) {
        // Step 1: Handle invalid input. Catalan numbers are defined for non-negative integers.
        if (n < 0) {
            return -1;
        }

        // Step 2: Create the DP array to store Catalan numbers.
        // We use 'long' because the numbers grow very quickly and will overflow 'int'.
        long[] catalan = new long[n + 1];

        // Step 3: Initialize the base case, C(0) = 1.
        catalan[0] = 1;

        // Step 4: Fill the DP table iteratively to find C(1) through C(n).
        // The outer loop calculates the value for catalan[i].
        for (int i = 1; i <= n; i++) {
            // Initialize the current catalan number to 0 before summing.
            catalan[i] = 0;
            
            // Step 5: Apply the summation formula using an inner loop.
            // C(i) = Σ [from j=0 to i-1] ( C(j) * C(i-1-j) )
            for (int j = 0; j < i; j++) {
                catalan[i] += catalan[j] * catalan[i - 1 - j];
            }
        }

        // Step 6: The nth Catalan number is now stored at the nth index of our array.
        return catalan[n];
    }

    public static void main(String[] args) {
        CatalanNumbersBhumika cn = new CatalanNumbersBhumika();
        int limit = 15;

        System.out.println("The first " + limit + " Catalan numbers are:");
        for (int i = 0; i < limit; i++) {
            System.out.println("C(" + i + ") = " + cn.findCatalan(i));
        }
    }
}
