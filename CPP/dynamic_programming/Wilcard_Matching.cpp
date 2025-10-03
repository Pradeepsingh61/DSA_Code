/*
 * Wildcard Matching Algorithm
 * 
 * Description:
 * Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for:
 * - '?' Matches any single character
 * - '*' Matches any sequence of characters (including the empty sequence)
 * 
 * The matching should cover the entire input string (not partial).
 *
 * Approach:
 * We use recursion with the following rules:
 * 1. If both string and pattern are exhausted, return true.
 * 2. If pattern is exhausted but string remains, return false.
 * 3. If string is exhausted but pattern remains, check if remaining characters in pattern are all '*'.
 * 4. If characters match OR pattern has '?', move both indices back by 1.
 * 5. If pattern has '*', try two options:
 *      - Treat '*' as matching one character (move string index back by 1, keep pattern index same).
 *      - Treat '*' as matching empty (move pattern index back by 1, keep string index same).
 *
 * Time Complexity: Exponential in worst case (O(2^(m+n))) without memoization,
 *                  since '*' can branch into two recursive calls.
 *                  With DP memoization, this can be optimized to O(m*n).
 *
 * Space Complexity: O(m+n) recursion stack (without memoization).
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool solve(int index1, int index2, string &text, string &pattern) {
        // Both strings exhausted
        if (index1 < 0 && index2 < 0) return true;

        // Pattern exhausted, text remains
        if (index2 < 0 && index1 >= 0) return false;

        // Text exhausted, check if remaining pattern is all '*'
        if (index1 < 0 && index2 >= 0) {
            for (int i = 0; i <= index2; i++) {
                if (pattern[i] != '*') return false;
            }
            return true;
        }

        // Characters match OR pattern has '?'
        if (text[index1] == pattern[index2] || pattern[index2] == '?') {
            return solve(index1 - 1, index2 - 1, text, pattern);
        }

        // If pattern has '*': try both possibilities
        if (pattern[index2] == '*') {
            return solve(index1 - 1, index2, text, pattern)   // '*' matches one char
                || solve(index1, index2 - 1, text, pattern); // '*' matches empty
        }

        return false;
    }

    bool isMatch(string s, string p) {
        int n1 = s.size();
        int n2 = p.size();
        return solve(n1 - 1, n2 - 1, s, p);
    }
};

// Main function with test cases
int main() {
    Solution sol;

    // Test Case 1
    cout << "Test Case 1:" << endl;
    string s1 = "aa", p1 = "a";
    cout << "String: " << s1 << ", Pattern: " << p1 << endl;
    cout << "Match: " << (sol.isMatch(s1, p1) ? "true" : "false") << endl << endl; // false

    // Test Case 2
    cout << "Test Case 2:" << endl;
    string s2 = "aa", p2 = "*";
    cout << "String: " << s2 << ", Pattern: " << p2 << endl;
    cout << "Match: " << (sol.isMatch(s2, p2) ? "true" : "false") << endl << endl; // true

    // Test Case 3
    cout << "Test Case 3:" << endl;
    string s3 = "cb", p3 = "?a";
    cout << "String: " << s3 << ", Pattern: " << p3 << endl;
    cout << "Match: " << (sol.isMatch(s3, p3) ? "true" : "false") << endl << endl; // false

    // Test Case 4
    cout << "Test Case 4:" << endl;
    string s4 = "adceb", p4 = "*a*b";
    cout << "String: " << s4 << ", Pattern: " << p4 << endl;
    cout << "Match: " << (sol.isMatch(s4, p4) ? "true" : "false") << endl << endl; // true

    // Test Case 5
    cout << "Test Case 5:" << endl;
    string s5 = "acdcb", p5 = "a*c?b";
    cout << "String: " << s5 << ", Pattern: " << p5 << endl;
    cout << "Match: " << (sol.isMatch(s5, p5) ? "true" : "false") << endl << endl; // false

    return 0;
}
