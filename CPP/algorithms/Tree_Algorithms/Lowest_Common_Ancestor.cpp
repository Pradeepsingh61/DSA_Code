// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) { data = val; left = right = NULL; }
};

Node* LCA(Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (root->data == n1 || root->data == n2) return root;

    Node* leftLCA = LCA(root->left, n1, n2);
    Node* rightLCA = LCA(root->right, n1, n2);

    if (leftLCA && rightLCA) return root;
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Node* lca = LCA(root, 4, 5);
    cout << "LCA of 4 and 5 is: " << lca->data << endl;
}
