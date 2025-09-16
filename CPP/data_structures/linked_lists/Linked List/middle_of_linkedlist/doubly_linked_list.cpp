#include <iostream>
using namespace std;

// Definition of a Node in the doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Function to insert a new node at the end of the doubly linked list
void insertAtEnd(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to find the middle element of the doubly linked list
int findMiddle(Node* head) {
    if (!head) {
        cout << "The list is empty." << endl;
        return -1;
    }
    Node* slow = head;
    Node* fast = head;

    // Move fast pointer by two steps and slow pointer by one step
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // slow pointer is now at the middle
    return slow->data;
}

// Function to display the doubly linked list
void display(Node* head) {
    while (head) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = nullptr;

    // Insert elements into the doubly linked list
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);
    insertAtEnd(head, 50);

    // Display the doubly linked list
    cout << "Doubly Linked List: ";
    display(head);

    // Find and display the middle element
    int middle = findMiddle(head);
    if (middle != -1) {
        cout << "The middle element is: " << middle << endl;
    }

    return 0;
}
