import java.lang.reflect.Constructor;
import java.sql.Driver;

public class StackUsingLinkedList {
    private static class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    private Node top; // top of the stack

    // Constructor to initialize the stack
    public StackUsingLinkedList() {
        this.top = null;
    }

    // Pushes an element onto the stack.
    public void push(int value) {
        Node newNode = new Node(value);
        newNode.next = top;
        top = newNode;
        System.out.println(value + " pushed to stack.");
    }

    // Removes the top element from the stack and returns it.
    public int pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Stack Underflow! Cannot pop from an empty stack.");
        }
        int popped = top.data;
        top = top.next;
        System.out.println(popped + " popped from stack.");
        return popped;
    }

    // Returns the top element without removing it.
    public int peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Stack is empty! No top element.");
        }
        return top.data;
    }

    // Checks if the stack is empty.
    public boolean isEmpty() {
        return top == null;
    }

    // Displays all elements in the stack.
    public void display() {
        if (isEmpty()) {
            System.out.println("Stack is empty!");
            return;
        }

        System.out.print("Stack elements: ");
        Node current = top;
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("NULL");
    }

    // Driver code to test the Stack implementation
    public static void main(String[] args) {
        StackUsingLinkedList stack = new StackUsingLinkedList();

        stack.push(10);
        stack.push(20);
        stack.push(30);

        stack.display();

        System.out.println("Top element is: " + stack.peek());

        stack.pop();
        stack.display();
    }
}
