// Definition for singly-linked list node
class ListNode {
    int val;         // value stored in the node
    ListNode next;   // pointer to the next node

    // Constructor to create a new node
    ListNode(int val) {
        this.val = val;
        this.next = null;
    }
}

public class RemoveDuplicatesSortedList {

    // Function to remove duplicates from a sorted linked list
    public static ListNode deleteDuplicates(ListNode head) {
        // If the list is empty or has only one node, return as it is
        if (head == null || head.next == null)
            return head;

        // Start with the first node
        ListNode current = head;

        // Traverse the entire linked list
        while (current != null && current.next != null) {
            // If current node and next node have the same value
            if (current.val == current.next.val) {
                // Skip the next node (remove duplicate)
                current.next = current.next.next;
            } else {
                // Move to the next distinct element
                current = current.next;
            }
        }

        // Return the modified list
        return head;
    }

    // Utility function to print the linked list
    public static void printList(ListNode head) {
        ListNode temp = head;
        while (temp != null) {
            System.out.print(temp.val + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    // Main method to test the code
    public static void main(String[] args) {
        // Creating a sample sorted linked list: 1 -> 1 -> 2 -> 3 -> 3
        ListNode head = new ListNode(1);
        head.next = new ListNode(1);
        head.next.next = new ListNode(2);
        head.next.next.next = new ListNode(3);
        head.next.next.next.next = new ListNode(3);

        System.out.println("Original Linked List:");
        printList(head);

        // Remove duplicates
        head = deleteDuplicates(head);

        System.out.println("Linked List after removing duplicates:");
        printList(head);
    }
}
