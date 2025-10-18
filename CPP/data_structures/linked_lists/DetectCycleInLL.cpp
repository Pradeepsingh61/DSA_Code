// Problem Statement: Given the head of a linked list, determine if the linked list has a cycle in it.
// This implementation uses Floyd's Tortoise and Hare algorithm.

#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // Initialize two pointers, slow and fast, to the head of the list.
        ListNode* slow = head;
        ListNode* fast = head;

        // Traverse the list with two pointers.
        while (slow && fast && fast->next) {
            // Slow pointer moves one step at a time.
            slow = slow->next;
            // Fast pointer moves two steps at a time.
            fast = fast->next->next;

            // If the pointers meet, there is a cycle.
            if (slow == fast) {
                return true;
            }
        }

        // If the loop finishes, fast has reached the end, so no cycle.
        return false;
    }
};

int main() {
    Solution sol;

    // Test Case 1: Linked list with a cycle
    ListNode* head1 = new ListNode(3);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);
    head1->next->next->next->next = head1->next; // Create a cycle

    bool result1 = sol.hasCycle(head1);
    std::cout << "Test Case 1 (with cycle): " << (result1 ? "true" : "false") << std::endl;

    // Test Case 2: Linked list without a cycle
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);

    bool result2 = sol.hasCycle(head2);
    std::cout << "Test Case 2 (no cycle): " << (result2 ? "true" : "false") << std::endl;

    // Test Case 3: Single node without a cycle
    ListNode* head3 = new ListNode(1);

    bool result3 = sol.hasCycle(head3);
    std::cout << "Test Case 3 (single node): " << (result3 ? "true" : "false") << std::endl;
    
    // Clean up memory for non-cyclic lists to prevent leaks.
    // Note: Deleting a cyclic list requires breaking the cycle first.
    delete head2->next;
    delete head2;
    delete head3;
    // For head1, proper cleanup is more complex and omitted for this example.

    return 0;
}