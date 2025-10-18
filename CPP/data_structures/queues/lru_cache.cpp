/**
 * @file lru_cache.cpp
 * @brief Implementation of the Least Recently Used (LRU) Cache.
 *
 * Description:
 * An LRU Cache is a fixed-size cache that evicts the least recently used item
 * when it reaches its capacity. This implementation uses a combination of a
 * hash map (std::unordered_map) and a doubly-linked list (std::list) to
 * achieve O(1) average time complexity for both `get` and `put` operations.
 *
 * - The `list` stores pairs of key-value to maintain the order of usage.
 * The most recently used items are moved to the front of the list.
 * - The `std::unordered_map` stores the key and an iterator to its corresponding
 * node in the list, allowing for O(1) access to any item.
 *
 * Complexity Analysis:
 * - Time Complexity: O(1) for both `get` and `put` operations.
 * - `get`: Hash map lookup is O(1) on average. Moving the element to the front of the list is also O(1).
 * - `put`: Hash map lookup and insertion are O(1) on average. List operations (push_front, pop_back, erase) are O(1).
 * - Space Complexity: O(capacity), as the cache stores up to 'capacity' elements.
 */
#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;
    // Doubly-linked list to store {key, value} pairs.
    // The front of the list is the most recently used.
    list<pair<int, int>> items_list;
    // Hash map to store key -> list iterator for O(1) lookup.
    unordered_map<int, list<pair<int, int>>::iterator> items_map;

public:
    // Constructor to initialize the cache with a given capacity.
    // Capacity must be a positive integer.
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        // Check if the key exists in the map.
        if (items_map.find(key) == items_map.end()) {
            return -1; // Key not found
        }

        // Key found, get the iterator from the map.
        auto it = items_map[key];
        // The value is the second element of the pair in the list.
        int value = it->second;

        // Move the accessed item to the front of the list to mark it as most recently used.
        // splice() efficiently moves the node without creating/destroying elements.
        items_list.splice(items_list.begin(), items_list, it);

        return value;
    }

    // put key-value pair into the cache
    // If the key already exists, update its value and move it to the front.
    // If the cache is at capacity, evict the least recently used item.
    void put(int key, int value) {
        // If the key already exists, update its value and move it to the front.
        if (items_map.find(key) != items_map.end()) {
            auto it = items_map[key];
            it->second = value; // Update value
            items_list.splice(items_list.begin(), items_list, it); // Move to front
            return;
        }

        // If the cache is at full capacity, evict the least recently used item.
        if (items_map.size() == capacity) {
            // The least recently used item is at the back of the list.
            pair<int, int> last_item = items_list.back();
            items_map.erase(last_item.first); // Remove from map
            items_list.pop_back();            // Remove from list
        }

        // Insert the new key-value pair at the front of the list.
        items_list.push_front({key, value});
        // Store the iterator to the new item in the map.
        items_map[key] = items_list.begin();
    }
};

// Example usage and test cases
int main() {
    // Create a cache with capacity 2
    LRUCache cache(2);

    cout << "Putting (1, 10)" << endl;
    cache.put(1, 10);
    cout << "Putting (2, 20)" << endl;
    cache.put(2, 20);

    // Test basic get
    cout << "Getting key 1: " << cache.get(1) << endl; // returns 10

    // Test eviction: putting 3 should evict key 2 (least recently used)
    cout << "Putting (3, 30)" << endl;
    cache.put(3, 30);
    cout << "Getting key 2: " << cache.get(2) << endl; // returns -1 (not found)

    // Test that key 1 is still present and now is the LRU
    cout << "Getting key 1: " << cache.get(1) << endl; // returns 10

    // Test updating an existing key
    cout << "Putting (1, 100) to update" << endl;
    cache.put(1, 100);
    cout << "Getting key 1: " << cache.get(1) << endl; // returns 100

    return 0;
}