/****************************************
*Reverse a Stack using Recursion
*
* Description: Reverses a stack using recursion without loops. 
* Removes the top element recursively until the stack is empty 
* and inserts each element at the bottom to reverse the stack.

* Time Complexity: O(n^2) - each element may require moving n elements into/out of a temporary stack
* Space Complexity: O(n) - recursion depth + temporary stack

* Output:
* Original: 5 4 3 2 1
* Reversed: 1 2 3 4 5
****************************************/

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
