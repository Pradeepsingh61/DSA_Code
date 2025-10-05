/*
-----------------------------------------------
💡 Problem: Construct Binary Tree from Preorder and Inorder Traversal (LeetCode #105)
-----------------------------------------------
You are given two integer arrays `preorder` and `inorder` representing the preorder 
and inorder traversal of a binary tree. Construct and return the binary tree.

Example:
Input: 
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

-----------------------------------------------
🧠 Algorithm:
-----------------------------------------------
1. The first element in `preorder` is always the root node.
2. Using the root’s value, find its index in the `inorder` array.
   - All elements to the left of that index form the left subtree.
   - All elements to the right form the right subtree.
3. Recursively build the left and right subtrees.
4. A map (hash table) is used to store the indices of `inorder` elements 
   for O(1) lookup time.

-----------------------------------------------
⏱ Time Complexity: O(N)
   - Each node is visited once.
   - Building the map and recursive construction take linear time.

💾 Space Complexity: O(N)
   - O(N) for the recursion stack and hash map storage.

-----------------------------------------------
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// TreeNode structure
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Function to build a binary tree from preorder and inorder traversals
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Map to store indices of elements in inorder traversal
        map<int, int> inMap;
        
        // Store each element's index for O(1) lookup
        for (int i = 0; i < inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }

        // Recursively build tree using helper function
        TreeNode* root = buildTree(preorder, 0, preorder.size() - 1,
                                   inorder, 0, inorder.size() - 1, inMap);
        return root;
    }

private:
    // Recursive helper function to construct the tree
    TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd,
                        vector<int>& inorder, int inStart, int inEnd,
                        map<int, int>& inMap) {

        // Base case: if bounds are invalid, return NULL
        if (preStart > preEnd || inStart > inEnd)
            return NULL;

        // Create new node using current root value
        TreeNode* root = new TreeNode(preorder[preStart]);

        // Find root index in inorder array
        int inRoot = inMap[root->val];

        // Count of elements in left subtree
        int numsLeft = inRoot - inStart;

        // Recursively construct left subtree
        root->left = buildTree(preorder, preStart + 1, preStart + numsLeft,
                               inorder, inStart, inRoot - 1, inMap);

        // Recursively construct right subtree
        root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd,
                                inorder, inRoot + 1, inEnd, inMap);

        return root;
    }
};

// Function to print inorder traversal of a tree
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// Function to print a given vector
void printVector(vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main() {
    // Example input
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> preorder = {3, 9, 20, 15, 7};
    
    cout << "Inorder Vector: ";
    printVector(inorder);
    
    cout << "Preorder Vector: ";
    printVector(preorder);
    
    Solution sol;
    TreeNode* root = sol.buildTree(preorder, inorder);
    
    cout << "\nInorder of Constructed Binary Tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}
