/*
 * Algorithm Name
 * Stack Using Linked List
 * 
 * Programming Language
 * Java
 * 
 * Category
 * Data Structures / Stack
 * 
 * Difficulty Level
 * Easy
 * 
 * Algorithm Description:
 * 
 * 1. Problem it solves:
 * -> Implements a stack using a singly linked list.
 * -> Stack follows LIFO (Last In First Out) principle.
 * -> Supports push, pop, peek, and isEmpty operations.
 * 
 * 2. Approach / Idea:
 * -> Use a Node class representing each element with 'data' and 'next' pointer.
 * -> The 'top' pointer always points to the top of the stack.
 * -> push(x): Create a new node, link it to the current top, and update top.
 * -> pop(): Remove the top node and return its value.
 * -> peek(): Return value of the top node without removing it.
 * -> isEmpty(): Check if the top is null.
 * 
 * 3. Complexity:
 * Time:
 *   push: O(1) - insert at head
 *   pop: O(1) - remove from head
 *   peek: O(1) - access head
 *   isEmpty: O(1)
 * Space: O(n) - n nodes in the linked list
 * 
 * Author: Pradyumn Pratap Singh
 */

package DSA_Code.Java.data_structures.stacks;

public class StackUsingQueues {

    // Node class representing each element in the stack
    private static class Node {
        int data; // value of node
        Node next; // pointer to next node

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    private Node top; // Top of stack

    // Constructor
    public StackUsingQueues() {
        this.top = null;
    }

    // Push element onto stack
    public void push(int x) {
        Node newNode = new Node(x); // Create new node
        newNode.next = top;         // Link new node to current top
        top = newNode;              // Update top to new node
    }

    // Pop element from stack
    public int pop() {
        if (top == null) {          // Check for empty stack
            System.out.println("Stack Underflow!");
            return -1; // Empty stack
        }
        int value = top.data;       // Retrieve top value
        top = top.next;             // Move top to next node
        return value;
    }

    // Peek top element
    public int peek() {
        if (top == null) {          // Check for empty stack
            System.out.println("Stack is empty!");
            return -1;
        }
        return top.data;            // Return value without removing
    }

    // Check if stack is empty
    public boolean isEmpty() {
        return top == null;
    }

    // Test the implementation
    public static void main(String[] args) {
        StackUsingQueues stack = new StackUsingQueues();

        // Push test
        System.out.println("Pushing elements: 10, 20, 30");
        stack.push(10);
        stack.push(20);
        stack.push(30);

        // Peek test
        System.out.println("Top element: " + stack.peek()); // Expected: 30

        // Pop test
        System.out.println("Popped: " + stack.pop());      // Expected: 30
        System.out.println("Top after pop: " + stack.peek()); // Expected: 20

        // Empty check
        System.out.println("Is stack empty? " + stack.isEmpty()); // Expected: false

        // Edge case: Pop all elements
        stack.pop(); // removes 20
        stack.pop(); // removes 10git 
        System.out.println("Is stack empty after popping all? " + stack.isEmpty()); // true
        System.out.println("Pop on empty stack: " + stack.pop()); // Should show Stack Underflow
    }
}
