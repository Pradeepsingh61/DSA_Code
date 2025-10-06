/*
 * Algorithm Name
   Infix to Postfix Conversion

 * Programming Language
   Java

 * Category
   Data Structures / Stack Applications

 * Difficulty Level
   Medium

 * Algorithm Description:

   1. Problem it solves:
      -> Converts an arithmetic expression from Infix form (e.g., A + B * C)
         to Postfix form (e.g., A B C * +), which can be easily evaluated by computers.

   2. Approach / Idea:
      -> Use a stack to temporarily hold operators.
      -> Steps:
         - Scan the infix expression from left to right.
         - If the character is an operand (A–Z, a–z, 0–9), add it to the output.
         - If the character is '(', push it to stack.
         - If the character is ')', pop and output until '(' is found.
         - If the character is an operator (+, -, *, /, ^):
             * Pop operators from stack to output until the stack is empty or
               top of stack has lower precedence.
             * Then push the current operator to the stack.
         - After the full scan, pop and output all remaining operators from stack.

   3. Complexity:
      Time: O(n) — each element is pushed and popped at most once.
      Space: O(n) — stack and output storage.

 * Author: Pradyumn Pratap Singh (Strange)
 */

package DSA_Code.Java.data_structures.stacks;

import java.util.Stack;

public class InfixToPostfix {

    // Function to return precedence of operators
    private static int precedence(char ch) {
        switch (ch) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
        }
        return -1;
    }

    // Function to convert infix expression to postfix
    public static String infixToPostfix(String expression) {
        StringBuilder result = new StringBuilder();
        Stack<Character> stack = new Stack<>();

        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);

            // If the scanned character is an operand, add it to output
            if (Character.isLetterOrDigit(c)) {
                result.append(c);
            }
            // If the scanned character is '(', push it to stack
            else if (c == '(') {
                stack.push(c);
            }
            // If the scanned character is ')', pop and output until '(' is found
            else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    result.append(stack.pop());
                }
                if (!stack.isEmpty() && stack.peek() == '(') {
                    stack.pop();
                } else {
                    System.out.println("Invalid Expression: Mismatched parentheses.");
                    return "";
                }
            }
            // If an operator is encountered
            else {
                while (!stack.isEmpty() && precedence(c) <= precedence(stack.peek())) {
                    result.append(stack.pop());
                }
                stack.push(c);
            }
        }

        // Pop all remaining operators from the stack
        while (!stack.isEmpty()) {
            if (stack.peek() == '(') {
                System.out.println("Invalid Expression: Mismatched parentheses.");
                return "";
            }
            result.append(stack.pop());
        }

        return result.toString();
    }

    // Driver code for testing
    public static void main(String[] args) {
        String infixExp1 = "A+B*C";
        String infixExp2 = "(A+B)*C";
        String infixExp3 = "A+B*(C^D-E)^(F+G*H)-I";

        System.out.println("Infix Expression 1: " + infixExp1);
        System.out.println("Postfix Expression 1: " + infixToPostfix(infixExp1));

        System.out.println("\nInfix Expression 2: " + infixExp2);
        System.out.println("Postfix Expression 2: " + infixToPostfix(infixExp2));

        System.out.println("\nInfix Expression 3: " + infixExp3);
        System.out.println("Postfix Expression 3: " + infixToPostfix(infixExp3));
    }
}
