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
 * The algorithm traverses each node exactly once, resulting in a time complexity of O(n),
 * where n is the number of nodes in the binary tree.
 * The space complexity is O(h), where h is the height of the tree, due to the recursion stack.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode *prev = NULL;
    void validate(TreeNode *root, bool &ans){
        if(!ans || !root) return;
        if(root->left) validate(root->left, ans);
        if(prev && prev->val >= root->val){
            ans = false;
            return;
        }
        prev = root;
        if(root->right) validate(root->right, ans);
    }
    bool isValidBST(TreeNode* root) {
        bool ans = true;
        validate(root, ans);
        return ans;
    }
};
