class PalindromePartitioning {

    /**
     * Calculates the minimum number of cuts needed to partition a string such that every
     * substring of the partition is a palindrome.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * This problem asks for the minimum cuts, which suggests an optimization problem that is
     * well-suited for Dynamic Programming. The solution involves two main DP components.
     *
     * STAGE 1: PRE-COMPUTING ALL PALINDROMIC SUBSTRINGS
     * Before we can find the minimum cuts, we need an efficient way to check if any given
     * substring is a palindrome. We can pre-compute this information.
     *
     * State Definition:
     * We use a 2D boolean table `isPalindrome[i][j]`, where `isPalindrome[i][j]` is `true`
     * if the substring from index `i` to `j` (inclusive) is a palindrome, and `false` otherwise.
     *
     * Logic:
     * - A single character is always a palindrome (`isPalindrome[i][i] = true`).
     * - A substring of length > 1 from `i` to `j` is a palindrome if:
     * 1. The characters at the ends match (`s.charAt(i) == s.charAt(j)`).
     * 2. The inner substring from `i+1` to `j-1` is also a palindrome.
     * We can fill this table in O(N^2) time.
     *
     * STAGE 2: FINDING THE MINIMUM CUTS
     * With our palindrome information ready, we can now find the minimum cuts.
     *
     * State Definition:
     * We use a 1D integer array `cuts[i]`, where `cuts[i]` stores the minimum number of
     * cuts needed for the prefix of the string of length `i+1` (i.e., `s.substring(0, i+1)`).
     *
     * Logic:
     * - Initialize `cuts[i] = i`, which represents the worst-case scenario where we cut
     * after every character (e.g., "abc" -> "a|b|c" needs 2 cuts for a prefix of length 3).
     * - We then iterate `i` from 0 to the end of the string. For each `i`, we check all
     * substrings ending at `i`. Let's say a substring starts at `j` (where `0 <= j <= i`).
     * - If `s.substring(j, i+1)` is a palindrome (which we can check in O(1) from our table):
     * - It means the entire segment from `j` to `i` needs 0 cuts.
     * - The total cuts needed for the prefix up to `i` would be `1 +` (the minimum cuts
     * needed for the prefix ending at `j-1`).
     * - We update `cuts[i]` with the minimum value found among all such valid `j`.
     * - A special case: if the entire prefix `s.substring(0, i+1)` is a palindrome (`j=0`),
     * then `cuts[i]` is 0.
     *
     * Final Answer: The result is `cuts[s.length() - 1]`.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Let N be the length of the string `s`.
     *
     * Time Complexity: O(N^2)
     * - Stage 1 (building the `isPalindrome` table) takes O(N^2).
     * - Stage 2 (building the `cuts` array) has two nested loops, also taking O(N^2).
     * - Total time complexity is O(N^2) + O(N^2) = O(N^2).
     *
     * Space Complexity: O(N^2)
     * - The `isPalindrome` table requires O(N^2) space.
     * - The `cuts` array requires O(N) space.
     * - The dominant factor is the 2D table, so the total space complexity is O(N^2).
     *
     * @param s The input string.
     * @return The minimum number of cuts required.
     */
    public int minCuts(String s) {
        // Step 1: Handle edge cases.
        if (s == null || s.length() <= 1) {
            return 0;
        }
        int n = s.length();

        // --- STAGE 1: Pre-compute the palindrome table ---
        // isPalindrome[i][j] is true if substring s[i..j] is a palindrome.
        boolean[][] isPalindrome = new boolean[n][n];

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                // Check if characters at ends match and if the inner substring is also a palindrome.
                if (s.charAt(i) == s.charAt(j) && (len <= 2 || isPalindrome[i + 1][j - 1])) {
                    isPalindrome[i][j] = true;
                }
            }
        }

        // --- STAGE 2: Calculate the minimum cuts using the palindrome table ---
        // cuts[i] = minimum cuts for the prefix s[0..i].
        int[] cuts = new int[n];

        for (int i = 0; i < n; i++) {
            // Check if the whole prefix s[0..i] is a palindrome.
            if (isPalindrome[0][i]) {
                cuts[i] = 0; // 0 cuts needed.
            } else {
                // Worst-case: cut after every character.
                cuts[i] = i;
                // Find the minimum cuts by checking all possible last palindromic substrings.
                // If s[j..i] is a palindrome, then we can make a cut after s[j-1].
                for (int j = 1; j <= i; j++) {
                    if (isPalindrome[j][i]) {
                        // The number of cuts would be 1 (for the new cut) + cuts[j-1] (for the prefix).
                        cuts[i] = Math.min(cuts[i], 1 + cuts[j - 1]);
                    }
                }
            }
        }

        // The final answer is the minimum cuts for the entire string s[0..n-1].
        return cuts[n - 1];
    }

    public static void main(String[] args) {
        PalindromePartitioning pp = new PalindromePartitioning();

        // Example 1: "aab" -> "aa" | "b" -> 1 cut
        String s1 = "aab";
        System.out.println("The minimum cuts for \"" + s1 + "\" is: " + pp.minCuts(s1)); // Expected: 1

        // Example 2: "racecar" is already a palindrome
        String s2 = "racecar";
        System.out.println("The minimum cuts for \"" + s2 + "\" is: " + pp.minCuts(s2)); // Expected: 0

        // Example 3: A more complex case
        String s3 = "ababbbabbababa";
        System.out.println("The minimum cuts for \"" + s3 + "\" is: " + pp.minCuts(s3)); // Expected: 3

        // Example 4: All different characters
        String s4 = "abcde";
        System.out.println("The minimum cuts for \"" + s4 + "\" is: " + pp.minCuts(s4)); // Expected: 4
    }
}