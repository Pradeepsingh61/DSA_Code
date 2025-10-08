/*
 * Algorithm Name
Lowest Common Ancestor (LCA) in a Binary Tree
 * 
 * Programming Language
Java
 * 
 * Category
Tree / Recursion
 * 
 * Difficulty Level
Medium
 * 
 * Algorithm Description :
 * 
 * 1. Problem it solves:
 * -> Finds the lowest (deepest) node in a binary tree that is the ancestor of two given nodes.
 * 
 * 2. Approach / Idea:
 * -> Traverse the tree recursively.
 * -> If the current node matches one of the given nodes, return it.
 * -> Recursively check in left and right subtrees.
 * -> If both left and right subtrees return non-null, the current node is the LCA.
 * 
 * 3. Complexity:
 * -> Time: O(N), where N = number of nodes.
 * -> Space: O(H), where H = height of the tree (recursion stack).
 * 
 * Author : Surya Pratap Singh
 */

import java.util.*;

public class LCA {

    // Node structure
    static class Node {
        int val;
        Node left, right;

        Node(int val) {
            this.val = val;
        }
    }

    // Function to find LCA of two nodes
    static Node findLCA(Node root, int n1, int n2) {
        if (root == null) return null;

        // If root is one of the nodes, return it
        if (root.val == n1 || root.val == n2) {
            return root;
        }

        // Recurse left and right
        Node left = findLCA(root.left, n1, n2);
        Node right = findLCA(root.right, n1, n2);

        // If both sides return non-null, root is LCA
        if (left != null && right != null) return root;

        // Otherwise return whichever side is non-null
        return (left != null) ? left : right;
    }

    // Function to build a simple binary tree (for demonstration)
    static Node buildTree() {
        Node root = new Node(3);
        root.left = new Node(5);
        root.right = new Node(1);
        root.left.left = new Node(6);
        root.left.right = new Node(2);
        root.left.right.left = new Node(7);
        root.left.right.right = new Node(4);
        root.right.left = new Node(0);
        root.right.right = new Node(8);
        return root;
    }

    // Main method
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Node root = buildTree();

        System.out.println("Tree built successfully!");
        System.out.print("Enter first node value: ");
        int n1 = sc.nextInt();
        System.out.print("Enter second node value: ");
        int n2 = sc.nextInt();

        Node ans = findLCA(root, n1, n2);
        if (ans != null)
            System.out.println("LCA of " + n1 + " and " + n2 + " is: " + ans.val);
        else
            System.out.println("One or both nodes not found in the tree.");
    }
}
