#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to split the linked list into two halves
void splitLinkedList(Node* head, Node** firstHalf, Node** secondHalf) {
    if (head == nullptr || head->next == nullptr) {
        *firstHalf = head;
        *secondHalf = nullptr;
        return;
    }

    Node* slow = head;
    Node* fast = head->next;

    // Using slow and fast pointers to find the middle
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list into two halves
    *firstHalf = head;
    *secondHalf = slow->next;
    slow->next = nullptr;
}

// Function to print the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Helper function to append a new node at the end
void append(Node** headRef, int newData) {
    Node* newNode = new Node(newData);
    if (*headRef == nullptr) {
        *headRef = newNode;
        return;
    }
    Node* last = *headRef;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = newNode;
}

int main() {
    Node* head = nullptr;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    cout << "Original List: ";
    printList(head);

    Node* firstHalf = nullptr;
    Node* secondHalf = nullptr;

    splitLinkedList(head, &firstHalf, &secondHalf);

    cout << "First Half: ";
    printList(firstHalf);

    cout << "Second Half: ";
    printList(secondHalf);

    return 0;
}
