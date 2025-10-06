#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *arr;
    int front;
    int rear;
    int size;
    int capacity;

public:
    CircularQueue(int capacity) {
        this->capacity = capacity;
        arr = new int[capacity];
        front = rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int value = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        size--;
        return value;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

    int getSize() {
        return size;
    }
};

int main() {
    CircularQueue q(5);
    
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    
    q.enqueue(6);
    q.enqueue(7);
    
    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
    }
    
    return 0;
}