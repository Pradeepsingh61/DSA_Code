/**
 * Binary Search Tree (BST) Traversal Methods in JavaScript
 * * Description:
 * These algorithms define the order in which nodes in a BST are visited.
 * Traversal is fundamental for processing all nodes in the tree.
 * * Approach & Purpose:
 * 1. Inorder Traversal: Visits Left -> Root -> Right. Output is always sorted data. (Useful for listing sorted elements).
 * 2. Preorder Traversal: Visits Root -> Left -> Right. (Useful for copying the tree structure).
 * 3. Postorder Traversal: Visits Left -> Right -> Root. (Useful for deleting the tree).
 * 4. Level Order (BFS): Visits nodes level by level using a queue. (Useful for finding the shortest path).
 * * Time Complexity:
 * - All Traversals (Inorder, Preorder, Postorder, Level Order): O(n)
 * Each node is visited exactly once.
 * * Space Complexity:
 * - DFS (Recursive): O(h), where 'h' is the height of the tree. O(log n) for balanced BSTs, O(n) for skewed BSTs (stack space).
 * - BFS (Level Order/Iterative): O(w), where 'w' is the maximum width of the tree. O(n) in the worst case (full level is stored in the queue).
 */

class BSTNode {
  constructor(data) {
    this.data = data;
    this.left = null;
    this.right = null;
  }
}

class BSTTraversal {
  constructor() {
    this.root = null;
  }

  // Utility to insert for testing traversals
  insert(data) {
    const newNode = new BSTNode(data);
    if (!this.root) {
      this.root = newNode;
      return;
    }
    let current = this.root;
    while (true) {
      if (data < current.data) {
        if (!current.left) {
          current.left = newNode;
          return;
        }
        current = current.left;
      } else {
        if (!current.right) {
          current.right = newNode;
          return;
        }
        current = current.right;
      }
    }
  }

  // --- Recursive Traversal Methods (DFS) ---

  // 1. Inorder: Left -> Root -> Right
  inorder(node = this.root, result = []) {
    if (node) {
      this.inorder(node.left, result);
      result.push(node.data);
      this.inorder(node.right, result);
    }
    return result; // Return array for easy testing
  }

  // 2. Preorder: Root -> Left -> Right
  preorder(node = this.root, result = []) {
    if (node) {
      result.push(node.data);
      this.preorder(node.left, result);
      this.preorder(node.right, result);
    }
    return result;
  }

  // 3. Postorder: Left -> Right -> Root
  postorder(node = this.root, result = []) {
    if (node) {
      this.postorder(node.left, result);
      this.postorder(node.right, result);
      result.push(node.data);
    }
    return result;
  }

  // --- Iterative Traversal Method (BFS) ---

  // 4. Level Order Traversal
  levelOrder() {
    if (!this.root) return [];

    const queue = [this.root];
    const result = [];

    while (queue.length) {
      const node = queue.shift();
      result.push(node.data);

      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    return result;
  }
}