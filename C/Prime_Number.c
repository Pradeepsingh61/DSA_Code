#include <stdio.h>
#include <math.h>
int isPrime(int num) {
   if (num <= 1) return 0;
   if (num == 2) return 1;
   if (num % 2 == 0) return 0;
   for (int i = 3; i <= sqrt(num); i += 2) {
       if (num % i == 0) return 0;
   }
   return 1;
}
int main() {
   int num = 23;
   if (isPrime(num))
       printf("%d is prime\n", num);
   else
       printf("%d is not prime\n", num);
   return 0;
}
