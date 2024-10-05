#include <iostream>

using namespace std;

// Define the structure for a BST node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Function to insert a new node into the BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// In-order traversal (LNR)
void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}

// Pre-order traversal (NLR)
void preOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

// Post-order traversal (LRN)
void postOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int value : values) {
        root = insert(root, value);
    }

    cout << "In-order traversal: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "Pre-order traversal: ";
    preOrderTraversal(root);
    cout << endl;

    cout << "Post-order traversal: ";
    postOrderTraversal(root);
    cout << endl;

    return 0;
}
