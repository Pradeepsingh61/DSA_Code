// File: StackUsingQueues.java
// Author: Pradyumn Pratap Singh
// Description: Implementation of Stack using two Queues
// Algorithm Explanation and Complexity Analysis included

import java.util.LinkedList;
import java.util.Queue;

/**
 * Implementation of a Stack using two Queues.
 * Stack follows LIFO (Last In First Out) principle.
 * 
 * Algorithm:
 * 1. For push(x): 
 *    - Add x to queue2
 *    - Move all elements from queue1 to queue2
 *    - Swap queue1 and queue2
 * 
 * 2. For pop():
 *    - Remove and return the front element of queue1
 * 
 * Time Complexity:
 *  Push → O(n)
 *  Pop  → O(1)
 *  Peek → O(1)
 *  isEmpty → O(1)
 * 
 * Space Complexity: O(n)
 */
class StackUsingQueues {
    private Queue<Integer> queue1 = new LinkedList<>();
    private Queue<Integer> queue2 = new LinkedList<>();

    // Push element onto the stack
    public void push(int x) {
        queue2.add(x);

        // Move all elements from queue1 to queue2
        while (!queue1.isEmpty()) {
            queue2.add(queue1.remove());
        }

        // Swap queue1 and queue2
        Queue<Integer> temp = queue1;
        queue1 = queue2;
        queue2 = temp;
    }

    // Removes the top element
    public int pop() {
        if (queue1.isEmpty()) {
            System.out.println("Stack Underflow!");
            return -1;
        }
        return queue1.remove();
    }

    // Returns the top element
    public int top() {
        if (queue1.isEmpty()) {
            System.out.println("Stack is empty!");
            return -1;
        }
        return queue1.peek();
    }

    // Check if the stack is empty
    public boolean isEmpty() {
        return queue1.isEmpty();
    }

    // Test the implementation
    public static void main(String[] args) {
        StackUsingQueues stack = new StackUsingQueues();

        System.out.println("Pushing elements: 10, 20, 30");
        stack.push(10);
        stack.push(20);
        stack.push(30);

        System.out.println("Top element: " + stack.top());  // Expected: 30
        System.out.println("Popped: " + stack.pop());       // Expected: 30
        System.out.println("Top after pop: " + stack.top()); // Expected: 20
        System.out.println("Is stack empty? " + stack.isEmpty()); // Expected: false
    }
}
