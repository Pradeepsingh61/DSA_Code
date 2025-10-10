/*
  Binary Tree Traversal in C
  --------------------------
  This program demonstrates three standard traversal techniques for binary trees:
  
  1. In-order Traversal (Left → Root → Right)
  2. Pre-order Traversal (Root → Left → Right)
  3. Post-order Traversal (Left → Right → Root)

  Each traversal is implemented using recursion.

  Time Complexity:
    - O(n) for each traversal, where n is the number of nodes in the tree.
      (Each node is visited exactly once.)

  Space Complexity:
    - O(h) due to recursive function calls, where h is the height of the tree.
    - Worst-case (skewed tree): O(n)
    - Best-case (balanced tree): O(log n)
*/

#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct Node {
    int data;                // Value stored in the node
    struct Node* left;       // Pointer to the left child
    struct Node* right;      // Pointer to the right child
};

// Function to create a new tree node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// In-order Traversal: Left → Root → Right
void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

// Pre-order Traversal: Root → Left → Right
void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Post-order Traversal: Left → Right → Root
void postOrderTraversal(struct Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Driver code
int main() {
    // Manually creating a sample binary tree
    /*
            1
           / \
          2   3
         / \ / \
        4  5 6  7
    */
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Display traversals
    printf("In-order Traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
git