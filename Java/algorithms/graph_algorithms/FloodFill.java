import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Implements the Flood Fill algorithm using both DFS and BFS approaches.
 * LeetCode Problem 733: https://leetcode.com/problems/flood-fill/
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
    // Main method for demonstration and testing
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
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };
        int sr2 = 1, sc2 = 1, color2 = 2;
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