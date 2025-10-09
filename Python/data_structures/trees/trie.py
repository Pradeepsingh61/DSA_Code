"""Comprehensive Trie (Prefix Tree) Implementation

A Trie is a tree-like data structure that stores a dynamic set of strings,
where keys are usually strings. It's particularly useful for:
- Autocomplete functionality
- Spell checking
- IP routing (longest prefix matching)
- Dictionary implementations

Time Complexity:
- Insert: O(m) where m is the length of the word
- Search: O(m) where m is the length of the word
- StartsWith: O(m) where m is the length of the prefix
- Delete: O(m) where m is the length of the word

Space Complexity: O(ALPHABET_SIZE * N * M) where N is number of words and M is average length
"""

class TrieNode:
    """Node class for Trie structure"""
    
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.word_count = 0  # Count of words ending at this node
        
class Trie:
    """Complete Trie implementation with all common operations"""
    
    def __init__(self):
        """Initialize the trie with an empty root node"""
        self.root = TrieNode()
        self.total_words = 0
        
    def insert(self, word: str) -> None:
        """Insert a word into the trie
        
        Args:
            word: String to insert
            
        Time Complexity: O(m) where m is length of word
        """
        if not word:
            return
            
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
            
        if not node.is_end_of_word:
            self.total_words += 1
        node.is_end_of_word = True
        node.word_count += 1
        
    def search(self, word: str) -> bool:
        """Search for a complete word in the trie
        
        Args:
            word: String to search for
            
        Returns:
            True if word exists in trie, False otherwise
            
        Time Complexity: O(m) where m is length of word
        """
        node = self._find_node(word)
        return node is not None and node.is_end_of_word
        
    def starts_with(self, prefix: str) -> bool:
        """Check if any word in the trie starts with given prefix
        
        Args:
            prefix: Prefix string to check
            
        Returns:
            True if any word starts with prefix, False otherwise
            
        Time Complexity: O(m) where m is length of prefix
        """
        return self._find_node(prefix) is not None
        
    def delete(self, word: str) -> bool:
        """Delete a word from the trie
        
        Args:
            word: String to delete
            
        Returns:
            True if word was deleted, False if word didn't exist
            
        Time Complexity: O(m) where m is length of word
        """
        def _delete_helper(node: TrieNode, word: str, index: int) -> bool:
            if index == len(word):
                if not node.is_end_of_word:
                    return False
                    
                node.word_count -= 1
                if node.word_count == 0:
                    node.is_end_of_word = False
                    self.total_words -= 1
                    
                return len(node.children) == 0
                
            char = word[index]
            if char not in node.children:
                return False
                
            child = node.children[char]
            should_delete_child = _delete_helper(child, word, index + 1)
            
            if should_delete_child:
                del node.children[char]
                return len(node.children) == 0 and not node.is_end_of_word
                
            return False
            
        if not word:
            return False
        return _delete_helper(self.root, word, 0)
        
    def get_all_words_with_prefix(self, prefix: str) -> list:
        """Get all words in the trie that start with the given prefix
        
        Args:
            prefix: Prefix string
            
        Returns:
            List of all words with given prefix
            
        Time Complexity: O(p + n) where p is prefix length and n is number of nodes under prefix
        """
        node = self._find_node(prefix)
        if node is None:
            return []
            
        words = []
        self._collect_all_words(node, prefix, words)
        return words
        
    def autocomplete(self, prefix: str, limit: int = 10) -> list:
        """Get autocomplete suggestions for a given prefix
        
        Args:
            prefix: Prefix string
            limit: Maximum number of suggestions to return
            
        Returns:
            List of up to 'limit' words that start with prefix
        """
        words = self.get_all_words_with_prefix(prefix)
        return words[:limit]
        
    def count_words_with_prefix(self, prefix: str) -> int:
        """Count how many words start with the given prefix
        
        Args:
            prefix: Prefix string
            
        Returns:
            Number of words with given prefix
        """
        node = self._find_node(prefix)
        if node is None:
            return 0
            
        count = [0]
        self._count_words(node, count)
        return count[0]
        
    def longest_common_prefix(self) -> str:
        """Find the longest common prefix of all words in the trie
        
        Returns:
            Longest common prefix string
        """
        if not self.root.children:
            return ""
            
        prefix = []
        node = self.root
        
        while len(node.children) == 1 and not node.is_end_of_word:
            char = next(iter(node.children))
            prefix.append(char)
            node = node.children[char]
            
        return ''.join(prefix)
        
    def get_all_words(self) -> list:
        """Get all words stored in the trie
        
        Returns:
            List of all words in the trie
        """
        words = []
        self._collect_all_words(self.root, "", words)
        return words
        
    def is_empty(self) -> bool:
        """Check if trie is empty
        
        Returns:
            True if trie has no words, False otherwise
        """
        return self.total_words == 0
        
    def size(self) -> int:
        """Get the number of words in the trie
        
        Returns:
            Number of words stored
        """
        return self.total_words
        
    def clear(self) -> None:
        """Remove all words from the trie"""
        self.root = TrieNode()
        self.total_words = 0
        
    # Helper methods
    
    def _find_node(self, word: str) -> TrieNode:
        """Find the node corresponding to the last character of word
        
        Args:
            word: String to find
            
        Returns:
            TrieNode if found, None otherwise
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return None
            node = node.children[char]
        return node
        
    def _collect_all_words(self, node: TrieNode, prefix: str, words: list) -> None:
        """Recursively collect all words from given node
        
        Args:
            node: Current node
            prefix: Current prefix
            words: List to collect words into
        """
        if node.is_end_of_word:
            words.append(prefix)
            
        for char, child in node.children.items():
            self._collect_all_words(child, prefix + char, words)
            
    def _count_words(self, node: TrieNode, count: list) -> None:
        """Recursively count words from given node
        
        Args:
            node: Current node
            count: List containing single count value
        """
        if node.is_end_of_word:
            count[0] += 1
            
        for child in node.children.values():
            self._count_words(child, count)


# Example usage and testing
if __name__ == "__main__":
    # Create a new trie
    trie = Trie()
    
    # Insert words
    words = ["apple", "app", "application", "apply", "banana", "band", "bandana"]
    print("Inserting words:", words)
    for word in words:
        trie.insert(word)
    
    print(f"\nTotal words in trie: {trie.size()}")
    
    # Search for words
    print("\n--- Search Operations ---")
    print(f"Search 'apple': {trie.search('apple')}")  # True
    print(f"Search 'app': {trie.search('app')}")      # True
    print(f"Search 'appl': {trie.search('appl')}")    # False
    
    # Check prefixes
    print("\n--- Prefix Operations ---")
    print(f"Starts with 'app': {trie.starts_with('app')}")    # True
    print(f"Starts with 'ban': {trie.starts_with('ban')}")    # True
    print(f"Starts with 'cat': {trie.starts_with('cat')}")    # False
    
    # Get all words with prefix
    print("\n--- Autocomplete ---")
    print(f"Words with prefix 'app': {trie.get_all_words_with_prefix('app')}")
    print(f"Words with prefix 'ban': {trie.get_all_words_with_prefix('ban')}")
    
    # Autocomplete suggestions
    print(f"\nAutocomplete for 'app' (limit 3): {trie.autocomplete('app', 3)}")
    
    # Count words with prefix
    print("\n--- Count Operations ---")
    print(f"Count words with prefix 'app': {trie.count_words_with_prefix('app')}")
    print(f"Count words with prefix 'ban': {trie.count_words_with_prefix('ban')}")
    
    # Get all words
    print(f"\nAll words in trie: {trie.get_all_words()}")
    
    # Delete operations
    print("\n--- Delete Operations ---")
    print(f"Delete 'app': {trie.delete('app')}")
    print(f"Search 'app' after deletion: {trie.search('app')}")
    print(f"Search 'apple' after deleting 'app': {trie.search('apple')}")
    print(f"Total words after deletion: {trie.size()}")
    
    # Longest common prefix
    trie2 = Trie()
    trie2.insert("flower")
    trie2.insert("flow")
    trie2.insert("flight")
    print(f"\nLongest common prefix: '{trie2.longest_common_prefix()}'")
