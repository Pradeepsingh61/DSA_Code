#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

void mergeBSTs(Node* root1, Node* root2, Node*& mergedRoot) {
    if (root1) {
        mergeBSTs(root1->left, root2, mergedRoot);
        mergedRoot = insert(mergedRoot, root1->data);
        mergeBSTs(root1->right, root2, mergedRoot);
    }
    if (root2) {
        mergeBSTs(root1, root2->left, mergedRoot);
        mergedRoot = insert(mergedRoot, root2->data);
        mergeBSTs(root1, root2->right, mergedRoot);
    }
}

int main() {
    Node* root1 = nullptr;
    Node* root2 = nullptr;

    root1 = insert(root1, 50);
    root1 = insert(root1, 30);
    root1 = insert(root1, 70);
    root1 = insert(root1, 20);
    root1 = insert(root1, 40);
    root1 = insert(root1, 60);
    root1 = insert(root1, 80);

    cout << "In-order traversal of BST 1: ";
    inOrder(root1);
    cout << endl;

    root2 = insert(root2, 25);
    root2 = insert(root2, 35);
    root2 = insert(root2, 45);

    cout << "In-order traversal of BST 2: ";
    inOrder(root2);
    cout << endl;

    Node* mergedRoot = nullptr;
    mergeBSTs(root1, root2, mergedRoot);

    cout << "In-order traversal of the merged BST: ";
    inOrder(mergedRoot);
    cout << endl;

    return 0;
}
