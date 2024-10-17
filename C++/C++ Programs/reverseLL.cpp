/*
Reversing a linked list
*/
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

int main() {
  // init ll
  // 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    ListNode* reversedHead = prev;

    ListNode* temp = reversedHead;
    while (temp != nullptr) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }

    return 0;
}
