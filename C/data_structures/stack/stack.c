// Stack implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000
int stack[MAX];

// Initialize top of stack
int top = -1;

// Function to add an item to stack
void push(int data) {
  if (top == MAX - 1) {
    printf("Stack Overflow\n");
    return;
  }
  stack[++top] = data;
}

// Function to remove an item from stack
int pop() {
  if (top == -1) {
    printf("Stack Underflow\n");
    return INT_MIN;
  }
  return stack[top--];
}

// Function to return the top from stack without removing it
int peek() {
  if (top == -1) {
    printf("Stack is empty\n");
    return INT_MIN;
  }
  return stack[top];
}

// helper functions
int isEmpty() { return top == -1; }
int isFull() { return top == MAX - 1; }
int size() { return top + 1; }

// Function to display stack elements
void display() {
  if (top == -1) {
    printf("Stack is empty\n");
    return;
  }
  for (int i = top; i >= 0; i--) {
    printf("%d ", stack[i]);
  }
  printf("\n");
}

/**
 * Main function to demonstrate stack operations
*/
int main() {
  push(10); // Push 10 onto the stack
  push(20); // Push 20 onto the stack
  push(30); // Push 30 onto the stack
  display(); // Display stack elements
  printf("Top element is %d\n", peek()); // Peek at the top element
  printf("Stack size is %d\n", size()); // Get the size of the stack
  printf("Popped element is %d\n", pop()); // Pop the top element
  display(); // Display stack elements after pop
  return 0;
}