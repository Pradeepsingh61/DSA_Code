#include <iostream>
#include <unordered_set>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Function to remove duplicates from an unsorted linked list
void removeDuplicatesUnsorted(Node* head) {
    if (head == nullptr) return;

    unordered_set<int> seen;
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (seen.find(current->data) != seen.end()) {
            // Duplicate node found, remove it
            prev->next = current->next;
            delete current;
        } else {
            // Not a duplicate, add to set
            seen.insert(current->data);
            prev = current;
        }
        current = prev->next;
    }
}

// Helper functions
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

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    append(&head, 5);
    append(&head, 1);
    append(&head, 3);
    append(&head, 3);
    append(&head, 4);
    append(&head, 1);
    append(&head, 5);

    cout << "Original Unsorted List: ";
    printList(head);

    removeDuplicatesUnsorted(head);

    cout << "List after removing duplicates: ";
    printList(head);

    return 0;
}
