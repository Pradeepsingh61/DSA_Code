class Queue {
  constructor() {
    this.items = [];
  }

  // Add element to rear
  enqueue(element) {
    this.items.push(element);
  }

  // Remove element from front
  dequeue() {
    if (this.isEmpty()) return "Underflow";
    return this.items.shift();
  }

  // Get front element
  peek() {
    if (this.isEmpty()) return "No elements in Queue";
    return this.items[0];
  }

  // Check if empty
  isEmpty() {
    return this.items.length === 0;
  }

  // Size of queue
  size() {
    return this.items.length;
  }

  // Display queue
  print() {
    console.log(this.items.join(" <- "));
  }
}

// Example usage:
const q = new Queue();
q.enqueue(10);
q.enqueue(20);
q.enqueue(30);
q.print();       // Output: 10 <- 20 <- 30
console.log(q.dequeue()); // Output: 10
console.log(q.peek());    // Output: 20
console.log(q.size());    // Output: 2
console.log(q.isEmpty()); // Output: false
