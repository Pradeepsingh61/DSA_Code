#include <bits/stdc++.h> 
using namespace std;
class CircularQueue{
	public:
    int* arr;
    int front, rear;
    int size;

    CircularQueue(int n){
        size = n;
        arr = new int[size];
        front = rear = -1;
    }

    bool enqueue(int value){
        if((rear == size-1 && front == 0) || (rear == (front-1)%(size-1))){
            return false;
        }
        else if(front == -1){
            front = rear = 0;
        }
        else if(front != 0 && rear == size-1){
            rear = 0;
        }
        else{
            rear++;
        }
        arr[rear] = value;
        return true;
    }

    int dequeue(){
        if(front == -1){
            return -1;
        }
        
        int temp = arr[front];
        arr[front] = -1;
        if(front == rear){
            front = rear = -1;
        }
        else if(front == size-1){
            front = 0;
        }
        else{
            front++;
        }
        return temp;
    }
};

int main(){
	CircularQueue q(5);
	q.enqueue(5);
	q.enqueue(16);
	q.enqueue(8);
	q.enqueue(27);

	if(q.front == -1)
		cout << "Queue is empty" << endl;
	else
		cout << "Queue is not empty" << endl;

	cout << "Top element of the queue: " << q.dequeue() << endl;
	int ans = q.dequeue();
	ans = q.dequeue();
	ans = q.dequeue();
	ans = q.dequeue();

	if(q.front == -1)
		cout << "Queue is empty" << endl;
	else
		cout << "Queue is not empty" << endl;

	return 0;
}
