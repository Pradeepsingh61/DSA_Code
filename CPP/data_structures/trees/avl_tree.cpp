/**
 * AVL Tree - Self-Balancing Binary Search Tree
 * 
 * Description:
 * AVL (Adelson-Velsky and Landis) tree is a self-balancing binary search tree where
 * the difference between heights of left and right subtrees (balance factor) cannot
 * be more than 1 for all nodes. This ensures O(log n) time for search, insert, and delete.
 * 
 * Key Concepts:
 * - Balance Factor = height(left subtree) - height(right subtree)
 * - Balance factor must be in {-1, 0, 1} for all nodes
 * - Four rotation types: Left, Right, Left-Right, Right-Left
 * 
 * Operations:
 * - Insert: O(log n) - Insert node and rebalance
 * - Delete: O(log n) - Delete node and rebalance
 * - Search: O(log n) - Find a value
 * - Traversal: O(n) - Inorder, Preorder, Postorder
 * 
 * Advantages over regular BST:
 * - Guaranteed O(log n) height
 * - No skewed trees
 * - Predictable performance
 * 
 * Time Complexity:
 * - Search: O(log n)
 * - Insert: O(log n)
 * - Delete: O(log n)
 * - Traversal: O(n)
 * 
 * Space Complexity: O(n) for storing n nodes
 * 
 * Applications:
 * - Database indexing
 * - Memory management
 * - File systems
 * - Priority queues
 * - In-memory databases
 * 
 * Author: GitHub Copilot
 * Date: October 2025
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

/**
 * Node structure for AVL Tree
 */
class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;  // Height of the node
    
    // Constructor
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;  // New node is initially at height 1
    }
};

/**
 * AVL Tree class with all operations
 */
class AVLTree {
private:
    Node* root;
    
