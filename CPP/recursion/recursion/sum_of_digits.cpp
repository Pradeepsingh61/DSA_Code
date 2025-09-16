#include <iostream>
using namespace std;

// Recursive function to calculate the sum of digits of a number
int sumOfDigits(int num) {
    // Base case: if num is 0, the sum is 0
    if (num == 0) {
        return 0;
    }

    // Recursive case: Add the last digit to the sum of the remaining digits
    return (num % 10) + sumOfDigits(num / 10);
}

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    // Call the recursive function and output the result
    int sum = sumOfDigits(number);
    cout << "Sum of digits: " << sum << endl;

    return 0;
}
