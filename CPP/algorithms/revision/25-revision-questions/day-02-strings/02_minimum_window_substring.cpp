// 02_minimum_window_substring.cpp
//
// 🔍 Algorithm: Minimum Window Substring
// Description:
//   Finds the smallest substring in `source` that contains all 
//   characters of `target` (including duplicates).
//   Uses a Sliding Window approach combined with frequency maps 
//   to expand and contract the window optimally.
//
// Use Case:
//   Useful in text search problems, DNA sequence matching, 
//   or when finding minimal segments containing specific data.
//
// Time Complexity: O(|S| + |T|)
// Space Complexity: O(|T|)
//
// LeetCode: https://leetcode.com/problems/minimum-window-substring/


#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow(const string &source, const string &target) {
    if (target.empty() || source.empty() || source.size() < target.size()) return "";

    unordered_map<char,int> need;
    for (char c : target) need[c]++;

    int required = need.size();       // distinct characters needed
    int formed = 0;                   // how many distinct characters currently satisfy required count
    unordered_map<char,int> windowCounts;

    int left = 0, right = 0;
    int bestLeft = 0;
    int bestLen = INT_MAX;

    while (right < (int)source.size()) {
        char c = source[right];
        windowCounts[c]++;

        // If current char count matches the required count, we've satisfied one distinct char
        if (need.count(c) && windowCounts[c] == need[c]) {
            formed++;
        }

        // When all required chars are satisfied, try to shrink from the left
        while (left <= right && formed == required) {
            if (right - left + 1 < bestLen) {
                bestLen = right - left + 1;
                bestLeft = left;
            }

            char leftChar = source[left];
            windowCounts[leftChar]--;
            if (need.count(leftChar) && windowCounts[leftChar] < need[leftChar]) {
                formed--;
            }
            left++;
        }

        right++;
    }

    if (bestLen == INT_MAX) return "";
    return source.substr(bestLeft, bestLen);
}

int main() {
    cout << "Minimum Window Substring\n";
    cout << "Input format (two lines):\nS\nT\n\nEnter S (source string) and T (target string) each on a new line:\n";

    string S, T;
    if (!getline(cin, S)) return 0;
    if (!getline(cin, T)) return 0;

    string answer = minWindow(S, T);
    if (answer.empty()) {
        cout << "No valid window found\n";
    } else {
        cout << "Minimum window: " << answer << "\n";
    }
    return 0;
}

/*
Example:
S = "ADOBECODEBANC"
T = "ABC"
Output: "BANC"
*/
