// File: Algorithms/Greedy/huffman_coding.cpp
// Algorithm: Huffman Coding
// Category: Greedy Algorithm
// Difficulty: Medium (Intermediate)
// Description: Builds a Huffman Tree to assign variable-length codes to characters 
//              based on their frequencies, minimizing the total encoding length.

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// 🧠 Node structure for Huffman Tree
struct Node {
    char ch;          // Character
    int freq;         // Frequency of the character
    Node *left;       // Left child
    Node *right;      // Right child

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// ⚡ Custom comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // Smaller frequency gets higher priority
    }
};

// 📌 Recursive function to generate Huffman Codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node -> store the code
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// 🌳 Build Huffman Tree and encode
void buildHuffmanTree(const string& text) {
    // Step 1: Count frequency of each character
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Step 2: Create a min-heap (priority queue) of leaf nodes
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Step 3: Merge two lowest frequency nodes until one node remains
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    // Step 4: Generate Huffman Codes by traversing the tree
    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "\nHuffman Codes for each character:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Step 5: Encode the input string
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCode[ch];
    }

    cout << "\nOriginal string: " << text << endl;
    cout << "Encoded string : " << encodedString << endl;

    // (Optional) Step 6: Decoding - to verify correctness
    string decodedString = "";
    Node* curr = root;
    for (char bit : encodedString) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            decodedString += curr->ch;
            curr = root;
        }
    }

    cout << "Decoded string : " << decodedString << endl;
}

// 🧪 Main function to test Huffman Coding
int main() {
    string text;
    cout << "Enter a string to encode using Huffman Coding: ";
    getline(cin, text);

    buildHuffmanTree(text);
    return 0;
}


//added to main branch