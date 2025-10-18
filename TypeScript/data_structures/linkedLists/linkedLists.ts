class Node<T> {
  value: T;
  next: Node<T> | null = null;
  constructor(value: T) {
    this.value = value;
  }
}

class LinkedList<T> {
  private head: Node<T> | null = null;
  private length: number = 0;

  append(value: T): void {
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

  prepend(value: T): void {
    const newNode = new Node(value);
    newNode.next = this.head;
    this.head = newNode;
    this.length++;
  }

  insertAt(index: number, value: T): void {
    if (index < 0 || index > this.length) return console.log("Invalid index");
    if (index === 0) return this.prepend(value);
    if (index === this.length) return this.append(value);

    const newNode = new Node(value);
    let current = this.head;
    let prev: Node<T> | null = null;
    let i = 0;
    while (i < index && current) {
      prev = current;
      current = current.next;
      i++;
    }
    if (prev) {
      newNode.next = current;
      prev.next = newNode;
      this.length++;
    }
  }

  remove(value: T): void {
    if (!this.head) return;

    if (this.head.value === value) {
      this.head = this.head.next;
      this.length--;
      return;
    }

    let current = this.head;
    let prev: Node<T> | null = null;
    while (current && current.value !== value) {
      prev = current;
      current = current.next;
    }

    if (current && prev) {
      prev.next = current.next;
      this.length--;
    }
  }

  search(value: T): number {
    let current = this.head;
    let index = 0;
    while (current) {
      if (current.value === value) return index;
      current = current.next;
      index++;
    }
    return -1;
  }

  printList(): void {
    let current = this.head;
    let result = "";
    while (current) {
      result += current.value + " -> ";
      current = current.next;
    }
    console.log(result + "null");
  }

  size(): number {
    return this.length;
  }

  isEmpty(): boolean {
    return this.length === 0;
  }
}

// Example usage:
const list = new LinkedList<number>();
list.append(1);
list.append(2);
list.append(3);
list.prepend(0);
list.printList(); // Output: 0 -> 1 -> 2 -> 3 -> null
console.log(list.search(2)); // Output: 2
list.remove(1);
list.printList(); // Output: 0 -> 2 -> 3 -> null
console.log(list.size());    // Output: 3
