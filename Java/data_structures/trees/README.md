# Tree Data Structures in Java

This directory contains implementations of various tree data structures in Java, showcasing different tree-based algorithms and their practical applications.

## 📁 Available Implementations

### 1. Trie (Prefix Tree) - `Trie.java`
**Description**: A tree-like data structure for efficient storage and retrieval of strings, commonly used for prefix-based operations.

**Key Features**:
- Insert, search, and delete words
- Prefix checking and counting
- Auto-complete functionality
- Memory-efficient string storage
- Comprehensive statistics

**Time Complexity**:
- Insert: O(m) where m is word length
- Search: O(m) where m is word length  
- Delete: O(m) where m is word length
- Prefix operations: O(p) where p is prefix length

**Space Complexity**: O(ALPHABET_SIZE × N × M) where N is number of words, M is average length

**Applications**:
- Auto-complete/Auto-suggestion systems
- Spell checkers and word validators
- IP routing tables (Longest Prefix Matching)
- T9 predictive text input
- Word games (Scrabble, Boggle)
- Search engines and indexing

**Code Highlights**:
```java
Trie trie = new Trie();
trie.insert("hello");
trie.insert("help");
trie.insert("hero");

// Search operations
boolean exists = trie.search("hello");           // true
boolean hasPrefix = trie.startsWith("hel");      // true

// Advanced operations
List<String> words = trie.getWordsWithPrefix("he"); // [hello, help, hero]
int count = trie.countWordsWithPrefix("hel");       // 2
String commonPrefix = trie.getLongestCommonPrefix(); // "he"
```

## 🚀 How to Run

### Compile and Run Trie
```bash
# Compile
javac Trie.java

# Run
java Trie
```

### Program Modes
1. **Interactive Mode**: Enter your own words and perform operations
2. **Demonstration Mode**: See predefined examples and test cases

## 📊 Performance Comparison

| Operation | Trie | HashMap | Array |
|-----------|------|---------|-------|
| Insert | O(m) | O(m) | O(n) |
| Search | O(m) | O(m) | O(n×m) |
| Prefix Search | O(p) | O(n×p) | O(n×m×p) |
| Memory | High | Medium | Low |
| Cache Locality | Good | Poor | Excellent |

## 🎯 When to Use Trie

**✅ Use Trie When**:
- You need frequent prefix-based operations
- Implementing auto-complete features
- Working with large dictionaries
- Need memory-efficient string storage
- Implementing spell checkers
- Building search suggestions

**❌ Don't Use Trie When**:
- Only doing exact string matches (use HashMap)
- Memory is extremely limited
- Working with very long strings
- Need range queries on strings

## 🔧 Customization Options

The Trie implementation can be easily extended:

1. **Different Alphabets**: Modify `ALPHABET_SIZE` and character mapping
2. **Case Sensitivity**: Remove toLowerCase() calls
3. **Unicode Support**: Use HashMap<Character, TrieNode> instead of array
4. **Weighted Trie**: Add frequency counts for auto-complete ranking
5. **Compressed Trie**: Implement path compression for space optimization

## 📚 Educational Value

This implementation demonstrates:
- **Tree Traversal**: Depth-first search patterns
- **Recursive Algorithms**: Clean recursive deletion and traversal
- **Memory Management**: Efficient node creation and cleanup
- **String Processing**: Character-by-character manipulation
- **Data Structure Design**: Balancing time vs space complexity

## 🤝 Contributing

Feel free to contribute additional tree implementations:
- Binary Search Tree (BST)
- AVL Tree (Self-balancing BST)
- Red-Black Tree
- B-Tree / B+ Tree
- Segment Tree
- Fenwick Tree (Binary Indexed Tree)
- Suffix Tree
- Radix Tree (Compressed Trie)

## 📖 References

- [Trie Data Structure - GeeksforGeeks](https://www.geeksforgeeks.org/trie-insert-and-search/)
- [Introduction to Algorithms - CLRS](https://mitpress.mit.edu/books/introduction-algorithms)
- [Data Structures and Algorithms in Java - Goodrich](https://www.wiley.com/en-us/Data+Structures+and+Algorithms+in+Java%2C+6th+Edition-p-9781118771334)

---

**Author**: Abhijit  
**Hacktoberfest 2025**: ✅  
**Language**: Java  
**Category**: Data Structures - Trees