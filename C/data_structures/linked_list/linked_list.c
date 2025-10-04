/**
 * Singly Linked List Implementation in C
 *
 * Description:
 * A linked list is a linear data structure where each element (called a "node") 
 * contains some data and a pointer to the next node in the sequence. Unlike arrays,
 * linked lists do not store elements in contiguous memory locations.
 *
 * Key Features:
 * - Dynamic memory allocation (no fixed size)
 * - Efficient insertion and deletion at the beginning
 * - Sequential access to elements
 * - Memory efficient (allocates only as needed)
 *
 * Time Complexity:
 * - Insertion at beginning: O(1)
 * - Insertion at end: O(n)
 * - Insertion at position: O(n)
 * - Deletion at beginning: O(1)
 * - Deletion at end: O(n)
 * - Search: O(n)
 * - Display: O(n)
 *
 * Space Complexity: O(n) where n is the number of nodes
 *
 * Advantages:
 * - Dynamic size
 * - Efficient memory utilization
 * - Easy insertion/deletion at beginning
 *
 * Disadvantages:
 * - No random access (must traverse from head)
 * - Extra memory overhead for storing pointers
 * - Not cache friendly due to non-contiguous memory
 *
 * Author: Generated for Issue #408
 * Category: Data Structures
 * Difficulty: Easy (Beginner friendly)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Node structure definition
 * Each node contains:
 * - data: integer value stored in the node
 * - next: pointer to the next node in the list
 */
struct Node {
    int data;
    struct Node* next;
};

// Global head pointer to the first node of the list
struct Node* head = NULL;

/**
 * Function to create a new node
 * 
 * @param data The integer value to store in the new node
 * @return Pointer to the newly created node, or NULL if allocation fails
 */
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * Insert a new node at the beginning of the list
 * Time Complexity: O(1)
 * 
 * @param data The integer value to insert
 */
void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    newNode->next = head;  // Point new node to current head
    head = newNode;        // Update head to point to new node
    printf("Inserted %d at the beginning\n", data);
}

/**
 * Insert a new node at the end of the list
 * Time Complexity: O(n)
 * 
 * @param data The integer value to insert
 */
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    // If list is empty, make new node the head
    if (head == NULL) {
        head = newNode;
        printf("Inserted %d at the end (first node)\n", data);
        return;
    }
    
    // Traverse to the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Link the last node to the new node
    temp->next = newNode;
    printf("Inserted %d at the end\n", data);
}

/**
 * Insert a new node at a specific position (0-indexed)
 * Time Complexity: O(n)
 * 
 * @param data The integer value to insert
 * @param position The position where to insert (0-indexed)
 */
void insertAtPosition(int data, int position) {
    if (position < 0) {
        printf("Invalid position! Position must be >= 0\n");
        return;
    }
    
    // If inserting at position 0, use insertAtBeginning
    if (position == 0) {
        insertAtBeginning(data);
        return;
    }
    
    struct Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    struct Node* temp = head;
    
    // Traverse to the node before the desired position
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    // If position is beyond the list length
    if (temp == NULL) {
        printf("Position %d is beyond the list length. Inserting at end.\n", position);
        free(newNode);
        insertAtEnd(data);
        return;
    }
    
    // Insert the new node
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d\n", data, position);
}

/**
 * Delete the first node of the list
 * Time Complexity: O(1)
 */
void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }
    
    struct Node* temp = head;
    head = head->next;
    printf("Deleted %d from the beginning\n", temp->data);
    free(temp);
}

/**
 * Delete the last node of the list
 * Time Complexity: O(n)
 */
