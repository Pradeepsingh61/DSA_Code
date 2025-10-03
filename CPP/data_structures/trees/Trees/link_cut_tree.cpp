/*
 * Link/Cut Tree (Dynamic Tree using Splay Trees)
 *
 * Supports dynamic connectivity, path queries, and path updates in a forest of rooted trees.
 * Operations: link, cut, findRoot, path aggregate (e.g., sum, min, max), etc.
 *
 * Time Complexity: O(log n) per operation (amortized)
 *
 * Author: Abhi
 * Date: October 2, 2025
 */

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node *left, *right, *parent;
    bool revert;
    int value, pathValue; // pathValue can be sum/min/max on the path
    Node(int v) : left(nullptr), right(nullptr), parent(nullptr), revert(false), value(v), pathValue(v) {}
};

// Utility functions
void push(Node* x) {
    if (!x || !x->revert) return;
    swap(x->left, x->right);
    if (x->left) x->left->revert ^= 1;
    if (x->right) x->right->revert ^= 1;
    x->revert = false;
}

void update(Node* x) {
    x->pathValue = x->value;
    if (x->left) x->pathValue ^= x->left->pathValue; // Example: xor on path
    if (x->right) x->pathValue ^= x->right->pathValue;
}

bool isRoot(Node* x) {
    return !x->parent || (x->parent->left != x && x->parent->right != x);
}

void rotate(Node* x) {
    Node* p = x->parent;
    Node* g = p->parent;
    push(p); push(x);
    if (p->left == x) {
        p->left = x->right;
        if (x->right) x->right->parent = p;
        x->right = p;
    } else {
        p->right = x->left;
        if (x->left) x->left->parent = p;
        x->left = p;
    }
    p->parent = x;
    x->parent = g;
    if (g) {
        if (g->left == p) g->left = x;
        if (g->right == p) g->right = x;
    }
    update(p); update(x);
}

void splay(Node* x) {
    push(x);
    while (!isRoot(x)) {
        Node* p = x->parent;
        Node* g = p->parent;
        if (!isRoot(p))
            rotate((g->left == p) == (p->left == x) ? p : x);
        rotate(x);
    }
}

// Expose: brings the path from x to root to the top
Node* expose(Node* x) {
    Node* last = nullptr;
    for (Node* y = x; y; y = y->parent) {
        splay(y);
        y->right = last;
        update(y);
        last = y;
    }
    splay(x);
    return last;
}

// Make x the root of its tree
void makeRoot(Node* x) {
    expose(x);
    x->revert ^= 1;
    push(x);
}

// Link x as a child of y
void link(Node* x, Node* y) {
    makeRoot(x);
    x->parent = y;
}

// Cut the connection between x and its parent
void cut(Node* x, Node* y) {
    makeRoot(x);
    expose(y);
    if (y->left == x && !x->right) {
        y->left = nullptr;
        x->parent = nullptr;
        update(y);
    }
}

// Find the root of the tree containing x
Node* findRoot(Node* x) {
    expose(x);
    while (x->left) {
        push(x);
        x = x->left;
    }
    splay(x);
    return x;
}

// Query the xor of values on the path from x to y
int pathQuery(Node* x, Node* y) {
    makeRoot(x);
    expose(y);
    return y->pathValue;
}

// Example usage
int main() {
    // Create nodes
    int n = 5;
    vector<Node*> nodes;
    for (int i = 0; i < n; ++i) nodes.push_back(new Node(i+1));

    // Link nodes to form a tree: 1-2-3, 4-5
    link(nodes[0], nodes[1]); // 1-2
    link(nodes[1], nodes[2]); // 2-3
    link(nodes[3], nodes[4]); // 4-5

    // Query xor on path 1-3
    cout << "XOR on path 1-3: " << pathQuery(nodes[0], nodes[2]) << endl;

    // Link 3-4 to connect the two trees
    link(nodes[2], nodes[3]);
    cout << "XOR on path 1-5: " << pathQuery(nodes[0], nodes[4]) << endl;

    // Cut edge 2-3
    cut(nodes[1], nodes[2]);
    cout << "After cut, root of 3: " << findRoot(nodes[2])->value << endl;
    cout << "After cut, root of 1: " << findRoot(nodes[0])->value << endl;

    // Clean up
    for (auto node : nodes) delete node;
    return 0;
}
