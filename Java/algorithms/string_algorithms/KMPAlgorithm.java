/**
 * Algorithm: KMP (Knuth-Morris-Pratt) Pattern Matching Algorithm
 * Description: Efficient string searching algorithm that finds occurrences of a pattern
 *              within a text string. Uses preprocessing to avoid unnecessary comparisons
 *              by utilizing information from previous match attempts.
 * 
 * Time Complexity: O(n + m) where n = text length, m = pattern length
 * Space Complexity: O(m) for the LPS (Longest Proper Prefix which is also Suffix) array
 * 
 * Advantages over naive pattern matching:
 * - Linear time complexity instead of O(n*m)
 * - Never backtracks in the text string
 * - Efficient for patterns with repeating sub-patterns
 * - Preprocessing step enables smart shifting of pattern
 * 
 * Use Cases:
 * - Text editors (find and replace functionality)
 * - DNA sequence matching in bioinformatics
 * - Plagiarism detection systems
 * - Search engines and text processing
 * - Network intrusion detection systems
 *
 * @author DSA_Code Contributors
 * @version 1.0
 * @since 2025-10-09
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class KMPAlgorithm {

    /**
     * Searches for all occurrences of a pattern in the given text using KMP algorithm.
     *
     * @param text the text string to search in
     * @param pattern the pattern string to search for
     * @return List of starting indices where pattern is found (empty list if not found)
     * @throws IllegalArgumentException if text or pattern is null or pattern is empty
     */
    public static List<Integer> search(String text, String pattern) {
        // Input validation
        if (text == null || pattern == null) {
            throw new IllegalArgumentException("Text and pattern cannot be null");
        }
        if (pattern.isEmpty()) {
            throw new IllegalArgumentException("Pattern cannot be empty");
        }

        List<Integer> occurrences = new ArrayList<>();

        // Handle edge case: pattern longer than text
        if (pattern.length() > text.length()) {
            return occurrences;
        }

        // Compute LPS (Longest Proper Prefix which is also Suffix) array
        int[] lps = computeLPS(pattern);

        int i = 0; // index for text
        int j = 0; // index for pattern

        // Scan through the text
        while (i < text.length()) {
            // Characters match - advance both pointers
            if (text.charAt(i) == pattern.charAt(j)) {
                i++;
                j++;
            }

            // Found complete pattern match
            if (j == pattern.length()) {
                occurrences.add(i - j); // Record starting index
                j = lps[j - 1]; // Continue searching with LPS information
            }
            // Mismatch after some matches
            else if (i < text.length() && text.charAt(i) != pattern.charAt(j)) {
                if (j != 0) {
                    // Use LPS to avoid re-matching already matched characters
                    j = lps[j - 1];
                } else {
                    // No match at all, move to next character in text
                    i++;
                }
            }
        }

        return occurrences;
    }

    /**
     * Computes the LPS (Longest Proper Prefix which is also Suffix) array for the pattern.
     * This preprocessing step is the key to KMP's efficiency.
     * 
     * LPS[i] = length of the longest proper prefix of pattern[0..i] which is also a suffix
     *
     * Example: For pattern "ABABC"
     * - LPS[0] = 0 (base case)
     * - LPS[1] = 0 (no proper prefix)
     * - LPS[2] = 1 ("A" is both prefix and suffix of "ABA")
     * - LPS[3] = 2 ("AB" is both prefix and suffix of "ABAB")
     * - LPS[4] = 0 (no proper prefix of "ABABC" is also a suffix)
     *
     * @param pattern the pattern string to preprocess
     * @return LPS array where lps[i] stores length of longest proper prefix which is also suffix
     */
    private static int[] computeLPS(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];

        // LPS[0] is always 0 (no proper prefix/suffix for single character)
        lps[0] = 0;

        int len = 0; // length of previous longest prefix suffix
        int i = 1;

        // Build LPS array by comparing characters
        while (i < m) {
            if (pattern.charAt(i) == pattern.charAt(len)) {
                // Characters match - extend the current prefix-suffix
                len++;
                lps[i] = len;
                i++;
            } else {
                // Mismatch after some matches
                if (len != 0) {
                    // Try smaller prefix-suffix
                    // This is the key optimization - we don't start from 0
                    len = lps[len - 1];
                } else {
                    // No match possible
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    /**
     * Finds the first occurrence of pattern in text.
     *
     * @param text the text string to search in
     * @param pattern the pattern string to search for
     * @return index of first occurrence, or -1 if not found
     */
    public static int searchFirst(String text, String pattern) {
        List<Integer> occurrences = search(text, pattern);
        return occurrences.isEmpty() ? -1 : occurrences.get(0);
    }

    /**
     * Checks if pattern exists in text.
     *
     * @param text the text string to search in
     * @param pattern the pattern string to search for
     * @return true if pattern is found, false otherwise
     */
    public static boolean contains(String text, String pattern) {
        return searchFirst(text, pattern) != -1;
    }

    /**
     * Counts total number of occurrences of pattern in text.
     *
     * @param text the text string to search in
     * @param pattern the pattern string to search for
     * @return count of occurrences
     */
    public static int countOccurrences(String text, String pattern) {
        return search(text, pattern).size();
    }

    /**
     * Prints detailed information about the search process.
     */
    private static void printSearchDetails(String text, String pattern, List<Integer> occurrences) {
        System.out.println("Text: \"" + text + "\"");
        System.out.println("Pattern: \"" + pattern + "\"");
        System.out.println("LPS Array: " + Arrays.toString(computeLPS(pattern)));
        
        if (occurrences.isEmpty()) {
            System.out.println("Result: Pattern not found");
        } else {
            System.out.println("Result: Pattern found at indices: " + occurrences);
            System.out.println("Total occurrences: " + occurrences.size());
            
            // Highlight matches in text (simple visualization without handling overlaps)
            System.out.print("Matches: ");
            for (int i = 0; i < occurrences.size(); i++) {
                if (i > 0) System.out.print(", ");
                System.out.print("index " + occurrences.get(i));
            }
            System.out.println();
        }
        System.out.println();
    }

    /**
     * Comprehensive test cases demonstrating KMP algorithm functionality.
     */
    public static void main(String[] args) {
        System.out.println("=== KMP (Knuth-Morris-Pratt) Pattern Matching Algorithm ===\n");

        // Test Case 1: Simple pattern matching
        System.out.println("Test Case 1: Simple Pattern Match");
        String text1 = "ABABDABACDABABCABAB";
        String pattern1 = "ABABCABAB";
        List<Integer> result1 = search(text1, pattern1);
        printSearchDetails(text1, pattern1, result1);

        // Test Case 2: Multiple occurrences
        System.out.println("Test Case 2: Multiple Occurrences");
        String text2 = "AABAACAADAABAABA";
        String pattern2 = "AABA";
        List<Integer> result2 = search(text2, pattern2);
        printSearchDetails(text2, pattern2, result2);

        // Test Case 3: Overlapping patterns
        System.out.println("Test Case 3: Overlapping Patterns");
        String text3 = "AAAA";
        String pattern3 = "AA";
        List<Integer> result3 = search(text3, pattern3);
        printSearchDetails(text3, pattern3, result3);

        // Test Case 4: Pattern not found
        System.out.println("Test Case 4: Pattern Not Found");
        String text4 = "ABCDEFGH";
        String pattern4 = "XYZ";
        List<Integer> result4 = search(text4, pattern4);
        printSearchDetails(text4, pattern4, result4);

        // Test Case 5: Pattern at the beginning
        System.out.println("Test Case 5: Pattern at Beginning");
        String text5 = "HELLO WORLD";
        String pattern5 = "HELLO";
        List<Integer> result5 = search(text5, pattern5);
        printSearchDetails(text5, pattern5, result5);

        // Test Case 6: Pattern at the end
        System.out.println("Test Case 6: Pattern at End");
        String text6 = "HELLO WORLD";
        String pattern6 = "WORLD";
        List<Integer> result6 = search(text6, pattern6);
        printSearchDetails(text6, pattern6, result6);

        // Test Case 7: Single character pattern
        System.out.println("Test Case 7: Single Character Pattern");
        String text7 = "ABACABAD";
        String pattern7 = "A";
        List<Integer> result7 = search(text7, pattern7);
        printSearchDetails(text7, pattern7, result7);

        // Test Case 8: Pattern equals text
        System.out.println("Test Case 8: Pattern Equals Text");
        String text8 = "EXACT";
        String pattern8 = "EXACT";
        List<Integer> result8 = search(text8, pattern8);
        printSearchDetails(text8, pattern8, result8);

        // Test Case 9: DNA sequence matching (practical example)
        System.out.println("Test Case 9: DNA Sequence Matching");
        String dna = "GCATCGCAGAGAGTATACAGTACG";
        String sequence = "AGAGAG";
        List<Integer> dnaResult = search(dna, sequence);
        printSearchDetails(dna, sequence, dnaResult);

        // Test Case 10: Utility methods
        System.out.println("Test Case 10: Utility Methods");
        String text10 = "The quick brown fox jumps over the lazy dog";
        String pattern10 = "the";
        System.out.println("Text: \"" + text10 + "\"");
        System.out.println("Pattern: \"" + pattern10 + "\"");
        System.out.println("First occurrence: " + searchFirst(text10, pattern10));
        System.out.println("Contains pattern: " + contains(text10, pattern10));
        System.out.println("Total count: " + countOccurrences(text10, pattern10));
        System.out.println();

        // Test Case 11: Error handling - null text
        System.out.println("Test Case 11: Error Handling (Null Text)");
        try {
            search(null, "pattern");
            System.out.println("ERROR: Should have thrown exception!");
        } catch (IllegalArgumentException e) {
            System.out.println("Correctly caught exception: " + e.getMessage());
        }
        System.out.println();

        // Test Case 12: Error handling - empty pattern
        System.out.println("Test Case 12: Error Handling (Empty Pattern)");
        try {
            search("text", "");
            System.out.println("ERROR: Should have thrown exception!");
        } catch (IllegalArgumentException e) {
            System.out.println("Correctly caught exception: " + e.getMessage());
        }
        System.out.println();

        // Test Case 13: Pattern longer than text
        System.out.println("Test Case 13: Pattern Longer Than Text");
        String text13 = "SHORT";
        String pattern13 = "VERYLONGPATTERN";
        List<Integer> result13 = search(text13, pattern13);
        printSearchDetails(text13, pattern13, result13);

        System.out.println("=== All tests completed successfully! ===");
    }
}
