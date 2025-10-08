/*
 * Algorithm Name:LFU Cache .
 * Programming Language: Java
 * Category: Linked List .
 * Difficulty Level: Hard
 *
 * Author: Priya Rani 
 *
 * Algorithm Description:Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
- int get(int key) Gets the value of the key if the key exists in the cache.  Otherwise, returns -1.
- void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. - For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated and so on 

 

 * Time Complexity:O(1) (average) HashMap and LinkedHashSet operations (insert/remove/lookup) are O(1)
 * Space complexity: O(capacity)Stores up to capacity nodes and frequency mappings
*/

import java.util.*;

class LFUCache {
    private final int capacity;
    private int minFreq;
    private final Map<Integer, Node> nodeMap;              
    private final Map<Integer, LinkedHashSet<Node>> freqMap; 

    private static class Node {
        int key, value, freq;
        Node(int key, int value) {
            this.key = key;
            this.value = value;
            this.freq = 1;
        }
    }

    public LFUCache(int capacity) {
        this.capacity = capacity;
        this.minFreq = 0;
        this.nodeMap = new HashMap<>();
        this.freqMap = new HashMap<>();
    }

    public int get(int key) {
        if (!nodeMap.containsKey(key)) return -1;

        Node node = nodeMap.get(key);
        updateFreq(node);
        return node.value;
    }

    public void put(int key, int value) {
        if (capacity == 0) return;

        if (nodeMap.containsKey(key)) {
            Node node = nodeMap.get(key);
            node.value = value;
            updateFreq(node);
            return;
        }

        if (nodeMap.size() >= capacity) {
            // Remove LFU node
            LinkedHashSet<Node> minFreqNodes = freqMap.get(minFreq);
            Node toRemove = minFreqNodes.iterator().next(); 
            minFreqNodes.remove(toRemove);
            nodeMap.remove(toRemove.key);
            if (minFreqNodes.isEmpty()) freqMap.remove(minFreq);
        }

        Node newNode = new Node(key, value);
        nodeMap.put(key, newNode);
        freqMap.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(newNode);
        minFreq = 1; 
    }

    private void updateFreq(Node node) {
        int oldFreq = node.freq;
        LinkedHashSet<Node> oldSet = freqMap.get(oldFreq);
        oldSet.remove(node);
        if (oldSet.isEmpty()) {
            freqMap.remove(oldFreq);
            if (minFreq == oldFreq) minFreq++;
        }

        node.freq++;
        freqMap.computeIfAbsent(node.freq, k -> new LinkedHashSet<>()).add(node);
    }

    public static void main(String[] args) {
        LFUCache lfu = new LFUCache(2);
        lfu.put(1, 1);
        lfu.put(2, 2);
        System.out.println(lfu.get(1)); 
        lfu.put(3, 3);                 
        System.out.println(lfu.get(2)); 
        System.out.println(lfu.get(3)); 
        lfu.put(4, 4);                 
        System.out.println(lfu.get(1)); 
        System.out.println(lfu.get(3)); 
        System.out.println(lfu.get(4)); 
    }
}
