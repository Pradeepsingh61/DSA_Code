#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass(int val) : data(val) 
    {
        cout << "Dynamic constructor called." << endl;
    }

    void display()
    {
        cout << "Data: " << data << endl;
    }

private:
    int data;
};

int main() 
{
    MyClass* objPtr = new MyClass(42);

    objPtr->display();

    delete objPtr;

    return 0;
}