// 02_next_greater_element.cpp
// Problem: Next Greater Element (monotonic stack)
// LeetCode (related): https://leetcode.com/problems/next-greater-element-i/
// Author: DeveloperViraj (curated DSA set)
// Compile: g++ -std=c++17 02_next_greater_element.cpp -o 02_next_greater_element
// Run: ./02_next_greater_element
//
// Description:
//   For each element in an array, find the next greater element to its right.
//   If no greater element exists, the answer for that position is -1.
//   We use a monotonic decreasing stack that stores indices of elements whose
//   next greater element hasn't been found yet. As we iterate, when we find
//   a greater element, we pop and assign its next greater.
//
// Use case:
//   Useful in many pattern problems: stock span variants, skyline queries,
//   preprocessing for range queries, etc.
//
// Time Complexity: O(n) — each element is pushed and popped at most once.
// Space Complexity: O(n) — stack + output array.
//
// Input format:
//   n
//   a0 a1 a2 ... a(n-1)
//
// Output:
//   n integers (space-separated) — next greater element for each index, -1 if none.
//
// Example:
// Input:
// 9
// 2 1 2 4 3 5 1 2 0
//
// Output:
// 4 2 4 5 5 -1 2  -1 -1
//
// (Each index replaced by its next greater to the right)

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> nextGreaterElements(const vector<int> &values) {
    int n = (int)values.size();
    vector<int> answer(n, -1);
    stack<int> indexStack; // store indices of elements, monotonic decreasing by value

    for (int i = 0; i < n; ++i) {
        int currentValue = values[i];
        // While current value is greater than the value at stack top index,
        // we have found the next greater for that index.
        while (!indexStack.empty() && values[indexStack.top()] < currentValue) {
            int idx = indexStack.top();
            indexStack.pop();
            answer[idx] = currentValue;
        }
        // Push current index — its NG not known yet
        indexStack.push(i);
    }

    // Remaining indices have no next greater; their answer remains -1.
    return answer;
}

int main() {
    cout << "🔹 Problem: Next Greater Element (to the right)\n";
    cout << "Input format:\n n\n a0 a1 ... a(n-1)\nEnter n and the array:\n";

    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid input for n.\n";
        return 0;
    }

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    vector<int> result = nextGreaterElements(arr);

    cout << "\nNext greater elements:\n";
    for (int i = 0; i < n; ++i) {
        cout << result[i];
        if (i + 1 < n) cout << ' ';
    }
    cout << '\n';

    return 0;
}

/*
Example:
Input:
6
2 7 3 5 4 6

Output:
7 -1 5 6 6 -1

Explanation:
- Next greater after 2 is 7
- 7 has no next greater -> -1
- After 3 is 5
- After 5 is 6
- After 4 is 6
- 6 has none -> -1
*/
