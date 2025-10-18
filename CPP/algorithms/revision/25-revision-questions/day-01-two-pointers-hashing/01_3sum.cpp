// 01_3sum.cpp
// Problem: 3Sum (Arrays / Two Pointers + Sorting)
// LeetCode: https://leetcode.com/problems/3sum/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 01_3sum.cpp -o 01_3sum
// Run: ./01_3sum
//
// 🧩 Summary:
// Given an integer array 'numbers', return all unique triplets (a, b, c)
// such that a + b + c == 0. Each triplet should be printed one per line.
//
// 🧠 Approach (Two Pointers + Sorting):
// 1. Sort the array.
// 2. For each index i (value a), use two pointers (left, right) to find
//    pairs (b, c) such that b + c == -a.
// 3. Skip duplicate values for i, left, and right to ensure uniqueness.
//
// ✅ Correctness:
// Sorting enables ordered traversal and duplicate skipping.
// Two pointers ensure linear-time scanning per fixed element.
//
// ⏱️ Complexity:
// Time:  O(n²)
// Space: O(1) (ignoring output storage)
//
// 📘 LeetCode Link: https://leetcode.com/problems/3sum/
// Try it yourself on LeetCode with various input cases.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> findThreeSumTriplets(vector<int> numbers) {
    vector<vector<int>> result;
    int n = numbers.size();
    if (n < 3) return result;

    sort(numbers.begin(), numbers.end());

    for (int i = 0; i < n; ++i) {
        // Skip duplicate 'a' values
        if (i > 0 && numbers[i] == numbers[i - 1]) continue;

        // No need to continue if current number > 0 (as array is sorted)
        if (numbers[i] > 0) break;

        int firstNumber = numbers[i];
        int target = -firstNumber;
        int left = i + 1, right = n - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                result.push_back({firstNumber, numbers[left], numbers[right]});

                // Skip duplicates for left and right
                int leftValue = numbers[left], rightValue = numbers[right];
                while (left < right && numbers[left] == leftValue) ++left;
                while (left < right && numbers[right] == rightValue) --right;
            }
            else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return result;
}

int main() {
    cout << "🔹 3Sum Problem — Arrays / Two Pointers\n";
    cout << "Input format:\n";
    cout << "n\n";
    cout << "a0 a1 a2 ... a(n-1)\n\n";
    cout << "Enter n and array elements:\n";

    int n;
    if (!(cin >> n) || n <= 0) {
        cerr << "❌ Invalid input. Exiting.\n";
        return 0;
    }

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) cin >> numbers[i];

    auto triplets = findThreeSumTriplets(numbers);

    if (triplets.empty()) {
        cout << "No triplets found.\n";
    } else {
        cout << "\n✅ Unique Triplets (a + b + c = 0):\n";
        for (auto &t : triplets) {
            cout << t[0] << " " << t[1] << " " << t[2] << "\n";
        }
    }

    return 0;
}

/*
🔍 Example Input:
6
-1 0 1 2 -1 -4

🧾 Expected Output:
-1 -1 2
-1 0 1

📊 Edge Cases:
1️⃣ n < 3 → "No triplets found"
2️⃣ [0,0,0,0] → one triplet "0 0 0"
3️⃣ All positives → "No triplets found"
4️⃣ Large input → Works efficiently for up to 10^4 elements

🔗 LeetCode: https://leetcode.com/problems/3sum/
*/
