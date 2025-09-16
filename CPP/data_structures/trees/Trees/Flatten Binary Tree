#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void flatten(TreeNode* root) {
    if (!root) return;
    flatten(root->left);
    flatten(root->right);
    TreeNode* rightSubtree = root->right;
    root->right = root->left;
    root->left = nullptr;
    TreeNode* current = root;
    while (current->right) {
        current = current->right;
    }
    current->right = rightSubtree;
}

void printFlattenedTree(TreeNode* root) {
    while (root) {
        cout << root->val << " ";
        root = root->right;
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    
    flatten(root);
    printFlattenedTree(root);

    return 0;
}
