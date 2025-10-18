/*
 * Aho-Corasick Algorithm for Pattern Searching
 * 
 * This algorithm efficiently searches for multiple patterns in a text string simultaneously.
 * It's especially useful when you need to find all occurrences of a large set of patterns
 * in a text. The time complexity is O(n + m + z) where:
 * - n is the length of the text
 * - m is the total length of all patterns
 * - z is the number of pattern occurrences
 * 
 * The key components of the algorithm are:
 * 1. A trie (prefix tree) containing all patterns
 * 2. Failure links (similar to KMP algorithm's prefix function)
 * 3. Output links to track matches
 * 
 * Author: Abhiram
 * Date: October 2, 2025
 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class AhoCorasick {
private:
    struct Node {
        // Children nodes for trie structure
        unordered_map<char, int> children;
        
        // Failure link (where to go if current character doesn't match)
        int failureLink;
        
        // Dictionary link (points to the nearest node that is the end of a pattern)
        int dictionaryLink;
        
        // Pattern indices that end at this node
        vector<int> patternIndices;
        
        // Whether this node represents the end of a pattern
        bool isEnd;
        
        Node() : failureLink(0), dictionaryLink(-1), isEnd(false) {}
    };
    
    vector<Node> trie;  // The trie structure
    int states;         // Number of states/nodes in the trie
    vector<string> patterns; // Store the patterns for output
    
    // Build the trie (prefix tree) from patterns
    void buildTrie(const vector<string>& patterns) {
        // Initialize the root node
        trie.push_back(Node());
        states = 1;
        
        // Store patterns for later reference
        this->patterns = patterns;
        
        // Insert each pattern into the trie
        for (int i = 0; i < patterns.size(); i++) {
            insertPattern(patterns[i], i);
        }
    }
    
    // Insert a pattern into the trie
    void insertPattern(const string& pattern, int patternIndex) {
        int currentState = 0;  // Start from the root
        
        // Follow/create a path for each character of the pattern
        for (char ch : pattern) {
            // If there is no transition for this character, create one
            if (trie[currentState].children.find(ch) == trie[currentState].children.end()) {
                trie.push_back(Node());
                trie[currentState].children[ch] = states++;
            }
            
            // Move to the next state
            currentState = trie[currentState].children[ch];
        }
        
        // Mark the end of the pattern
        trie[currentState].isEnd = true;
        trie[currentState].patternIndices.push_back(patternIndex);
    }
    
    // Build the failure and dictionary links
    void buildLinks() {
        queue<int> q;
        
        // Initialize failure links for depth 1 nodes
        for (auto& transition : trie[0].children) {
            int nextState = transition.second;
            trie[nextState].failureLink = 0;  // Root is the failure for depth 1
            q.push(nextState);
        }
        
        // BFS to build failure links for the rest of the trie
        while (!q.empty()) {
            int currentState = q.front();
            q.pop();
            
            // Process all transitions from the current state
            for (auto& transition : trie[currentState].children) {
                char ch = transition.first;
                int nextState = transition.second;
                
                // Enqueue the next state
                q.push(nextState);
                
                // Find the failure state
                int failureState = trie[currentState].failureLink;
                
                // Follow failure links until we find a state with a valid transition
                while (failureState != 0 && trie[failureState].children.find(ch) == trie[failureState].children.end()) {
                    failureState = trie[failureState].failureLink;
                }
                
                // If there's a valid transition, update the failure link
                if (trie[failureState].children.find(ch) != trie[failureState].children.end()) {
                    failureState = trie[failureState].children[ch];
                }
                
                trie[nextState].failureLink = failureState;
                
                // Set dictionary link and inherit pattern indices
                if (trie[failureState].isEnd) {
                    trie[nextState].dictionaryLink = failureState;
                } else {
                    trie[nextState].dictionaryLink = trie[failureState].dictionaryLink;
                }
            }
        }
    }
    
public:
    // Constructor
    AhoCorasick(const vector<string>& patterns) {
        buildTrie(patterns);
        buildLinks();
    }
    
    // Search for all pattern occurrences in the text
    vector<pair<int, int>> search(const string& text) {
        vector<pair<int, int>> matches;  // (patternIndex, position)
        int currentState = 0;
        
        // Process each character of the text
        for (int i = 0; i < text.length(); i++) {
            char ch = text[i];
            
            // Follow failure links until we find a valid transition or reach root
            while (currentState != 0 && trie[currentState].children.find(ch) == trie[currentState].children.end()) {
                currentState = trie[currentState].failureLink;
            }
            
            // If there's a valid transition, move to the next state
            if (trie[currentState].children.find(ch) != trie[currentState].children.end()) {
                currentState = trie[currentState].children[ch];
            }
            
            // Check if we've found a pattern match
            if (trie[currentState].isEnd) {
                // Add all pattern matches at the current state
                for (int patternIndex : trie[currentState].patternIndices) {
                    int endPos = i;
                    int startPos = endPos - patterns[patternIndex].length() + 1;
                    matches.push_back({patternIndex, startPos});
                }
            }
            
            // Follow dictionary links to find more matches
            int dictState = trie[currentState].dictionaryLink;
            while (dictState != -1) {
                for (int patternIndex : trie[dictState].patternIndices) {
                    int endPos = i;
                    int startPos = endPos - patterns[patternIndex].length() + 1;
                    matches.push_back({patternIndex, startPos});
                }
                dictState = trie[dictState].dictionaryLink;
            }
        }
        
        return matches;
    }
    
    // Print the trie structure for debugging
    void printTrie() {
        cout << "Trie Structure:" << endl;
        for (int i = 0; i < trie.size(); i++) {
            cout << "State " << i << ":" << endl;
            cout << "  Children: ";
            for (auto& transition : trie[i].children) {
                cout << "'" << transition.first << "'→" << transition.second << " ";
            }
            cout << endl;
            cout << "  Failure Link: " << trie[i].failureLink << endl;
            cout << "  Dictionary Link: " << trie[i].dictionaryLink << endl;
            cout << "  Is End: " << (trie[i].isEnd ? "Yes" : "No") << endl;
            if (!trie[i].patternIndices.empty()) {
                cout << "  Pattern Indices: ";
                for (int idx : trie[i].patternIndices) {
                    cout << idx << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    // Example 1: Basic pattern searching
    vector<string> patterns1 = {"he", "she", "his", "hers"};
    string text1 = "ahishershe";
    
    cout << "Example 1: Basic pattern searching" << endl;
    cout << "Patterns: ";
    for (const string& pattern : patterns1) {
        cout << "\"" << pattern << "\" ";
    }
    cout << endl;
    cout << "Text: \"" << text1 << "\"" << endl;
    
    AhoCorasick ac1(patterns1);
    vector<pair<int, int>> matches1 = ac1.search(text1);
    
    cout << "Matches:" << endl;
    for (const auto& match : matches1) {
        int patternIndex = match.first;
        int position = match.second;
        cout << "  Pattern \"" << patterns1[patternIndex] << "\" found at position "
             << position << " to " << (position + patterns1[patternIndex].length() - 1) << endl;
    }
    cout << endl;
    
    // Example 2: DNA sequence pattern matching
    vector<string> patterns2 = {"AGTC", "TCG", "GAT", "TGAT"};
    string text2 = "GTGATCGTCAGTCGATCG";
    
    cout << "Example 2: DNA sequence pattern matching" << endl;
    cout << "Patterns: ";
    for (const string& pattern : patterns2) {
        cout << "\"" << pattern << "\" ";
    }
    cout << endl;
    cout << "Text: \"" << text2 << "\"" << endl;
    
    AhoCorasick ac2(patterns2);
    vector<pair<int, int>> matches2 = ac2.search(text2);
    
    cout << "Matches:" << endl;
    for (const auto& match : matches2) {
        int patternIndex = match.first;
        int position = match.second;
        cout << "  Pattern \"" << patterns2[patternIndex] << "\" found at position "
             << position << " to " << (position + patterns2[patternIndex].length() - 1) << endl;
    }
    cout << endl;
    
    // Example 3: Overlapping patterns
    vector<string> patterns3 = {"abc", "bcd", "cde"};
    string text3 = "abcde";
    
    cout << "Example 3: Overlapping patterns" << endl;
    cout << "Patterns: ";
    for (const string& pattern : patterns3) {
        cout << "\"" << pattern << "\" ";
    }
    cout << endl;
    cout << "Text: \"" << text3 << "\"" << endl;
    
    AhoCorasick ac3(patterns3);
    vector<pair<int, int>> matches3 = ac3.search(text3);
    
    cout << "Matches:" << endl;
    for (const auto& match : matches3) {
        int patternIndex = match.first;
        int position = match.second;
        cout << "  Pattern \"" << patterns3[patternIndex] << "\" found at position "
             << position << " to " << (position + patterns3[patternIndex].length() - 1) << endl;
    }
    
    return 0;
}
