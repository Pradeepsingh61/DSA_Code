/**
 * Data Structure: Trie (Prefix Tree)
 * Description: Tree-like data structure for efficient storage and retrieval of strings
 *              Supports insert, search, delete, and prefix operations
 * Time Complexity: O(m) for all operations where m is the length of the word
 * Space Complexity: O(ALPHABET_SIZE * N * M) where N is number of words, M is average length
 * 
 * Features:
 * - Insert words into the trie
 * - Search for complete words
 * - Check if any word starts with a given prefix
 * - Delete words from the trie
 * - Get all words with a given prefix
 * - Count words and prefixes
 * 
 * Applications:
 * - Auto-complete/Auto-suggestion systems
 * - Spell checkers
 * - IP routing tables
 * - T9 predictive text
 * - Word games (Scrabble, Boggle)
 * 
 * @author Abhijit
 * @version 1.0
 * @since October 2025
 * Hacktoberfest 2025
 */

import java.util.*;

public class Trie {
    
    /**
     * TrieNode represents each node in the Trie
     * Contains children array and end-of-word marker
     */
    private static class TrieNode {
        private static final int ALPHABET_SIZE = 26; // for lowercase a-z
        private TrieNode[] children;
        private boolean isEndOfWord;
        private int wordCount; // Number of words ending at this node
        private int prefixCount; // Number of words passing through this node
        
        /**
         * Constructor for TrieNode
         */
        public TrieNode() {
            children = new TrieNode[ALPHABET_SIZE];
            isEndOfWord = false;
            wordCount = 0;
            prefixCount = 0;
        }
        
        /**
         * Check if this node has any children
         * @return true if node has children, false otherwise
         */
        public boolean hasChildren() {
            for (TrieNode child : children) {
                if (child != null) {
                    return true;
                }
            }
            return false;
        }
        
        /**
         * Get the child node for a specific character
         * @param ch character to find child for
         * @return TrieNode child or null if doesn't exist
         */
        public TrieNode getChild(char ch) {
            if (ch < 'a' || ch > 'z') {
                return null;
            }
            return children[ch - 'a'];
        }
        
        /**
         * Set the child node for a specific character
         * @param ch character to set child for
         * @param node TrieNode to set as child
         */
        public void setChild(char ch, TrieNode node) {
            if (ch >= 'a' && ch <= 'z') {
                children[ch - 'a'] = node;
            }
        }
    }
    
    private TrieNode root;
    private int totalWords;
    
    /**
     * Constructor - Initialize empty Trie
     */
    public Trie() {
        root = new TrieNode();
        totalWords = 0;
    }
    
    /**
     * Insert a word into the Trie
     * @param word string to insert (must be lowercase)
     * @throws IllegalArgumentException if word is null or contains invalid characters
     */
    public void insert(String word) {
        if (word == null || word.isEmpty()) {
            throw new IllegalArgumentException("Word cannot be null or empty");
        }
        
        // Validate that word contains only lowercase letters
        if (!word.matches("[a-z]+")) {
            throw new IllegalArgumentException("Word must contain only lowercase letters a-z");
        }
        
        TrieNode current = root;
        
        // Traverse/create path for each character
        for (char ch : word.toCharArray()) {
            TrieNode child = current.getChild(ch);
            if (child == null) {
                child = new TrieNode();
                current.setChild(ch, child);
            }
            current = child;
            current.prefixCount++; // Increment prefix count for this path
        }
        
        // Mark end of word if it's a new word
        if (!current.isEndOfWord) {
            current.isEndOfWord = true;
            totalWords++;
        }
        current.wordCount++;
    }
    
    /**
     * Search for a complete word in the Trie
     * @param word string to search for
     * @return true if word exists, false otherwise
     */
    public boolean search(String word) {
        if (word == null || word.isEmpty()) {
            return false;
        }
        
        TrieNode node = searchNode(word);
        return node != null && node.isEndOfWord;
    }
    
