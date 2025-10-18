/*
 *
 * Data Structure : Linked List
 * Description : A linked list is a linear data structure where each element
 * (called a "node") contains some data and a pointer to the next node. Time
 * Complexity :-
 *     - Insertion at End : O(n)
 * Space Complexity :-
 *     - Insertion at End : O(n)
 * Author : tanshen-kun
 *
 * Hacktoberfest2025
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * struct Node =>
 *   @ data : data to be stored
 *   @ next : pointer to the next node
 */
struct Node {
  int data;
  struct Node *next;
};

/*
 * createNode : function to create Node =>
 *   @ data : data to store to node's data
 */
struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("[x] Memory allocation for new Node failed\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

/*
 * insertAtEnd : function to insert data at the end of a node =>
 *  @head : pointer to the head of the linked list
 *  @data : data to be stored in the new node inserted at the end.
 */
void insertAtEnd(struct Node **head, int data) {
  struct Node *newNode = createNode(data);
  if (*head == NULL) {
    *head = newNode;
    return;
  }
  struct Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

// Function to print the linked list
void printList(struct Node *head) {
  struct Node *temp = head;
  while (temp != NULL) {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }
  printf("NULL\n");
}

// Function to free the list
void freeList(struct Node *head) {
  struct Node *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int main() {
  struct Node *head = NULL;

  insertAtEnd(&head, 10);
  insertAtEnd(&head, 20);
  insertAtEnd(&head, 30);

  printf("Linked List: ");
  printList(head);

  freeList(head);
  return 0;
}
