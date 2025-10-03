/*
* Algorithm: [Binary Search]
 * Description: [Binary search is an efficient algorithm used to find the position of a target value within a sorted array or list. It works on the principle of repeatedly dividing the search interval in half.]
 * Time Complexity :
 *     Best Case : O(1)  // when given array is already sorted.
 *     Average Case : O(log n) //when given array is in random order
 *     Worst Case : O(log n) // when given array is in reverse order
 * Space Complexity:
 *   Worst : 0(1)
 * Author: [Kaustubh Udavant]
 */

#include <stdio.h>
#define SIZE 10
int BinarySearch(int [],int);
int main()
{
    int a[SIZE]={3,5,9,11,15,17,22,25,37,68},key,pos;
    printf("Enter the Search Key\n");
    scanf("%d",&key);
    pos=BinarySearch(a,key);
    if(pos==-1)
    printf("The search key is not in the array\n");
    else
    printf("The search key %d is at location %d\n",key,pos);
    return 0;    
    }

    int BinarySearch (int A[],int skey)
    {
    int low=0,high=SIZE-1,middle;
    while (low <=high){
         middle=(low+high)/2;
         if(skey==A[middle])
           return middle;
         else if(skey <A[middle])
                  high=middle-1;
              else 
                 low=middle+1;
           }
       return -1; 
       }