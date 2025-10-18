#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* front;
    Node* rear;
    int size;

public:
    Deque() : front(nullptr), rear(nullptr), size(0) {}

    ~Deque() {
        while (size > 0) {
            deleteFront();
        }
    }

    void insertFront(T value) {
        Node* newNode = new Node{value, nullptr, front};
        if (front) {
            front->prev = newNode;
        }
        front = newNode;
        if (!rear) {
            rear = front;
        }
        ++size;
    }

    void insertRear(T value) {
        Node* newNode = new Node{value, rear, nullptr};
        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = rear;
        }
        ++size;
    }

    void deleteFront() {
        if (front) {
            Node* temp = front;
            front = front->next;
            if (front) {
                front->prev = nullptr;
            } else {
                rear = nullptr;
            }
            delete temp;
            --size;
        } else {
            throw std::out_of_range("Deque is empty");
        }
    }

    void deleteRear() {
        if (rear) {
            Node* temp = rear;
            rear = rear->prev;
            if (rear) {
                rear->next = nullptr;
            } else {
                front = nullptr;
            }
            delete temp;
            --size;
        } else {
            throw std::out_of_range("Deque is empty");
        }
    }

    T getFront() const {
        if (front) {
            return front->data;
        } else {
            throw std::out_of_range("Deque is empty");
        }
    }

    T getRear() const {
        if (rear) {
            return rear->data;
        } else {
            throw std::out_of_range("Deque is empty");
        }
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    Deque<int> dq;
    dq.insertFront(10);
    dq.insertRear(20);
    dq.insertFront(5);

    std::cout << "Front: " << dq.getFront() << std::endl;
    std::cout << "Rear: " << dq.getRear() << std::endl;
    std::cout << "Size: " << dq.getSize() << std::endl;

    dq.deleteFront();
    dq.deleteRear();

    std::cout << "Size after deletions: " << dq.getSize() << std::endl;

    return 0;
}
