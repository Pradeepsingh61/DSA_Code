/*
 * Algorithm Name:Spiral Matrix2 .
 * Programming Language: Java
 * Category: Array ,matrix
 * Difficulty Level: Medium
 *
 * Author: Priya Rani 
 *
 * Algorithm Description: Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
 * Input: n = 3
   Output: [[1,2,3],[8,9,4],[7,6,5]]
   Example 2:
   Input: n = 1
   Output: [[1]]

 

 * Time Complexity: O(1) Time complexity: O(n²)
 * Space complexity: O(1) (excluding output matrix)
*/
import java.util.*;

public class SpiralMatrixII {
    public int[][] generateMatrix(int n) {
        int[][] matrix = new int[n][n];
        int left = 0, right = n - 1;
        int top = 0, bottom = n - 1;
        int num = 1;

        while (left <= right && top <= bottom) {
            for (int i = left; i <= right; i++) {
                matrix[top][i] = num++;
            }
            top++;

            for (int i = top; i <= bottom; i++) {
                matrix[i][right] = num++;
            }
            right--;

            if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    matrix[bottom][i] = num++;
                }
                bottom--;
            }

            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    matrix[i][left] = num++;
                }
                left++;
            }
        }

        return matrix;
    }

    public static void main(String[] args) {
        SpiralMatrixII sm = new SpiralMatrixII();
        int n = 3;
        int[][] result = sm.generateMatrix(n);

        for (int[] row : result) {
            System.out.println(Arrays.toString(row));
        }
    }
}

