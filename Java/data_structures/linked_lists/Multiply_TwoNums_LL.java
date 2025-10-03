class ListNode {
  int data;
  ListNode next;

  ListNode(int data) {
    this.data = data;
    this.next = null;
  }
}

public class MultiplyTwoNumbersLL {

  // Multiply two numbers represented as linked lists
  public ListNode multiplyTwoNumbers(ListNode l1, ListNode l2) {
    if (l1 == null || l2 == null)
      return new ListNode(0);

    l1 = reverseList(l1);
    l2 = reverseList(l2);

    ListNode result = new ListNode(0);
    ListNode l2Ptr = l2;
    int l2Pos = 0;

    while (l2Ptr != null) {
      ListNode partialProduct = multiplyWithSingleDigit(l1, l2Ptr.data);
      partialProduct = addZeros(partialProduct, l2Pos);
      result = addTwoNumbers(result, partialProduct);
      l2Ptr = l2Ptr.next;
      l2Pos++;
    }

    return reverseList(result.next);
  }

  // Multiply a linked list with a single digit
  private ListNode multiplyWithSingleDigit(ListNode l, int digit) {
    ListNode dummy = new ListNode(0);
    ListNode current = dummy;
    int carry = 0;

    while (l != null || carry != 0) {
      int sum = carry + (l != null ? l.data * digit : 0);
      carry = sum / 10;
      current.next = new ListNode(sum % 10);
      current = current.next;
      if (l != null)
        l = l.next;
    }

    return dummy.next;
  }

  // Add leading zeros for place value shift
  private ListNode addZeros(ListNode l, int count) {
    while (count-- > 0) {
      ListNode newNode = new ListNode(0);
      newNode.next = l;
      l = newNode;
    }
    return l;
  }

  // Add two linked list numbers
  private ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    ListNode dummy = new ListNode(0);
    ListNode current = dummy;
    int carry = 0;

    while (l1 != null || l2 != null || carry != 0) {
      int sum = carry + (l1 != null ? l1.data : 0) + (l2 != null ? l2.data : 0);
      carry = sum / 10;
      current.next = new ListNode(sum % 10);
      current = current.next;
      if (l1 != null)
        l1 = l1.next;
      if (l2 != null)
        l2 = l2.next;
    }
    return dummy.next;
  }

  // Reverse a linked list
  private ListNode reverseList(ListNode head) {
    ListNode prev = null, current = head;
    while (current != null) {
      ListNode next = current.next;
      current.next = prev;
      prev = current;
      current = next;
    }
    return prev;
  }

  // Helper function to print linked list
  public static void printList(ListNode head) {
    while (head != null) {
      System.out.print(head.data);
      head = head.next;
    }
    System.out.println();
  }

  // Example usage
  public static void main(String[] args) {
    // Number 342
    ListNode l1 = new ListNode(3);
    l1.next = new ListNode(4);
    l1.next.next = new ListNode(2);

    // Number 465
    ListNode l2 = new ListNode(4);
    l2.next = new ListNode(6);
    l2.next.next = new ListNode(5);

    MultiplyTwoNumbersLL mt = new MultiplyTwoNumbersLL();
    ListNode result = mt.multiplyTwoNumbers(l1, l2);

    System.out.print("Product: ");
    printList(result); // Expected output: 159030
  }
}
