/*
-----------------------------------------------
💡 Problem: Add Two Numbers (LeetCode #2)
-----------------------------------------------
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each node contains a single digit. 
Add the two numbers and return the sum as a linked list.

Example:
Input:  (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807

-----------------------------------------------
🧠 Algorithm:
-----------------------------------------------
1. Use two pointers (t1 and t2) to traverse both linked lists simultaneously.
2. Maintain a variable `carry` to handle sums ≥ 10.
3. For each step:
   - Calculate `sum = (t1 ? t1->val : 0) + (t2 ? t2->val : 0) + carry`
   - Create a new node with value `sum % 10`
   - Update `carry = sum / 10`
4. Move both pointers ahead if possible.
5. After traversal, if `carry` is non-zero, create one last node for it.
6. Return the dummy head's next pointer.

-----------------------------------------------
⏱ Time Complexity: O(max(m, n))
   - Where m and n are the lengths of the two linked lists.
   - We traverse both lists once.

💾 Space Complexity: O(max(m, n))
   - Resultant linked list size depends on the longer input list (plus carry node).
-----------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* t1 = l1;
        ListNode* t2 = l2;
        ListNode* dummyn = new ListNode(-1); // Dummy node for easier list handling
        ListNode* cur = dummyn;
        int carry = 0;

        // Traverse both lists
        while (t1 != NULL || t2 != NULL) {
            int sum = carry;
            if (t1) sum += t1->val;
            if (t2) sum += t2->val;

            // Create a new node with digit value
            ListNode* newnode = new ListNode(sum % 10);
            carry = sum / 10;

            // Attach node to result list
            cur->next = newnode;
            cur = cur->next;

            // Move ahead
            if (t1) t1 = t1->next;
            if (t2) t2 = t2->next;
        }

        // Handle leftover carry
        if (carry) {
            ListNode* newnode = new ListNode(carry);
            cur->next = newnode;
        }

        return dummyn->next;
    }
};

// Helper function to create a linked list from vector
ListNode* createList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* temp = head;
    for (int i = 1; i < vals.size(); i++) {
        temp->next = new ListNode(vals[i]);
        temp = temp->next;
    }
    return head;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Example input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
    vector<int> num1 = {2, 4, 3};
    vector<int> num2 = {5, 6, 4};

    ListNode* l1 = createList(num1);
    ListNode* l2 = createList(num2);

    Solution sol;
    ListNode* result = sol.addTwoNumbers(l1, l2);

    cout << "List 1: ";
    printList(l1);
    cout << "List 2: ";
    printList(l2);
    cout << "Sum: ";
    printList(result);

    return 0;
}
