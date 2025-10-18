#include <bits/stdc++.h>
using namespace std;

//Problem: Binary tree traversals (Inorder, Preorder, Postorder)
//Approach: Recursive traversals
//Time Complexity: O(n)
//Space Complexity: O(n)

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// Function to insert a node into the BST
TreeNode* insert(TreeNode* root, int val) {

    if (!root) return new TreeNode(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

// Inorder traversal (Left, Root, Right)
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

//Preorder traversal (Root, Left, Right)
void preorder(TreeNode* root){
    if(!root) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

//Postorder traversal (Left, Right, Root)
void postorder(TreeNode* root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}


int main() {
    TreeNode* root = NULL;
    int n, val;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter values to insert into BST:";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\nInorder Traversal: ";
    inorder(root);
    cout << "\nPreorder Traversal: ";
    preorder(root);
    cout<<"\nPostorder Traversal: ";
    postorder(root);
    cout<<endl;

    return 0;
}
