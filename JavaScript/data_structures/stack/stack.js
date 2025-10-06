class Stack {
  constructor() {
    this.items = [];
  }

  push(element) {
    this.items.push(element);
  }

  pop() {
    if (this.isEmpty()) {
      return "Stack is empty";
    }
    return this.items.pop();
  }

  peek() {
    if (this.isEmpty()) {
      return "Stack is empty";
    }
    return this.items[this.size() - 1];
  }

  isEmpty() {
    return this.size() === 0;
  }

  size() {
    return this.items.length;
  }

  display() {
    return `[${this.items.join(", ")}]`;
  }

  clear() {
    this.items = [];
  }
}

// Test cases
function testStack() {
  console.log("---------- Stack Test Cases ----------");

  const stack = new Stack();

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