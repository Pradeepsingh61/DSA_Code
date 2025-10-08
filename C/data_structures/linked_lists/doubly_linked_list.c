#include <stdio.h>
#include <stdlib.h>

/*
* insert_end : it takes the pointer to the head of the list and a data value. 
* It creates a new node and inserts it at the end of the doubly linked list. 
* If the list is empty, the new node becomes the head.
* @param head: Pointer to the head pointer of the list
* @param data: Data value to insert in the new node
* @return: None
*/

// Structure of a node in a doubly linked list
struct Node {
    int data;           // Data stored in the node
    struct Node* prev;  // Pointer to the previous node
    struct Node* next;  // Pointer to the next node
};

// Function to create a new node
struct Node* create_node(int data) {
    // Allocate memory for a new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;   // Set the node's data
    new_node->prev = NULL;   // Previous is NULL for a new node
    new_node->next = NULL;   // Next is NULL for a new node
    return new_node;         // Return the newly created node
}

// Function to insert a node at the front (beginning) of the list
void insert_front(struct Node** head, int data) {
    struct Node* new_node = create_node(data); // Create a new node

    new_node->next = *head;  // Make new node point to current head
    if (*head != NULL) {
        // If list is not empty, previous of current head becomes new node
        (*head)->prev = new_node;
    }
    *head = new_node;        // Update head to point to new node
}

// Function to insert a node at the end of the list
void insert_end(struct Node** head, int data) {
    struct Node* new_node = create_node(data); // Create a new node

    if (*head == NULL) {
        // If list is empty, new node becomes head
        *head = new_node;
        return;
    }

    // Traverse to the last node
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Update links to insert new node at the end
    temp->next = new_node;
    new_node->prev = temp;
}

// Function to insert a node at a specific position (1-based index)
void insert_at_position(struct Node** head, int data, int pos) {
    if (pos <= 1 || *head == NULL) {
        // If position is 1 or list is empty, insert at front
        insert_front(head, data);
        return;
    }

    struct Node* new_node = create_node(data); // Create new node
    struct Node* temp = *head;

    // Traverse to the node after which new node will be inserted
    int i;
    for (i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }

    // Update links to insert the new node
    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != NULL) {
        // If not inserting at the end, update previous pointer of next node
        temp->next->prev = new_node;
    }

    temp->next = new_node; // Link previous node to new node
}

// Helper function to delete a node using its pointer
void delete_node_pointer(struct Node** head, struct Node* del_node) {
    if (*head == NULL || del_node == NULL) return; // Nothing to delete

    if (*head == del_node) {
        // If deleting the head node, move head pointer to next node
        *head = del_node->next;
    }

    if (del_node->next != NULL) {
        // Update previous pointer of next node
        del_node->next->prev = del_node->prev;
    }

    if (del_node->prev != NULL) {
        // Update next pointer of previous node
        del_node->prev->next = del_node->next;
    }

    free(del_node); // Free memory of deleted node
}

// Function to delete a node by its value
void delete_by_value(struct Node** head, int key) {
    struct Node* temp = *head;

    // Search for the node containing the value
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        // Value not found in the list
        printf("Value %d not found in list.\n", key);
        return;
    }

    // Delete the found node
    delete_node_pointer(head, temp);
}

// Function to display the list from head to tail
void display_forward(struct Node* head) {
    struct Node* temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data); // Print current node data
        temp = temp->next;         // Move to next node
    }
    printf("\n");
}

// Function to display the list from tail to head
void display_reverse(struct Node* head) {
    if (head == NULL) {
        printf("Reverse: (empty list)\n");
        return;
    }

    struct Node* temp = head;

    // Move to the last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("Reverse: ");
    // Traverse reverse using prev pointer
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Main function to demonstrate DLL operations
int main() {
    struct Node* head = NULL; // Initialize empty list

    // Insert nodes
    insert_end(&head, 10);          // List: 10
    insert_end(&head, 20);          // List: 10->20
    insert_front(&head, 5);         // List: 5->10->20
    insert_at_position(&head, 15, 3); // List: 5->10->15->20
    insert_end(&head, 30);          // List: 5->10->15->20->30

    // Display the list in both directions
    display_forward(head);          // Output: 5 10 15 20 30
    display_reverse(head);         // Output: 30 20 15 10 5

    // Delete a node by value
    delete_by_value(&head, 20);     // Delete 20

    // Display after deletion
    display_forward(head);          // Output: 5 10 15 30

    // Try deleting a non-existent value
    delete_by_value(&head, 100);    // Output: Value 100 not found in list

    return 0;
}
/*
 * Algorithm: Doubly Linked List (DLL)
 * Description: A Doubly Linked List is a data structure consisting of nodes, 
 *               where each node contains data and two pointers: 'prev' pointing 
 *               to the previous node and 'next' pointing to the next node. This 
 *               allows traversal in both forward and backward directions. Common 
 *               operations include insertion (front, end, or specific position), 
 *               deletion (by value or position), and traversal.
 * Time Complexity:
 *     Insertion at beginning  : O(1)
 *     Insertion at end        : O(n)
 *     Insertion at position   : O(n)
 *     Deletion by value       : O(n)
 *     Traversal (forward/reverse) : O(n)
 * Space Complexity: O(n)  
 * Advantages:
 *     - Can traverse both directions
 *     - Efficient deletion if node pointer is known
 * Disadvantages:
 *     - Extra memory per node for prev pointer
 *     - More pointer manipulation can lead to bugs
 * Author: subhahens
 */
