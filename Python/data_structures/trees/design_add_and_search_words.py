"""
Data Structure: Word Dictionary (Trie with Wildcard Search)

Description:
    This data structure allows adding words and searching for them efficiently,
    including support for the wildcard character '.' which matches any letter.

Use Case:
    Useful in applications like autocomplete, spell-checkers, and word games 
    where prefix and pattern-based searches are required.

Time Complexity:
    - addWord(word): O(L), where L = length of the word
    - search(word): O(L * 26) in the worst case (when '.' is used frequently)
      Average case is close to O(L).
    
Space Complexity:
    O(N * L), where N = number of words and L = average word length.
"""

class TrieNode:
    """Represents a single node in the Trie."""
    def __init__(self):
        self.children = {}
        self.is_word = False


class WordDictionary:
    """
    Implements a Trie-based word dictionary with wildcard search support.

    Methods:
        addWord(word): Insert a word into the dictionary.
        search(word): Search for a word, supporting '.' as a wildcard.
    """
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        """
        Insert a word into the trie.
        
        Args:
            word (str): Word to be added.
        """
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_word = True

    def search(self, word: str) -> bool:
        """
        Search for a word in the trie (supports '.' as a wildcard).
        
        Args:
            word (str): Word or pattern to search.
            
        Returns:
            bool: True if the word exists in the trie, otherwise False.
        """
        return self._dfs(self.root, word, 0)

    def _dfs(self, node: TrieNode, word: str, index: int) -> bool:
        """Helper DFS method to handle wildcard searches."""
        if index == len(word):
            return node.is_word

        ch = word[index]

        # Wildcard case
        if ch == ".":
            for child in node.children.values():
                if self._dfs(child, word, index + 1):
                    return True
            return False

        # Exact match case
        if ch in node.children:
            return self._dfs(node.children[ch], word, index + 1)

        return False


def main():
    """Test the WordDictionary implementation with examples."""
    wd = WordDictionary()
    
    # Test case 1: Adding and searching words
    wd.addWord("bad")
    wd.addWord("dad")
    wd.addWord("mad")
    
    print(wd.search("pad"))   # False (not in dictionary)
    print(wd.search("bad"))   # True
    print(wd.search(".ad"))   # True (wildcard match)
    print(wd.search("b.."))   # True (wildcard match for "bad")


if __name__ == "__main__":
    main()
