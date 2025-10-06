#include <stdio.h>
#include <stdlib.h>

/*
Problem:
Implement a Singly Linked List that allows insertion, deletion, and display operations.
Each node contains an integer value and a pointer to the next node.
*/

// Define the structure for a linked list node
struct Node {
    int data;              // Stores the data value
    struct Node* next;     // Pointer to the next node
};

// Function to create a new node with the given value
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // Allocate memory
    if (newNode == NULL) {  // Check for memory allocation failure
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;  // Set data value
    newNode->next = NULL;   // Initialize next pointer as NULL
    return newNode;
}

// Function to insert a new node at the end of the linked list
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);  // Create new node
    if (*head == NULL) {   // If list is empty, make newNode the head
        *head = newNode;
        return;
    }

    // Traverse to the end of the list
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Link the new node at the end
    temp->next = newNode;
}

// Function to display all elements of the linked list
void display(struct Node* head) {
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);  // Print current node data
        temp = temp->next;             // Move to next node
    }
    printf("NULL\n");
}

// Function to delete a node by its value
void deleteNode(struct Node** head, int value) {
    struct Node *temp = *head, *prev = NULL;

    // Case 1: If the list is empty
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    // Case 2: If the node to be deleted is the head
    if (temp != NULL && temp->data == value) {
        *head = temp->next; // Move head to next node
        free(temp);         // Free memory of deleted node
        return;
    }

    // Case 3: Search for the node to delete
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If node not found
    if (temp == NULL) {
        printf("Value %d not found in list.\n", value);
        return;
    }

    // Unlink and delete the node
    prev->next = temp->next;
    free(temp);
}

// Main function to demonstrate linked list operations
int main() {
    struct Node* head = NULL; // Initialize an empty linked list

    // Insert some nodes
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    // Display the linked list
    display(head); // Expected Output: 10 -> 20 -> 30 -> NULL

    // Delete a node with value 20
    deleteNode(&head, 20);

    // Display list after deletion
    display(head); // Expected Output: 10 -> 30 -> NULL

    return 0;
}

/*
----------------------------------------
Algorithm Explanation:
----------------------------------------
1. Create Node:
   - Dynamically allocate memory for each node.
   - Store the data and set 'next' pointer as NULL.

2. Insert at End:
   - Traverse to the last node.
   - Link the newly created node at the end.

3. Delete by Value:
   - Search for the node with the given value.
   - Adjust links to remove the node and free its memory.

4. Display:
   - Traverse through the list and print each node’s data.

----------------------------------------
Time & Space Complexities:
----------------------------------------
Operation           Time Complexity      Space Complexity
---------------------------------------------------------
Insertion (End)     O(n)                 O(1)
Deletion (By Value) O(n)                 O(1)
Traversal/Display   O(n)                 O(1)
----------------------------------------
*/
