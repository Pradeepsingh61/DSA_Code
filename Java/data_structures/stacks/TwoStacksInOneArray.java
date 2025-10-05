/*
 * Algorithm Name
   Two Stacks in One Array

 * Programming Language
   Java

 * Category
   Data Structures / Stack Implementations

 * Difficulty Level
   Medium

 * Algorithm Description:

   1. Problem it solves:
      -> Efficiently implements two separate stacks using a single array to optimize space utilization.

   2. Approach / Idea:
      -> Use one array `arr` of fixed size.
      -> Maintain two top pointers:
         - `top1` starts from -1 and grows from left to right.
         - `top2` starts from the end (size) and grows from right to left.
      -> Push and pop operations are performed independently for both stacks.
      -> Overflow occurs if `top1 + 1 == top2`.

   3. Complexity:
      Time: O(1) per operation (push, pop, peek)
      Space: O(n) for the array

 * Author: Pradyumn Pratap Singh (Strange)
 */


public class TwoStacksInOneArray {

    private int[] arr;
    private int size;
    private int top1, top2;

    // Constructor to initialize the two stacks
    public TwoStacksInOneArray(int size) {
        this.size = size;
        arr = new int[size];
        top1 = -1;
        top2 = size;
    }

    // Push an element to Stack 1
    public void push1(int x) {
        if (top1 < top2 - 1) {
            arr[++top1] = x;
        } else {
            System.out.println("Stack Overflow! No space left for Stack 1.");
        }
    }

    // Push an element to Stack 2
    public void push2(int x) {
        if (top1 < top2 - 1) {
            arr[--top2] = x;
        } else {
            System.out.println("Stack Overflow! No space left for Stack 2.");
        }
    }

    // Pop an element from Stack 1
    public int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        } else {
            System.out.println("Stack Underflow! Stack 1 is empty.");
            return -1;
        }
    }

    // Pop an element from Stack 2
    public int pop2() {
        if (top2 < size) {
            return arr[top2++];
        } else {
            System.out.println("Stack Underflow! Stack 2 is empty.");
            return -1;
        }
    }

    // Peek top of Stack 1
    public int peek1() {
        if (top1 >= 0) {
            return arr[top1];
        }
        System.out.println("Stack 1 is empty.");
        return -1;
    }

    // Peek top of Stack 2
    public int peek2() {
        if (top2 < size) {
            return arr[top2];
        }
        System.out.println("Stack 2 is empty.");
        return -1;
    }

    // Utility methods to check if stacks are empty
    public boolean isEmpty1() {
        return top1 == -1;
    }

    public boolean isEmpty2() {
        return top2 == size;
    }

    // Display both stacks
    public void displayStacks() {
        System.out.print("Stack 1: ");
        for (int i = 0; i <= top1; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        System.out.print("Stack 2: ");
        for (int i = size - 1; i >= top2; i--) {
            System.out.print(arr[i] + " ");
        }
        System.out.println("\n");
    }

    // Driver code for testing
    public static void main(String[] args) {
        TwoStacksInOneArray stacks = new TwoStacksInOneArray(10);

        System.out.println("Pushing elements into Stack 1 and Stack 2...");

        stacks.push1(10);
        stacks.push1(20);
        stacks.push1(30);

        stacks.push2(100);
        stacks.push2(200);
        stacks.push2(300);

        stacks.displayStacks();

        System.out.println("Popped from Stack 1: " + stacks.pop1());
        System.out.println("Popped from Stack 2: " + stacks.pop2());

        stacks.displayStacks();

        System.out.println("Top of Stack 1: " + stacks.peek1());
        System.out.println("Top of Stack 2: " + stacks.peek2());
    }
}