    /**
     * Get height of a node
     * 
     * @param node Pointer to node
     * @return Height of the node, 0 if node is null
     */
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    
    /**
     * Calculate balance factor of a node
     * Balance Factor = height(left) - height(right)
     * 
     * @param node Pointer to node
     * @return Balance factor of the node
     */
    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    /**
     * Update height of a node based on its children
     * 
     * @param node Pointer to node
     */
    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    /**
     * Right rotation (LL case)
     * 
     *       y                               x
     *      / \     Right Rotation          / \
     *     x   T3   --------------->       T1  y
     *    / \                                 / \
     *   T1  T2                              T2  T3
     * 
     * @param y Root of subtree to rotate
     * @return New root after rotation
     */
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;  // New root
    }
    
    /**
     * Left rotation (RR case)
     * 
     *     x                               y
     *    / \      Left Rotation          / \
     *   T1  y     --------------->       x   T3
     *      / \                          / \
     *     T2  T3                       T1  T2
     * 
     * @param x Root of subtree to rotate
     * @return New root after rotation
     */
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;  // New root
    }
    
    /**
     * Insert a node and rebalance the tree
     * 
     * @param node Current root of subtree
     * @param value Value to insert
     * @return New root after insertion and balancing
     */
    Node* insertNode(Node* node, int value) {
        // 1. Perform standard BST insertion
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            // Duplicate values not allowed
            cout << "Value " << value << " already exists in the tree.\n";
            return node;
        }
        
        // 2. Update height of current node
        updateHeight(node);
        
        // 3. Get balance factor
        int balance = getBalanceFactor(node);
        
        // 4. Balance the tree if needed
        
        // Left-Left Case (LL)
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        
        // Right-Right Case (RR)
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        
        // Left-Right Case (LR)
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Left Case (RL)
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    /**
     * Find node with minimum value (leftmost node)
     * 
     * @param node Root of subtree
     * @return Node with minimum value
     */
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    /**
     * Delete a node and rebalance the tree
     * 
     * @param node Current root of subtree
     * @param value Value to delete
     * @return New root after deletion and balancing
     */
    Node* deleteNode(Node* node, int value) {
        // 1. Perform standard BST deletion
        if (node == nullptr) {
            cout << "Value " << value << " not found in the tree.\n";
            return node;
        }
        
        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node to be deleted found
            
            // Case 1: Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 2: Node with two children
            // Get inorder successor (smallest in right subtree)
            Node* temp = findMin(node->right);
            
            // Copy successor's data to this node
            node->data = temp->data;
            
            // Delete the successor
            node->right = deleteNode(node->right, temp->data);
        }
        
        // If tree had only one node
        if (node == nullptr)
            return node;
        
        // 2. Update height of current node
        updateHeight(node);
        
        // 3. Get balance factor
        int balance = getBalanceFactor(node);
        
        // 4. Balance the tree if needed
        
        // Left-Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Left-Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Right-Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    /**
     * Search for a value in the tree
     * 
     * @param node Current root of subtree
     * @param value Value to search
     * @return True if found, false otherwise
     */
    bool searchNode(Node* node, int value) {
        if (node == nullptr)
            return false;
        
        if (node->data == value)
            return true;
        
        if (value < node->data)
            return searchNode(node->left, value);
        else
            return searchNode(node->right, value);
    }
    
    /**
     * Inorder traversal (Left -> Root -> Right)
     * Gives sorted order for BST
     * 
     * @param node Current node
     */
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    
    /**
     * Preorder traversal (Root -> Left -> Right)
     * 
     * @param node Current node
     */
    void preorderTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    
    /**
     * Postorder traversal (Left -> Right -> Root)
     * 
     * @param node Current node
     */
    void postorderTraversal(Node* node) {
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->data << " ";
        }
    }
    
    /**
     * Level order traversal (breadth-first)
     * 
     * @param node Root of tree
     */
    void levelOrderTraversal(Node* node) {
        if (node == nullptr)
            return;
        
        queue<Node*> q;
        q.push(node);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            cout << current->data << " ";
            
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
    }
    
    /**
     * Display tree structure with balance factors
     * 
     * @param node Current node
     * @param space Current indentation
     */
    void displayTree(Node* node, int space) {
        if (node == nullptr)
            return;
        
        space += 10;
        
        displayTree(node->right, space);
        
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << node->data << "[" << getBalanceFactor(node) << "]" << endl;
        
        displayTree(node->left, space);
    }
    
    /**
     * Check if tree is balanced
     * 
     * @param node Current node
     * @return True if balanced, false otherwise
     */
    bool isBalanced(Node* node) {
        if (node == nullptr)
            return true;
        
        int balance = getBalanceFactor(node);
        
        if (abs(balance) > 1)
            return false;
        
        return isBalanced(node->left) && isBalanced(node->right);
    }
    
    /**
     * Count total nodes in tree
     * 
     * @param node Current node
     * @return Number of nodes
     */
    int countNodes(Node* node) {
        if (node == nullptr)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
public:
    /**
     * Constructor
     */
    AVLTree() {
        root = nullptr;
    }
    
    /**
     * Insert a value into the AVL tree
     * 
     * @param value Value to insert
     */
    void insert(int value) {
        root = insertNode(root, value);
    }
    
    /**
     * Delete a value from the AVL tree
     * 
     * @param value Value to delete
     */
    void remove(int value) {
        root = deleteNode(root, value);
    }
    
    /**
     * Search for a value
     * 
     * @param value Value to search
     * @return True if found, false otherwise
     */
    bool search(int value) {
        return searchNode(root, value);
    }
    
    /**
     * Display inorder traversal
     */
    void inorder() {
        cout << "Inorder Traversal: ";
        inorderTraversal(root);
        cout << endl;
    }
    
    /**
     * Display preorder traversal
     */
    void preorder() {
        cout << "Preorder Traversal: ";
        preorderTraversal(root);
        cout << endl;
    }
    
    /**
     * Display postorder traversal
     */
    void postorder() {
        cout << "Postorder Traversal: ";
        postorderTraversal(root);
        cout << endl;
    }
    
    /**
     * Display level order traversal
     */
    void levelOrder() {
        cout << "Level Order Traversal: ";
        levelOrderTraversal(root);
        cout << endl;
    }
    
    /**
     * Display tree structure
     */
    void display() {
        cout << "\nTree Structure (value[balance factor]):\n";
        displayTree(root, 0);
        cout << endl;
    }
    
    /**
     * Get height of tree
     * 
     * @return Height of tree
     */
    int height() {
        return getHeight(root);
    }
    
    /**
     * Check if tree is balanced
     * 
     * @return True if balanced, false otherwise
     */
    bool isBalanced() {
        return isBalanced(root);
    }
    
    /**
     * Get total number of nodes
     * 
     * @return Number of nodes
     */
    int size() {
        return countNodes(root);
    }
    
    /**
     * Check if tree is empty
     * 
     * @return True if empty, false otherwise
     */
    bool isEmpty() {
        return root == nullptr;
    }
};

