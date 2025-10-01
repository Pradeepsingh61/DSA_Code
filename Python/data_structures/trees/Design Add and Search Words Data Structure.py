class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_word = False
        
class WordDictionary:
    def __init__(self):
        self.root = TrieNode()      

    def addWord(self, word: str) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_word = True
        
    def search(self, word: str) -> bool:
        return self._dfs(self.root, word, 0)
    
    def _dfs(self, node: TrieNode, word: str, index: int) -> bool:
        
        if index == len(word):
            return node.is_word
        
        ch = word[index]
        
        
        if ch == ".":
            for child in node.children.values():
                if self._dfs(child, word, index + 1):
                    return True
            return False
        
        
        if ch in node.children:
            return self._dfs(node.children[ch], word, index + 1)
        
        return False
