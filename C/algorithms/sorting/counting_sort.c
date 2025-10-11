//C code to implement counting sort


//Counting Sort is a simple sorting algorithm that works by counting how many times each element appears in the input array instead of comparing them directly. First, it finds the largest value in the array to determine the range of numbers. Then, it creates a separate “count” array, where each index represents a number from the input and stores how many times that number occurs. After counting all elements, the algorithm reconstructs the sorted array by writing each number according to its frequency. This process efficiently sorts the elements in **O(n + k)** time, where *n* is the number of elements and *k* is the range of possible values. Counting Sort is best suited for sorting integers or small-range data.



//Time Complexity= O(n+max), same for all cases
//Space Complexity= O(max), same for all cases

//Drawback: Not suitable for large set of data

#include<stdio.h>
int main()
{
    //input array
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    //find max element
    int max=arr[0];
    for(int i=0;i<n;i++)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
    }
    //initialize count array
    int countArr[max+1];
    for(int i=0;i<max+1;i++)
    {
        countArr[i]=0;
    }
    //count frequencies
    for(int i=0;i<n;i++)
    {
        countArr[arr[i]]++;
    }
    //Build sorted array in ascending order
    int x=0;
    for(int i=0;i<max+1;i++)
    {
        while(countArr[i]>0)
        {
            arr[x]=i;
            countArr[i]--;
            x++;
        }
    }
    //Print the array
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}