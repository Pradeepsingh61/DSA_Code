/**
 * Binary Search Tree (BST) Traversal Methods in JavaScript
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
    this.root = null; // A simple BST for demonstration
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

  // --- Recursive Traversal Methods ---

  // 1. Inorder: Left -> Root -> Right (Yields sorted data)
  inorder(node = this.root) {
    if (node) {
      this.inorder(node.left);
      console.log(node.data);
      this.inorder(node.right);
    }
  }

  // 2. Preorder: Root -> Left -> Right (Useful for copying the tree)
  preorder(node = this.root) {
    if (node) {
      console.log(node.data);
      this.preorder(node.left);
      this.preorder(node.right);
    }
  }

  // 3. Postorder: Left -> Right -> Root (Useful for deleting the tree)
  postorder(node = this.root) {
    if (node) {
      this.postorder(node.left);
      this.postorder(node.right);
      console.log(node.data);
    }
  }

  // --- Iterative Traversal Method ---

  // 4. Breadth-First Search (Level Order Traversal)
  levelOrder() {
    if (!this.root) return;

    const queue = [this.root];
    const result = [];

    while (queue.length) {
      const node = queue.shift();
      result.push(node.data);

      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    console.log(result.join(' '));
  }
}

// --- Example Usage ---

const bst = new BSTTraversal();
[50, 30, 70, 20, 40, 60, 80].forEach(data => bst.insert(data));

console.log("\n--- Inorder Traversal (Sorted) ---");
// Expected: 20 30 40 50 60 70 80
bst.inorder(); 

console.log("\n--- Level Order Traversal (BFS) ---");
// Expected: 50 30 70 20 40 60 80
bst.levelOrder();