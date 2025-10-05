/**
 * Algorithm: Manacher's Algorithm
 * Description: Finds the longest palindromic substring in linear time by 
 *              transforming the string and using mirror indices to optimize expansion.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @author Yuvaraj
 * @version 1.0
 * @since 2025-10-05
 */

public class ManacherAlgorithm {

    /**
     * Finds the longest palindromic substring using Manacher's Algorithm.
     *
     * @param s input string
     * @return the longest palindromic substring
     * @throws IllegalArgumentException if input string is null
     *
     * <p>Examples:
     * <pre>
     *     longestPalindrome("babad") → "bab" or "aba"
     *     longestPalindrome("cbbd") → "bb"
     * </pre>
     */
    public static String longestPalindrome(String s) {
        if (s == null) {
            throw new IllegalArgumentException("Input string cannot be null");
        }

        if (s.length() < 2) {
            return s; // Single char or empty string is itself a palindrome
        }

        // Preprocess string: add separators to handle even-length palindromes
        String t = preprocess(s);
        int n = t.length();
        int[] p = new int[n];
        int center = 0, right = 0;

        // Core Manacher's algorithm
        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;

            if (i < right) {
                p[i] = Math.min(right - i, p[mirror]);
            }

            // Expand palindrome centered at i
            while (t.charAt(i + 1 + p[i]) == t.charAt(i - 1 - p[i])) {
                p[i]++;
            }

            // Update center and right boundary
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }

        // Find the maximum length palindrome
        int maxLen = 0;
        int centerIndex = 0;
        for (int i = 1; i < n - 1; i++) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                centerIndex = i;
            }
        }

        int start = (centerIndex - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    /**
     * Preprocesses the string by inserting boundary markers.
     * Example: "abba" -> "^#a#b#b#a#$"
     *
     * @param s input string
     * @return transformed string with boundaries
     */
    private static String preprocess(String s) {
        StringBuilder sb = new StringBuilder("^");
        for (char c : s.toCharArray()) {
            sb.append("#").append(c);
        }
        sb.append("#$");
        return sb.toString();
    }

    /**
     * Test the Manacher's Algorithm implementation.
     */
    public static void main(String[] args) {
        String[] testCases = {"babad", "cbbd", "a", "ac", "abacdfgdcaba"};

        for (String test : testCases) {
            System.out.println("Input: " + test);
            System.out.println("Longest Palindrome: " + longestPalindrome(test));
            System.out.println();
        }

        // Edge cases
        assert longestPalindrome("a").equals("a");
        assert longestPalindrome("").equals("");
        System.out.println("All tests passed!");
    }
}
