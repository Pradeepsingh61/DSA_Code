/**
 * Definition for singly-linked list.
 */
class ListNode {
  int val;
  ListNode next;

  ListNode() {}

  ListNode(int val) { this.val = val; }

  ListNode(int val, ListNode next) {
    this.val = val;
    this.next = next;
  }
}

class Solution {
  // Reverses a singly linked list.
  public ListNode reverseList(ListNode head) {
    ListNode curr = head;
    ListNode prev = null;
    ListNode next = null;

    // Traverse the list and reverse links
    while (curr != null) {
      next = curr.next; // Store next node
      curr.next = prev; // Reverse current node's pointer
      prev = curr;      // Move prev to current
      curr = next;      // Move to next node
    }

    return prev; // New head of reversed list
  }
}
