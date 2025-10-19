// Node class
class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

// Circular Linked List class
class CircularLinkedList {
  constructor() {
    this.head = null;
  }

  // Insert node at the end
  insert(data) {
    const newNode = new Node(data);
    if (!this.head) {
      this.head = newNode;
      newNode.next = this.head; // point to itself
      return;
    }

    let temp = this.head;
    while (temp.next !== this.head) {
      temp = temp.next;
    }
    temp.next = newNode;
    newNode.next = this.head; // complete the circle
  }

  // Delete a node by value
  delete(data) {
    if (!this.head) return;

    let current = this.head;
    let prev = null;

    // If head node itself needs to be deleted
    if (current.data === data) {
      // If only one node
      if (current.next === this.head) {
        this.head = null;
        return;
      }

      // Find the last node to fix circular link
      let last = this.head;
      while (last.next !== this.head) {
        last = last.next;
      }

      last.next = this.head.next;
      this.head = this.head.next;
      return;
    }

    // Search for the node to delete
    do {
      prev = current;
      current = current.next;
      if (current.data === data) {
        prev.next = current.next;
        return;
      }
    } while (current !== this.head);
  }

  // Display all elements
  display() {
    if (!this.head) {
      console.log("List is empty");
      return;
    }

    let result = "";
    let temp = this.head;
    do {
      result += temp.data + " -> ";
      temp = temp.next;
    } while (temp !== this.head);

    console.log(result + "(back to head)");
  }
}

// Example usage
const cll = new CircularLinkedList();

cll.insert(10);
cll.insert(20);
cll.insert(30);
cll.insert(40);

console.log("Circular Linked List:");
cll.display();

console.log("Deleting 20...");
cll.delete(20);
cll.display();
