// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert in BST
Node* insert(Node* root, int val) {
    if (root == NULL) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

// Search in BST
bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

// Find minimum value node
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Delete node from BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (root->left == NULL) return root->right;
        else if (root->right == NULL) return root->left;
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder to check BST
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    root = insert(root, 8);
    insert(root, 3);
    insert(root, 10);
    insert(root, 1);
    insert(root, 6);
    insert(root, 14);

    cout << "Inorder before deletion: "; inorder(root); cout << endl;
    cout << "Searching 6: " << (search(root, 6) ? "Found" : "Not Found") << endl;

    root = deleteNode(root, 3);
    cout << "Inorder after deletion: "; inorder(root); cout << endl;
}
    