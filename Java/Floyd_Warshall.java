import java.util.Scanner;

public class FloydWarshall {
    final static int INF = 99999;

    // Function to print the solution matrix
    void printSolution(int dist[][], int V) {
        System.out.println("Shortest distances between every pair of vertices:");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF)
                    System.out.print("INF" + "     ");
                else
                    System.out.print(dist[i][j] + "     ");
            }
            System.out.println();
        }
    }

    // Function to implement the Floyd-Warshall algorithm
    void floydWarshall(int graph[][], int V) {
        int dist[][] = new int[V][V];

        // Initialize the distance matrix with the input graph
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                dist[i][j] = graph[i][j];

        // Update the distance matrix
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        printSolution(dist, V);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        FloydWarshall fw = new FloydWarshall();

        System.out.println("Enter the number of vertices:");
        int V = scanner.nextInt();  // User-defined number of vertices
        
        int[][] graph = new int[V][V];
        System.out.println("Enter the adjacency matrix (use " + INF + " for no direct path):");

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                System.out.print("Distance from vertex " + i + " to vertex " + j + ": ");
                graph[i][j] = scanner.nextInt();
            }
        }

        fw.floydWarshall(graph, V);  // Pass V as a parameter
        scanner.close();
    }
}
