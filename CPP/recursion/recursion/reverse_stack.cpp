/****************************************
 * @description: Reverse a Stack using Recursion
 *
 * Intuition:
 * - A stack only allows access to the top element.
 * - To reverse it, we need to place the bottom element first.
 * - Recursion lets us remove elements until the stack is empty.
 * - As recursion unwinds, each popped element is inserted at the bottom, reversing the stack.
 *
 * Approach:
 * - Base case: If the stack is empty, return.
 * - Pop the top element and store it temporarily.
 * - Recursively reverse the remaining stack.
 * - Insert the stored element at the bottom using a temporary stack:
 *     - Move all elements to a temporary stack.
 *     - Push the saved element onto the main stack.
 *     - Restore the elements from the temporary stack.
 * - Repeat until all elements are back in reversed order.
 *
 * Complexity:
 * - Time: O(n^2)
 * - Space: O(n)
 *
 * Output:
 * Original: 5 4 3 2 1
 * Reversed: 1 2 3 4 5
 ****************************************/

 * 
 * Output:
 * Original: 5 4 3 2 1 
 * Reversed: 1 2 3 4 5 
 *
 * Original: 51 12 42 
 * Reversed: 42 12 51 
 *
 * Original: 
 * Reversed:
 ******************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverseStack(stack<int> &st) {
        if (st.empty()) {
            return;
        }

        // Remove the top element
        int top = st.top();
        st.pop();

        // Reverse the smaller stack
        reverseStack(st);  //recursive call to reverse the remaining stack

        // Use a helper stack to insert 'top' at the bottom
        stack<int> temp;
        while (!st.empty()) {
            temp.push(st.top());
            st.pop();
        }

        // Place the removed element
        st.push(top);

        // Restore other elements back
        while (!temp.empty()) {
            st.push(temp.top());
            temp.pop();
        }
    }
};

// Print without modifying the actual stack
void displayStack(const stack<int> &st) {
    stack<int> copy = st;
    while (!copy.empty()) {
        cout << copy.top() << " ";
        copy.pop();
    }
    cout << endl;
}

int main() {
    Solution sol;

    // Test 1: Normal case
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    cout << "Original: ";
    displayStack(st);

    sol.reverseStack(st);

    cout << "Reversed: ";
    displayStack(st);

    // Test 2: Single element
    stack<int> st2;
    st2.push(42);
    st2.push(12);
    st2.push(51);

    cout << "\nOriginal: ";
    displayStack(st2);

    sol.reverseStack(st2);

    cout << "Reversed: ";
    displayStack(st2);

    // Test 3: Empty stack
    stack<int> st3;

    cout << "\nOriginal: ";
    displayStack(st3);

    sol.reverseStack(st3);

    cout << "Reversed: ";
    displayStack(st3);

    return 0;
}
