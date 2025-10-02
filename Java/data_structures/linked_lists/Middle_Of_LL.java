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
  public ListNode middleNode(ListNode head) {
    ListNode slow = head;
    ListNode fast = head;

    // Move fast pointer twice as fast as slow pointer
    while (fast != null && fast.next != null) {
      slow = slow.next;
      fast = fast.next.next;
    }

    return slow;
  }
}
