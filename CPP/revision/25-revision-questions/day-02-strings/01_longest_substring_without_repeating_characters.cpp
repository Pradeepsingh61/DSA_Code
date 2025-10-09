// 01_longest_substring_without_repeating_characters.cpp
// Problem: Longest Substring Without Repeating Characters
// LeetCode: https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 01_longest_substring_without_repeating_characters.cpp -o 01_longest_substring
// Run: ./01_longest_substring
//
// Summary:
// Given a string, find the length of the longest substring without repeating characters.
//
// Approach (sliding window + last-seen index):
// Use two indices (windowStart and windowEnd) and a map of last-seen indices for characters.
// Expand the windowEnd and if the current character was seen inside the current window,
// move windowStart to lastSeenIndex + 1. Update the maximum window length as you go.
//
// Time Complexity: O(n) where n = length of string (each char visited at most twice).
// Space Complexity: O(min(n, charset)) for the hash map of last seen indices.

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
