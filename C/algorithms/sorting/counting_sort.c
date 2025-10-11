//C code to implement counting sort
//Time Complexity= O(n+max), same for all cases
//Space Complexity= O(max), same for all cases
//Not suitable for large set of data
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