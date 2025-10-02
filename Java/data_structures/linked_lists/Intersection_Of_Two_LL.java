/**
 * Definition for singly-linked list.
 */
class ListNode {
  int val;
  ListNode next;

  ListNode(int val) {
    this.val = val;
    this.next = null;
  }
}

public class Intersection_Of_Two_LL {

  public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
    // Count the length of both lists
    int countA = 0, countB = 0;
    ListNode tempA = headA, tempB = headB;

    while (tempA != null) {
      countA++;
      tempA = tempA.next;
    }

    while (tempB != null) {
      countB++;
      tempB = tempB.next;
    }

    // Align the start of both lists
    tempA = headA;
    tempB = headB;

    if (countB > countA) {
      int diff = countB - countA;
      while (diff-- > 0)
        tempB = tempB.next;
    } else if (countA > countB) {
      int diff = countA - countB;
      while (diff-- > 0)
        tempA = tempA.next;
    }

    // Traverse both lists together to find intersection
    while (tempA != null && tempB != null) {
      if (tempA == tempB) {
        return tempA;
      }
      tempA = tempA.next;
      tempB = tempB.next;
    }

    return null; // No intersection
  }
}
