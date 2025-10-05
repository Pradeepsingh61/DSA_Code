
/*
Infix to Postfix Conversion (Shunting Yard Algorithm)

Description:
This algorithm converts an infix expression (e.g., A+B*C) into a postfix expression (e.g., A B C * +)
using the C++ Standard Template Library (STL) stack.
It follows operator precedence and associativity rules to ensure correct order of operations.
The stack temporarily stores operators and parentheses during the conversion process.

Example:
Input:  A+B*C
Output: A B C * +

Time Complexity: O(n)
Each character in the infix expression is scanned once and pushed/popped from the stack at most once.

Space Complexity: O(n)
A stack is used to store operators and parentheses during processing.

Reference:
https://en.wikipedia.org/wiki/Shunting_yard_algorithm
*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to define operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // If operand, add to output
        if (isalnum(c)) {
            postfix += c;
        }
        // If '(', push to stack
        else if (c == '(') {
            st.push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // remove '('
        }
        // If operator
        else if (isOperator(c)) {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop remaining operators
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    return 0;
}
