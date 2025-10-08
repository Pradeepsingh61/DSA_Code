import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Arrays;

public class WordBreakProblem {

    /**
     * Solves the Word Break problem using Dynamic Programming.
     *
     * ALGORITHM DESCRIPTION:
     * --------------------
     * The Word Break problem asks if a given string `s` can be segmented into a
     * space-separated sequence of one or more words from a given dictionary `wordDict`.
     *
     * DYNAMIC PROGRAMMING APPROACH:
     * We use a 1D boolean array, let's call it `dp`, to solve this problem.
     *
     * State Definition:
     * `dp[i]` will be `true` if the prefix of the string `s` of length `i`
     * (i.e., `s.substring(0, i)`) can be successfully segmented into words from the
     * dictionary. Otherwise, it will be `false`.
     * The size of our DP array will be `s.length() + 1`.
     *
     * Base Case:
     * `dp[0]` is set to `true`. This is a crucial starting point, as an empty string
     * (a prefix of length 0) is always considered segmentable.
     *
     * State Transition Logic:
     * We iterate through the string from length 1 up to `s.length()`. For each length `i`,
     * we check all possible split points `j` before `i` (where `0 <= j < i`).
     * `dp[i]` will be `true` if we can find a split point `j` such that:
     * 1. `dp[j]` is `true` (meaning the prefix `s.substring(0, j)` is already known to be segmentable).
     * 2. The substring from `j` to `i` (i.e., `s.substring(j, i)`) is a word in our dictionary.
     *
     * If both conditions are met for any `j`, we know `s.substring(0, i)` is segmentable,
     * so we set `dp[i] = true` and can break the inner loop to check the next length.
     *
     * Final Answer:
     * The final answer is the value of `dp[s.length()]`, which tells us if the entire
     * string `s` can be segmented.
     *
     * COMPLEXITY ANALYSIS:
     * --------------------
     * Let N be the length of the string `s` and D be the number of characters in the dictionary.
     *
     * Time Complexity: O(N^2)
     * We have two nested loops to fill the DP table. The outer loop runs N times, and the
     * inner loop runs up to N times. Inside the inner loop, substring creation and hash set
     * lookups take, on average, time proportional to the substring length. While a looser
     * analysis might suggest O(N^3), the total work done across all substring operations
     * in the loops averages out, and the complexity is commonly cited as O(N^2).
     *
     * Space Complexity: O(N + D)
     * We use a DP array of size N+1, so that's O(N). We also store the dictionary in a
     * HashSet for efficient lookups, which takes space proportional to the total number
     * of characters in the dictionary, O(D).
     *
     * @param s The input string to be segmented.
     * @param wordDict A list of words that can be used for segmentation.
     * @return `true` if the string can be segmented, `false` otherwise.
     */
    public boolean wordBreak(String s, List<String> wordDict) {
        // Step 1: Create a HashSet from the dictionary for O(1) average time complexity lookups.
        Set<String> wordSet = new HashSet<>(wordDict);
        int n = s.length();

        // Step 2: Create a DP array of size n+1.
        // dp[i] will be true if the prefix s.substring(0, i) can be segmented.
        boolean[] dp = new boolean[n + 1];

        // Step 3: Initialize the base case.
        // An empty string (prefix of length 0) is always considered segmentable.
        dp[0] = true;

        // Step 4: Iterate through the string to fill the DP array.
        // 'i' represents the length of the prefix we are checking (from 1 to n).
        for (int i = 1; i <= n; i++) {
            // Step 5: Iterate through all possible split points 'j' before 'i'.
            for (int j = 0; j < i; j++) {
                // Check two conditions:
                // 1. Is the prefix s.substring(0, j) already known to be segmentable? (dp[j])
                // 2. Is the remaining part s.substring(j, i) a word in our dictionary?
                if (dp[j] && wordSet.contains(s.substring(j, i))) {
                    // If both are true, we've found a valid segmentation for the prefix s.substring(0, i).
                    dp[i] = true;
                    // We can break the inner loop and move to the next length 'i'.
                    break;
                }
            }
        }

        // Step 6: The final result is stored in the last element of the DP array.
        return dp[n];
    }

    public static void main(String[] args) {
        WordBreakProblem wb = new WordBreakProblem();

        // Example 1: Should return true
        String s1 = "leetcode";
        List<String> wordDict1 = Arrays.asList("leet", "code");
        System.out.println("String: \"" + s1 + "\"");
        System.out.println("Dictionary: " + wordDict1);
        System.out.println("Can be segmented? " + wb.wordBreak(s1, wordDict1)); // Expected: true
        System.out.println("--------------------");

        // Example 2: Should return true
        String s2 = "applepenapple";
        List<String> wordDict2 = Arrays.asList("apple", "pen");
        System.out.println("String: \"" + s2 + "\"");
        System.out.println("Dictionary: " + wordDict2);
        System.out.println("Can be segmented? " + wb.wordBreak(s2, wordDict2)); // Expected: true
        System.out.println("--------------------");

        // Example 3: Should return false
        String s3 = "catsandog";
        List<String> wordDict3 = Arrays.asList("cats", "dog", "sand", "and", "cat");
        System.out.println("String: \"" + s3 + "\"");
        System.out.println("Dictionary: " + wordDict3);
        System.out.println("Can be segmented? " + wb.wordBreak(s3, wordDict3)); // Expected: false
        System.out.println("--------------------");
    }
}