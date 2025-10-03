# Given the root of a binary tree, return all root to leaf paths.
 
# Input
# Since this is a functional problem, you don't have to input anything. You just need to complete the rootToLeafPaths().

# You are given root node of the binary tree as function parameter.



'''
class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
'''
def rootToLeafPaths(root):
    result = []

    def dfs(node, path):
        if not node:
            return

        path.append(node.data)

        if not node.left and not node.right:
            result.append(path.copy())
        else:
            dfs(node.left, path)
            dfs(node.right, path)

        path.pop()

    dfs(root, [])
    return result





Input:
11
50 25 -1 -1 12 37 -1 -1 30 -1 -1
Output:
[[50, 25], [50, 12, 37], [50, 12, 30]]


