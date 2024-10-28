import java.util.PriorityQueue;
import java.util.Scanner;

public class OptimalMergePattern {

    // Function to find the optimal merge pattern
    static int optimalMergePattern(int[] files) {
        // Create a priority queue (min-heap)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        // Insert all file sizes into the min-heap
        for (int file : files)
            minHeap.add(file);

        int totalCost = 0;

        // Repeat the process until there is only one file left
        while (minHeap.size() > 1) {
            // Extract the two smallest files
            int first = minHeap.poll();
            int second = minHeap.poll();

            // Merge them and calculate the cost
            int mergeCost = first + second;
            totalCost += mergeCost;

            // Push the merged file back into the heap
            minHeap.add(mergeCost);
        }

        return totalCost;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of files: ");
        int n = scanner.nextInt();

        int[] files = new int[n];
        System.out.println("Enter the file sizes:");
        for (int i = 0; i < n; i++) {
            System.out.print("File " + (i + 1) + ": ");
            files[i] = scanner.nextInt();
        }

        int minCost = optimalMergePattern(files);
        System.out.println("Minimum cost to merge files: " + minCost);

        scanner.close();
    }
}
