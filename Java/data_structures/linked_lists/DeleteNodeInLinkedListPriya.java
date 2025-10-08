/*
 * Algorithm Name:Delete Node in a Linked List .
 * Programming Language: Java
 * Category: Linked List  
 * Difficulty Level: Medium
 *
 * Author: Priya Rani 
 *
 * Algorithm Description:
 * There is a singly-linked list head and we want to delete a node node in it.

You are given the node to be deleted node. You will not be given access to the first node of head.

All the values of the linked list are unique, and it is guaranteed that the given node node is not the last node in the linked list.

Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:

The value of the given node should not exist in the linked list.
The number of nodes in the linked list should decrease by one.
All the values before node should be in the same order.
All the values after node should be in the same order.
 *
 * Time Complexity: O(1) -No traversal or loops are used, so the time complexity is O(1).
 * Space Complexity: O(1) - The algorithm uses only a constant amount of extra space (a few variables, no additional data structures).
 */
class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
    }
}

public class DeleteNodeInLinkedListPriya {
    public void deleteNode(ListNode node) {
        node.val = node.next.val; 
        node.next = node.next.next;
    }

    public static void main(String[] args) {
    
        ListNode head = new ListNode(4);
        head.next = new ListNode(5);
        head.next.next = new ListNode(1);
        head.next.next.next = new ListNode(9);

        DeleteNodeInLinkedList solution = new DeleteNodeInLinkedList();
        solution.deleteNode(head.next); 

       
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + (current.next != null ? " -> " : ""));
            current = current.next;
        }
    }
}

