
/*
    Description: Lowest Common Ancestor (LCA) in BST

    Given a Binary Search Tree (BST) and two nodes p and q,
    find the lowest common ancestor (LCA) of the two nodes.

    Definition:
    - LCA of p and q is the lowest node in BST that has both p and q as descendants.

    Example:
            6
           / \
          2   8
         / \ / \
        0  4 7  9
          / \
         3   5

        LCA(2, 8) = 6
        LCA(2, 4) = 2
*/

class TreeNode {
    int val;
    TreeNode left, right;

    TreeNode(int val) {
        this.val = val;
        this.left = this.right = null;
    }
}

public class LCAinBST {

    // -----------------------------------------------------------
    //  1. RECURSIVE APPROACH
    // -----------------------------------------------------------
    // Idea:
    // 1. If both p and q are smaller than root → LCA is in left subtree
    // 2. If both p and q are greater than root → LCA is in right subtree
    // 3. Otherwise → root is LCA
    //
    // Time Complexity: O(h) — h = height of BST
    // Space Complexity: O(h) — recursion stack
    public static TreeNode lowestCommonAncestorRecursive(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) return null;

        if (p.val < root.val && q.val < root.val)
            return lowestCommonAncestorRecursive(root.left, p, q);
        else if (p.val > root.val && q.val > root.val)
            return lowestCommonAncestorRecursive(root.right, p, q);
        else
            return root; // split point found
    }

    // -----------------------------------------------------------
    //  2. ITERATIVE APPROACH
    // -----------------------------------------------------------
    // Idea:
    // Similar logic, but traverse using while loop instead of recursion
    //
    // Time Complexity: O(h)
    // Space Complexity: O(1)
    public static TreeNode lowestCommonAncestorIterative(TreeNode root, TreeNode p, TreeNode q) {
        TreeNode current = root;

        while (current != null) {
            if (p.val < current.val && q.val < current.val)
                current = current.left;
            else if (p.val > current.val && q.val > current.val)
                current = current.right;
            else
                return current; // split point found
        }

        return null;
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
              / \
             3   5
        */
        TreeNode root = new TreeNode(6);
        root.left = new TreeNode(2);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(4);
        root.left.right.left = new TreeNode(3);
        root.left.right.right = new TreeNode(5);
        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(9);

        TreeNode p = root.left;       // Node 2
        TreeNode q = root.right;      // Node 8

        System.out.println("LCA (Recursive): " + lowestCommonAncestorRecursive(root, p, q).val);
        System.out.println("LCA (Iterative): " + lowestCommonAncestorIterative(root, p, q).val);

        p = root.left;    // Node 2
        q = root.left.right; // Node 4

        System.out.println("LCA (Recursive): " + lowestCommonAncestorRecursive(root, p, q).val);
        System.out.println("LCA (Iterative): " + lowestCommonAncestorIterative(root, p, q).val);
    }
}
