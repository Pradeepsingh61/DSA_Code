// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) { data = val; left = right = NULL; }
};

int diameterUtil(Node* root, int& height) {
    if (root == NULL) {
        height = 0;
        return 0;
    }
    int lh = 0, rh = 0;
    int ldiameter = diameterUtil(root->left, lh);
    int rdiameter = diameterUtil(root->right, rh);

    height = max(lh, rh) + 1;

    return max(lh + rh + 1, max(ldiameter, rdiameter));
}

int diameter(Node* root) {
    int height = 0;
    return diameterUtil(root, height);
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Diameter of tree is: " << diameter(root) << endl;
}
