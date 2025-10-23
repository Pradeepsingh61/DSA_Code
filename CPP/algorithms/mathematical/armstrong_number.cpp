/*
Armstrong number: An Armstrong number is a number that is equal to the sum of its own 
digits, each raised to the power of the total number of digits. 

Author = Anuj Parwal
*/
#include<bits/stdc++.h>
using namespace std;
//Simple power function which is to be used later:
long long int power(int base, int exp) {
    long long int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}
/*The following function checks whether or not the number provided is armstrong number or 
not. If the number is an armstrong number, it will return 1 but if it isn't, 0 will be returned.
*/
int armstrong(long long int n){
    int num_dig = 0;
    long long int num_temp1 = n;
    long long int num_temp2 = n;
    for (int i = 0; i < 18; i++){
        num_temp1/=10;
        num_dig++;
        if(num_temp1==0){
            break;
        }
    }
    /*Initialising sum, and then adding digits to the power of the number of digits to 
    it*/
    long long int sum = 0;
    for (int i = 0; i < 18; i++){
        int j = num_temp2%10;
        sum += power(j, num_dig); 
        num_temp2/=10;
        if(num_temp2==0){
            break;
        }
    }
    //if it is an armstrong number, n=sum
    if(sum==n){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    //Initialising and taking input of number:
    int n;
    cout << "Enter your number here: ";
    cin >> n;
    int checker = armstrong(n);
    if(checker==0){
        cout << "No, it is not an armstrong number.";
    }
    else{
        cout << "Yes, it is an Armstrong number.";
    }
    return 0;
}
/*Space Complexity = O(1)
Time Complexity = O(n)*/