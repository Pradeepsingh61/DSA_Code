#include<stdio.h>
#include<limits.h>

int main(){

    int m, q, result = 0, count = CHAR_BIT * sizeof(int);
    
    printf("Enter the Multiplicand: ");
    scanf("%d", &m);

    printf("Enter the Multiplier: ");
    scanf("%d", &q);

    int a = m, q_temp = q;

    while (count > 0){
        if((q_temp & 1) == 1){
            result += a;
        }
        a <<= 1;
        q_temp >>= 1;
        count--;
    }

    printf("The Multiplication of %d and %d is: %d", m, q, result);
    

    return 0;
}