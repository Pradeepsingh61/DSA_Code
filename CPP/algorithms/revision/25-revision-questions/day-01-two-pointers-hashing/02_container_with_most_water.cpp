// 02_container_with_most_water.cpp
// Problem: Container With Most Water (Two Pointers / Greedy)
// LeetCode: https://leetcode.com/problems/container-with-most-water/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 02_container_with_most_water.cpp -o 02_container_with_most_water
// Run: ./02_container_with_most_water
//
// 🧩 Problem Summary:
// You are given n non-negative integers `height[i]` where each represents a vertical line
// drawn at position i. Two lines form a container with the x-axis that can hold water.
// Find two lines that together can contain the **maximum area of water**.
// The container cannot be tilted.
//
// Example:
// heights = [1,8,6,2,5,4,8,3,7]
// Maximum water area = 49 (between lines with heights 8 and 7)
//
// 🧠 Approach (Two Pointers):
// 1️⃣ Start with two pointers — left at 0 and right at n-1.
// 2️⃣ Compute the area = (right - left) * min(height[left], height[right]).
// 3️⃣ Move the pointer pointing to the *smaller height* inward —
//     because only that move can possibly increase the area.
// 4️⃣ Continue until left >= right.
//
// ✅ Why it works:
// The height of water is limited by the shorter of the two lines.
// Moving the taller line inward won’t help — it only reduces width
// without increasing the limiting height.
//
// ⏱️ Complexity:
// Time: O(n)
// Space: O(1)
//
// 📘 LeetCode Link:
// https://leetcode.com/problems/container-with-most-water/
// Try it out on LeetCode to test the same logic.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 🔹 Function to calculate the maximum water area
int maxWaterContainer(vector<int>& heights) {
    int left = 0, right = heights.size() - 1;
    int maxArea = 0;

    while (left < right) {
        int width = right - left;
        int height = min(heights[left], heights[right]);
        int area = width * height;
        maxArea = max(maxArea, area);

        // Move pointer of smaller height inward
        if (heights[left] < heights[right])
            ++left;
        else
            --right;
    }

    return maxArea;
}

int main() {
    cout << "🔹 Problem: Container With Most Water\n";
    cout << "Input format:\n";
    cout << "n\nh0 h1 h2 ... h(n-1)\n\n";
    cout << "Enter n and the heights:\n";

    int n;
    if (!(cin >> n) || n <= 1) {
        cerr << "❌ Invalid input. Need at least 2 heights.\n";
        return 0;
    }

    vector<int> heights(n);
    for (int i = 0; i < n; ++i)
        cin >> heights[i];

    int maxArea = maxWaterContainer(heights);
    cout << "\n✅ Maximum water that can be contained: " << maxArea << "\n";

    return 0;
}

/*
🔍 Example Input:
9
1 8 6 2 5 4 8 3 7

🧾 Expected Output:
✅ Maximum water that can be contained: 49

📊 Explanation:
Pair chosen: heights[1] = 8, heights[8] = 7
Width = 8 - 1 = 7
Height = min(8, 7) = 7
Area = 7 × 7 = 49

📘 LeetCode Link:
https://leetcode.com/problems/container-with-most-water/

🧠 Key Insight:
- The shorter height limits the water area.
- Always move the smaller height inward to explore potential larger areas.
*/
