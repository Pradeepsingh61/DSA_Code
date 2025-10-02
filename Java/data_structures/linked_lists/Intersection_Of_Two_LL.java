/**
 * Definition for singly-linked list.
 */

class ListNode {
  int val;
  ListNode next;
  ListNode(int x) {
    val = x;
    next = null;
  }
}

public class Intersection_Of_Two_LL {
  public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
    ListNode tempA = headA;
    ListNode tempB = headB;
    int countA = 0;
    while (tempA != null) {
      countA++;
      tempA = tempA.next;
    }
    int countB = 0;
    while (tempB != null) {
      countB++;
      tempB = tempB.next;
    }
    tempA = headA;
    tempB = headB;
    if (countB > countA) {
      int diff = countB - countA;
      while (diff-- > 0) {
        tempB = tempB.next;
      }
    } else if (countA > countB) {
      int diff = countA - countB;
      while (diff-- > 0) {
        tempA = tempA.next;
      }
    }

    while (tempA != null && tempB != null) {
      if (tempA == tempB) {
        return tempA;
      }
      tempA = tempA.next;
      tempB = tempB.next;
    }
    return null;
  }

  public static void main(String[] args) {
    // Creating two intersecting linked lists:
    // A: 1 -> 2 \
    //             3 -> 4 -> 5
    // B:    6  /
    ListNode common = new ListNode(3);
    common.next = new ListNode(4);
    common.next.next = new ListNode(5);

    ListNode headA = new ListNode(1);
    headA.next = new ListNode(2);
    headA.next.next = common;

    ListNode headB = new ListNode(6);
    headB.next = common;

    Intersection_Of_Two_LL solution = new Intersection_Of_Two_LL();
    ListNode intersection = solution.getIntersectionNode(headA, headB);

    if (intersection != null) {
      System.out.println("Intersection at node with value: " + intersection.val);
    } else {
      System.out.println("No intersection.");
    }
  }
}