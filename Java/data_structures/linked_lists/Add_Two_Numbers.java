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
  /**
   * Adds two numbers represented by linked lists.
   * Each node contains a single digit, and digits are stored in reverse order.
   * @param l1 The first linked list.
   * @param l2 The second linked list.
   * @return The sum as a linked list.
   */
  public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    // Dummy node to simplify list operations
    ListNode dummy = new ListNode(0);
    ListNode tail = dummy;
    int carry = 0;

    // Traverse both lists until all nodes and carry are processed
    while (l1 != null || l2 != null || carry > 0) {
      int sum = carry;

      if (l1 != null) {
        sum += l1.val;
        l1 = l1.next;
      }

      if (l2 != null) {
        sum += l2.val;
        l2 = l2.next;
      }

      // Update carry for next iteration
      carry = sum / 10;

      // Create new node with current digit
      tail.next = new ListNode(sum % 10);
      tail = tail.next;
    }

    return dummy.next;
  }
}
