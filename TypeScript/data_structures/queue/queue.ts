class Queue<T> {
  private items: T[] = [];

  // Add element to rear
  enqueue(element: T): void {
    this.items.push(element);
  }

  // Remove element from front
  dequeue(): T | string {
    if (this.isEmpty()) return "Underflow";
    return this.items.shift()!;
  }

  // Get front element
  peek(): T | string {
    if (this.isEmpty()) return "No elements in Queue";
    return this.items[0];
  }

  // Check if empty
  isEmpty(): boolean {
    return this.items.length === 0;
  }

  // Size of queue
  size(): number {
    return this.items.length;
  }

  // Display queue
  print(): void {
    console.log(this.items.join(" <- "));
  }
}

// Example usage:
const q = new Queue<number>();
q.enqueue(5);
q.enqueue(15);
q.enqueue(25);
q.print();       // Output: 5 <- 15 <- 25
console.log(q.dequeue()); // Output: 5
console.log(q.peek());    // Output: 15
console.log(q.size());    // Output: 2
console.log(q.isEmpty()); // Output: false
