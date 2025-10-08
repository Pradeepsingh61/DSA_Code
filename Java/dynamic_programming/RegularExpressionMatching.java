public class RegularExpressionMatching {

    /**
     * Determines if an input string `s` matches a given pattern `p` that supports '.' and '*'.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * This problem is solved using a 2D Dynamic Programming approach. We create a boolean
     * table `dp[i][j]` where `i` corresponds to the length of the string prefix and `j`
     * corresponds to the length of the pattern prefix.
     *
     * State Definition:
     * `dp[i][j]` is `true` if the first `i` characters of the string `s` can be matched by
     * the first `j` characters of the pattern `p`. Otherwise, it is `false`.
     * The table size will be (s.length() + 1) x (p.length() + 1) to handle empty prefixes.
     *
     * Base Case:
     * - `dp[0][0] = true`: An empty string matches an empty pattern.
     * - `dp[0][j]`: An empty string `s` can be matched by a pattern `p` only if `p` consists
     * of characters followed by `*`. For example, `a*`, `a*b*`, `c*a*b*` can all match
     * an empty string. So, if `p.charAt(j-1) == '*'`, `dp[0][j]` depends on `dp[0][j-2]`.
     *
     * State Transition Logic:
     * We fill the table by iterating through `s` (i) and `p` (j).
     * Let `s_char` be `s.charAt(i-1)` and `p_char` be `p.charAt(j-1)`.
     *
     * 1. If `p_char` is a normal character or '.':
     * - If `p_char == s_char` or `p_char == '.'`, the current characters match. The overall
     * match then depends on whether the prefixes *before* these characters matched.
     * So, `dp[i][j] = dp[i-1][j-1]`.
     * - Otherwise, there is no match, and `dp[i][j]` remains `false`.
     *
     * 2. If `p_char` is '*':
     * The `*` modifies its preceding character, `p.charAt(j-2)`. It means "zero or more"
     * of the preceding element. We have two choices:
     *
     * a) Treat '*' as matching ZERO occurrences of the preceding element.
     * In this case, we effectively ignore the `char*` part of the pattern (e.g., in "a*b", we
     * ignore "a*"). The match depends on the pattern up to `j-2`.
     * So, `dp[i][j] = dp[i][j-2]`.
     *
     * b) Treat '*' as matching ONE OR MORE occurrences of the preceding element.
     * This is only possible if the current string character `s_char` matches the
     * preceding pattern character `p.charAt(j-2)` (or if it's a '.'). If they match,
     * it means `s_char` is another character consumed by the `*`. The result then
     * depends on whether the string prefix of length `i-1` matched the same pattern
     * prefix of length `j`.
     * So, the condition is `(s_char == p.charAt(j-2) || p.charAt(j-2) == '.')`
     * and we check `dp[i-1][j]`.
     *
     * Since `*` allows either choice, `dp[i][j]` is `true` if either (a) or (b) is `true`.
     *
     * Final Answer: The result is `dp[s.length()][p.length()]`.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Let M be the length of the string `s` and N be the length of the pattern `p`.
     *
     * Time Complexity: O(M * N)
     * We fill a 2D DP table of size (M+1) x (N+1), and each cell is computed in constant time.
     *
     * Space Complexity: O(M * N)
     * This is the space required to store the DP table.
     *
     * @param s The input string.
     * @param p The pattern.
     * @return `true` if `s` is fully matched by `p`, `false` otherwise.
     */
    public boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();

        // Step 1: Create the DP table.
        boolean[][] dp = new boolean[m + 1][n + 1];

        // Step 2: Initialize the base case - an empty string matches an empty pattern.
        dp[0][0] = true;

        // Step 3: Handle patterns that can match an empty string (like a*, a*b*, etc.).
        // `j` starts from 2 because a single '*' cannot match anything and needs a preceding char.
        for (int j = 2; j <= n; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Step 4: Fill the rest of the DP table.
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sChar = s.charAt(i - 1);
                char pChar = p.charAt(j - 1);

                // Case 1: The pattern character is NOT a '*'
                if (pChar != '*') {
                    // Check if the current characters match (or if pattern is '.')
                    // and if the previous prefixes matched.
                    if (pChar == '.' || pChar == sChar) {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                } else { // Case 2: The pattern character IS a '*'
                    // Subcase 2.1: The '*' matches ZERO occurrences of the preceding element.
                    // In this case, we look at the pattern two steps back (ignoring char*).
                    dp[i][j] = dp[i][j - 2];

                    // Subcase 2.2: The '*' matches ONE OR MORE occurrences.
                    // This is only possible if the current string char matches the char before '*'.
                    char prevPChar = p.charAt(j - 2);
                    if (prevPChar == '.' || prevPChar == sChar) {
                        // If they match, we check if either the zero-occurrence case was true
                        // OR if the one-or-more-occurrence case is true. The latter depends
                        // on the result for the previous string char with the same pattern.
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        // Step 5: The final answer is in the bottom-right corner of the table.
        return dp[m][n];
    }

    public static void main(String[] args) {
        RegularExpressionMatching rem = new RegularExpressionMatching();

        // Example 1: Simple '*' usage
        System.out.println("s = \"aa\", p = \"a*\" -> " + rem.isMatch("aa", "a*")); // Expected: true

        // Example 2: '.' usage with '*'
        System.out.println("s = \"ab\", p = \".*\" -> " + rem.isMatch("ab", ".*")); // Expected: true

        // Example 3: More complex pattern with '*' matching zero elements
        System.out.println("s = \"aab\", p = \"c*a*b\" -> " + rem.isMatch("aab", "c*a*b")); // Expected: true

        // Example 4: Mismatch case
        System.out.println("s = \"mississippi\", p = \"mis*is*p*.\" -> " + rem.isMatch("mississippi", "mis*is*p*.")); // Expected: false
        
        // Example 5: Simple mismatch
        System.out.println("s = \"aa\", p = \"a\" -> " + rem.isMatch("aa", "a")); // Expected: false
    }
}