/**
 * Edit Distance Algorithm
 *
 * Description: Finds the minimum number of operations (insert, delete, or substitute)
 * required to convert one string into another using Dynamic Programming.
 * Time Complexity: O(m*n), where m and n are the lengths of the two strings.
 * Space Complexity: O(m*n) for the DP table.
 */
public class EditDistance {

    /**
     * Calculates the minimum edit distance between two words.
     *
     * @param word1 The first word.
     * @param word2 The second word.
     * @return The minimum number of operations to transform word1 to word2.
     */
    public static int minDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();

        // Create a DP table to store results of subproblems.
        // dp[i][j] will be the edit distance of the first i chars of word1 and first j chars of word2.
        int[][] dp = new int[m + 1][n + 1];

        // Fill the DP table in a bottom-up manner.
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                // If the first string is empty, the only option is to insert all characters of the second string.
                if (i == 0) {
                    dp[i][j] = j;
                }
                // If the second string is empty, the only option is to remove all characters of the first string.
                else if (j == 0) {
                    dp[i][j] = i;
                }
                // If the last characters are the same, no new operation is needed.
                // The cost is the same as the cost for the strings without the last character.
                else if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // If the last characters are different, we must perform an operation.
                // We take the minimum cost of the three possible operations:
                // 1. Insert: dp[i][j-1]
                // 2. Delete: dp[i-1][j]
                // 3. Substitute: dp[i-1][j-1]
                else {
                    dp[i][j] = 1 + Math.min(dp[i][j - 1],      // Insert
                                           Math.min(dp[i - 1][j],      // Remove
                                                    dp[i - 1][j - 1])); // Replace
                }
            }
        }

        return dp[m][n];
    }

    // Test cases
    public static void main(String[] args) {
        // Test case 1: LeetCode example
        String word1 = "horse";
        String word2 = "ros";
        System.out.println("Edit distance between '" + word1 + "' and '" + word2 + "': " + minDistance(word1, word2)); // Expected Output: 3

        // Test case 2: Another LeetCode example
        String word3 = "intention";
        String word4 = "execution";
        System.out.println("Edit distance between '" + word3 + "' and '" + word4 + "': " + minDistance(word3, word4)); // Expected Output: 5

        // Test case 3: One string is empty
        String word5 = "apple";
        String word6 = "";
        System.out.println("Edit distance between '" + word5 + "' and '" + word6 + "': " + minDistance(word5, word6)); // Expected Output: 5

        // Test case 4: Both strings are identical
        String word7 = "test";
        String word8 = "test";
        System.out.println("Edit distance between '" + word7 + "' and '" + word8 + "': " + minDistance(word7, word8)); // Expected Output: 0
    }
}