#include <iostream>
#include <vector>
#include <stdexcept>

class Stack {
private:
    std::vector<int> elements; // Vector to store stack elements

public:
    // Push an element onto the stack
    void push(int value) {
        elements.push_back(value); // Add value to the end of the vector
    }

    // Remove the top element from the stack
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty"); // Throw error if stack is empty
        }
        elements.pop_back(); // Remove the last element from the vector
    }

    // Get the top element of the stack
    int top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty"); // Throw error if stack is empty
        }
        return elements.back(); // Return the last element of the vector
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return elements.empty(); // Return true if vector is empty
    }

    // Get the size of the stack
    size_t size() const {
        return elements.size(); // Return the number of elements in the vector
    }
};

class Queue {
private:
    std::vector<int> elements; // Vector to store queue elements

public:
    // Add an element to the back of the queue
    void enqueue(int value) {
        elements.push_back(value); // Add value to the end of the vector
    }

    // Remove the front element from the queue
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty"); // Throw error if queue is empty
        }
        elements.erase(elements.begin()); // Remove the first element from the vector
    }

    // Get the front element of the queue
    int front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty"); // Throw error if queue is empty
        }
        return elements.front(); // Return the first element of the vector
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return elements.empty(); // Return true if vector is empty
    }

    // Get the size of the queue
    size_t size() const {
        return elements.size(); // Return the number of elements in the vector
    }
};

int main() {
    Stack stack; // Create a stack instance
    Queue queue; // Create a queue instance

    // Stack operations
    stack.push(1); // Push 1 onto the stack
    stack.push(2); // Push 2 onto the stack
    std::cout << "Top of stack: " << stack.top() << std::endl; // Get top element
    stack.pop(); // Remove top element
    std::cout << "Top of stack after pop: " << stack.top() << std::endl; // Get new top element

    // Queue operations
    queue.enqueue(1); // Enqueue 1 into the queue
    queue.enqueue(2); // Enqueue 2 into the queue
    std::cout << "Front of queue: " << queue.front() << std::endl; // Get front element
    queue.dequeue(); // Dequeue front element
    std::cout << "Front of queue after dequeue: " << queue.front() << std::endl; // Get new front element

    return 0; // End of program
}