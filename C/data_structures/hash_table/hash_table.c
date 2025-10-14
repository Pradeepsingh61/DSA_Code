/*
 * Data Structure: Hash Table
 * Description: Implements a hash table storing integer key-value pairs,
 *              resolving collisions with linked list chaining.
 * Time Complexity: Average O(1) insert/search, worst O(n)
 * Space Complexity: O(n)
 * Author: tanshen-kun
 *
 * Hacktoberfest2025
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node for chaining in hash table
struct Node {
  int key;
  int value;
  struct Node *next;
};

/**
 * Create a new node for the chain
 *
 * @param key : integer key
 * @param value : integer value
 * @return pointer to newly created node
 */
struct Node *createNode(int key, int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("[x] Memory allocation for new Node failed\n");
    exit(1);
  }
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

/**
 * Simple modulo hash function
 *
 * @param key : integer key
 * @return hash index within table size
 */
unsigned int hashFunction(int key) { return key % TABLE_SIZE; }

/**
 * Insert or update key-value pair in hash table
 *
 * @param table : hash table array
 * @param key : integer key to insert
 * @param value : integer value associated with key
 */
void insert(struct Node **table, int key, int value) {
  unsigned int index = hashFunction(key);
  struct Node *head = table[index];

  // Check if key already exists
  struct Node *temp = head;
  while (temp != NULL) {
    if (temp->key == key) {
      temp->value = value;
      return;
    }
    temp = temp->next;
  }

  // Insert new node at beginning of chain
  struct Node *newNode = createNode(key, value);
  newNode->next = head;
  table[index] = newNode;
}

/**
 * Search for a key and return its value or -1 if not found
 *
 * @param table : hash table array
 * @param key : key to search
 * @return value associated with key or -1 if not found
 */
int search(struct Node **table, int key) {
  unsigned int index = hashFunction(key);
  struct Node *temp = table[index];

  while (temp != NULL) {
    if (temp->key == key)
      return temp->value;
    temp = temp->next;
  }
  return -1; // Not found
}

/**
 * Free all nodes in the hash table
 *
 * @param table : hash table array
 */
void freeTable(struct Node **table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    struct Node *temp = table[i];
    while (temp != NULL) {
      struct Node *next = temp->next;
      free(temp);
      temp = next;
    }
    table[i] = NULL;
  }
}

/**
 * Test the hash table insert and search functionality
 */
void testHashTable() {
  struct Node *hashTable[TABLE_SIZE] = {NULL};

  // Test insertions
  insert(hashTable, 1, 100);
  insert(hashTable, 2, 200);
  insert(hashTable, 12, 1200); // Collision at index 2
  insert(hashTable, 22, 2200); // Collision at index 2
  insert(hashTable, 3, 300);

  // Test searches (including a missing key)
  int keys[] = {1, 2, 12, 22, 3, 99};
  int n = sizeof(keys) / sizeof(keys[0]);

  for (int i = 0; i < n; i++) {
    int val = search(hashTable, keys[i]);
    if (val != -1) {
      printf("Key [%d] found with value [%d]\n", keys[i], val);
    } else {
      printf("Key [%d] not found\n", keys[i]);
    }
  }

  // Cleanup
  freeTable(hashTable);
}

int main() {
  printf("[--- HASH TABLE ---]\n\n");
  testHashTable();
  return 0;
}
