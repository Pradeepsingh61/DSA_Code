'''
Algorithm Name
Trie, Depth-First Serch

Programming Language
Python

Category
Graph Algorithms

Difficulty Level
Medium (Intermediate)

Algorithm Description
This algorithm implements a Word Dictionary using a Trie (Prefix Tree) data structure. The addWord method inserts words into the trie by creating nodes for each character and marking the end of a valid word. The search method supports both exact word lookup and pattern matching with the special character ".", which can represent any single letter. It uses a depth-first search (DFS) to explore all possible paths when encountering ".".

This approach is useful because the trie provides efficient word storage and retrieval, especially when handling a large set of words or prefix-based searches. The support for "." makes it powerful for solving problems like wildcard searches, autocomplete systems, and word games, where flexible matching is required. Overall, it ensures fast lookups and scalable word management compared to brute-force string comparisons.

'''
class TrieNode:
    def __init__(self):
        self.children = {}  # Maps character to TrieNode
        self.is_end_of_word = False

class WordDictionary:
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        def dfs(node, i):
            if i == len(word):
                return node.is_end_of_word

            if word[i] == '.':
                for child in node.children.values():
                    if dfs(child, i + 1):
                        return True
                return False
            else:
                if word[i] not in node.children:
                    return False
                return dfs(node.children[word[i]], i + 1)

        return dfs(self.root, 0)

# Example Usage
wd = WordDictionary()
wd.addWord("bad")
wd.addWord("dad")
wd.addWord("mad")

print(wd.search("pad"))  # False
print(wd.search("bad"))  # True
print(wd.search(".ad"))  # True
print(wd.search("b.."))  # True


'''
Trie Structure

a. Each node contains a children dictionary mapping characters → nodes.

b. is_end_of_word marks the completion of a valid word.

addWord Method

a. Insert characters sequentially.

b. Create nodes if they don’t exist.

c. Mark the last node as is_end_of_word = True.

search Method

a. Supports exact match and wildcard match (.).

b. Uses DFS to explore all possible children when encountering '.'.

Advantages

a. Efficient storage and retrieval for large dictionaries.

b. Fast prefix searches, autocomplete, and wildcard matching.

c. Avoids brute-force string comparisons.
'''

'''
Time Complexity:

addWord: O(L), where L = length of the word

search: O(26^L) worst-case (all letters are wildcards), average much faster

Space Complexity: O(N × L), N = number of words, L = average word length
'''

'''
Output

False
True
True
True
'''