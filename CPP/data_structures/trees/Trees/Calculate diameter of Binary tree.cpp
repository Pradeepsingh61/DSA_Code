#include <iostream>
#include <algorithm>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor to initialize the node with a value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Class for calculating the diameter
class Solution {
public:
    // Function to find the diameter of a binary tree
    int diameterOfBinaryTree(Node* root) {
        int diameter = 0; // Initialize diameter
        height(root, diameter); // Call height function
        return diameter; // Return the calculated diameter
    }

private:
    // Function to calculate the height of the tree and update the diameter
    int height(Node* node, int& diameter) {
        if (!node) {
            return 0; // Base case: height of an empty tree is 0
        }

        // Recursively calculate height of left and right subtrees
        int lh = height(node->left, diameter);
        int rh = height(node->right, diameter);

        // Update the diameter with the maximum of current diameter or sum of left and right heights
        diameter = max(diameter, lh + rh);

        // Return the height of the current node's subtree
        return 1 + max(lh, rh);
    }
};

// Function to delete the tree and free memory
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node; // Free memory
    }
}

// Function to create a sample binary tree
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);
    return root;
}

// Main function
int main() {
    // Creating a sample binary tree
    Node* root = createSampleTree();

    // Creating an instance of the Solution class
    Solution solution;

    // Calculate the diameter of the binary tree
    int diameter = solution.diameterOfBinaryTree(root);

    cout << "The diameter of the binary tree is: " << diameter << endl;

    // Clean up memory
    deleteTree(root); // Free the allocated memory

    // Additional test cases
    Node* testRoot1 = new Node(1); // Single node tree
    cout << "Diameter of single node tree: " << solution.diameterOfBinaryTree(testRoot1) << endl;
    delete testRoot1;

    Node* testRoot2 = new Node(1); // Balanced tree
    testRoot2->left = new Node(2);
    testRoot2->right = new Node(3);
    testRoot2->left->left = new Node(4);
    testRoot2->left->right = new Node(5);
    cout << "Diameter of balanced tree: " << solution.diameterOfBinaryTree(testRoot2) << endl;
    deleteTree(testRoot2);

    Node* testRoot3 = new Node(1); // Right skewed tree
    testRoot3->right = new Node(2);
    testRoot3->right->right = new Node(3);
    cout << "Diameter of right skewed tree: " << solution.diameterOfBinaryTree(testRoot3) << endl;
    deleteTree(testRoot3);

    return 0;
}
