#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BinaryTreeToDLL {
public:
    Node* head = nullptr; // Head of the resulting DLL
    Node* prev = nullptr; // Previous node in DLL

    void convertToDLL(Node* root) {
        if (root == nullptr)
            return;

        // Recursively convert the left subtree
        convertToDLL(root->left);

        // Process the current node
        if (head == nullptr) {
            // Set the first node as the head of the DLL
            head = root;
        } else {
            // Link the current node with the previous node in DLL
            root->left = prev;
            prev->right = root;
        }

        // Move the prev pointer to the current node
        prev = root;

        // Recursively convert the right subtree
        convertToDLL(root->right);
    }

    void printDLL() {
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->right) {
                cout << " <-> ";
            }
            current = current->right;
        }
        cout << endl;
    }
};

// Example Usage
int main() {
    // Constructing a sample binary tree
    //        10
    //       /  \
    //      5    15
    //     / \     \
    //    2   7     20

    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->right->right = new Node(20);

    // Convert the binary tree to doubly linked list
    BinaryTreeToDLL converter;
    converter.convertToDLL(root);

    // Print the resulting doubly linked list
    converter.printDLL();

    return 0;
}
