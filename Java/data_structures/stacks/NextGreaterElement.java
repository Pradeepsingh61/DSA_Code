/*
 * Algorithm Name:
 * Next Greater Element (NGE) using Stack
 *
 * Programming Language:
 * Java
 *
 * Category:
 * Data Structures / Stack Applications
 *
 * Difficulty Level:
 * Easy to Medium
 *
 * ---------------------------------------------------------------------
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> For every element in an array, find the next greater element
 *       to its right. If no greater element exists, assign -1.
 *
 * 2. Approach / Idea:
 *    -> Traverse the array from right to left.
 *    -> Use a stack to keep track of possible “next greater” candidates.
 *    -> For each element:
 *         - While stack is not empty and stack.top() <= current element,
 *           pop from stack (since it can't be the next greater for any earlier element).
 *         - If stack becomes empty → no greater element → assign -1.
 *         - Else → top of stack is the next greater element.
 *         - Push the current element onto the stack.
 *    -> Store results in an output array and print them.
 *
 * 3. Example:
 *    Input:  [4, 5, 2, 25]
 *    Output: [5, 25, 25, -1]
 *
 *    Input:  [13, 7, 6, 12]
 *    Output: [-1, 12, 12, -1]
 *
 * 4. Complexity:
 *    Time Complexity: O(n) — Each element is pushed and popped at most once.
 *    Space Complexity: O(n) — Stack and result array.
 *
 * 5. Author:
 *    Pradyumn Pratap Singh (Strange)
 * ---------------------------------------------------------------------
 */

package DSA_Code.Java.data_structures.stacks;
import java.util.*;

public class NextGreaterElement {

    // Function to find next greater elements
    public static int[] findNextGreaterElements(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Stack<Integer> stack = new Stack<>();

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {
            int current = arr[i];

            // Pop all smaller or equal elements
            while (!stack.isEmpty() && stack.peek() <= current) {
                stack.pop();
            }

            // If stack empty → no greater element
            if (stack.isEmpty()) {
                result[i] = -1;
            } else {
                result[i] = stack.peek();
            }

            // Push current element to stack
            stack.push(current);
        }

        return result;
    }

    // Main function for testing
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter " + n + " elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        int[] result = findNextGreaterElements(arr);

        System.out.println("Next Greater Elements:");
        for (int val : result) {
            System.out.print(val + " ");
        }

        sc.close();
    }
}