void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }
    
    // If there's only one node
    if (head->next == NULL) {
        printf("Deleted %d from the end\n", head->data);
        free(head);
        head = NULL;
        return;
    }
    
    // Traverse to the second last node
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    printf("Deleted %d from the end\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

/**
 * Delete a node with specific value
 * Time Complexity: O(n)
 * 
 * @param data The value to delete from the list
 */
void deleteByValue(int data) {
    if (head == NULL) {
        printf("List is empty! Cannot delete.\n");
        return;
    }
    
    // If head node contains the data to be deleted
    if (head->data == data) {
        deleteFromBeginning();
        return;
    }
    
    struct Node* temp = head;
    
    // Search for the node to be deleted
    while (temp->next != NULL && temp->next->data != data) {
        temp = temp->next;
    }
    
    // If data not found
    if (temp->next == NULL) {
        printf("Value %d not found in the list\n", data);
        return;
    }
    
    // Delete the node
    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Deleted %d from the list\n", data);
    free(nodeToDelete);
}

/**
 * Search for a value in the list
 * Time Complexity: O(n)
 * 
 * @param data The value to search for
 * @return Position of the value (0-indexed), or -1 if not found
 */
int search(int data) {
    struct Node* temp = head;
    int position = 0;
    
    while (temp != NULL) {
        if (temp->data == data) {
            printf("Value %d found at position %d\n", data, position);
            return position;
        }
        temp = temp->next;
        position++;
    }
    
    printf("Value %d not found in the list\n", data);
    return -1;
}

/**
 * Get the length of the list
 * Time Complexity: O(n)
 * 
 * @return Number of nodes in the list
 */
int getLength() {
    int count = 0;
    struct Node* temp = head;
    
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    return count;
}

/**
 * Check if the list is empty
 * Time Complexity: O(1)
 * 
 * @return true if list is empty, false otherwise
 */
bool isEmpty() {
    return head == NULL;
}

/**
 * Display all elements in the list
 * Time Complexity: O(n)
 */
void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("Linked List: ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

/**
 * Reverse the linked list
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
void reverse() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one element\n");
        return;
    }
    
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;  // Store next node
        current->next = prev;  // Reverse the link
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }
    
    head = prev;  // Update head to the new first node
    printf("List has been reversed\n");
}

/**
 * Free all nodes in the list
 * Time Complexity: O(n)
 */
void freeList() {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("All memory has been freed\n");
}

/**
 * Display the menu options
 */
void displayMenu() {
    printf("\n=== Linked List Operations ===\n");
    printf("1.  Insert at beginning\n");
    printf("2.  Insert at end\n");
    printf("3.  Insert at position\n");
    printf("4.  Delete from beginning\n");
    printf("5.  Delete from end\n");
    printf("6.  Delete by value\n");
    printf("7.  Search for value\n");
    printf("8.  Display list\n");
    printf("9.  Get list length\n");
    printf("10. Check if empty\n");
    printf("11. Reverse list\n");
    printf("12. Run test cases\n");
    printf("0.  Exit\n");
    printf("Enter your choice: ");
}

/**
 * Run comprehensive test cases
 */
void runTestCases() {
    printf("\n=== Running Test Cases ===\n");
    
    // Clear existing list
    freeList();
    
    // Test Case 1: Basic insertions
    printf("\nTest Case 1: Basic insertions\n");
    insertAtBeginning(10);
    insertAtBeginning(20);
    insertAtEnd(30);
    insertAtEnd(40);
    display();
    
    // Test Case 2: Insert at specific positions
    printf("\nTest Case 2: Insert at positions\n");
    insertAtPosition(25, 2);  // Insert 25 at position 2
    insertAtPosition(5, 0);   // Insert 5 at beginning
    insertAtPosition(50, 10); // Insert beyond length
    display();
    
    // Test Case 3: Search operations
    printf("\nTest Case 3: Search operations\n");
    search(25);
    search(100);  // Not found
    
    // Test Case 4: Length and empty check
    printf("\nTest Case 4: Length and empty check\n");
    printf("List length: %d\n", getLength());
    printf("Is empty: %s\n", isEmpty() ? "Yes" : "No");
    
    // Test Case 5: Deletions
    printf("\nTest Case 5: Deletions\n");
    deleteFromBeginning();
    deleteFromEnd();
    deleteByValue(25);
    deleteByValue(100);  // Not found
    display();
    
    // Test Case 6: Reverse operation
    printf("\nTest Case 6: Reverse operation\n");
    printf("Before reverse: ");
    display();
    reverse();
    printf("After reverse: ");
    display();
    
    // Test Case 7: Edge cases
    printf("\nTest Case 7: Edge cases\n");
    freeList();  // Empty list
    display();
    deleteFromBeginning();  // Delete from empty list
    search(10);  // Search in empty list
    printf("Length of empty list: %d\n", getLength());
    printf("Is empty: %s\n", isEmpty() ? "Yes" : "No");
    
    printf("\nAll test cases completed!\n");
}

/**
 * Main function to demonstrate linked list operations
 */
int main() {
    int choice, data, position;
    
    printf("Linked List Implementation in C\n");
    printf("================================\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
                
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
                
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
                
            case 4:
                deleteFromBeginning();
                break;
                
            case 5:
                deleteFromEnd();
                break;
                
            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                deleteByValue(data);
                break;
                
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &data);
                search(data);
                break;
                
            case 8:
                display();
                break;
                
            case 9:
                printf("List length: %d\n", getLength());
                break;
                
            case 10:
                printf("List is %s\n", isEmpty() ? "empty" : "not empty");
                break;
                
            case 11:
                reverse();
                break;
                
            case 12:
                runTestCases();
                break;
                
            case 0:
                printf("Freeing memory and exiting...\n");
                freeList();
                printf("Thank you for using Linked List!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
