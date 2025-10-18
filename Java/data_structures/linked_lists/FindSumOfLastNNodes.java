/**
 * Definition for a singly linked list node.
 */
class Node {
  int data;
  Node next;

  Node(int data) {
    this.data = data;
    this.next = null;
  }
}

/**
 * Find the sum of the last N nodes of a linked list.
 */
class Solution {
  public int sumOfLastN_Nodes(Node head, int n) {
    int count = 0;
    int sum = 0;

    Node temp1 = head;
    Node temp2 = head;

    while (temp1 != null) {
      count++;
      temp1 = temp1.next;
    }

    while (temp2 != null) {
      if (count <= n) {
        sum += temp2.data;
      }
      count--;
      temp2 = temp2.next;
    }

    return sum;
  }
}
