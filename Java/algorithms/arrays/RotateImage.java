/*
 * Algorithm Name:Rotate Image .
 * Programming Language: Java
 * Category: Array ,matrix
 * Difficulty Level: Medium
 *
 * Author: Priya Rani 
 *
 * Algorithm Description: You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

  You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

 
* Time Complexity:	O(n²)	Each element is visited once during transpose and once during row reversal
* Space Complexity: O(1)	Rotation is done in-place without using extra data structures
*/
import java.util.*;

public class RotateImage {
    public void rotate(int[][] matrix) {
        int n = matrix.length;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }

    public static void main(String[] args) {
        RotateImage solution = new RotateImage();

        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        solution.rotate(matrix);


        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }
}
