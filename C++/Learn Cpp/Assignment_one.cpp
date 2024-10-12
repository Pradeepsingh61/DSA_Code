#include<iostream>
using namespace std;

class firstprogram
{
    public:
    int largest(int a, int b, int c)
    {
        if(a > b && a > c)
            return a;
        else if(b > a && b > c)
            return b;
        else
            return c;
    }
};

int main()
{
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    firstprogram obj;
    int result = obj.largest(a, b, c);

    cout << "The largest number is: " << result << endl;

    return 0;
}