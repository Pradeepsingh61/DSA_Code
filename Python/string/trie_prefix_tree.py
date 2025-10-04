# Section: String Algorithms

"""
Algorithm: Trie (Prefix Tree)
Purpose: Efficiently stores and searches strings by prefix. Commonly used in autocomplete, spell-check, and dictionary apps.

Time Complexity:
- Insertion: O(L), where L is the length of the word
- Search: O(L)
- Prefix Search: O(L)

Space Complexity: O(N * A), where N is the number of words and A is the alphabet size
"""

class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        if not isinstance(word, str):
            raise ValueError("Only strings can be inserted into the Trie.")
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word):
        node = self._find_node(word)
        return node is not None and node.is_end_of_word

    def starts_with(self, prefix):
        return self._find_node(prefix) is not None

    def _find_node(self, prefix):
        node = self.root
        for char in prefix:
            if char not in node.children:
                return None
            node = node.children[char]
        return node


# 🧪 Test Cases
if __name__ == "__main__":
    trie = Trie()
    trie.insert("apple")
    trie.insert("app")
    trie.insert("bat")
    trie.insert("ball")

    assert trie.search("apple") == True, "apple should be found"
    assert trie.search("app") == True, "app should be found"
    assert trie.search("appl") == False, "appl should not be found"
    assert trie.starts_with("ap") == True, "Prefix 'ap' should exist"
    assert trie.starts_with("ba") == True, "Prefix 'ba' should exist"
    assert trie.starts_with("cat") == False, "Prefix 'cat' should not exist"

    print("All Trie test cases passed.")
