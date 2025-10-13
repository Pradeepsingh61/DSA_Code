/*
 * Splay Tree Implementation
 *
 * A Splay Tree is a self-adjusting binary search tree with the property that recently
 * accessed elements are quick to access again. It performs basic operations such as
 * insertion, look-up, and removal in O(log n) amortized time.
 *
 * Time Complexity (amortized):
 * - Search: O(log n)
 * - Insert: O(log n)
 * - Delete: O(log n)
 * 
 * Space Complexity: O(n)
 * 
 * The key feature of splay trees is the "splaying" operation, which brings a node to the root
 * through a sequence of rotations, restructuring the tree to provide faster access to recently
 * used elements.
 * 
 * Author: Abhiram
 * Date: October 13, 2025
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class SplayTree {
private:
    struct Node {
        int key;          // The value stored in the node
        Node* left;       // Pointer to left child
        Node* right;      // Pointer to right child
        
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    
    Node* root;    // Root of the splay tree
    
    // Rotates right at node x
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    // Rotates left at node x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    // Splays the tree so that key is at the root
    Node* splay(Node* root, int key) {
        // Base cases: root is NULL or key is at root
        if (root == nullptr || root->key == key)
            return root;
        
        // Key is in the left subtree
        if (root->key > key) {
            // Key is not in the tree, return
            if (root->left == nullptr) return root;
            
            // Zig-Zig (Left Left)
            if (root->left->key > key) {
                // First recursively bring the key as root of left-left
                root->left->left = splay(root->left->left, key);
                // Do first rotation for root, second rotation is done after else
                root = rightRotate(root);
            }
            // Zig-Zag (Left Right)
            else if (root->left->key < key) {
                // First recursively bring the key as root of left-right
                root->left->right = splay(root->left->right, key);
                
                // Do first rotation for root->left
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            
            // Do second rotation for root
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        // Key is in the right subtree
        else {
            // Key is not in the tree, return
            if (root->right == nullptr) return root;
            
            // Zag-Zig (Right Left)
            if (root->right->key > key) {
                // First recursively bring the key as root of right-left
                root->right->left = splay(root->right->left, key);
                
                // Do first rotation for root->right
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            // Zag-Zag (Right Right)
            else if (root->right->key < key) {
                // First recursively bring the key as root of right-right
                root->right->right = splay(root->right->right, key);
                // Do first rotation for root, second rotation is done after else
                root = leftRotate(root);
            }
            
            // Do second rotation for root
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }
    
    // Function to search a key in the tree
    Node* search(Node* root, int key) {
        return splay(root, key);
    }
    
    // Function to insert a new key into the tree
    Node* insert(Node* root, int key) {
        // Base case: If tree is empty
        if (root == nullptr) return new Node(key);
        
        // Splay the tree to potentially bring the key or its neighbor to the root
        root = splay(root, key);
        
        // If key is already present, return
        if (root->key == key) return root;
        
        // Create a new node
        Node* newNode = new Node(key);
        
        // If root's key is greater, make root as the right child of newNode
        // and copy the left subtree of root as the left subtree of newNode
        if (root->key > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        // If root's key is smaller, make root as the left child of newNode
        // and copy the right subtree of root as the right subtree of newNode
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        
        return newNode;
    }
    
    // Function to delete a key from the tree
    Node* deleteKey(Node* root, int key) {
        if (root == nullptr) return nullptr;
        
        // Splay the tree to bring the key to the root if it exists
        root = splay(root, key);
        
        // If the key is not found, return
        if (root->key != key) return root;
        
        // We found the key
        Node* temp;
        
        // No left subtree, make right subtree as the new tree
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        }
        // Left subtree exists
        else {
            // Make the right subtree as the new tree, and attach the original
            // right subtree to the rightmost node of the left subtree
            temp = root;
            root = root->left;
            
            // Splay the left subtree so that the max element is the root
            root = splay(root, key);
            
            // Attach the right subtree
            root->right = temp->right;
        }
        
        delete temp;
        return root;
    }
    
    // Function to find the minimum key value in the tree
    Node* findMin(Node* root) {
        if (root == nullptr) return nullptr;
        
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        
        // Splay the tree to bring the min to the root
        return splay(root, current->key);
    }
    
    // Function to find the maximum key value in the tree
    Node* findMax(Node* root) {
        if (root == nullptr) return nullptr;
        
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        
        // Splay the tree to bring the max to the root
        return splay(root, current->key);
    }
    
    // Function to print the tree in-order
    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }
    
    // Function to print the tree in level order
    void levelOrderTraversal(Node* root) {
        if (root == nullptr) return;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                
                cout << current->key << " ";
                
                if (current->left != nullptr)
                    q.push(current->left);
                    
                if (current->right != nullptr)
                    q.push(current->right);
            }
            
            cout << endl;
        }
    }
    
    // Helper function to clean up memory
    void cleanup(Node* root) {
        if (root != nullptr) {
            cleanup(root->left);
            cleanup(root->right);
            delete root;
        }
    }
    
public:
    // Constructor
    SplayTree() : root(nullptr) {}
    
    // Destructor
    ~SplayTree() {
        cleanup(root);
    }
    
    // Public methods
    
    // Insert a key into the tree
    void insert(int key) {
        root = insert(root, key);
    }
    
    // Search for a key in the tree
    bool search(int key) {
        if (root == nullptr) return false;
        
        root = search(root, key);
        return (root->key == key);
    }
    
    // Delete a key from the tree
    void remove(int key) {
        if (root == nullptr) return;
        
        root = deleteKey(root, key);
    }
    
    // Find the minimum key in the tree
    int findMin() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return -1; // Assuming -1 is not a valid key
        }
        
        root = findMin(root);
        return root->key;
    }
    
    // Find the maximum key in the tree
    int findMax() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return -1; // Assuming -1 is not a valid key
        }
        
        root = findMax(root);
        return root->key;
    }
    
    // Print the tree in-order
    void printInorder() {
        cout << "In-order traversal: ";
        inorderTraversal(root);
        cout << endl;
    }
    
    // Print the tree level by level
    void printLevelOrder() {
        cout << "Level-order traversal:" << endl;
        levelOrderTraversal(root);
    }
    
    // Check if the tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

// Example usage
int main() {
    SplayTree tree;
    
    cout << "Inserting elements: 10, 20, 30, 40, 50, 25" << endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    
    tree.printInorder();
    cout << endl;
    
    cout << "Searching for 30..." << endl;
    if (tree.search(30))
        cout << "30 found in the tree" << endl;
    else
        cout << "30 not found in the tree" << endl;
    
    // The tree structure might have changed after the search
    tree.printInorder();
    cout << endl;
    
    cout << "Searching for 35..." << endl;
    if (tree.search(35))
        cout << "35 found in the tree" << endl;
    else
        cout << "35 not found in the tree" << endl;
    
    // The tree structure might have changed after the search
    tree.printInorder();
    cout << endl;
    
    cout << "Minimum element: " << tree.findMin() << endl;
    cout << "Maximum element: " << tree.findMax() << endl;
    
    cout << endl;
    cout << "Tree structure (level order):" << endl;
    tree.printLevelOrder();
    
    cout << endl;
    cout << "Removing 30..." << endl;
    tree.remove(30);
    tree.printInorder();
    
    cout << endl;
    cout << "Removing 10..." << endl;
    tree.remove(10);
    tree.printInorder();
    
    cout << endl;
    cout << "Final tree structure (level order):" << endl;
    tree.printLevelOrder();
    
    return 0;
}