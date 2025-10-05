import java.util.Scanner;

class Queue {
    private int front, rear, size;
    private int capacity;
    private int[] queueArray;

    // Constructor
    public Queue(int capacity) {
        this.capacity = capacity;
        queueArray = new int[capacity];
        front = 0;
        size = 0;
        rear = -1;
    }

    // Check if queue is full
    public boolean isFull() {
        return size == capacity;
    }

    // Check if queue is empty
    public boolean isEmpty() {
        return size == 0;
    }

    // Add element to the queue
    public void enqueue(int item) {
        if (isFull()) {
            System.out.println("Queue is full! Cannot enqueue " + item);
            return;
        }
        rear = (rear + 1) % capacity;
        queueArray[rear] = item;
        size++;
        System.out.println(item + " enqueued to queue.");
    }

    // Remove element from the queue
    public int dequeue() {
        if (isEmpty()) {
            System.out.println("Queue is empty! Nothing to dequeue.");
            return -1;
        }
        int item = queueArray[front];
        front = (front + 1) % capacity;
        size--;
        System.out.println(item + " dequeued from queue.");
        return item;
    }

    // View the front element
    public int peek() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return -1;
        }
        return queueArray[front];
    }

    // Display all elements
    public void display() {
        if (isEmpty()) {
            System.out.println("Queue is empty!");
            return;
        }
        System.out.print("Queue elements: ");
        for (int i = 0; i < size; i++) {
            int index = (front + i) % capacity;
            System.out.print(queueArray[index] + " ");
        }
        System.out.println();
    }
}

public class QueueDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter queue capacity: ");
        int capacity = sc.nextInt();

        Queue q = new Queue(capacity);

        while (true) {
            System.out.println("\n1. Enqueue");
            System.out.println("2. Dequeue");
            System.out.println("3. Peek");
            System.out.println("4. Display");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");

            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter value to enqueue: ");
                    int val = sc.nextInt();
                    q.enqueue(val);
                    break;
                case 2:
                    q.dequeue();
                    break;
                case 3:
                    System.out.println("Front element: " + q.peek());
                    break;
                case 4:
                    q.display();
                    break;
                case 5:
                    System.out.println("Exiting...");
                    sc.close();
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice!");
            }
        }
    }
}
