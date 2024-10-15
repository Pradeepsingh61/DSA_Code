import java.util.*;

public class Max {
    public static void main(String[] args) {
        // Create a max-priority queue using a comparator
        PriorityQueue<Integer> maxPriorityQueue = new PriorityQueue<>(Collections.reverseOrder());

        // Adding elements to the max-priority queue
        maxPriorityQueue.add(10);
        maxPriorityQueue.add(5);
        maxPriorityQueue.add(20);
        maxPriorityQueue.add(15);

        System.out.println("Max Priority Queue: " + maxPriorityQueue);

        // Retrieve and remove the highest priority element (largest number)
        System.out.println("Polling from the max queue: " + maxPriorityQueue.poll());

        maxPriorityQueue.add(2);
        maxPriorityQueue.add(8);

        // Print the priority queue after adding new elements
        System.out.println("Priority Queue after adding more elements: " + maxPriorityQueue);

        // View the current highest priority element without removing it
        System.out.println("Peek at the max queue: " + maxPriorityQueue.peek());

        // Print the max priority queue after polling
        System.out.println("Max Priority Queue after polling: " + maxPriorityQueue);

        while (!maxPriorityQueue.isEmpty()) {
            System.out.println("Removing: " + maxPriorityQueue.poll());
        }
        System.out.println("Priority Queue is empty: " + maxPriorityQueue.isEmpty());
    }
}
