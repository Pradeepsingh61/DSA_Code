class Solution {
public:
    // Recursive function to calculate the minimum number of operations (insert, delete, replace)
    // to convert the substring word1[0..n-1] to word2[0..m-1]
    // dp[n][m] stores the result of subproblem for word1[0..n-1] and word2[0..m-1]
    int f(string word1, string word2, int n, int m, vector<vector<int>>& dp) {
        // Base case: If word1 is empty, we need to insert all characters of word2
        if (n == 0) {
            return dp[n][m] = m;  // Insert m characters
        }

        // Base case: If word2 is empty, we need to delete all characters of word1
        if (m == 0) {
            return dp[n][m] = n;  // Delete n characters
        }

        // If the last characters of both substrings are the same, no operation is needed
        if (word1[n - 1] == word2[m - 1]) {
            return dp[n][m] = f(word1, word2, n - 1, m - 1, dp);
        }

        // If the subproblem has already been solved, return the cached result from dp
        if (dp[n][m] != -1) {
            return dp[n][m];
        }

        // Initialize variables to store the minimum number of operations
        long long int delet = INT_MAX;    // Case for delete operation
        long long int insert = INT_MAX;   // Case for insert operation
        long long int replace = INT_MAX;  // Case for replace operation

        // Case 1: Delete the current character of word1 and solve for the smaller subproblem
        delet = f(word1, word2, n - 1, m, dp);

        // Case 2: Insert the current character of word2 into word1 and solve for the smaller subproblem
        insert = f(word1, word2, n, m - 1, dp);

        // Case 3: Replace the current character of word1 with the character of word2 and solve for the smaller subproblem
        replace = f(word1, word2, n - 1, m - 1, dp);

        // Store the result for this subproblem in dp and return the minimum number of operations + 1
        return dp[n][m] = min({delet, insert, replace}) + 1;
    }

    // Main function to find the minimum number of operations to convert word1 into word2
    int minDistance(string word1, string word2) {
        int n = word1.size();  // Length of word1
        int m = word2.size();  // Length of word2

        // Create a dp table of size (n+1)x(m+1), initialized with -1 to indicate unsolved subproblems
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        // Call the recursive function to solve the problem for word1[0..n-1] and word2[0..m-1]
        int ans = f(word1, word2, n, m, dp);

        // Return the result
        return ans;
    }
};
