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
