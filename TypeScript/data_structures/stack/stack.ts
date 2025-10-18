/* Stack

Description: A stack is a linear data structure that follows the Last In, First Out (LIFO) principle, meaning the last element added to the stack will be the first one to be removed. Common operations include push (add element), pop (remove top element), and peek (view top element).

Time Complexity: O(1)
Space Complexity: O(1)
*/

class Stack<T> {
  private items: T[];

  constructor() {
    this.items = [];
  }

  push(element: T): void {
    this.items.push(element);
  }

  pop(): T | string {
    if (this.isEmpty()) {
      return "Stack is empty";
    }
    return this.items.pop()!;
  }

  peek(): T | string {
    if (this.isEmpty()) {
      return "Stack is empty";
    }
    return this.items[this.size() - 1];
  }

  isEmpty(): boolean {
    return this.size() === 0;
  }

  size(): number {
    return this.items.length;
  }

  display(): string {
    return `[${this.items.join(", ")}]`;
  }

  clear(): void {
    this.items = [];
  }
}

// Test cases
function testStack(): void {
  console.log("---------- Stack Test Cases ----------");

  const stack = new Stack<number>();

  console.log("Test 1 - isEmpty():", stack.isEmpty());

  stack.push(10);
  stack.push(20);
  stack.push(30);

  console.log("Test 2 - After pushing 10, 20, 30:", stack.display());

  console.log("Test 3 - Size:", stack.size());

  console.log("Test 4 - Peek:", stack.peek());

  console.log("Test 5 - Pop:", stack.pop());

  console.log("Test 5 - After pop:", stack.display());

  console.log("Test 6 - isEmpty() after operations:", stack.isEmpty());

  stack.pop();
  stack.pop();

  console.log("Test 7 - After popping all:", stack.display());

  console.log("Test 8 - Pop from empty:", stack.pop());

  console.log("Test 9 - Peek empty:", stack.peek());

  stack.push(1);
  stack.push(2);

  stack.clear();

  console.log("Test 10 - After clear:", stack.isEmpty());
}

testStack();

export default Stack;
