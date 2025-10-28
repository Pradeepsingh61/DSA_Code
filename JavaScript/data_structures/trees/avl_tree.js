/**
 * AVL Tree Implementation in JavaScript
 * * Description: 
 * An AVL Tree is a self-balancing Binary Search Tree (BST). It automatically 
 * keeps its height as small as possible by performing rotations (single or double) 
 * whenever the balance factor (height difference between left and right subtrees) 
 * of any node exceeds 1 or -1. This ensures search, insertion, and deletion 
 * operations remain efficient even in the worst-case scenario.
 * * Approach:
 * 1. Standard BST insertion is performed.
 * 2. The height and balance factor of ancestor nodes are updated.
 * 3. If the balance factor is violated, one of four rotations (LL, RR, LR, RL) 
 * is applied to rebalance the tree.
 * * Time Complexity:
 * - Search: O(log n)
 * - Insertion: O(log n) (due to balanced nature)
 * - Deletion: O(log n)
 * * Space Complexity:
 * - O(n) - Stores 'n' nodes in the tree structure.
 */

class AVLNode {
  constructor(data) {
    this.data = data;
    this.left = null;
    this.right = null;
    this.height = 1;
  }
}

class AVLTree {
  constructor() {
    this.root = null;
  }

  // Helper: Get node height
  getHeight(node) {
    return node ? node.height : 0;
  }

  // Helper: Calculate balance factor (Left Height - Right Height)
  getBalanceFactor(node) {
    return node ? this.getHeight(node.left) - this.getHeight(node.right) : 0;
  }

  // Helper: Update height of the node
  updateHeight(node) {
    node.height = 1 + Math.max(this.getHeight(node.left), this.getHeight(node.right));
  }

  // Right Rotation (LL case)
  rotateRight(y) {
    const x = y.left;
    const T2 = x.right;

    x.right = y;
    y.left = T2;

    this.updateHeight(y);
    this.updateHeight(x);

    return x;
  }

  // Left Rotation (RR case)
  rotateLeft(x) {
    const y = x.right;
    const T2 = y.left;

    y.left = x;
    x.right = T2;

    this.updateHeight(x);
    this.updateHeight(y);

    return y;
  }

  insert(data) {
    this.root = this._insertNode(this.root, data);
  }

  _insertNode(node, data) {
    // 1. Standard BST Insertion
    if (!node) return new AVLNode(data);
    if (data < node.data) {
      node.left = this._insertNode(node.left, data);
    } else if (data > node.data) {
      node.right = this._insertNode(node.right, data);
    } else {
      return node;
    }

    // 2. Update height
    this.updateHeight(node);

    // 3. Get the balance factor
    const balance = this.getBalanceFactor(node);

    // 4. Rebalance (Rotations)
    // Left Left Case
    if (balance > 1 && data < node.left.data) {
      return this.rotateRight(node);
    }
    // Right Right Case
    if (balance < -1 && data > node.right.data) {
      return this.rotateLeft(node);
    }
    // Left Right Case
    if (balance > 1 && data > node.left.data) {
      node.left = this.rotateLeft(node.left);
      return this.rotateRight(node);
    }
    // Right Left Case
    if (balance < -1 && data < node.right.data) {
      node.right = this.rotateRight(node.right);
      return this.rotateLeft(node);
    }

    return node;
  }

  // --- Utility for Testing (Inorder Traversal) ---
  inorder(node = this.root, result = []) {
    if (node) {
      this.inorder(node.left, result);
      result.push(node.data);
      this.inorder(node.right, result);
    }
    return result;
  }
}
