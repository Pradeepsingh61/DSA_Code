#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5;
const int MAX_TREE = 2e6;

struct Node {
    int left, right;
    int sum;
} tree[MAX_TREE];

int root[MAXN]; // root[i] is the root of version i
int node_cnt = 0;

int build(int l, int r, const vector<int>& arr) {
    int node = node_cnt++;
    if (l == r) {
        tree[node].sum = arr[l];
        return node;
    }
    int mid = (l + r) / 2;
    tree[node].left = build(l, mid, arr);
    tree[node].right = build(mid + 1, r, arr);
    tree[node].sum = tree[tree[node].left].sum + tree[tree[node].right].sum;
    return node;
}

int update(int prev_node, int l, int r, int pos, int val) {
    int node = node_cnt++;
    if (l == r) {
        tree[node].sum = val;
        return node;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        tree[node].left = update(tree[prev_node].left, l, mid, pos, val);
        tree[node].right = tree[prev_node].right;
    } else {
        tree[node].left = tree[prev_node].left;
        tree[node].right = update(tree[prev_node].right, mid + 1, r, pos, val);
    }
    tree[node].sum = tree[tree[node].left].sum + tree[tree[node].right].sum;
    return node;
}

int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return tree[node].sum;
    int mid = (l + r) / 2;
    return query(tree[node].left, l, mid, ql, qr) +
           query(tree[node].right, mid + 1, r, ql, qr);
}

int main() {
    int n = 5;
    vector<int> arr = {0, 1, 2, 3, 4, 5}; // 1-based indexing

    root[0] = build(1, n, arr);

    root[1] = update(root[0], 1, n, 3, 10); // update index 3 to 10
    root[2] = update(root[1], 1, n, 5, 20); // update index 5 to 20

    cout << "Version 0, sum(1,5): " << query(root[0], 1, n, 1, 5) << endl;
    cout << "Version 1, sum(1,5): " << query(root[1], 1, n, 1, 5) << endl;
    cout << "Version 2, sum(1,5): " << query(root[2], 1, n, 1, 5) << endl;

    return 0;
}
