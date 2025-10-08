// 02_container_with_most_water.cpp
// Problem: Container With Most Water (Two Pointers / Greedy)
// LeetCode: https://leetcode.com/problems/container-with-most-water/
// Author: DeveloperViraj (curated DSA set for Hacktoberfest 2025)
// Compile: g++ -std=c++17 02_container_with_most_water.cpp -o 02_container_with_most_water
// Run: ./02_container_with_most_water
//
// 🧩 Problem Summary:
// Given n non-negative integers `height[i]` where each represents a vertical line
// on the x-axis, find two lines that together with the x-axis form a container,
// such that the container holds the **maximum amount of water**.
//
// You cannot tilt the container.
//
// Example: heights = [1,8,6,2,5,4,8,3,7]
// Maximum water area = 49 (between lines 8 and 7)
//
// 🧠 Approach (Two Pointers):
// 1. Use two pointers — one at start (left) and one at end (right).
// 2. Compute area = (right - left) * min(height[left], height[right])
// 3. Move the pointer pointing to the *smaller* height inward,
//    because only that can potentially increase the area.
// 4. Continue until left >= right.
//
// ✅ Why this works:
// The area is constrained by the shorter line.
// Moving the taller line inward can never increase area —
// it only reduces the width without increasing the height.
//
// ⏱️ Complexity:
// Time: O(n)
// Space: O(1)
//
// 📘 LeetCode Link: https://leetcode.com/problems/container-with-most-water/
// Try it on LeetCode to verify the same approach.

#include <iostream>
#include <vector>
using namespace std;

int maxWaterContainer(vector<int>& heights) {
    int left = 0, right = heights.size() - 1;
    int maxArea = 0;

    while (left < right) {
        int width = right - left;
        int height = min(heights[left], heights[right]);
        int area = width * height;
        maxArea = max(maxArea, area);

        // Move the smaller height inward
        if (heights[left] < heights[right])
            left++;
        else
            right--;
    }

    return maxArea;
}

int main() {
    cout << "🔹 Problem: Container With Most Water\n";
    cout << "Input format:\n";
    cout << "n\n";
    cout << "h0 h1 h2 ... h(n-1)\n\n";
    cout << "Enter n and heights:\n";

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
Maximum water that can be contained: 49

📊 Explanation:
- Pair (8,7) at indices (1,8)
- Width = 8 - 1 = 7
- Height = min(8,7) = 7
=> Area = 7 * 7 = 49

📘 LeetCode Link:
https://leetcode.com/problems/container-with-most-water/

🧠 Key Insight:
- Move the pointer pointing to the smaller height inward.
- This guarantees exploring all possible containers efficiently.
*/
