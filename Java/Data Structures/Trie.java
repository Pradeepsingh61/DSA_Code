// Java Program to Implement Trie
// Data Structure

// Helper Class TrieNode
class TrieNode {
    TrieNode[] children;
    boolean isEndOfWord;

    public TrieNode() {
          // Assuming lowercase English letters
        children = new TrieNode[26]; 
        isEndOfWord = false;
    }
}

// Class Trie
public class Trie {
    private TrieNode root;

      // Constructor
    public Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    public void insert(String word) {
        TrieNode current = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (current.children[ch - 'a'] == null) {
                current.children[ch - 'a'] = new TrieNode();
            }
            current = current.children[ch - 'a'];
        }
        current.isEndOfWord = true;
    }

    // Search for a word in the Trie
    public boolean search(String word) {
        TrieNode current = root;
      
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
          
            if (current.children[ch - 'a'] == null) {
                  // Word not found
                return false; 
            }
          
            current = current.children[ch - 'a'];
        }
        return current != null && current.isEndOfWord;
    }

    // Check if a given prefix exists in the Trie
    public boolean startsWith(String prefix) {
        TrieNode current = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
          
            if (current.children[ch - 'a'] == null) {
                  // Prefix not found
                return false; 
            }
          
            current = current.children[ch - 'a'];
        }
        return true;
    }
}
