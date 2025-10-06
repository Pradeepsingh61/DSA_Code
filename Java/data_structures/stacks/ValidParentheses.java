/*
 * Algorithm Name:
 * Valid Parentheses Check using Stack
 *
 * Programming Language:
 * Java
 *
 * Category:
 * Data Structures / Stack Applications
 *
 * Difficulty Level:
 * Easy
 *
 * ---------------------------------------------------------------------
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> Checks whether a given string containing parentheses (such as (), {}, [])
 *       is valid — meaning every opening bracket has a corresponding closing one
 *       in the correct order.
 *
 * 2. Approach / Idea:
 *    -> Traverse the string one character at a time.
 *    -> Push every opening bracket ('(', '{', '[') onto the stack.
 *    -> For every closing bracket (')', '}', ']'):
 *         - Check if the stack is empty → invalid.
 *         - Otherwise, pop the top element and verify if it matches the type of the closing bracket.
 *    -> At the end, the stack should be empty for the expression to be valid.
 *
 * 3. Example:
 *    Input: "{[()]}"
 *    Output: true
 *
 *    Input: "([)]"
 *    Output: false
 *
 * 4. Complexity:
 *    Time Complexity: O(n) — Each character is processed once.
 *    Space Complexity: O(n) — For storing opening brackets in the stack.
 *
 * 5. Author:
 *    Pradyumn Pratap Singh (Strange)
 * ---------------------------------------------------------------------
 */

package DSA_Code.Java.data_structures.stacks;
import java.util.Stack;
import java.util.Scanner;

public class ValidParentheses {

    // Function to check if parentheses are valid
    public static boolean isValid(String s) {
        Stack<Character> stack = new Stack<>();

        for (char ch : s.toCharArray()) {
            // Push opening brackets
            if (ch == '(' || ch == '{' || ch == '[') {
                stack.push(ch);
            }
            // For closing brackets, check matching pair
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (stack.isEmpty()) return false;
                char top = stack.pop();

                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }

        // Stack should be empty if all brackets matched
        return stack.isEmpty();
    }

    // Main function for user input and test
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter expression: ");
        String expression = sc.nextLine();

        if (isValid(expression)) {
            System.out.println("✅ The expression is valid.");
        } else {
            System.out.println("❌ The expression is NOT valid.");
        }

        sc.close();
    }
}
