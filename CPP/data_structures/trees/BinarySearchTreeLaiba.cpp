#include <iostream>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new node
TreeNode* createNode(int value) {
    TreeNode* node = new TreeNode;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to check BST validity
bool isValidBSTHelper(TreeNode* root, long long minVal, long long maxVal) {
    if (root == NULL)
        return true;

    // Check current node value against range
    if (root->val <= minVal || root->val >= maxVal)
        return false;

    // Recursively check left and right subtrees
    return isValidBSTHelper(root->left, minVal, root->val) &&
           isValidBSTHelper(root->right, root->val, maxVal);
}

// Main function to check if tree is a valid BST
bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, -9223372036854775807LL, 9223372036854775807LL);
}

// Example usage
int main() {
    /*
        Example 1:
             2
            / \
           1   3
        Expected output: Valid BST
    */

    TreeNode* root = createNode(2);
    root->left = createNode(1);
    root->right = createNode(3);

    if (isValidBST(root))
        cout << "Valid BST" << endl;
    else
        cout << "Invalid BST" << endl;

    /*
        Example 2:
             5
            / \
           1   4
              / \
             3   6
        Expected output: Invalid BST
    */

    TreeNode* root2 = createNode(5);
    root2->left = createNode(1);
    root2->right = createNode(4);
    root2->right->left = createNode(3);
    root2->right->right = createNode(6);

    if (isValidBST(root2))
        cout << "Valid BST" << endl;
    else
        cout << "Invalid BST" << endl;

    return 0;
}
