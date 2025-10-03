/**
 * MultiplyTwoNumbersLL
 *
 * Description:
 * This class multiplies two numbers represented as singly linked lists.
 * Each node contains a single digit, and digits are stored in forward order.
 * The algorithm works by reversing the lists, multiplying digit by digit,
 * shifting partial results according to place value, adding them together,
 * and finally reversing the result to get the correct order.
 *
 * Use Cases:
 * - Multiplying very large numbers that cannot fit into primitive data types
 * - Working with numbers stored in linked list format in memory-efficient
 * applications
 *
 * Time Complexity: O(m * n)
 * - m = number of nodes in l1
 * - n = number of nodes in l2
 * - Each digit of l2 is multiplied with all digits of l1, and partial sums are
 * added
 *
 * Space Complexity: O(m + n)
 * - For storing the result linked list and intermediate partial products
 */

class ListNode {
  int data;
  ListNode next;

  ListNode(int data) {
    this.data = data;
    this.next = null;
  }
}

public class Multiply_TwoNums_LL {

  /**
   * Multiplies two numbers represented as linked lists
   */
  public ListNode multiplyTwoNumbers(ListNode l1, ListNode l2) {
    if (l1 == null || l2 == null)
      return new ListNode(0);

    l1 = reverseList(l1); // Reverse to start from least significant digit
    l2 = reverseList(l2);

    ListNode result = new ListNode(0);
    ListNode l2Ptr = l2;
    int l2Pos = 0;

    while (l2Ptr != null) {
      // Multiply l1 with current digit of l2
      ListNode partialProduct = multiplyWithSingleDigit(l1, l2Ptr.data);

      // Add zeros to shift the partial product
      partialProduct = addZeros(partialProduct, l2Pos);

      // Add partial product to cumulative result
      result = addTwoNumbers(result, partialProduct);

      l2Ptr = l2Ptr.next;
      l2Pos++;
    }

    return reverseList(result.next); // Reverse final result to correct order
  }

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

  private ListNode addZeros(ListNode l, int count) {
    while (count-- > 0) {
      ListNode newNode = new ListNode(0);
      newNode.next = l;
      l = newNode;
    }
    return l;
  }

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

  public static void printList(ListNode head) {
    while (head != null) {
      System.out.print(head.data);
      head = head.next;
    }
    System.out.println();
  }

  public static void main(String[] args) {
    // Test case 1: 342 * 465 = 159030
    ListNode l1 = new ListNode(3);
    l1.next = new ListNode(4);
    l1.next.next = new ListNode(2);

    ListNode l2 = new ListNode(4);
    l2.next = new ListNode(6);
    l2.next.next = new ListNode(5);

    Multiply_TwoNums_LL mt = new Multiply_TwoNums_LL();
    ListNode result = mt.multiplyTwoNumbers(l1, l2);

    System.out.print("Product: ");
    printList(result);
  }
}
