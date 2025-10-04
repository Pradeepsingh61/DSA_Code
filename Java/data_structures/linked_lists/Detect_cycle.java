// File: Detecycle.java

/**
 * Detect Cycle in a Linked List
 *
 * Description:
 * This algorithm detects whether a singly linked list contains a cycle.
 * It uses Floyd’s Tortoise and Hare Algorithm:
 *   - A slow pointer moves one step at a time.
 *   - A fast pointer moves two steps at a time.
 * If there is a cycle, the fast pointer will eventually meet the slow pointer.
 * If there is no cycle, the fast pointer will reach the end of the list (null).
 *
 * Time Complexity: O(n) - each node is visited at most twice
 * Space Complexity: O(1) - only two pointers are used
 *
 * Use Cases:
 *   - Detecting loops in linked lists
 *   - Applications in graph cycles, network routing, and memory management
 */

class ListNode {
    int val;
    ListNode next;
    ListNode(int val) {
        this.val = val;
        this.next = null;
    }
}

public class Detect_cycle {

    /**
     * Detects if the linked list has a cycle.
     *
     * @param head The head node of the linked list
     * @return true if there is a cycle, false otherwise
     */
    public static boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) return false;

        ListNode slow = head;  // moves 1 step at a time
        ListNode fast = head;  // moves 2 steps at a time

        while (fast != null && fast.next != null) {
            slow = slow.next;          // advance slow pointer
            fast = fast.next.next;     // advance fast pointer

            if (slow == fast) return true; // cycle detected
        }

        return false; // no cycle
    }

    // Driver code for testing
    public static void main(String[] args) {
        // Test 1: List with cycle
        ListNode node1 = new ListNode(3);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(0);
        ListNode node4 = new ListNode(-4);
        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node2; // cycle
        System.out.println("Test 1 (with cycle): " + hasCycle(node1)); // true

        // Test 2: List without cycle
        ListNode nodeA = new ListNode(1);
        ListNode nodeB = new ListNode(2);
        nodeA.next = nodeB;
        System.out.println("Test 2 (no cycle): " + hasCycle(nodeA)); // false

        // Test 3: Single node without cycle
        ListNode single = new ListNode(1);
        System.out.println("Test 3 (single node): " + hasCycle(single)); // false

        // Test 4: Empty list
        System.out.println("Test 4 (empty list): " + hasCycle(null)); // false
    }
}