/**
 * Demo function showing AVL tree operations
 */
void runDemo() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "              AVL TREE DEMONSTRATION\n";
    cout << string(60, '=') << "\n";
    
    AVLTree avl;
    
    // Demo 1: Insertions causing LL rotation
    cout << "\n--- DEMO 1: Left-Left (LL) Rotation ---\n";
    cout << "Inserting: 30, 20, 10\n";
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);  // This will cause LL rotation
    avl.display();
    avl.inorder();
    
    // Demo 2: RR rotation
    cout << "\n--- DEMO 2: Right-Right (RR) Rotation ---\n";
    AVLTree avl2;
    cout << "Inserting: 10, 20, 30\n";
    avl2.insert(10);
    avl2.insert(20);
    avl2.insert(30);  // This will cause RR rotation
    avl2.display();
    avl2.inorder();
    
    // Demo 3: LR rotation
    cout << "\n--- DEMO 3: Left-Right (LR) Rotation ---\n";
    AVLTree avl3;
    cout << "Inserting: 30, 10, 20\n";
    avl3.insert(30);
    avl3.insert(10);
    avl3.insert(20);  // This will cause LR rotation
    avl3.display();
    avl3.inorder();
    
    // Demo 4: RL rotation
    cout << "\n--- DEMO 4: Right-Left (RL) Rotation ---\n";
    AVLTree avl4;
    cout << "Inserting: 10, 30, 20\n";
    avl4.insert(10);
    avl4.insert(30);
    avl4.insert(20);  // This will cause RL rotation
    avl4.display();
    avl4.inorder();
    
    // Demo 5: Complex insertions
    cout << "\n--- DEMO 5: Complex AVL Tree ---\n";
    AVLTree avl5;
    int values[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 65};
    cout << "Inserting values: ";
    for (int val : values) {
        cout << val << " ";
        avl5.insert(val);
    }
    cout << "\n";
    avl5.display();
    avl5.inorder();
    cout << "Tree Height: " << avl5.height() << endl;
    cout << "Tree Size: " << avl5.size() << endl;
    cout << "Is Balanced: " << (avl5.isBalanced() ? "Yes" : "No") << endl;
    
    // Demo 6: Deletions
    cout << "\n--- DEMO 6: Deletions with Rebalancing ---\n";
    cout << "Deleting: 10, 25\n";
    avl5.remove(10);
    avl5.remove(25);
    avl5.display();
    avl5.inorder();
    cout << "Tree Height: " << avl5.height() << endl;
    cout << "Is Balanced: " << (avl5.isBalanced() ? "Yes" : "No") << endl;
    
    // Demo 7: Search operations
    cout << "\n--- DEMO 7: Search Operations ---\n";
    int searchValues[] = {50, 100, 60, 25};
    for (int val : searchValues) {
        cout << "Searching for " << val << ": " 
             << (avl5.search(val) ? "Found" : "Not Found") << endl;
    }
    
    cout << "\n" << string(60, '=') << "\n";
}

/**
 * Main function - Runs comprehensive demo
 */
int main() {
    cout << "\n";
    cout << "========================================================\n";
    cout << "                                                        \n";
    cout << "              AVL TREE IMPLEMENTATION                   \n";
    cout << "                                                        \n";
    cout << "    Self-Balancing Binary Search Tree with O(log n)    \n";
    cout << "                                                        \n";
    cout << "========================================================\n";
    
    // Run the comprehensive demo
    runDemo();
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "KEY FEATURES:\n";
    cout << string(60, '=') << "\n";
    cout << "* Self-balancing with automatic rotations\n";
    cout << "* Four rotation types: LL, RR, LR, RL\n";
    cout << "* Guaranteed O(log n) height\n";
    cout << "* Balance factor maintained in {-1, 0, 1}\n";
    cout << "* All operations in O(log n) time\n";
    cout << "\nOperations:\n";
    cout << "  - Insert: O(log n)\n";
    cout << "  - Delete: O(log n)\n";
    cout << "  - Search: O(log n)\n";
    cout << "  - Traversals: O(n)\n";
    cout << "\nApplications:\n";
    cout << "  - Database indexing\n";
    cout << "  - Memory management\n";
    cout << "  - File systems\n";
    cout << "  - In-memory databases\n";
    cout << string(60, '=') << "\n\n";
    
    return 0;
}
