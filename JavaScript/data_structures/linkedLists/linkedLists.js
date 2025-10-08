// Node structure
class Node {
  constructor(value) {
    this.value = value;
    this.next = null;
  }
}

// Linked List class
class LinkedList {
  constructor() {
    this.head = null;
    this.length = 0;
  }

  // Add to end
  append(value) {
    const newNode = new Node(value);
    if (!this.head) {
      this.head = newNode;
    } else {
      let current = this.head;
      while (current.next) {
        current = current.next;
      }
      current.next = newNode;
    }
    this.length++;
  }

  // Add to beginning
  prepend(value) {
    const newNode = new Node(value);
    newNode.next = this.head;
    this.head = newNode;
    this.length++;
  }

  // Insert at index
  insertAt(index, value) {
    if (index < 0 || index > this.length) return console.log("Invalid index");
    if (index === 0) return this.prepend(value);
    if (index === this.length) return this.append(value);

    const newNode = new Node(value);
    let current = this.head;
    let prev = null;
    let i = 0;
    while (i < index) {
      prev = current;
      current = current.next;
      i++;
    }
    newNode.next = current;
    prev.next = newNode;
    this.length++;
  }

  // Remove by value
  remove(value) {
    if (!this.head) return;

    if (this.head.value === value) {
      this.head = this.head.next;
      this.length--;
      return;
    }

    let current = this.head;
    let prev = null;
    while (current && current.value !== value) {
      prev = current;
      current = current.next;
    }

    if (current) {
      prev.next = current.next;
      this.length--;
    }
  }

  // Remove at index
  removeAt(index) {
    if (index < 0 || index >= this.length) return console.log("Invalid index");

    if (index === 0) {
      this.head = this.head.next;
    } else {
      let current = this.head;
      let prev = null;
      let i = 0;
      while (i < index) {
        prev = current;
        current = current.next;
        i++;
      }
      prev.next = current.next;
    }
    this.length--;
  }

  // Search for value
  search(value) {
    let current = this.head;
    let index = 0;
    while (current) {
      if (current.value === value) return index;
      current = current.next;
      index++;
    }
    return -1; // Not found
  }

  // Print all nodes
  printList() {
    let current = this.head;
    let result = "";
    while (current) {
      result += current.value + " -> ";
      current = current.next;
    }
    console.log(result + "null");
  }

  // Get size
  size() {
    return this.length;
  }

  // Check if empty
  isEmpty() {
    return this.length === 0;
  }
}

// Example usage
const list = new LinkedList();
list.append(10);
list.append(20);
list.prepend(5);
list.insertAt(1, 15);
list.printList(); // Output: 5 -> 15 -> 10 -> 20 -> null
list.remove(15);
list.printList(); // Output: 5 -> 10 -> 20 -> null
console.log(list.search(10)); // Output: 1
console.log(list.size());     // Output: 3
console.log(list.isEmpty());  // Output: false
