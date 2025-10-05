/**
 * validateBST.cpp
 *
 * Description:
 * This algorithm checks whether a given binary tree is a valid Binary Search Tree (BST).
 * It uses an in-order traversal to verify that each node's value is greater than the value of the previously visited node.
 * The in-order traversal naturally visits nodes in ascending order for a valid BST.
 * If any node violates the BST property (i.e., its value is not greater than the previous node's value), the algorithm sets the answer to false.
 * 
 * Time Complexity:
 * O(n) — each node visited once.
 * Space Complexity:
 * O(h) — recursion stack (tree height).
 */

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    TreeNode *prev = nullptr;

    void validate(TreeNode *root, bool &ans) {
        if (!ans || !root) return;

        validate(root->left, ans);

        if (prev && prev->val >= root->val) {
            ans = false;
            return;
        }

        prev = root;

        validate(root->right, ans);
    }

    bool isValidBST(TreeNode* root) {
        bool ans = true;
        prev = nullptr;
        validate(root, ans);
        return ans;
    }
};
