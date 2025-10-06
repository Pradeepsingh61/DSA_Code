"""
Trie (Prefix Tree) Algorithm

📌 Description:
A Trie is a tree-like data structure used to efficiently store and retrieve strings, especially useful for prefix-based queries. Each node represents a character, and paths from root to leaf form words. It supports fast insertions, lookups, and prefix checks.

🔍 Use Cases:
- Autocomplete systems
- Spell checkers
- Dictionary word lookups
- IP routing and longest prefix match

📈 Time Complexity:
- Insert: O(L) — where L is the length of the word
- Search: O(L)
- startsWith: O(P) — where P is the length of the prefix

📦 Space Complexity:
- O(N * A) — N = number of nodes, A = alphabet size
"""

class TrieNode:
    def __init__(self):
        # Each node holds a map of children and a flag for end-of-word
        self.children = {}
        self.is_end_of_word = False


class Trie:
    def __init__(self):
        # Root node doesn't hold any character
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the Trie.
        """
        if not isinstance(word, str):
            raise TypeError("Input word must be a string.")

        node = self.root
        for char in word:
            # Create a new node if the character is not present
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        # Mark the end of the word
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Returns True if the word is in the Trie.
        """
        if not isinstance(word, str):
            raise TypeError("Input word must be a string.")

        node = self.root
        for char in word:
            # If character not found, word doesn't exist
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        """
        Returns True if there is any word in the Trie that starts with the given prefix.
        """
        if not isinstance(prefix, str):
            raise TypeError("Input prefix must be a string.")

        node = self.root
        for char in prefix:
            # If character not found, prefix doesn't exist
            if char not in node.children:
                return False
            node = node.children[char]
        return True


# 🧪 Test Cases
if __name__ == "__main__":
    trie = Trie()

    # ✅ Insert words
    trie.insert("apple")
    trie.insert("app")
    trie.insert("bat")
    trie.insert("batch")

    # ✅ Search for full words
    print("Search 'apple':", "✅ Found" if trie.search("apple") else "❌ Not Found")
    print("Search 'app':", "✅ Found" if trie.search("app") else "❌ Not Found")
    print("Search 'bat':", "✅ Found" if trie.search("bat") else "❌ Not Found")
    print("Search 'bath':", "❌ Not Found" if not trie.search("bath") else "✅ Found")

    # ✅ Check prefixes
    print("StartsWith 'ap':", "✅ Yes" if trie.startsWith("ap") else "❌ No")
    print("StartsWith 'ba':", "✅ Yes" if trie.startsWith("ba") else "❌ No")
    print("StartsWith 'cat':", "❌ No" if not trie.startsWith("cat") else "✅ Yes")

    # ✅ Edge case: empty string
    print("Search '':", "❌ Not Found" if not trie.search("") else "✅ Found")
    print("StartsWith '':", "✅ Yes" if trie.startsWith("") else "❌ No")

    # ✅ Error handling: non-string input
    try:
        trie.insert(123)
    except TypeError:
        print("Insert non-string: ✅ Caught TypeError")
    else:
        print("Insert non-string: ❌ Failed")

    try:
        trie.search(None)
    except TypeError:
        print("Search non-string: ✅ Caught TypeError")
    else:
        print("Search non-string: ❌ Failed")
