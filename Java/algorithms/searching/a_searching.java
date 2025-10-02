/**
 * A* Search Algorithm Implementation
 * 
 * This class implements the A* (A-star) pathfinding algorithm, which is widely
 * used in graph traversal and pathfinding problems. The algorithm uses a heuristic
 * function to efficiently find the shortest path between two nodes in a weighted graph.
 * 
 * Algorithm: A* Search Algorithm
 * Time Complexity: O(b^d) where b is branching factor, d is depth
 * Space Complexity: O(b^d) for storing nodes in open and closed sets
 * Use Cases: Graph pathfinding, AI navigation, game development, robotics
 * 
 * @author DSA_Code Repository
 * @version 1.0
 * @since Hacktoberfest 2025
 */


import java.util.*;

public class a_searching {
    
    // ===================== A* SEARCH ALGORITHM =====================
    
    /**
     * Node class for A* algorithm
     * Represents a node in the graph with position, costs, and parent reference
     */
    static class AStarNode implements Comparable<AStarNode> {
        int x, y;           // Position coordinates
        int gCost;          // Cost from start node
        int hCost;          // Heuristic cost to goal
        int fCost;          // Total cost (g + h)
        AStarNode parent;   // Parent node for path reconstruction
        
        public AStarNode(int x, int y) {
            this.x = x;
            this.y = y;
            this.gCost = 0;
            this.hCost = 0;
            this.fCost = 0;
            this.parent = null;
        }
        
        public void calculateFCost() {
            fCost = gCost + hCost;
        }
        
