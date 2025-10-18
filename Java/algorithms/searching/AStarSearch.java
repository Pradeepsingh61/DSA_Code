/**
 * A* (A-star) Search Algorithm in Java
 *
 * A* is a pathfinding algorithm used to find the shortest path
 * from a start node to a target node in a graph. It combines
 * features of Dijkstra's algorithm and Greedy Best-First Search.
 *
 * f(n) = g(n) + h(n)
 * g(n) = cost from start to node n
 * h(n) = heuristic estimate from node n to target
 *
 * Author: Your Name
 */

import java.util.*;

class Node implements Comparable<Node> {
    int id;
    int gCost; // Cost from start node
    int hCost; // Heuristic cost to target
    int fCost; // Total cost = g + h
    Node parent;

    public Node(int id) {
        this.id = id;
    }

    @Override
    public int compareTo(Node other) {
        return this.fCost - other.fCost;
    }
}

public class AStarSearch {

    private static int heuristic(int current, int target) {
        // Simple heuristic (can be improved depending on graph)
        return Math.abs(current - target);
    }

    public static List<Integer> aStar(int[][] graph, int start, int target) {
        int n = graph.length;
        Node[] nodes = new Node[n];
        for (int i = 0; i < n; i++) nodes[i] = new Node(i);

        PriorityQueue<Node> openSet = new PriorityQueue<>();
        boolean[] closedSet = new boolean[n];

        nodes[start].gCost = 0;
        nodes[start].hCost = heuristic(start, target);
        nodes[start].fCost = nodes[start].gCost + nodes[start].hCost;
        openSet.add(nodes[start]);

        while (!openSet.isEmpty()) {
            Node current = openSet.poll();

            if (current.id == target) {
                // Path found, reconstruct path
                List<Integer> path = new ArrayList<>();
                Node temp = current;
                while (temp != null) {
                    path.add(temp.id);
                    temp = temp.parent;
                }
                Collections.reverse(path);
                return path;
            }

            closedSet[current.id] = true;

            // Explore neighbors
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (graph[current.id][neighbor] > 0 && !closedSet[neighbor]) {
                    int tentativeG = current.gCost + graph[current.id][neighbor];
                    Node neighborNode = nodes[neighbor];

                    if (!openSet.contains(neighborNode) || tentativeG < neighborNode.gCost) {
                        neighborNode.gCost = tentativeG;
                        neighborNode.hCost = heuristic(neighbor, target);
                        neighborNode.fCost = neighborNode.gCost + neighborNode.hCost;
                        neighborNode.parent = current;

                        if (!openSet.contains(neighborNode)) openSet.add(neighborNode);
                    }
                }
            }
        }

        return new ArrayList<>(); // No path found
    }

    // Example usage
    public static void main(String[] args) {
        // Example graph (adjacency matrix)
        int[][] graph = {
            {0, 1, 4, 0, 0, 0},
            {1, 0, 4, 2, 7, 0},
            {4, 4, 0, 3, 5, 0},
            {0, 2, 3, 0, 4, 6},
            {0, 7, 5, 4, 0, 7},
            {0, 0, 0, 6, 7, 0}
        };

        int start = 0;
        int target = 5;
        List<Integer> path = aStar(graph, start, target);

        if (!path.isEmpty()) {
            System.out.println("Shortest path from " + start + " to " + target + ": " + path);
        } else {
            System.out.println("No path found from " + start + " to " + target);
        }
    }
}
