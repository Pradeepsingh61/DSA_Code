import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 * ✍️ Algorithm: Flood Fill (LeetCode 733)
 * * 📖 Description:
 * The Flood Fill algorithm is used to fill a connected region of a multi-dimensional array 
 * with a specific color. Starting from a given seed pixel, it changes the color of all 
 * pixels that are connected to it (4-directionally) and have the same original color.
 *
 * 💡 Approach & Methodology:
 * This problem can be solved using standard graph traversal algorithms. The grid of pixels
 * is treated as a graph where each pixel is a node and adjacent pixels with the same color
 * have an edge between them.
 * This file provides two common implementations:
 * 1.  DFS (Depth-First Search): A recursive approach that explores as far as possible down
 * each path before backtracking. It's concise and elegant.
 * 2.  BFS (Breadth-First Search): An iterative approach using a queue that explores all
 * neighboring pixels level by level. It's useful for finding the shortest path but
 * works equally well here.
 *
 * 📊 Complexity Analysis:
 * Let N be the number of rows and M be the number of columns in the image.
 * * - Time Complexity: O(N * M)
 * In the worst-case scenario, the algorithm has to visit every pixel in the grid once
 * to check its color and potentially change it. Both DFS and BFS ensure that each
 * pixel is processed at most once.
 *
 * - Space Complexity: O(N * M)
 * - DFS: The space complexity is determined by the maximum depth of the recursion stack.
 * In the worst case (e.g., a long, snake-like path), the recursion depth could be
 * proportional to the total number of pixels.
 * - BFS: The space complexity is determined by the maximum size of the queue. In the
 * worst case (e.g., a checkerboard pattern), the queue could hold a significant
 * fraction of the pixels.
 *
 * 🎯 Use Cases & Applications:
 * - "Paint Bucket" tool in image editing software (e.g., Photoshop, MS Paint).
 * - Finding connected components in a grid or matrix.
 * - Pathfinding and solving maze puzzles in games.
 */
public class FloodFill {

    //=========================================================================
    // 1. Depth-First Search (DFS) Approach - Recursive
    //=========================================================================

    /**
     * Fills a region of the image with a new color using a recursive DFS approach.
     *
     * @param image The 2D integer array representing the image.
     * @param sr    The starting row index.
     * @param sc    The starting column index.
     * @param color The new color to fill with.
     * @return The modified image after the flood fill.
     */
    public int[][] floodFillDFS(int[][] image, int sr, int sc, int color) {
        // Get the original color of the starting pixel.
        int originalColor = image[sr][sc];

        // Edge Case: If the original color is the same as the new color,
        // no changes are needed. Return the image as is to avoid infinite recursion.
        if (originalColor == color) {
            return image;
        }

        // Start the recursive DFS traversal from the starting pixel.
        dfs(image, sr, sc, originalColor, color);

        return image;
    }

    /**
     * Helper method to perform the recursive depth-first search.
     *
     * @param image         The image grid.
     * @param r             The current row.
     * @param c             The current column.
     * @param originalColor The color of the region to be replaced.
     * @param newColor      The color to fill the region with.
     */
    private void dfs(int[][] image, int r, int c, int originalColor, int newColor) {
        // Base Case for recursion:
        // 1. Check for out-of-bounds rows (r < 0 or r >= height).
        // 2. Check for out-of-bounds columns (c < 0 or c >= width).
        // 3. Check if the current pixel's color is not the original color we want to replace.
        if (r < 0 || r >= image.length || c < 0 || c >= image[0].length || image[r][c] != originalColor) {
            return;
        }

        // Change the color of the current pixel.
        image[r][c] = newColor;

        // Recursively call dfs for all 4-directionally connected neighbors.
        dfs(image, r + 1, c, originalColor, newColor); // Down
        dfs(image, r - 1, c, originalColor, newColor); // Up
        dfs(image, r, c + 1, originalColor, newColor); // Right
        dfs(image, r, c - 1, originalColor, newColor); // Left
    }


    //=========================================================================
    // 2. Breadth-First Search (BFS) Approach - Iterative with Queue
    //=========================================================================

    /**
     * Fills a region of the image with a new color using an iterative BFS approach.
     *
     * @param image The 2D integer array representing the image.
     * @param sr    The starting row index.
     * @param sc    The starting column index.
     * @param color The new color to fill with.
     * @return The modified image after the flood fill.
     */
    public int[][] floodFillBFS(int[][] image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];

        // Edge Case: If the start color is already the target color, do nothing.
        if (originalColor == color) {
            return image;
        }

        int rows = image.length;
        int cols = image[0].length;

        // Queue for BFS, storing coordinates as int arrays {row, col}.
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{sr, sc}); // Add the starting pixel to the queue.

        // Change the color of the starting pixel immediately.
        image[sr][sc] = color;

        // Define the 4 directions (up, down, left, right).
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Process the queue until it's empty.
        while (!queue.isEmpty()) {
            // Dequeue the current pixel.
            int[] currentPixel = queue.poll();
            int r = currentPixel[0];
            int c = currentPixel[1];

            // Explore its 4-directional neighbors.
            for (int[] dir : directions) {
                int newR = r + dir[0];
                int newC = c + dir[1];

                // Check for valid neighbors:
                // 1. Within grid boundaries.
                // 2. Has the original color we are trying to replace.
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && image[newR][newC] == originalColor) {
                    // Change the neighbor's color.
                    image[newR][newC] = color;
                    // Enqueue the neighbor to process its neighbors later.
                    queue.add(new int[]{newR, newC});
                }
            }
        }

        return image;
    }

    //=========================================================================
    // Main method for demonstration and testing (Test Cases)
    //=========================================================================

    public static void main(String[] args) {
        FloodFill solver = new FloodFill();

        System.out.println("--- DFS Approach ---");
        int[][] image1 = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };
        int sr1 = 1, sc1 = 1, color1 = 2;
        System.out.println("Original Image:");
        printImage(image1);
        int[][] resultDFS = solver.floodFillDFS(image1, sr1, sc1, color1);
        System.out.println("\nModified Image (DFS):");
        printImage(resultDFS);

        System.out.println("\n---------------------\n");

        System.out.println("--- BFS Approach ---");
        int[][] image2 = {
            {0, 0, 0},
            {0, 1, 1},
            {0, 1, 1}
        };
        int sr2 = 1, sc2 = 1, color2 = 5;
        System.out.println("Original Image:");
        printImage(image2);
        int[][] resultBFS = solver.floodFillBFS(image2, sr2, sc2, color2);
        System.out.println("\nModified Image (BFS):");
        printImage(resultBFS);
    }

    /**
     * Utility method to print the 2D image array for easy visualization.
     */
    public static void printImage(int[][] image) {
        for (int[] row : image) {
            System.out.println(Arrays.toString(row));
        }
    }
}