#include <iostream>
#include <map>
using namespace std;

class Node{
	public:
	int data;
	Node* next;

	Node(int data){
		this->data = data;
		this->next = NULL;
	}
};

bool detectLoop(Node* head){
	if(head == NULL)
		return false;

	map <Node*, bool> visited;
	Node* temp = head;

	while(temp != NULL){
		if(visited[temp] == true)
			return true;

		visited[temp] = true;
		temp = temp->next;
	}
	return false;
}

Node* floydCycleDetect(Node* head){
	if(head == NULL)
		return NULL;

	Node *slow = head, *fast = head;
	while(slow != NULL && fast != NULL){
		fast = fast->next;
		if(fast != NULL)
			fast = fast->next;

		slow = slow->next;

		if(slow == fast)
			return slow;
	}
	return NULL;
}

void InsertAtTail(Node* &h, Node* &t, int data){
	if(!h){
		h = new Node(data);
		t = h;
		return;
	}
	Node* temp = new Node(data);
	t->next = temp;
	t = temp;
}

Node* getStartingNode(Node* head){
	Node* intersection = floydCycleDetect(head);
	Node* slow = head;

	while(slow != intersection){
		slow = slow->next;
		intersection = intersection->next;
	}
	return slow;
}

void removeLoop(Node* head){
	Node* startingNode = getStartingNode(head);
	Node* temp = startingNode;

	while(temp->next != startingNode)
		temp = temp->next;

	temp->next = NULL;
}

void print(Node *head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main(){
	Node *head, *tail;
	head = tail = NULL;
	InsertAtTail(head, tail, 5);
	InsertAtTail(head, tail, 4);
	InsertAtTail(head, tail, 3);
	InsertAtTail(head, tail, 7);
	InsertAtTail(head, tail, 9);
	InsertAtTail(head, tail, 2);
	print(head);

	tail->next = head->next->next;
	
	if(floydCycleDetect(head) != NULL){
		cout << "Loop is present in the linked list" << endl;
	}
	else{
		cout << "No loop is present in the linked list" << endl;
	}

	cout << "Starting node: " << getStartingNode(head)->data << endl;

	removeLoop(head);
	cout << "Linked list after removal of loop: ";
	print(head);
	return 0;
}
