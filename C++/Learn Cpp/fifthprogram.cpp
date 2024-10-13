#include<iostream>
#include<string>
using namespace std;

class bank_customer
{
    public :
        string name, customer_id;
        int age;
        double balance;
        void input()
        {
            cout << "Write your bank details :" << endl << endl;
            cout << "NAME : ";
            cin >> name;
            getline(cin, name);
            cout << "AGE : ";
            cin >> age;
            cout << "CUSTOMER ID : ";
            cin >> customer_id;
            cout << "BALANCE : ";
            cin >> balance;
        }
};
void display(const bank_customer& BankCustomer)
{
    cout << "Name : " << BankCustomer.name << endl;
    cout << "Age : " << BankCustomer.age << endl;
    cout << "Customer ID : " << BankCustomer.customer_id << endl;
    cout << "Balance : " << BankCustomer.balance << endl;
}


int main()
{
    bank_customer BankCustomer;
    BankCustomer.input();
    display(BankCustomer);
    return 0;
}