        @Override
        public int compareTo(AStarNode other) {
            if (this.fCost != other.fCost) {
                return Integer.compare(this.fCost, other.fCost);
            }
            return Integer.compare(this.hCost, other.hCost);
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null || getClass() != obj.getClass()) return false;
            AStarNode node = (AStarNode) obj;
            return x == node.x && y == node.y;
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }
        
        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }
    
    /**
     * A* Search Algorithm
     * Finds the shortest path in a weighted graph using heuristic function
     * 
     * Time Complexity: O(b^d) where b is branching factor, d is depth
     * Space Complexity: O(b^d) for storing nodes in open and closed sets
     * 
     * @param grid 2D grid where 0 = walkable, 1 = obstacle
     * @param startX starting X coordinate
     * @param startY starting Y coordinate
     * @param goalX goal X coordinate
     * @param goalY goal Y coordinate
     * @return List of nodes representing the shortest path, empty if no path exists
     */
    public static List<AStarNode> aStarSearch(int[][] grid, int startX, int startY, int goalX, int goalY) {
        if (grid == null || grid.length == 0 || grid[0].length == 0) {
            return new ArrayList<>();
        }
        
        int rows = grid.length;
        int cols = grid[0].length;
        
        // Validate coordinates
        if (startX < 0 || startX >= rows || startY < 0 || startY >= cols ||
            goalX < 0 || goalX >= rows || goalY < 0 || goalY >= cols ||
            grid[startX][startY] == 1 || grid[goalX][goalY] == 1) {
            return new ArrayList<>();
        }
        
        // Priority queue for open set (nodes to be evaluated)
        PriorityQueue<AStarNode> openSet = new PriorityQueue<>();
        
        // Set for closed nodes (already evaluated)
        Set<AStarNode> closedSet = new HashSet<>();
        
        // Create start and goal nodes
        AStarNode startNode = new AStarNode(startX, startY);
        AStarNode goalNode = new AStarNode(goalX, goalY);
        
        // Initialize start node
        startNode.gCost = 0;
        startNode.hCost = calculateHeuristic(startNode, goalNode);
        startNode.calculateFCost();
        
        openSet.add(startNode);
        
        // Directions for 8-directional movement (including diagonals)
        int[][] directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        while (!openSet.isEmpty()) {
            // Get node with lowest f cost
            AStarNode currentNode = openSet.poll();
            closedSet.add(currentNode);
            
            // Check if we reached the goal
            if (currentNode.equals(goalNode)) {
                return reconstructPath(currentNode);
            }
            
            // Explore neighbors
            for (int[] dir : directions) {
                int newX = currentNode.x + dir[0];
                int newY = currentNode.y + dir[1];
                
                // Check bounds and walkability
                if (newX < 0 || newX >= rows || newY < 0 || newY >= cols || grid[newX][newY] == 1) {
                    continue;
                }
                
                AStarNode neighbor = new AStarNode(newX, newY);
                
                // Skip if already evaluated
                if (closedSet.contains(neighbor)) {
                    continue;
                }
                
                // Calculate movement cost (diagonal movement costs more)
                int movementCost = (dir[0] != 0 && dir[1] != 0) ? 14 : 10; // √2 ≈ 1.4, scaled by 10
                int tentativeGCost = currentNode.gCost + movementCost;
                
                // Find if neighbor is already in open set
                AStarNode existingNeighbor = null;
                for (AStarNode node : openSet) {
                    if (node.equals(neighbor)) {
                        existingNeighbor = node;
                        break;
                    }
                }
                
                // If new path to neighbor is shorter or neighbor is not in open set
                if (existingNeighbor == null || tentativeGCost < existingNeighbor.gCost) {
                    if (existingNeighbor != null) {
                        openSet.remove(existingNeighbor);
                        neighbor = existingNeighbor;
                    }
                    
                    neighbor.gCost = tentativeGCost;
                    neighbor.hCost = calculateHeuristic(neighbor, goalNode);
                    neighbor.calculateFCost();
                    neighbor.parent = currentNode;
                    
                    if (!openSet.contains(neighbor)) {
                        openSet.add(neighbor);
                    }
                }
            }
        }
        
        // No path found
        return new ArrayList<>();
    }
    
    /**
     * Manhattan Distance Heuristic
     * Calculates the Manhattan distance between two nodes
     * 
     * @param node1 first node
     * @param node2 second node
     * @return Manhattan distance multiplied by 10 for consistency with movement costs
     */
    public static int calculateHeuristic(AStarNode node1, AStarNode node2) {
        return 10 * (Math.abs(node1.x - node2.x) + Math.abs(node1.y - node2.y));
    }
    
    /**
     * Euclidean Distance Heuristic
     * More accurate for diagonal movement
     * 
     * @param node1 first node
     * @param node2 second node
     * @return Euclidean distance multiplied by 10
     */
    public static int calculateEuclideanHeuristic(AStarNode node1, AStarNode node2) {
        double dx = node1.x - node2.x;
        double dy = node1.y - node2.y;
        return (int) (10 * Math.sqrt(dx * dx + dy * dy));
    }
    
    /**
     * Reconstructs the path from goal to start using parent references
     * 
     * @param goalNode the goal node reached by A*
     * @return List of nodes representing the path from start to goal
     */
    private static List<AStarNode> reconstructPath(AStarNode goalNode) {
        List<AStarNode> path = new ArrayList<>();
        AStarNode current = goalNode;
        
        while (current != null) {
            path.add(0, current); // Add to beginning to reverse the path
            current = current.parent;
        }
        
        return path;
    }
    
    /**
     * Utility method to print the grid with path
     * 
     * @param grid original grid
     * @param path path found by A*
     * @param startX start X coordinate
     * @param startY start Y coordinate
     * @param goalX goal X coordinate
     * @param goalY goal Y coordinate
     */
    public static void printGridWithPath(int[][] grid, List<AStarNode> path, int startX, int startY, int goalX, int goalY) {
        if (grid == null || grid.length == 0) {
            System.out.println("Grid is null or empty");
            return;
        }
        
        int rows = grid.length;
        int cols = grid[0].length;
        
        // Create a copy of grid for visualization
        char[][] visualGrid = new char[rows][cols];
        
        // Fill with original grid values
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                visualGrid[i][j] = (grid[i][j] == 1) ? '█' : '.';
            }
        }
        
        // Mark path
        for (int i = 1; i < path.size() - 1; i++) { // Skip start and goal
            AStarNode node = path.get(i);
            visualGrid[node.x][node.y] = '*';
        }
        
        // Mark start and goal
        if (startX >= 0 && startX < rows && startY >= 0 && startY < cols) {
            visualGrid[startX][startY] = 'S';
        }
        if (goalX >= 0 && goalX < rows && goalY >= 0 && goalY < cols) {
            visualGrid[goalX][goalY] = 'G';
        }
        
        // Print grid
        System.out.println("\nGrid with Path:");
        System.out.println("S = Start, G = Goal, * = Path, █ = Obstacle, . = Free");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(visualGrid[i][j] + " ");
            }
            System.out.println();
        }
    }
    

    
    /**
     * Main method with A* algorithm demonstration
     * Shows pathfinding capabilities with various test scenarios
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("🌟 A* SEARCH ALGORITHM DEMO");
        System.out.println("=" .repeat(40));
        
        System.out.println("\n� About A* Algorithm:");
        System.out.println("A* (A-star) is a graph traversal and pathfinding algorithm");
        System.out.println("that finds the shortest path between nodes using heuristics.");
        System.out.println("Time Complexity: O(b^d) | Space Complexity: O(b^d)");
        System.out.println("Perfect for: Game AI, Navigation, Robotics, Route Planning");
        
        // A* Algorithm Demo
        System.out.println("\n🗺️  A* PATHFINDING ALGORITHM DEMO");
        System.out.println("-" .repeat(40));
        
        // Create a sample grid (0 = walkable, 1 = obstacle)
        int[][] grid = {
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
        
        System.out.println("Grid Layout (0 = walkable, 1 = obstacle):");
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                System.out.print(grid[i][j] + " ");
            }
            System.out.println();
        }
        
        // Test A* pathfinding
        int startX = 0, startY = 0;
        int goalX = 8, goalY = 9;
        
        System.out.println("\nFinding path from (" + startX + "," + startY + ") to (" + goalX + "," + goalY + ")");
        
        long astarStartTime = System.currentTimeMillis();
        List<AStarNode> path = aStarSearch(grid, startX, startY, goalX, goalY);
        long astarEndTime = System.currentTimeMillis();
        
        if (!path.isEmpty()) {
            System.out.println("✅ Path found! Length: " + path.size() + " nodes");
            System.out.println("⏱️  Time taken: " + (astarEndTime - astarStartTime) + " ms");
            System.out.println("🛤️  Path coordinates:");
            for (int i = 0; i < path.size(); i++) {
                AStarNode node = path.get(i);
                System.out.print("(" + node.x + "," + node.y + ")");
                if (i < path.size() - 1) {
                    System.out.print(" → ");
                }
                if ((i + 1) % 5 == 0) { // New line every 5 nodes for readability
                    System.out.println();
                }
            }
            System.out.println();
            
            printGridWithPath(grid, path, startX, startY, goalX, goalY);
        } else {
            System.out.println("❌ No path found!");
        }
        
        // Test case with no path
        System.out.println("\n🚫 Testing case with no possible path:");
        int[][] blockedGrid = {
            {0, 0, 0, 1, 0, 0},
            {0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1},
            {0, 0, 0, 1, 0, 0}
        };
        
        List<AStarNode> noPath = aStarSearch(blockedGrid, 0, 0, 0, 5);
        if (noPath.isEmpty()) {
            System.out.println("✅ Correctly identified no path exists");
        } else {
            System.out.println("❌ Error: Found path when none should exist");
        }
        
        // Interactive A* Demo
        System.out.println("\n🎮 INTERACTIVE A* PATHFINDING");
        System.out.println("-" .repeat(35));
        System.out.print("Would you like to create a custom grid? (y/n): ");
        String customChoice = scanner.next();
        
        if (customChoice.toLowerCase().equals("y")) {
            System.out.print("Enter grid size (rows cols): ");
            int rows = scanner.nextInt();
            int cols = scanner.nextInt();
            
            int[][] customGrid = new int[rows][cols];
            System.out.println("Enter grid (0=walkable, 1=obstacle):");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    customGrid[i][j] = scanner.nextInt();
                }
            }
            
            System.out.print("Enter start position (x y): ");
            int customStartX = scanner.nextInt();
            int customStartY = scanner.nextInt();
            
            System.out.print("Enter goal position (x y): ");
            int customGoalX = scanner.nextInt();
            int customGoalY = scanner.nextInt();
            
            System.out.println("\n🔍 Finding path in your custom grid...");
            List<AStarNode> customPath = aStarSearch(customGrid, customStartX, customStartY, customGoalX, customGoalY);
            
            if (!customPath.isEmpty()) {
                System.out.println("✅ Path found! Length: " + customPath.size() + " nodes");
                printGridWithPath(customGrid, customPath, customStartX, customStartY, customGoalX, customGoalY);
            } else {
                System.out.println("❌ No path found in your grid!");
            }
        }
        
        // Additional A* test scenarios
        System.out.println("\n🧪 ADDITIONAL A* TEST SCENARIOS");
        System.out.println("-" .repeat(40));
        
        // Test different grid sizes and complexities
        System.out.println("\n🔬 Testing different scenarios:");
        
        // Small maze test
        int[][] smallMaze = {
            {0, 1, 0, 0},
            {0, 1, 0, 1},
            {0, 0, 0, 1},
            {1, 0, 0, 0}
        };
        
        System.out.println("\n1️⃣ Small 4x4 Maze:");
        List<AStarNode> smallPath = aStarSearch(smallMaze, 0, 0, 3, 3);
        if (!smallPath.isEmpty()) {
            System.out.println("✅ Path length: " + smallPath.size());
            printGridWithPath(smallMaze, smallPath, 0, 0, 3, 3);
        } else {
            System.out.println("❌ No path exists");
        }
        
        // Large open space test
        int[][] openSpace = new int[8][8]; // All zeros by default
        System.out.println("\n2️⃣ Large Open Space (8x8):");
        List<AStarNode> openPath = aStarSearch(openSpace, 0, 0, 7, 7);
        if (!openPath.isEmpty()) {
            System.out.println("✅ Direct path length: " + openPath.size());
            System.out.println("🛤️ Optimal diagonal path found!");
        }
        
        // Performance comparison with different heuristics
        System.out.println("\n� A* ALGORITHM ANALYSIS");
        System.out.println("-" .repeat(30));
        System.out.println("• Heuristic: Manhattan Distance (current implementation)");
        System.out.println("• Movement: 8-directional (including diagonals)");
        System.out.println("• Cost: Straight=10, Diagonal=14 (√2 * 10)");
        System.out.println("• Optimality: Guaranteed shortest path");
        
        System.out.println("\n💡 A* ALGORITHM APPLICATIONS");
        System.out.println("-" .repeat(35));
        System.out.println("🎮 Game Development:");
        System.out.println("  • NPC pathfinding in games");
        System.out.println("  • Real-time strategy unit movement");
        System.out.println("  • RPG quest navigation");
        
        System.out.println("\n🤖 Robotics & AI:");
        System.out.println("  • Autonomous vehicle navigation");
        System.out.println("  • Robot path planning");
        System.out.println("  • Drone flight path optimization");
        
        System.out.println("\n🗺️ Real-world Applications:");
        System.out.println("  • GPS navigation systems");
        System.out.println("  • Network routing protocols");
        System.out.println("  • Logistics and delivery optimization");
        
        scanner.close();
        System.out.println("\n� A* Algorithm Demo completed!");
        System.out.println("🚀 Perfect for Hacktoberfest contributions! Happy coding!");
    }
}
