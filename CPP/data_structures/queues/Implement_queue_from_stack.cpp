/*
💡 Problem: Implement Queue using Stacks

📘 Description:
Design a queue using two stacks such that all standard queue operations 
(push, pop, peek, and empty) are implemented.

You must implement the following:
1. void push(int x) — Pushes element x to the back of the queue.
2. int pop() — Removes the element from the front of the queue and returns it.
3. int peek() — Returns the element at the front of the queue.
4. bool empty() — Returns true if the queue is empty, false otherwise.

🧠 Algorithm:
- Use two stacks (s1 and s2).
- Push operation: push element directly to s1.
- Pop/Peek operations:
  - If s2 is not empty, directly pop/peek from s2.
  - Otherwise, transfer all elements from s1 to s2 (this reverses the order),
    then pop/peek from s2.
- Empty check: return true if both stacks are empty.

⏱️ Time Complexity:
- Push: O(1)
- Pop: Amortized O(1)
- Peek: Amortized O(1)
- Empty: O(1)

💾 Space Complexity:
- O(N), where N is the total number of elements stored in the queue.

✅ Example:
Input:
MyQueue q;
q.push(1);
q.push(2);
cout << q.peek(); // Output: 1
cout << q.pop();  // Output: 1
cout << q.empty(); // Output: false
*/

#include <bits/stdc++.h>
using namespace std;

class MyQueue {
    stack<int> s1;
    stack<int> s2;

public:
    // Constructor
    MyQueue() {}

    // Push element to the back of the queue
    void push(int x) {
        s1.push(x);
    }

    // Removes the element from the front of the queue
    int pop() {
        if (!s2.empty()) {
            int val = s2.top();
            s2.pop();
            return val;
        }

        // Transfer elements from s1 to s2
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        int val = s2.top();
        s2.pop();
        return val;
    }

    // Get the front element
    int peek() {
        if (!s2.empty())
            return s2.top();

        // Transfer elements if s2 is empty
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        return s2.top();
    }

    // Check if the queue is empty
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

// ---------------- Driver Code ----------------
int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << "Front element: " << q.peek() << endl; // 1
    cout << "Removed element: " << q.pop() << endl; // 1
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl; // No
    return 0;
}