    /**
     * Check if any word in the Trie starts with the given prefix
     * @param prefix string prefix to check
     * @return true if prefix exists, false otherwise
     */
    public boolean startsWith(String prefix) {
        if (prefix == null || prefix.isEmpty()) {
            return true; // Empty prefix matches everything
        }
        
        return searchNode(prefix) != null;
    }
    
    /**
     * Helper method to find the node corresponding to a given string
     * @param str string to search for
     * @return TrieNode if path exists, null otherwise
     */
    private TrieNode searchNode(String str) {
        TrieNode current = root;
        
        for (char ch : str.toCharArray()) {
            current = current.getChild(ch);
            if (current == null) {
                return null; // Path doesn't exist
            }
        }
        
        return current;
    }
    
    /**
     * Delete a word from the Trie
     * @param word string to delete
     * @return true if word was deleted, false if word didn't exist
     */
    public boolean delete(String word) {
        if (word == null || word.isEmpty()) {
            return false;
        }
        
        return deleteHelper(root, word, 0);
    }
    
    /**
     * Recursive helper method for deletion
     * @param current current node in traversal
     * @param word word being deleted
     * @param index current character index
     * @return true if current node should be deleted
     */
    private boolean deleteHelper(TrieNode current, String word, int index) {
        if (index == word.length()) {
            // Reached end of word
            if (!current.isEndOfWord) {
                return false; // Word doesn't exist
            }
            
            current.isEndOfWord = false;
            current.wordCount--;
            totalWords--;
            
            // Delete node if it has no children and is not end of another word
            return !current.hasChildren();
        }
        
        char ch = word.charAt(index);
        TrieNode child = current.getChild(ch);
        
        if (child == null) {
            return false; // Word doesn't exist
        }
        
        boolean shouldDeleteChild = deleteHelper(child, word, index + 1);
        
        if (shouldDeleteChild) {
            current.setChild(ch, null);
            child.prefixCount--;
            
            // Delete current node if it's not end of word and has no children
            return !current.isEndOfWord && !current.hasChildren();
        }
        
        return false;
    }
    
    /**
     * Get all words in the Trie that start with given prefix
     * @param prefix string prefix to search for
     * @return List of all words with the prefix
     */
    public List<String> getWordsWithPrefix(String prefix) {
        List<String> result = new ArrayList<>();
        TrieNode prefixNode = searchNode(prefix);
        
        if (prefixNode != null) {
            collectWords(prefixNode, prefix, result);
        }
        
        return result;
    }
    
    /**
     * Recursive helper to collect all words from a given node
     * @param node starting node
     * @param currentWord word built so far
     * @param result list to add complete words to
     */
    private void collectWords(TrieNode node, String currentWord, List<String> result) {
        if (node.isEndOfWord) {
            result.add(currentWord);
        }
        
        for (char ch = 'a'; ch <= 'z'; ch++) {
            TrieNode child = node.getChild(ch);
            if (child != null) {
                collectWords(child, currentWord + ch, result);
            }
        }
    }
    
    /**
     * Get all words in the Trie
     * @return List of all words
     */
    public List<String> getAllWords() {
        return getWordsWithPrefix("");
    }
    
    /**
     * Count how many words start with given prefix
     * @param prefix string prefix to count
     * @return number of words with the prefix
     */
    public int countWordsWithPrefix(String prefix) {
        TrieNode node = searchNode(prefix);
        return node != null ? node.prefixCount : 0;
    }
    
    /**
     * Get the total number of words in the Trie
     * @return total word count
     */
    public int size() {
        return totalWords;
    }
    
    /**
     * Check if the Trie is empty
     * @return true if empty, false otherwise
     */
    public boolean isEmpty() {
        return totalWords == 0;
    }
    
    /**
     * Clear all words from the Trie
     */
    public void clear() {
        root = new TrieNode();
        totalWords = 0;
    }
    
