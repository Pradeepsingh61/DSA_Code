/*
 * Data Structure Name:
 * AVL Tree (Adelson-Velsky and Landis Tree)
 *
 * Programming Language:
 * C
 *
 * Category:
 * Data Structures - Trees
 *
 * Difficulty Level:
 * Hard
 *
 * Data Structure Description:
 *
 * 1. What it is:
 *    -> AVL Tree is a self-balancing binary search tree where the heights of the
 *       two child subtrees of any node differ by at most one. If at any time they
 *       differ by more than one, rebalancing is done to restore this property.
 *
 * 2. Key Properties:
 *    -> Height-balanced: |height(left) - height(right)| ≤ 1 for every node
 *    -> Self-balancing: Automatically maintains balance through rotations
 *    -> BST property: Left subtree < node < right subtree
 *    -> Guaranteed O(log n) operations due to balanced height
 *
 * 3. Operations Complexity:
 *    Search: O(log n)
 *    Insert: O(log n)
 *    Delete: O(log n)
 *    Space: O(n)
 *
 * 4. Rotations:
 *    -> Left Rotation (LL): When right subtree is heavier
 *    -> Right Rotation (RR): When left subtree is heavier
 *    -> Left-Right Rotation (LR): Left child's right subtree is heavier
 *    -> Right-Left Rotation (RL): Right child's left subtree is heavier
 *
 * 5. Applications:
 *    -> Database indexing systems
 *    -> Memory management in operating systems
 *    -> Expression parsing in compilers
 *    -> Any application requiring guaranteed O(log n) search/insert/delete
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// AVL Tree Node structure
typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// Function prototypes
AVLNode* createNode(int data);
int getHeight(AVLNode* node);
int getBalance(AVLNode* node);
int max(int a, int b);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);
AVLNode* insert(AVLNode* node, int data);
AVLNode* findMin(AVLNode* node);
AVLNode* deleteNode(AVLNode* root, int data);
AVLNode* search(AVLNode* root, int data);
void inorderTraversal(AVLNode* root);
void preorderTraversal(AVLNode* root);
void postorderTraversal(AVLNode* root);
void levelOrderTraversal(AVLNode* root);
void printTree(AVLNode* root, int space);
void displayTreeStructure(AVLNode* root);
bool isAVL(AVLNode* root);
int countNodes(AVLNode* root);
void printNodeInfo(AVLNode* node);
void demonstrateRotations();
void freeTree(AVLNode* root);
void printLevel(AVLNode* root, int level);

int main() {
    AVLNode* root = NULL;
    int choice, value;
    
    printf("=== AVL Tree (Self-Balancing BST) Implementation ===\n\n");
    
    while (1) {
        printf("\n=== AVL Tree Operations ===\n");
        printf("1.  Insert element\n");
        printf("2.  Delete element\n");
        printf("3.  Search element\n");
        printf("4.  Display tree structure\n");
        printf("5.  Inorder traversal\n");
        printf("6.  Preorder traversal\n");
        printf("7.  Postorder traversal\n");
        printf("8.  Level order traversal\n");
        printf("9.  Check if tree is AVL balanced\n");
        printf("10. Show tree statistics\n");
        printf("11. Demonstrate rotations\n");
        printf("12. Insert multiple elements (demo)\n");
        printf("13. Clear tree\n");
        printf("0.  Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Inserted %d into AVL tree\n", value);
                if (root) {
                    printf("Tree height: %d\n", getHeight(root));
                }
                break;
                
            case 2:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                AVLNode* found = search(root, value);
                if (found) {
                    root = deleteNode(root, value);
                    printf("Deleted %d from AVL tree\n", value);
                    if (root) {
                        printf("Tree height: %d\n", getHeight(root));
                    }
                } else {
                    printf("Value %d not found in tree\n", value);
                }
                break;
                
            case 3:
                if (!root) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                scanf("%d", &value);
                AVLNode* result = search(root, value);
                if (result) {
                    printf("Found %d in the tree\n", value);
                    printNodeInfo(result);
                } else {
                    printf("Value %d not found in tree\n", value);
                }
                break;
                
            case 4:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("\nTree Structure:\n");
                    displayTreeStructure(root);
                }
                break;
                
            case 5:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Inorder traversal: ");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Preorder traversal: ");
                    preorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 7:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Postorder traversal: ");
                    postorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 8:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Level order traversal: ");
                    levelOrderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 9:
                if (!root) {
                    printf("Empty tree is considered AVL balanced\n");
                } else {
                    if (isAVL(root)) {
                        printf("Tree is AVL balanced ✓\n");
                    } else {
                        printf("Tree is NOT AVL balanced ✗\n");
                    }
                }
                break;
                
            case 10:
                if (!root) {
                    printf("Tree is empty!\n");
                } else {
                    printf("\n=== Tree Statistics ===\n");
                    printf("Root value: %d\n", root->data);
                    printf("Tree height: %d\n", getHeight(root));
                    printf("Total nodes: %d\n", countNodes(root));
                    printf("Balance factor of root: %d\n", getBalance(root));
                    printf("Is AVL balanced: %s\n", isAVL(root) ? "Yes" : "No");
                }
                break;
                
            case 11:
                demonstrateRotations();
                break;
                
            case 12: {
                printf("Inserting demo sequence: 10, 20, 30, 40, 50, 25\n");
                int demo[] = {10, 20, 30, 40, 50, 25};
                int demoSize = sizeof(demo) / sizeof(demo[0]);
                
                for (int i = 0; i < demoSize; i++) {
                    printf("\nInserting %d...\n", demo[i]);
                    root = insert(root, demo[i]);
                    printf("Tree after insertion:\n");
                    displayTreeStructure(root);
                }
                break;
            }
                
            case 13:
                if (root) {
                    freeTree(root);
                    root = NULL;
                    printf("Tree cleared successfully\n");
                } else {
                    printf("Tree is already empty\n");
                }
                break;
                
            case 0:
                if (root) {
                    freeTree(root);
                }
                printf("Exiting AVL Tree program. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/**
 * Create a new AVL tree node
 * 
 * @param data: Value to store in the node
 * @return: Pointer to the newly created node
 */
AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (!node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    node->data = data;
    node->height = 1; // New node is initially at height 1
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

/**
 * Get height of a node
 * 
 * @param node: Node to get height of
 * @return: Height of the node (0 if NULL)
 */
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

/**
 * Get balance factor of a node
 * Balance factor = height(left subtree) - height(right subtree)
 * 
 * @param node: Node to get balance factor of
 * @return: Balance factor (-1, 0, 1 for balanced tree)
 */
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

/**
 * Utility function to get maximum of two integers
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Right rotate (RR rotation)
 * Used when left subtree is heavier
 * 
 *       y                x
 *      / \              / \
 *     x   T3    -->    T1  y
 *    / \                  / \
 *   T1  T2               T2  T3
 * 
 * @param y: Root of subtree to rotate
 * @return: New root after rotation
 */
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    // Return new root
    return x;
}

/**
 * Left rotate (LL rotation)
 * Used when right subtree is heavier
 * 
 *     x                    y
 *    / \                  / \
 *   T1  y        -->     x   T3
 *      / \              / \
 *     T2  T3           T1  T2
 * 
 * @param x: Root of subtree to rotate
 * @return: New root after rotation
 */
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    // Return new root
    return y;
}

/**
 * Insert a value into AVL tree
 * Maintains AVL property through rotations
 * 
 * @param node: Root of the tree/subtree
 * @param data: Value to insert
 * @return: Root of the modified tree
 */
AVLNode* insert(AVLNode* node, int data) {
    // Step 1: Perform normal BST insertion
    if (node == NULL) {
        return createNode(data);
    }
    
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        // Duplicate values not allowed
        printf("Value %d already exists in tree\n", data);
        return node;
    }
    
    // Step 2: Update height of current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    // Step 3: Get balance factor
    int balance = getBalance(node);
    
    // Step 4: If unbalanced, there are 4 cases
    
    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }
    
    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }
    
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return unchanged node if already balanced
    return node;
}

/**
 * Find node with minimum value (leftmost node)
 * 
 * @param node: Root of tree/subtree
 * @return: Node with minimum value
 */
