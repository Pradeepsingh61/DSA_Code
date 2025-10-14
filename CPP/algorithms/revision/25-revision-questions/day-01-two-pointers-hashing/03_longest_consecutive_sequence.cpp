// 03_longest_consecutive_sequence.cpp
// Problem: Longest Consecutive Sequence (Hashing / unordered_set)
// LeetCode: https://leetcode.com/problems/longest-consecutive-sequence/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 03_longest_consecutive_sequence.cpp -o 03_longest_consecutive_sequence
// Run: ./03_longest_consecutive_sequence
//
// 🧩 Problem Summary:
// Given an unsorted array of integers, return the length of the longest
// consecutive elements sequence. The sequence elements can appear in any order.
//
// Example:
// Input: [100, 4, 200, 1, 3, 2]
// Output: 4  (sequence: 1, 2, 3, 4)
//
// 🧠 Approach (Hashing):
// 1️⃣ Insert all numbers into an unordered_set for O(1) lookups.
// 2️⃣ Iterate through each number. If (number - 1) doesn’t exist in the set,
//     treat this number as the start of a new sequence.
// 3️⃣ Count consecutive numbers (number + 1, number + 2, …) until the sequence breaks.
// 4️⃣ Track the maximum sequence length found.
//
// ✅ Why it works:
// - Each number is checked at most twice: once for start check, once while counting.
// - By starting only at sequence beginnings, we avoid redundant checks.
//
// ⏱️ Complexity:
// Time:  O(n) on average (unordered_set gives O(1) lookups)
// Space: O(n) for storing elements in the set
//
// 📘 LeetCode Link:
// https://leetcode.com/problems/longest-consecutive-sequence/
// Try it yourself to test your implementation.

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 🔹 Function to find longest consecutive sequence length
int longestConsecutiveSequence(const vector<int>& numbers) {
    if (numbers.empty()) return 0;

    unordered_set<int> values(numbers.begin(), numbers.end());
    int bestLength = 0;

    for (int num : numbers) {
        // Only start if current number is the first in sequence
        if (values.find(num - 1) == values.end()) {
            int current = num;
            int currentLength = 1;

            // Walk forward for consecutive numbers
            while (values.find(current + 1) != values.end()) {
                ++current;
                ++currentLength;
            }

            bestLength = max(bestLength, currentLength);
        }
    }

    return bestLength;
}

int main() {
    cout << "🔹 Problem: Longest Consecutive Sequence\n";
    cout << "Input format:\n";
    cout << "n\n";
    cout << "a0 a1 a2 ... a(n-1)\n\n";
    cout << "Enter n and the numbers:\n";

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
✅ Longest consecutive sequence length: 4

📊 Explanation:
Consecutive numbers: 1, 2, 3, 4 (length = 4)

📘 LeetCode:
https://leetcode.com/problems/longest-consecutive-sequence/

📌 Edge Cases:
- Empty array → 0
- All unique non-consecutive → 1
- Handles negatives too (e.g., -2, -1, 0 → 3)
- Duplicates are ignored automatically via unordered_set

🧠 Key Insight:
This avoids sorting (O(n log n)) and achieves O(n) average time
by leveraging hash-based lookups to expand sequences efficiently.
*/
