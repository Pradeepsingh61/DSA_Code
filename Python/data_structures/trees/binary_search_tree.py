"""
Binary Search Tree Implementation
Time Complexity:
    - Insert: O(log n) average, O(n) worst case
    - Search: O(log n) average, O(n) worst case
    - Delete: O(log n) average, O(n) worst case
Space Complexity: O(n)
Author: Karanjot Singh
Date: October 2025
Hacktoberfest 2025
"""

class TreeNode:
    """Node class for Binary Search Tree"""
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class BinarySearchTree:
    """Binary Search Tree implementation with common operations"""

    def __init__(self):
        self.root = None

    def insert(self, value):
        """
        Insert a value into the BST

        Args:
            value: Value to insert
        """
        if self.root is None:
            self.root = TreeNode(value)
        else:
            self._insert_recursive(self.root, value)

    def _insert_recursive(self, node, value):
        """Helper method for recursive insertion"""
        if value < node.value:
            if node.left is None:
                node.left = TreeNode(value)
            else:
                self._insert_recursive(node.left, value)
        else:
            if node.right is None:
                node.right = TreeNode(value)
            else:
                self._insert_recursive(node.right, value)

    def search(self, value):
        """
        Search for a value in the BST

        Args:
            value: Value to search for

        Returns:
            True if value exists, False otherwise
        """
        return self._search_recursive(self.root, value)

    def _search_recursive(self, node, value):
        """Helper method for recursive search"""
        if node is None:
            return False

        if value == node.value:
            return True
        elif value < node.value:
            return self._search_recursive(node.left, value)
        else:
            return self._search_recursive(node.right, value)

    def inorder_traversal(self):
        """
        Perform inorder traversal (Left -> Root -> Right)
        Returns sorted order for BST

        Returns:
            List of values in inorder
        """
        result = []
        self._inorder_recursive(self.root, result)
        return result

    def _inorder_recursive(self, node, result):
        """Helper method for inorder traversal"""
        if node:
            self._inorder_recursive(node.left, result)
            result.append(node.value)
            self._inorder_recursive(node.right, result)

    def preorder_traversal(self):
        """
        Perform preorder traversal (Root -> Left -> Right)

        Returns:
            List of values in preorder
        """
        result = []
        self._preorder_recursive(self.root, result)
        return result

    def _preorder_recursive(self, node, result):
        """Helper method for preorder traversal"""
        if node:
            result.append(node.value)
            self._preorder_recursive(node.left, result)
            self._preorder_recursive(node.right, result)

    def postorder_traversal(self):
        """
        Perform postorder traversal (Left -> Right -> Root)

        Returns:
            List of values in postorder
        """
        result = []
        self._postorder_recursive(self.root, result)
        return result

    def _postorder_recursive(self, node, result):
        """Helper method for postorder traversal"""
        if node:
            self._postorder_recursive(node.left, result)
            self._postorder_recursive(node.right, result)
            result.append(node.value)

    def find_min(self):
        """
        Find minimum value in BST

        Returns:
            Minimum value or None if tree is empty
        """
        if self.root is None:
            return None

        current = self.root
        while current.left:
            current = current.left
        return current.value

    def find_max(self):
        """
        Find maximum value in BST

        Returns:
            Maximum value or None if tree is empty
        """
        if self.root is None:
            return None

        current = self.root
        while current.right:
            current = current.right
        return current.value

    def height(self):
        """
        Calculate height of the tree

        Returns:
            Height of tree (0 for single node, -1 for empty tree)
        """
        return self._height_recursive(self.root)

    def _height_recursive(self, node):
        """Helper method to calculate height"""
        if node is None:
            return -1

        left_height = self._height_recursive(node.left)
        right_height = self._height_recursive(node.right)

        return 1 + max(left_height, right_height)


# Test cases
if __name__ == "__main__":
    print("=== Binary Search Tree Implementation ===\n")

    # Create BST and insert values
    bst = BinarySearchTree()
    values = [50, 30, 70, 20, 40, 60, 80]

    print(f"Inserting values: {values}")
    for val in values:
        bst.insert(val)

    # Test traversals
    print(f"\nInorder traversal (sorted): {bst.inorder_traversal()}")
    print(f"Preorder traversal: {bst.preorder_traversal()}")
    print(f"Postorder traversal: {bst.postorder_traversal()}")

    # Test search
    print("\n--- Search Operations ---")
    search_values = [40, 25, 80, 100]
    for val in search_values:
        found = bst.search(val)
        print(f"Search for {val}: {'Found' if found else 'Not found'}")

    # Test min/max
    print("\n--- Min/Max Operations ---")
    print(f"Minimum value: {bst.find_min()}")
    print(f"Maximum value: {bst.find_max()}")

    # Test height
    print(f"\nTree height: {bst.height()}")

    # Test with another tree
    print("\n--- Another BST Example ---")
    bst2 = BinarySearchTree()
    values2 = [15, 10, 20, 8, 12, 17, 25]
    print(f"Inserting values: {values2}")
    for val in values2:
        bst2.insert(val)

    print(f"Inorder traversal: {bst2.inorder_traversal()}")
    print(f"Tree height: {bst2.height()}")

    print("\n✅ All test cases completed!")
