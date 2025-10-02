/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
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
}