
/*
    Description: Binary Search Tree (BST) Traversals

    Given a BST, perform the following traversals:
    1. Inorder (Left, Root, Right)
    2. Preorder (Root, Left, Right)
    3. Postorder (Left, Right, Root)
    4. Level Order (BFS)

    Both recursive and iterative versions are included.
*/

import java.util.*;

class TreeNode {
    int val;
    TreeNode left, right;

    TreeNode(int val) {
        this.val = val;
        this.left = this.right = null;
    }
}

public class BSTTraversals {

    // -----------------------------------------------------------
    //  1. INORDER TRAVERSAL (Recursive)
    // -----------------------------------------------------------
    // Time Complexity: O(n)
    // Space Complexity: O(h) for recursion stack
    public static void inorderRecursive(TreeNode root) {
        if (root == null) return;
        inorderRecursive(root.left);
        System.out.print(root.val + " ");
        inorderRecursive(root.right);
    }

    // -----------------------------------------------------------
    //  2. INORDER TRAVERSAL (Iterative)
    // -----------------------------------------------------------
    public static void inorderIterative(TreeNode root) {
        Stack<TreeNode> stack = new Stack<>();
        TreeNode curr = root;

        while (curr != null || !stack.isEmpty()) {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }
            curr = stack.pop();
            System.out.print(curr.val + " ");
            curr = curr.right;
        }
    }

    // -----------------------------------------------------------
    //  3. PREORDER TRAVERSAL (Recursive)
    // -----------------------------------------------------------
    public static void preorderRecursive(TreeNode root) {
        if (root == null) return;
        System.out.print(root.val + " ");
        preorderRecursive(root.left);
        preorderRecursive(root.right);
    }

    // -----------------------------------------------------------
    //  4. PREORDER TRAVERSAL (Iterative)
    // -----------------------------------------------------------
    public static void preorderIterative(TreeNode root) {
        if (root == null) return;
        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();
            System.out.print(curr.val + " ");
            if (curr.right != null) stack.push(curr.right);
            if (curr.left != null) stack.push(curr.left);
        }
    }

    // -----------------------------------------------------------
    //  5. POSTORDER TRAVERSAL (Recursive)
    // -----------------------------------------------------------
    public static void postorderRecursive(TreeNode root) {
        if (root == null) return;
        postorderRecursive(root.left);
        postorderRecursive(root.right);
        System.out.print(root.val + " ");
    }

    // -----------------------------------------------------------
    //  6. POSTORDER TRAVERSAL (Iterative)
    // -----------------------------------------------------------
    public static void postorderIterative(TreeNode root) {
        if (root == null) return;
        Stack<TreeNode> stack1 = new Stack<>();
        Stack<TreeNode> stack2 = new Stack<>();
        stack1.push(root);

        while (!stack1.isEmpty()) {
            TreeNode curr = stack1.pop();
            stack2.push(curr);
            if (curr.left != null) stack1.push(curr.left);
            if (curr.right != null) stack1.push(curr.right);
        }

        while (!stack2.isEmpty()) {
            System.out.print(stack2.pop().val + " ");
        }
    }

    // -----------------------------------------------------------
    //  7. LEVEL ORDER TRAVERSAL (BFS)
    // -----------------------------------------------------------
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static void levelOrder(TreeNode root) {
        if (root == null) return;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode curr = queue.poll();
            System.out.print(curr.val + " ");
            if (curr.left != null) queue.offer(curr.left);
            if (curr.right != null) queue.offer(curr.right);
        }
    }

    // -----------------------------------------------------------
    //  MAIN METHOD (Test)
    // -----------------------------------------------------------
    public static void main(String[] args) {
        /*
                6
               / \
              2   8
             / \ / \
            0  4 7  9
        */
        TreeNode root = new TreeNode(6);
        root.left = new TreeNode(2);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(4);
        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(9);

        System.out.print("Inorder Recursive: ");
        inorderRecursive(root);
        System.out.println();

        System.out.print("Inorder Iterative: ");
        inorderIterative(root);
        System.out.println();

        System.out.print("Preorder Recursive: ");
        preorderRecursive(root);
        System.out.println();

        System.out.print("Preorder Iterative: ");
        preorderIterative(root);
        System.out.println();

        System.out.print("Postorder Recursive: ");
        postorderRecursive(root);
        System.out.println();

        System.out.print("Postorder Iterative: ");
        postorderIterative(root);
        System.out.println();

        System.out.print("Level Order (BFS): ");
        levelOrder(root);
        System.out.println();
    }
}
