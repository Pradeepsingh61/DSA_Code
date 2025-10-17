// reverse_LL.cpp
// 📘 Algorithm: Reverse a Linked List (Iterative + Recursive)
// Author: Poushali Mukherjee
// 🕒 Time Complexity: O(n)
// 💾 Space Complexity: O(1) for iterative, O(n) for recursive (stack space)
// Description: Reverses a singly linked list using both iterative and recursive approaches.
// Includes user input and edge case handling for Hacktoberfest DSA contribution.

#include <iostream>
using namespace std;

// Node structure
class Node
{
public:
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

// 🔁 Function to reverse a linked list iteratively
Node *reverseIterative(Node *head)
{
    Node *prev = nullptr;
    Node *curr = head;

    while (curr != nullptr)
    {
        Node *next = curr->next; // store next node
        curr->next = prev;       // reverse link
        prev = curr;             // move prev forward
        curr = next;             // move curr forward
    }
    return prev; // new head
}

// 🌀 Function to reverse a linked list recursively
Node *reverseRecursive(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    Node *newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// 🧾 Utility function to print linked list
void printList(Node *head)
{
    if (head == nullptr)
    {
        cout << "List is empty" << endl;
        return;
    }
    while (head != nullptr)
    {
        cout << head->data;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// 🧱 Function to build a linked list from user input
Node *buildFromInput()
{
    int n;
    cout << "\nEnter number of nodes: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "No nodes to create. Returning empty list.\n";
        return nullptr;
    }

    Node *head = nullptr;
    Node *tail = nullptr;
    cout << "Enter " << n << " node values: ";
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        Node *newNode = new Node(val);
        if (head == nullptr)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// 🧪 Function to demonstrate predefined edge cases
void runPredefinedTests()
{
    cout << "\n==========================" << endl;
    cout << "🚀 PREDEFINED TEST CASES" << endl;
    cout << "==========================" << endl;

    // ✅ Case 1: Normal List
    Node *list1 = new Node(1);
    list1->next = new Node(2);
    list1->next->next = new Node(3);
    list1->next->next->next = new Node(4);
    cout << "\nCase 1: Normal List (1 → 2 → 3 → 4)" << endl;
    cout << "Original: ";
    printList(list1);
    list1 = reverseIterative(list1);
    cout << "Reversed (Iterative): ";
    printList(list1);
    list1 = reverseRecursive(list1);
    cout << "Reversed Back (Recursive): ";
    printList(list1);

    // ✅ Case 2: Empty List
    cout << "\nCase 2: Empty List" << endl;
    Node *empty = nullptr;
    cout << "Original: ";
    printList(empty);
    empty = reverseIterative(empty);
    cout << "Reversed: ";
    printList(empty);

    // ✅ Case 3: Single Node
    cout << "\nCase 3: Single Node (10)" << endl;
    Node *single = new Node(10);
    cout << "Original: ";
    printList(single);
    single = reverseRecursive(single);
    cout << "Reversed (Recursive): ";
    printList(single);

    cout << "\n✅ Predefined tests executed successfully.\n";
}

// 🏁 Main function
int main()
{
    cout << "==========================" << endl;
    cout << "🔁 REVERSE LINKED LIST DEMO" << endl;
    cout << "==========================" << endl;

    // Step 1: Predefined test cases
    runPredefinedTests();

    // Step 2: User Input
    cout << "\n==========================" << endl;
    cout << "🎯 USER INPUT TEST" << endl;
    cout << "==========================" << endl;

    Node *head = buildFromInput();

    cout << "\nOriginal List: ";
    printList(head);

    // Iterative reverse
    head = reverseIterative(head);
    cout << "After Iterative Reverse: ";
    printList(head);

    // Recursive reverse (reverse back)
    head = reverseRecursive(head);
    cout << "After Recursive Reverse: ";
    printList(head);

    cout << "\n✅ Program executed successfully.\n";
    return 0;
}
