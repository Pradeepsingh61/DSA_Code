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