import java.util.Arrays;
import java.util.Scanner;

public class Dijkstra {
    static final int V = 5;

    int minDistance(int dist[], boolean sptSet[]) {
        int min = Integer.MAX_VALUE, minIndex = -1;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }

        return minIndex;
    }

    void dijkstra(int graph[][], int src) {
        int dist[] = new int[V];
        boolean sptSet[] = new boolean[V];

        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(sptSet, false);

        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; v++)
                if (!sptSet[v] && graph[u][v] != 0 && dist[u] != Integer.MAX_VALUE && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
        }

        System.out.println("Vertex \t Distance from Source");
        for (int i = 0; i < V; i++)
            System.out.println(i + " \t\t " + dist[i]);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Dijkstra dijkstra = new Dijkstra();

        int[][] graph = new int[V][V];
        System.out.println("Enter the adjacency matrix (enter 0 if no direct path exists):");

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                System.out.print("Distance from vertex " + i + " to vertex " + j + ": ");
                graph[i][j] = scanner.nextInt();
            }
        }

        System.out.print("Enter the source vertex: ");
        int source = scanner.nextInt();

        dijkstra.dijkstra(graph, source);
        scanner.close();
    }
}
