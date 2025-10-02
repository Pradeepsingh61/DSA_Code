/*
 * Algorithm: Union of Two Linked Lists
 * Language: C++
 * Description: 
 * Computes the union of two given singly linked lists. The union contains all 
 * elements that are present in either list, with duplicates removed. 
 * This implementation uses a Hash Set (unordered_set) for efficient duplicate 
 * checking and insertion.
 * Time Complexity: O(N + M) // Where N and M are the lengths of the two lists
 * Space Complexity: O(N + M) // To store elements in the Hash Set
 * Author: Adi-3108
*/

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>

using namespace std;


struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(NULL) {}
};

/**
 * @brief Computes the union of two linked lists using a hash set.
 * * @param head1 Head of the first linked list.
 * @param head2 Head of the second linked list.
 * @return Node* Head of the new linked list representing the union.
 */
Node* findUnion(Node* head1, Node* head2) {
    // Hash set to store all unique elements encountered.
    unordered_set<int> unique_elements;

    // --- Phase 1: Traverse List 1 and add elements to the set ---
    Node* current = head1;
    while (current != NULL) {
        unique_elements.insert(current->data);
        current = current->next;
    }

    // --- Phase 2: Traverse List 2 and add elements to the set ---
    // The set automatically handles duplicates, so this phase guarantees all 
    // unique elements from both lists are now present.
    current = head2;
    while (current != NULL) {
        unique_elements.insert(current->data);
        current = current->next;
    }

    // --- Phase 3: Construct the result linked list from the set ---
    Node* result_head = NULL;
    Node* result_tail = NULL;

    // Note: Iterating a hash set does not preserve the original order of insertion,
    // which is generally acceptable for a set operation like Union.
    for (int val : unique_elements) {
        Node* new_node = new Node(val);
        
        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }
    }

    return result_head;
}



// Function to print the Linked List
void printList(Node* head) {
    Node* current = head;
    cout << "[";
    while (current != NULL) {
        cout << current->data;
        if (current->next != NULL) {
            cout << ", ";
        }
        current = current->next;
    }
    cout << "]";
}

// Function to Clean up the memory used by linked list
void deleteList(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
}
// Test Function
void testUnionOfLists() {
    cout << " Testing Union of Two Linked Lists " << endl;

    // List 1: 10 -> 20 -> 5 -> 15
    Node* head1 = new Node(10);
    head1->next = new Node(20);
    head1->next->next = new Node(5);
    head1->next->next->next = new Node(15);

    // List 2: 20 -> 25 -> 10 -> 30
    // Note: 20 and 10 are duplicates
    Node* head2 = new Node(20);
    head2->next = new Node(25);
    head2->next->next = new Node(10);
    head2->next->next->next = new Node(30);

    cout << "List 1: ";
    printList(head1);
    cout << endl;

    cout << "List 2: ";
    printList(head2);
    cout << endl;

    // Expected unique elements: {10, 20, 5, 15, 25, 30}. Order may vary.
    // Total unique count: 6
    Node* union_list = findUnion(head1, head2);

    cout << "Union List (Order may vary): ";
    printList(union_list);
    cout << endl;
    
    // Simple check on the size of the union (to ensure correctness)
    unordered_set<int> expected_elements = {10, 20, 5, 15, 25, 30};
    int actual_count = 0;
    Node* current = union_list;
    while (current != NULL) {
        actual_count++;
        current = current->next;
    }
    // Printin Expected elements.size() for verification purpose
    cout << "Expected unique element count: " << expected_elements.size() << endl;
    cout << "Actual unique element count: " << actual_count << endl;
    
    // Check if the counts match
    cout << "Count Check: " 
              << (actual_count == expected_elements.size() ? "PASS" : "FAIL") 
              << endl;

   
    deleteList(head1);
    deleteList(head2);
    deleteList(union_list);
}

int main() {
    testUnionOfLists();
    return 0;
}