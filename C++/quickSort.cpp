#include <iostream>
using namespace std;



void swap(int*a,int*b){
    int t=*a;
    *a=*b;
    *b=t;
}

  
  int partition(int arr[], int low, int high) {
      int pivot=arr[high];
      int i=(low-1);
  
 
for(int j=low;j<=high-1;j++){
    if(arr[j]<=pivot){
        i++;
        swap(&arr[i],&arr[j]);
    }
}
swap(&arr[i+1],&arr[high]);
return (i+1);
}

void quickSort(int arr[], int low, int high) {
    if(low<high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

void printArray(int arr[], int size) {
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int arr[5];
    int n=sizeof(arr);
    cout<<"Enter the elements of array"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    quickSort(arr,0,n-1);
    cout<<"Sorted array: ";
    printArray(arr,n);
    return 0;
}
