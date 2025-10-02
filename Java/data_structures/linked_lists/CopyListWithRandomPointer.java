class Node {
  int val;
  Node next;
  Node random;

  public Node(int val) {
    this.val = val;
    this.next = null;
    this.random = null;
  }
}

class Solution {
  public Node copyRandomList(Node head) {
    if (head == null) {
      return head;
    }

    // Interleaving Nodes
    Node temp = head;

    while (temp != null) {
      Node copy = new Node(temp.val);
      copy.next = temp.next;
      temp.next = copy;
      temp = temp.next.next;
    }

    // Random Ptr
    temp = head;

    while (temp != null) {
      if (temp.random != null) {
        temp.next.random = temp.random.next;
      }
      temp = temp.next.next;
    }

    temp = head;
    Node dummy = new Node(0);
    Node curr = dummy;

    while (temp != null) {
      curr.next = temp.next;
      temp.next = temp.next.next;
      temp = temp.next;
      curr = curr.next;
    }

    return dummy.next;
  }
}

public class CopyListWithRandomPointer {
  public static void main(String[] args) {
    Node head = new Node(7);
    head.next = new Node(13);
    head.next.next = new Node(11);
    head.next.next.next = new Node(10);
    head.next.next.next.next = new Node(1);

    head.random = null;
    head.next.random = head;
    head.next.next.random = head.next.next.next.next;
    head.next.next.next.random = head.next.next;
    head.next.next.next.next.random = head;

    Solution solution = new Solution();
    Node copiedListHead = solution.copyRandomList(head);

    Node temp = copiedListHead;
    while (temp != null) {
      System.out.print("Node val: " + temp.val);
      if (temp.random != null) {
        System.out.print(", Random points to: " + temp.random.val);
      } else {
        System.out.print(", Random points to: null");
      }
      System.out.println();
      temp = temp.next;
    }
  }
}