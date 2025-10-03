import java.util.*;

class AStarSearch {
    static class Node implements Comparable<Node> {
        int x, y;
        int g; 
        int h; 
        Node parent;

        Node(int x, int y, int g, int h, Node parent) {
            this.x = x;
            this.y = y;
            this.g = g;
            this.h = h;
            this.parent = parent;
        }

        int f() {
            return g + h;
        }

        @Override
        public int compareTo(Node other) {
            return Integer.compare(this.f(), other.f());
        }

        @Override
        public boolean equals(Object obj) {
            if (!(obj instanceof Node)) return false;
            Node other = (Node) obj;
            return this.x == other.x && this.y == other.y;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }
    }

    private static int heuristic(int x1, int y1, int x2, int y2) {
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    public static List<int[]> aStar(int[][] grid, int[] start, int[] goal) {
        int rows = grid.length, cols = grid[0].length;
        PriorityQueue<Node> openSet = new PriorityQueue<>();
        Set<Node> closedSet = new HashSet<>();

        Node startNode = new Node(start[0], start[1], 0, heuristic(start[0], start[1], goal[0], goal[1]), null);
        openSet.add(startNode);

        int[][] directions = {{0,1},{1,0},{0,-1},{-1,0}}; 

        while (!openSet.isEmpty()) {
            Node current = openSet.poll();

            if (current.x == goal[0] && current.y == goal[1]) {
                List<int[]> path = new ArrayList<>();
                while (current != null) {
                    path.add(new int[]{current.x, current.y});
                    current = current.parent;
                }
                Collections.reverse(path);
                return path;
            }

            closedSet.add(current);

            for (int[] dir : directions) {
                int nx = current.x + dir[0], ny = current.y + dir[1];
                if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] == 1)
                    continue; 

                Node neighbor = new Node(nx, ny, current.g + 1, heuristic(nx, ny, goal[0], goal[1]), current);

                if (closedSet.contains(neighbor))
                    continue;

                boolean better = true;
                for (Node node : openSet) {
                    if (node.equals(neighbor) && node.g <= neighbor.g) {
                        better = false;
                        break;
                    }
                }
                if (better) {
                    openSet.add(neighbor);
                }
            }
        }
        return Collections.emptyList(); 
    }

    public static void main(String[] args) {
        int[][] grid = {
            {0, 0, 0, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        };
        int[] start = {0, 0};
        int[] goal = {4, 4};

        List<int[]> path = aStar(grid, start, goal);
        if (path.isEmpty()) {
            System.out.println("No path found.");
        } else {
            System.out.println("Path:");
            for (int[] p : path) {
                System.out.println(Arrays.toString(p));
            }
        }
    }
}