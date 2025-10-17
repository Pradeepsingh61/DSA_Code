// 01_valid_parentheses.cpp
// Problem: Valid Parentheses
// LeetCode: https://leetcode.com/problems/valid-parentheses/
// Author: DeveloperViraj (curated DSA set)
// Compile: g++ -std=c++17 01_valid_parentheses.cpp -o 01_valid_parentheses
// Run: ./01_valid_parentheses
//
// Description:
//   Given a string containing only the characters '(', ')', '{', '}', '[' and ']',
//   determine if the input string is valid. An input string is valid if:
//     1) Open brackets are closed by the same type of brackets.
//     2) Open brackets are closed in the correct order.
//   The algorithm uses a stack to keep track of opening brackets; upon encountering
//   a closing bracket we check whether the top of the stack matches the expected opening.
//
// Use case:
//   Syntax validation, small parser checks, expression validation in editors.
//
// Time Complexity: O(n) — each character is pushed/popped at most once.
// Space Complexity: O(n) — stack for open brackets (worst case all opens).
//
// Input format (example):
//   A single line containing the bracket string.
//   Example:
//     ()[]{}         => Valid
//     (]             => Invalid
//
// Output:
//   Prints "Valid" if the string is valid, otherwise prints "Invalid".

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

bool isValidParentheses(const string &s) {
    stack<char> openStack;
    // Map closing -> corresponding opening
    unordered_map<char, char> closingToOpening = {
        {')', '('},
        {'}', '{'},
        {']', '['},
    };

    for (char ch : s) {
        // If it's an opening bracket, push to stack
        if (ch == '(' || ch == '{' || ch == '[') {
            openStack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            // If stack empty or top doesn't match expected opening, invalid
            if (openStack.empty() || openStack.top() != closingToOpening[ch]) {
                return false;
            }
            openStack.pop();
        } else {
            // If other characters exist, ignore or treat as invalid depending on spec.
            // For this problem we assume input contains only parentheses characters.
        }
    }

    // Valid only if no unmatched opens remain
    return openStack.empty();
}

int main() {
    cout << "🔹 Problem: Valid Parentheses\n";
    cout << "Enter a single line containing the string of brackets (e.g. ()[]{}):\n";

    string input;
    if (!getline(cin, input)) {
        cerr << "No input provided.\n";
        return 0;
    }

    bool result = isValidParentheses(input);
    if (result) cout << "Valid\n";
    else cout << "Invalid\n";

    return 0;
}

/*
Example:
Input:
()[]{}

Output:
Valid
*/
