#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<vector<int>> &arr, int nR, int nC)           
{
    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            printf("%d \t", arr[i][j]);     
        }
        printf("\n");
    }
}
void transpose(vector<vector<int>> &arr, int nR, int nC)        // time complexity --> O(n2)
{
    nR = arr.size();
    nC = arr[0].size();
    for (int i = 0; i < nR; i++)
    {
        for (int j = i + 1; j < nC; j++)         // i+1 manage the correct swaping of element of the 2D matrix 
        {                                           
            swap(arr[i][j], arr[j][i]);
        }
    }
}
void reverseArray(vector<int> &arr, int nC)         // time complexity --> O(n2)
{
    int left = 0;
    int right = nC - 1;
    while (left < right)
    {
        swap(arr[left], arr[right]);        // must not swap (left, right)
        left++;
        right--;
    }
}
void RotateImage(vector<vector<int>> &arr, int nR, int nC)      //total time complexity --> O(n2)
{
    if (nR == 0)
        return;
    transpose(arr, nR, nC);
    for (int i = 0; i < nR; i++)            // Reversing each col. 
    {
        reverseArray(arr[i], nC);
    }
}
int main()
{
    vector<vector<int>> arr(3, vector<int>(3));         // decalring 3 X 3 matrix
    int nC = arr[0].size();
    int nR = arr.size();
    for (int i = 0; i < nC; i++)
    {
        for (int j = 0, k = 2 * i; j < nR; j++, k++)      // assigning to the matri
        {
            arr[i][j] = i + k + 1;
        }
    }
    printf("\n printing matrix \n");
    printArray(arr, nR, nC);

    printf("\n After rotating \n");
    RotateImage(arr, nR, nC);       // rotating the image clockwise by 90 degree 
    printArray(arr, nR, nC);

    return 0;
}