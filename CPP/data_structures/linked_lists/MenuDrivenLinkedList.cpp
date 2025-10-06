
/*
 * Algorithm: Menu Driven Linked List
 * Description: Implementation of a linked list with menu options 
 *              (insert, delete, display,middle, exit and many more ).
 * Time Complexity: O(n) for insertion/search/deletion
 * Space Complexity: O(n)
 * Author: Ayush Kumar Anand
 * Date: 2025-10-01
 */
#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head = nullptr;

public:
    // Display list
    void display() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        cout << "Linked List: ";
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Create list with n nodes
    void createList(int n) {
        head = nullptr;
        Node *temp = nullptr;
        for (int i = 0; i < n; i++) {
            int val;
            cout << "Enter value for node " << i + 1 << ": ";
            cin >> val;
            Node* newNode = new Node{val, nullptr};
            if (!head) {
                head = newNode;
                temp = head;
            } else {
                temp->next = newNode;
                temp = newNode;
            }
        }
        cout << "List created successfully\n";
    }

    // Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node{val, head};
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node{val, nullptr};
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // Insert at position
    void insertAtPosition(int pos, int val) {
        Node* newNode = new Node{val, nullptr};
        if (pos == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 1; temp && i < pos - 1; i++) temp = temp->next;
        if (!temp) {
            cout << "Position out of range!\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Insert after element
    void insertAfterElement(int element, int val) {
        Node* temp = head;
        while (temp && temp->data != element) temp = temp->next;
        if (!temp) {
            cout << "Element " << element << " not found!\n";
            return;
        }
        Node* newNode = new Node{val, temp->next};
        temp->next = newNode;
        cout << "Inserted " << val << " after " << element << "\n";
    }

    // Delete first node
    void deleteFirst() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        cout << "Deleted node with value " << temp->data << "\n";
        delete temp;
    }

    // Delete last node
    void deleteLast() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        if (!head->next) {
            cout << "Deleted node with value " << head->data << "\n";
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next) temp = temp->next;
        cout << "Deleted node with value " << temp->next->data << "\n";
        delete temp->next;
        temp->next = nullptr;
    }

    // Delete at position
    void deleteAtPosition(int pos) {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        Node* temp = head;
        if (pos == 1) {
            head = head->next;
            cout << "Deleted node with value " << temp->data << " at position 1\n";
            delete temp;
            return;
        }
        for (int i = 1; temp && i < pos - 1; i++) temp = temp->next;
        if (!temp || !temp->next) {
            cout << "Wrong position!\n";
            return;
        }
        Node* del = temp->next;
        temp->next = del->next;
        cout << "Deleted node with value " << del->data << " at position " << pos << "\n";
        delete del;
    }

    // Delete after element
    void deleteAfterElement(int element) {
        Node* temp = head;
        while (temp && temp->data != element) temp = temp->next;
        if (!temp) {
            cout << "Element " << element << " not found!\n";
            return;
        }
        if (!temp->next) {
            cout << "No node exists after element " << element << "\n";
            return;
        }
        Node* del = temp->next;
        temp->next = del->next;
        cout << "Deleted node with value " << del->data << " after element " << element << "\n";
        delete del;
    }

    // Append another list
    void appendList() {
        int n, val;
        cout << "Enter number of nodes to append: ";
        cin >> n;
        if (n <= 0) {
            cout << "Nothing to append!\n";
            return;
        }
        Node* newHead = nullptr;
        Node* temp = nullptr;
        for (int i = 0; i < n; i++) {
            cout << "Enter value for node " << i + 1 << ": ";
            cin >> val;
            Node* newNode = new Node{val, nullptr};
            if (!newHead) {
                newHead = newNode;
                temp = newHead;
            } else {
                temp->next = newNode;
                temp = newNode;
            }
        }
        if (!head) {
            head = newHead;
            return;
        }
        temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newHead;
        cout << "Another list appended successfully!\n";
    }

    // Sort list
    void sortList() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        for (Node* i = head; i; i = i->next) {
            for (Node* j = i->next; j; j = j->next) {
                if (i->data > j->data) swap(i->data, j->data);
            }
        }
        cout << "List sorted successfully!\n";
    }

    // Reverse print
    void reversePrint(Node* node) {
        if (!node) return;
        reversePrint(node->next);
        cout << node->data << " -> ";
    }
    void reverse() {
        cout << "Reversed List: ";
        reversePrint(head);
        cout << "NULL\n";
    }

    // Display middle node
    void displayMiddle() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Middle node value: " << slow->data << "\n";
    }

    // Count nodes
    int countNodes() {
        int count = 0;
        for (Node* temp = head; temp; temp = temp->next) count++;
        return count;
    }

    // Find largest and smallest
    void findLargestSmallest() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        int largest = head->data;
        int smallest = head->data;
        for (Node* temp = head; temp; temp = temp->next) {
            if (temp->data > largest) largest = temp->data;
            if (temp->data < smallest) smallest = temp->data;
        }
        cout << "Largest = " << largest << ", Smallest = " << smallest << "\n";
    }
};

int main() {
    LinkedList list;
    int choice, n, val, pos, element;

    while (true) {
        cout << "\n--- Linked List Menu ---\n";
        cout << "0. Display\n1. Create a single linked list\n2. Insert at beginning\n3. Insert at end\n";
        cout << "4. Insert at ith position\n5. Insert after element\n6. Delete first node\n7. Delete last node\n";
        cout << "8. Delete at ith position\n9. Delete after element\n11. Append another list\n12. Sort list\n";
        cout << "13. Print reversed list\n14. Display middle node\n15. Count nodes\n16. Find largest & smallest\n18. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 0: list.display(); break;
            case 1: cout << "Enter number of nodes: "; cin >> n; list.createList(n); break;
            case 2: cout << "Enter value: "; cin >> val; list.insertAtBeginning(val); break;
            case 3: cout << "Enter value: "; cin >> val; list.insertAtEnd(val); break;
            case 4: cout << "Enter position and value: "; cin >> pos >> val; list.insertAtPosition(pos, val); break;
            case 5: cout << "Enter element and value: "; cin >> element >> val; list.insertAfterElement(element, val); break;
            case 6: list.deleteFirst(); break;
            case 7: list.deleteLast(); break;
            case 8: cout << "Enter position to delete: "; cin >> pos; list.deleteAtPosition(pos); break;
            case 9: cout << "Enter element after which to delete: "; cin >> element; list.deleteAfterElement(element); break;
            case 11: list.appendList(); break;
            case 12: list.sortList(); break;
            case 13: list.reverse(); break;
            case 14: list.displayMiddle(); break;
            case 15: cout << "Total nodes: " << list.countNodes() << "\n"; break;
            case 16: list.findLargestSmallest(); break;
            case 18: exit(0);
            default: cout << "Invalid choice!\n"; break;
        }
    }
}