AVLNode* findMin(AVLNode* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * Delete a value from AVL tree
 * Maintains AVL property through rotations
 * 
 * @param root: Root of the tree
 * @param data: Value to delete
 * @return: Root of the modified tree
 */
AVLNode* deleteNode(AVLNode* root, int data) {
    // Step 1: Perform standard BST delete
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node to be deleted found
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                // No child case
                temp = root;
                root = NULL;
            } else {
                // One child case
                *root = *temp; // Copy contents of non-empty child
            }
            free(temp);
        } else {
            // Node with two children
            AVLNode* temp = findMin(root->right);
            
            // Copy inorder successor's data to this node
            root->data = temp->data;
            
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    // If tree had only one node
    if (root == NULL) {
        return root;
    }
    
    // Step 2: Update height of current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    // Step 3: Get balance factor
    int balance = getBalance(root);
    
    // Step 4: If unbalanced, there are 4 cases
    
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

/**
 * Search for a value in AVL tree
 * 
 * @param root: Root of the tree
 * @param data: Value to search for
 * @return: Pointer to node if found, NULL otherwise
 */
AVLNode* search(AVLNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
}

/**
 * Inorder traversal (Left, Root, Right)
 * Results in sorted order for BST
 */
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

/**
 * Preorder traversal (Root, Left, Right)
 */
void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

/**
 * Postorder traversal (Left, Right, Root)
 */
void postorderTraversal(AVLNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

/**
 * Level order traversal (breadth-first)
 * Simple implementation using recursion
 */
void levelOrderTraversal(AVLNode* root) {
    int height = getHeight(root);
    for (int i = 1; i <= height; i++) {
        printLevel(root, i);
    }
}

/**
 * Helper function for level order traversal
 */
void printLevel(AVLNode* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

/**
 * Print tree structure with indentation
 * 
 * @param root: Root of tree
 * @param space: Current indentation level
 */
void printTree(AVLNode* root, int space) {
    const int COUNT = 10;
    
    if (root == NULL) {
        return;
    }
    
    space += COUNT;
    
    printTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d(h:%d,b:%d)\n", root->data, root->height, getBalance(root));
    
    printTree(root->left, space);
}

/**
 * Display tree structure in a readable format
 */
void displayTreeStructure(AVLNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    printf("Tree structure (value(height:balance)):\n");
    printTree(root, 0);
    printf("\n");
}

/**
 * Check if tree maintains AVL property
 * 
 * @param root: Root of tree to check
 * @return: true if AVL balanced, false otherwise
 */
bool isAVL(AVLNode* root) {
    if (root == NULL) {
        return true;
    }
    
    int balance = getBalance(root);
    
    // Check if current node is balanced and subtrees are AVL
    return (abs(balance) <= 1) && isAVL(root->left) && isAVL(root->right);
}

/**
 * Count total number of nodes in tree
 * 
 * @param root: Root of tree
 * @return: Number of nodes
 */
int countNodes(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/**
 * Print detailed information about a node
 * 
 * @param node: Node to print info about
 */
void printNodeInfo(AVLNode* node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }
    
    printf("Node Info:\n");
    printf("  Value: %d\n", node->data);
    printf("  Height: %d\n", node->height);
    printf("  Balance Factor: %d\n", getBalance(node));
    printf("  Left child: %s\n", node->left ? "exists" : "NULL");
    printf("  Right child: %s\n", node->right ? "exists" : "NULL");
}

/**
 * Demonstrate different types of rotations
 */
void demonstrateRotations() {
    printf("\n=== AVL Tree Rotations Demonstration ===\n");
    
    printf("\n1. Right Rotation (RR) - Left Heavy Case:\n");
    printf("   Before:     After:\n");
    printf("      30        20\n");
    printf("     /         /  \\\n");
    printf("    20   -->  10   30\n");
    printf("   /\n");
    printf("  10\n");
    
    printf("\n2. Left Rotation (LL) - Right Heavy Case:\n");
    printf("   Before:     After:\n");
    printf("    10          20\n");
    printf("     \\         /  \\\n");
    printf("      20 -->  10   30\n");
    printf("       \\\n");
    printf("        30\n");
    
    printf("\n3. Left-Right Rotation (LR):\n");
    printf("   Before:       After:\n");
    printf("      30           20\n");
    printf("     /           /  \\\n");
    printf("    10    -->   10   30\n");
    printf("     \\\n");
    printf("      20\n");
    
    printf("\n4. Right-Left Rotation (RL):\n");
    printf("   Before:       After:\n");
    printf("    10            20\n");
    printf("     \\          /  \\\n");
    printf("      30  -->  10   30\n");
    printf("     /\n");
    printf("    20\n");
}

/**
 * Free all nodes in the tree
 * 
 * @param root: Root of tree to free
 */
void freeTree(AVLNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