    /**
     * Get the longest common prefix of all words in the Trie
     * @return longest common prefix string
     */
    public String getLongestCommonPrefix() {
        if (isEmpty()) {
            return "";
        }
        
        StringBuilder prefix = new StringBuilder();
        TrieNode current = root;
        
        while (current != null && !current.isEndOfWord && countChildren(current) == 1) {
            char ch = getOnlyChild(current);
            if (ch != '\0') {
                prefix.append(ch);
                current = current.getChild(ch);
            } else {
                break;
            }
        }
        
        return prefix.toString();
    }
    
    /**
     * Count number of children for a node
     * @param node TrieNode to count children for
     * @return number of children
     */
    private int countChildren(TrieNode node) {
        int count = 0;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (node.getChild(ch) != null) {
                count++;
            }
        }
        return count;
    }
    
    /**
     * Get the only child character if node has exactly one child
     * @param node TrieNode to get child from
     * @return character of only child, or '\0' if not exactly one child
     */
    private char getOnlyChild(TrieNode node) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (node.getChild(ch) != null) {
                return ch;
            }
        }
        return '\0';
    }
    
    /**
     * Demonstration and testing method
     */
    public static void demonstrateTrie() {
        System.out.println("=== Trie (Prefix Tree) Demonstration ===\n");
        
        Trie trie = new Trie();
        
        // Test 1: Basic insertions
        System.out.println("Test 1 - Inserting words:");
        String[] words = {"apple", "app", "application", "apply", "appreciate", "approach", "appropriate"};
        
        for (String word : words) {
            trie.insert(word);
            System.out.println("Inserted: " + word);
        }
        
        System.out.println("Total words in Trie: " + trie.size());
        System.out.println();
        
        // Test 2: Search operations
        System.out.println("Test 2 - Search operations:");
        String[] searchWords = {"app", "apple", "application", "appl", "orange"};
        
        for (String word : searchWords) {
            boolean found = trie.search(word);
            System.out.println("Search '" + word + "': " + (found ? "FOUND" : "NOT FOUND"));
        }
        System.out.println();
        
        // Test 3: Prefix operations
        System.out.println("Test 3 - Prefix operations:");
        String[] prefixes = {"app", "appl", "approa", "xyz"};
        
        for (String prefix : prefixes) {
            boolean hasPrefix = trie.startsWith(prefix);
            int count = trie.countWordsWithPrefix(prefix);
            System.out.println("Prefix '" + prefix + "': " + (hasPrefix ? "EXISTS" : "DOESN'T EXIST") + 
                             " (Words with this prefix: " + count + ")");
        }
        System.out.println();
        
        // Test 4: Get words with prefix
        System.out.println("Test 4 - Words with prefix 'app':");
        List<String> wordsWithApp = trie.getWordsWithPrefix("app");
        for (String word : wordsWithApp) {
            System.out.println("  " + word);
        }
        System.out.println();
        
        // Test 5: Longest common prefix
        System.out.println("Test 5 - Longest common prefix: '" + trie.getLongestCommonPrefix() + "'");
        System.out.println();
        
        // Test 6: Deletion
        System.out.println("Test 6 - Deletion:");
        System.out.println("Before deletion - Total words: " + trie.size());
        
        boolean deleted = trie.delete("app");
        System.out.println("Deleted 'app': " + deleted);
        System.out.println("After deletion - Total words: " + trie.size());
        System.out.println("Search 'app': " + (trie.search("app") ? "FOUND" : "NOT FOUND"));
        System.out.println("Search 'apple': " + (trie.search("apple") ? "FOUND" : "NOT FOUND"));
        System.out.println();
        
        // Test 7: All words
        System.out.println("Test 7 - All remaining words:");
        List<String> allWords = trie.getAllWords();
        for (String word : allWords) {
            System.out.println("  " + word);
        }
    }
    
    /**
     * Main method for testing and demonstration
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Trie (Prefix Tree) Data Structure in Java");
        System.out.println("========================================");
        System.out.println("1. Interactive mode");
        System.out.println("2. Demonstration mode");
        System.out.print("Choose mode (1 or 2): ");
        
        int choice = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        if (choice == 1) {
            // Interactive mode
            Trie trie = new Trie();
            
            while (true) {
                System.out.println("\n=== Trie Operations ===");
                System.out.println("1. Insert word");
                System.out.println("2. Search word");
                System.out.println("3. Check prefix");
                System.out.println("4. Delete word");
                System.out.println("5. Show words with prefix");
                System.out.println("6. Show all words");
                System.out.println("7. Show statistics");
                System.out.println("8. Exit");
                System.out.print("Choose operation: ");
                
                int operation = scanner.nextInt();
                scanner.nextLine(); // consume newline
                
                switch (operation) {
                    case 1:
                        System.out.print("Enter word to insert: ");
                        String insertWord = scanner.nextLine().toLowerCase();
                        try {
                            trie.insert(insertWord);
                            System.out.println("Word '" + insertWord + "' inserted successfully!");
                        } catch (IllegalArgumentException e) {
                            System.out.println("Error: " + e.getMessage());
                        }
                        break;
                        
                    case 2:
                        System.out.print("Enter word to search: ");
                        String searchWord = scanner.nextLine().toLowerCase();
                        boolean found = trie.search(searchWord);
                        System.out.println("Word '" + searchWord + "': " + (found ? "FOUND" : "NOT FOUND"));
                        break;
                        
                    case 3:
                        System.out.print("Enter prefix to check: ");
                        String prefix = scanner.nextLine().toLowerCase();
                        boolean hasPrefix = trie.startsWith(prefix);
                        int count = trie.countWordsWithPrefix(prefix);
                        System.out.println("Prefix '" + prefix + "': " + (hasPrefix ? "EXISTS" : "DOESN'T EXIST"));
                        System.out.println("Words with this prefix: " + count);
                        break;
                        
                    case 4:
                        System.out.print("Enter word to delete: ");
                        String deleteWord = scanner.nextLine().toLowerCase();
                        boolean deleted = trie.delete(deleteWord);
                        System.out.println("Word '" + deleteWord + "': " + (deleted ? "DELETED" : "NOT FOUND"));
                        break;
                        
                    case 5:
                        System.out.print("Enter prefix: ");
                        String showPrefix = scanner.nextLine().toLowerCase();
                        List<String> wordsWithPrefix = trie.getWordsWithPrefix(showPrefix);
                        System.out.println("Words with prefix '" + showPrefix + "':");
                        for (String word : wordsWithPrefix) {
                            System.out.println("  " + word);
                        }
                        break;
                        
                    case 6:
                        List<String> allWords = trie.getAllWords();
                        System.out.println("All words in Trie:");
                        for (String word : allWords) {
                            System.out.println("  " + word);
                        }
                        break;
                        
                    case 7:
                        System.out.println("=== Trie Statistics ===");
                        System.out.println("Total words: " + trie.size());
                        System.out.println("Is empty: " + trie.isEmpty());
                        System.out.println("Longest common prefix: '" + trie.getLongestCommonPrefix() + "'");
                        break;
                        
                    case 8:
                        System.out.println("Thank you for using Trie!");
                        scanner.close();
                        return;
                        
                    default:
                        System.out.println("Invalid choice! Please try again.");
                }
            }
            
        } else if (choice == 2) {
            // Demonstration mode
            demonstrateTrie();
            
        } else {
            System.out.println("Invalid choice!");
        }
        
        scanner.close();
        
        System.out.println("\n=== Algorithm Information ===");
        System.out.println("Time Complexity:");
        System.out.println("  - Insert/Search/Delete: O(m) where m is word length");
        System.out.println("  - Prefix operations: O(p) where p is prefix length");
        System.out.println("Space Complexity: O(ALPHABET_SIZE * N * M)");
        System.out.println("Applications: Auto-complete, spell-check, IP routing, T9");
    }
}