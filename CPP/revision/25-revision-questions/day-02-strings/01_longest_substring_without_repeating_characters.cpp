// 01_longest_substring_without_repeating_characters.cpp
//
// 🔍 Algorithm: Longest Substring Without Repeating Characters
// Description:
//   Finds the length of the longest substring in a given string 
//   that contains no repeating characters.
//   Uses the Sliding Window technique with a hash map to track 
//   character indices and adjust window boundaries efficiently.
//
// Use Case:
//   Commonly used to analyze substring patterns or find unique 
//   character sequences in data streams.
//
// Time Complexity: O(n) — each character visited once.
// Space Complexity: O(1) — constant size (at most 256 chars).
//
// LeetCode: https://leetcode.com/problems/longest-substring-without-repeating-characters/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestUniqueSubstring(const string &s) {
    unordered_map<char,int> lastSeen;
    int maxLength = 0;
    int windowStart = 0;

    for (int windowEnd = 0; windowEnd < (int)s.size(); ++windowEnd) {
        char currentChar = s[windowEnd];
        if (lastSeen.find(currentChar) != lastSeen.end()) {
            // If this character appeared inside current window, move start
            if (lastSeen[currentChar] >= windowStart) {
                windowStart = lastSeen[currentChar] + 1;
            }
        }
        lastSeen[currentChar] = windowEnd;
        int windowLength = windowEnd - windowStart + 1;
        if (windowLength > maxLength) maxLength = windowLength;
    }
    return maxLength;
}

int main() {
    cout << "Longest Substring Without Repeating Characters\n";
    cout << "Enter a single-line string and press Enter:\n";
    string input;
    if (!getline(cin, input)) return 0;

    int result = lengthOfLongestUniqueSubstring(input);
    cout << "Length: " << result << "\n";
    return 0;
}

/*
Example:
Input:
abcabcbb
Output:
Length: 3  (substring "abc")
*/
