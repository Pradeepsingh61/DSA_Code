/*
 * Algorithm Name
A* Search Algorithm

Programming Language
Java

Category
Searching

Difficulty Level
Medium (Intermediate)

Algorithm Description
A* (A-star) Search is a classic graph traversal and pathfinding algorithm that finds the shortest path from a start node to a target node. It combines features of Dijkstra’s Algorithm and Greedy Best-First Search by using a cost function (g + h) that balances path cost and heuristic estimate. A* is widely used in AI, games, robotics, and route planning due to its optimality and efficiency. Adding A* would expand the repository’s graph algorithms and offer a key tool for competitive programming, game development, and more.


*/
import java.util.*;

class Node implements Comparable<Node> {
    int x, y;          // Position on grid
    int g;             // Cost from start node
    int h;             // Heuristic cost to target
    int f;             // Total cost = g + h
    Node parent;       // To reconstruct path

    Node(int x, int y, int g, int h, Node parent) {
        this.x = x;
        this.y = y;
        this.g = g;
        this.h = h;
        this.f = g + h;
        this.parent = parent;
    }

    @Override
    public int compareTo(Node other) {
        return this.f - other.f; // Min-heap based on f
    }
}

public class AStarSearch {
    static int ROWS = 5;
    static int COLS = 5;

    // Directions: up, down, left, right
    static int[][] directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    // Heuristic function: Manhattan distance
    static int heuristic(int x, int y, int targetX, int targetY) {
        return Math.abs(x - targetX) + Math.abs(y - targetY);
    }

    public static List<int[]> aStar(int[][] grid, int[] start, int[] target) {
        boolean[][] visited = new boolean[ROWS][COLS];
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(start[0], start[1], 0, heuristic(start[0], start[1], target[0], target[1]), null));

        while (!pq.isEmpty()) {
            Node current = pq.poll();

            if (visited[current.x][current.y]) continue;
            visited[current.x][current.y] = true;

            // Target reached
            if (current.x == target[0] && current.y == target[1]) {
                List<int[]> path = new ArrayList<>();
                Node temp = current;
                while (temp != null) {
                    path.add(new int[]{temp.x, temp.y});
                    temp = temp.parent;
                }
                Collections.reverse(path);
                return path;
            }

            // Explore neighbors
            for (int[] dir : directions) {
                int nx = current.x + dir[0];
                int ny = current.y + dir[1];
                if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && grid[nx][ny] == 0 && !visited[nx][ny]) {
                    int gNew = current.g + 1;
                    int hNew = heuristic(nx, ny, target[0], target[1]);
                    pq.add(new Node(nx, ny, gNew, hNew, current));
                }
            }
        }

        return null; // No path found
    }

    public static void main(String[] args) {
        int[][] grid = {   // 0 = free cell, 1 = obstacle
            {0, 0, 0, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        };

        int[] start = {0, 0};
        int[] target = {4, 4};

        List<int[]> path = aStar(grid, start, target);

        if (path != null) {
            System.out.println("Shortest Path:");
            for (int[] p : path) System.out.println(Arrays.toString(p));
        } else {
            System.out.println("No path found!");
        }
    }
}

/*
 * Time Complexity: 
O(E) in worst case, but depends on heuristic quality

Space Complexity: 
O(V) for open/closed sets
 */

 /* 
Output
Shortest Path:
[0, 0]
[0, 1]
[0, 2]
[0, 3]
[0, 4]
[1, 4]
[2, 4]
[3, 4]
[4, 4]
 */