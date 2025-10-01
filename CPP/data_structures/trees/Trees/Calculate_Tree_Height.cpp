/*
 * Algorithm: Height of Binary Tree
 * Description: Recursively finds the maximum number of edges on the path from the root to any leaf node.
 * Time Complexity: O(n)
 * Space Complexity: O(h) // Where 'h' is the height of the tree, due to recursion stack
 * Author: Adi-3108
 */

#include <iostream>
#include <algorithm> // Required for max

using namespace std;
// 1. Structure Definition
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    
    // Constructor
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Recursively calculates the height of the binary tree.
 * * Height is defined as the number of edges on the longest path from the root to a leaf.
 * * @param root The root of the binary tree (or subtree).
 * @return The height of the tree (number of edges).
 */
int calculateHeight(TreeNode* root) {
    // Base case: An empty tree (NULL) has a height of -1 (so a single node returns 0).
    if (root == NULL) {
        return -1; 
    }

    // Recursively find the height of the left and right subtrees
    int left_height = calculateHeight(root->left);
    int right_height = calculateHeight(root->right);

    // The height of the current tree is 1 (for the current node/edge) 
    // plus the maximum height of the subtrees.
    return 1 + max(left_height, right_height);
}

// Test function with modern C++ features
void testCalculateHeight() {
    // Test Case 1: Skewed Tree (Height = 3)
    // 1 -> 2 -> 3 -> 4
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->left->left = new TreeNode(4);
     // for verification We are Printing the expected height
    cout << "Test Case 1 (Skewed Tree):\n";
    cout << "Expected Height: 3, Actual Height: " << calculateHeight(root1) << endl;

    // Test Case 2: Balanced Tree (Height = 2)
    //    1
    //   / \
    //  2   3
    // / \
    // 4  5
    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);

    cout << "\nTest Case 2 (Balanced Tree):\n";

    // for verification We are Printing the expected height
    cout << "Expected Height: 2, Actual Height: " << calculateHeight(root2) << endl;
    
    // Clean up memory
    delete root1->left->left->left;
    delete root1->left->left;
    delete root1->left;
    delete root1;

    delete root2->left->left;
    delete root2->left->right;
    delete root2->left;
    delete root2->right;
    delete root2;
}

int main() {
    testCalculateHeight();
    return 0;
}