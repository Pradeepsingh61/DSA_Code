// 03_longest_consecutive_sequence.cpp
// Problem: Longest Consecutive Sequence (Hashing / unordered_set)
// LeetCode: https://leetcode.com/problems/longest-consecutive-sequence/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 03_longest_consecutive_sequence.cpp -o 03_longest_consecutive_sequence
// Run: ./03_longest_consecutive_sequence
//
// 🧩 Summary:
// Given an unsorted integer array 'numbers', return the length of the longest
// sequence of consecutive integers (the sequence elements can be in any order).
//
// 🧠 Approach (Hashing):
// 1. Insert all numbers into an unordered_set for O(1) average lookup.
// 2. For each number, if (number - 1) is NOT in the set, treat this number
//    as the start of a potential sequence. Then walk forward (number+1, number+2, ...)
//    counting how long the sequence continues.
// 3. Track the maximum length found.
//
// ✅ Correctness:
// By only starting counts at sequence starts (no predecessor), we avoid
// counting the same sequence multiple times. Each element is checked at most
// twice (presence check and forward walk across its sequence once), giving
// linear average time complexity.
//
// ⏱️ Complexity:
// Time:  O(n) average (due to unordered_set lookups)
// Space: O(n) for the set
//
// 📘 LeetCode Link: https://leetcode.com/problems/longest-consecutive-sequence/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int longestConsecutiveSequence(const vector<int>& numbers) {
    if (numbers.empty()) return 0;

    unordered_set<int> values(numbers.begin(), numbers.end());
    int bestLength = 0;

    for (int value : numbers) {
        // Only start counting if 'value' is the start of a sequence
        if (values.find(value - 1) == values.end()) {
            int current = value;
            int currentLength = 1;

            // Walk forward while consecutive numbers exist
            while (values.find(current + 1) != values.end()) {
                ++current;
                ++currentLength;
            }

            if (currentLength > bestLength) bestLength = currentLength;
        }
    }

    return bestLength;
}

int main() {
    cout << "🔹 Longest Consecutive Sequence\n";
    cout << "Input format:\n";
    cout << "n\n";
    cout << "a0 a1 a2 ... a(n-1)\n\n";
    cout << "Enter n and numbers:\n";

    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "❌ Invalid input. Exiting.\n";
        return 0;
    }

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) cin >> numbers[i];

    int answer = longestConsecutiveSequence(numbers);

    cout << "\n✅ Longest consecutive sequence length: " << answer << "\n";
    return 0;
}

/*
🔍 Example Input:
6
100 4 200 1 3 2

🧾 Expected Output:
Longest consecutive sequence length: 4
Explanation: the consecutive sequence is 1,2,3,4

📘 LeetCode: https://leetcode.com/problems/longest-consecutive-sequence/

📌 Edge cases:
- Empty array -> length = 0
- All unique non-consecutive numbers -> length = 1
- Negative numbers work fine (e.g., -2,-1,0 -> length 3)
- Duplicates in input do not affect correctness because the set removes them

🧠 Implementation notes:
- unordered_set gives average O(1) membership checks — overall linear time on average.
- This avoids sorting (O(n log n)), which would also solve the problem but is slower.
*/
