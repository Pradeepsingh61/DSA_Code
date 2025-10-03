#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <map>
using namespace std;

/*
-----------------------------------------------------
🌳 All Nodes Distance K in Binary Tree
-----------------------------------------------------
📌 Description:
Given a binary tree, a target node, and an integer K,
find all nodes in the tree that are exactly K distance 
away from the target node. 

Approach:
1. First, traverse the tree to mark each node's parent.
2. Then, perform a BFS starting from the target node,
   moving both to children and parent, keeping track of visited nodes.
3. Collect all nodes at distance K.

📊 Complexity Analysis:
- Time Complexity: O(N), where N is the number of nodes in the tree.
  We visit each node at most twice (once for marking parents, once for BFS).
- Space Complexity: O(N), for parent mapping, visited map, and BFS queue.

✅ Applications:
- Tree-based graph problems
- Distance-related queries in trees
- Competitive programming / coding interviews
-----------------------------------------------------
*/

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Solution class
class Solution {
    // Helper function to mark parents of each node
    void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr->left) {
                parent[curr->left] = curr;
                q.push(curr->left);
            }
            if (curr->right) {
                parent[curr->right] = curr;
                q.push(curr->right);
            }
        }
    }

public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        unordered_map<TreeNode*, TreeNode*> parent;
        markParents(root, parent);

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;

        int currLevel = 0;
        while (!q.empty()) {
            int size = q.size();
            if (currLevel++ == K) break;
            for (int i = 0; i < size; i++) {
                TreeNode* curr = q.front();
                q.pop();

                if (curr->left && !visited[curr->left]) {
                    q.push(curr->left);
                    visited[curr->left] = true;
                }
                if (curr->right && !visited[curr->right]) {
                    q.push(curr->right);
                    visited[curr->right] = true;
                }
                if (parent[curr] && !visited[parent[curr]]) {
                    q.push(parent[curr]);
                    visited[parent[curr]] = true;
                }
            }
        }

        vector<int> res;
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            res.push_back(curr->val);
        }
        return res;
    }
};

// Utility function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    return root;
}

// Driver function
int main() {
    cout << "All Nodes Distance K in Binary Tree implementation." << endl;

    TreeNode* root = createSampleTree();
    TreeNode* target = root->left; // Node with value 5
    int K = 2;

    Solution sol;
    vector<int> result = sol.distanceK(root, target, K);

    cout << "Nodes at distance " << K << " from target (" << target->val << "): ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
