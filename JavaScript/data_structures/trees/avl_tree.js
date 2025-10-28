/**
 * AVL Tree Implementation in JavaScript
 * AVL is a Self-Balancing Binary Search Tree.
 */

class AVLNode {
  constructor(data) {
    this.data = data;
    this.left = null;
    this.right = null;
    this.height = 1; // Start with height 1
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

  // --- Rotations ---

  // Right Rotation (LL case)
  rotateRight(y) {
    const x = y.left;
    const T2 = x.right;

    // Perform rotation
    x.right = y;
    y.left = T2;

    // Update heights
    this.updateHeight(y);
    this.updateHeight(x);

    return x; // New root of the subtree
  }

  // Left Rotation (RR case)
  rotateLeft(x) {
    const y = x.right;
    const T2 = y.left;

    // Perform rotation
    y.left = x;
    x.right = T2;

    // Update heights
    this.updateHeight(x);
    this.updateHeight(y);

    return y; // New root of the subtree
  }

  // --- Insertion ---

  insert(data) {
    this.root = this._insertNode(this.root, data);
  }

  _insertNode(node, data) {
    // 1. Perform standard BST insertion
    if (!node) return new AVLNode(data);
    if (data < node.data) {
      node.left = this._insertNode(node.left, data);
    } else if (data > node.data) {
      node.right = this._insertNode(node.right, data);
    } else {
      return node; // Duplicate keys not allowed
    }

    // 2. Update height of current node
    this.updateHeight(node);

    // 3. Get the balance factor
    const balance = this.getBalanceFactor(node);

    // 4. Rebalance if needed (4 cases)

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

    // Return the (potentially updated) node pointer
    return node;
  }
}