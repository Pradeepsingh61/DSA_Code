#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;              // To store data
    struct Node* next;     // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode; // If list is empty, make newNode the head
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display the linked list
void display(struct Node* head) {
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to delete a node by value
void deleteNode(struct Node** head, int value) {
    struct Node *temp = *head, *prev = NULL;

    // If head node itself holds the value
    if (temp != NULL && temp->data == value) {
        *head = temp->next; // Change head
        free(temp);         // Free memory
        return;
    }

    // Search for the value to be deleted
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If value not found
    if (temp == NULL) {
        printf("Value %d not found in list.\n", value);
        return;
    }

    // Unlink node from list and free memory
    prev->next = temp->next;
    free(temp);
}

// Main function to demonstrate the linked list
int main() {
    struct Node* head = NULL; // Initialize empty list

    // Insert elements
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    display(head); // Output: 10 -> 20 -> 30 -> NULL

    // Delete a node
    deleteNode(&head, 20);

    display(head); // Output: 10 -> 30 -> NULL

    return 0;
}
