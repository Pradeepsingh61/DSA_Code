/**
 * Definition for a Node in a linked list with a random pointer.
 */
class Node {
  int val;
  Node next;
  Node random;

  Node(int val) {
    this.val = val;
    this.next = null;
    this.random = null;
  }
}

class Solution {
  public Node copyRandomList(Node head) {
    if (head == null) {
      return null;
    }

    // Interleave copied nodes with original nodes
    Node temp = head;
    while (temp != null) {
      Node copy = new Node(temp.val);
      copy.next = temp.next;
      temp.next = copy;
      temp = temp.next.next;
    }

    // Assign random pointers for copied nodes
    temp = head;
    while (temp != null) {
      if (temp.random != null) {
        temp.next.random = temp.random.next;
      }
      temp = temp.next.next;
    }

    // Separate the copied list from the original list
    temp = head;
    Node dummy = new Node(0);
    Node curr = dummy;
    while (temp != null) {
      curr.next = temp.next;
      temp.next = temp.next.next;
      curr = curr.next;
      temp = temp.next;
    }

    return dummy.next;
  }
}
