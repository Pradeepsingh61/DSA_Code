// Queue implementation in Java using Linked List
// Author: Asmita Roy
// Concept: FIFO (First In First Out)

// Each element in the queue is represented by a Node.
// This version demonstrates OOP concepts: Class Composition and Encapsulation.

class Node {
    int data;       // data field
    Node next;      // reference to the next node

    // Constructor to initialize node
    Node(int data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedQueue {
    private Node front, rear; // Pointers to the front and rear of the queue
    private int size;         // Keep track of queue size

    // Constructor: create an empty queue
    public LinkedQueue() {
        front = rear = null;
        size = 0;
    }

    // Method to check if the queue is empty
    public boolean isEmpty() {
        return front == null;
    }

    // Method to add (enqueue) an element
    public void enqueue(int data) {
        Node newNode = new Node(data);
        if (rear == null) {  // If queue is empty
            front = rear = newNode;
        } else {
            rear.next = newNode;
            rear = newNode;
        }
        size++;
        System.out.println(data + " enqueued to queue.");
    }

    // Method to remove (dequeue) an element
    public int dequeue() {
        if (isEmpty()) {
            System.out.println("Queue Underflow! Cannot dequeue element.");
            return -1;
        }
        int value = front.data;
        front = front.next;

        // If front becomes null, queue is now empty
        if (front == null)
            rear = null;

        size--;
        System.out.println(value + " dequeued from queue.");
        return value;
    }

    // Method to get the front element
    public int peek() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return -1;
        }
        return front.data;
    }

    // Method to get the current size of the queue
    public int getSize() {
        return size;
    }

    // Method to display all elements in the queue
    public void display() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return;
        }
        System.out.print("Queue elements (front to rear): ");
        Node temp = front;
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }
}

// Main class to test the queue
public class QueueUsingLL {
    public static void main(String[] args) {
        LinkedQueue queue = new LinkedQueue();

        // Enqueue elements
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        queue.enqueue(40);

        // Display queue
        queue.display();

        // Peek the front element
        System.out.println("Front element: " + queue.peek());

        // Dequeue elements
        queue.dequeue();
        queue.dequeue();

        // Display queue again
        queue.display();

        // Check size
        System.out.println("Current Queue size: " + queue.getSize());
    }
}
