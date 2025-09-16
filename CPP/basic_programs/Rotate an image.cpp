// Q. You are given an n x n 2D matrix representing an image, 
// rotate the image by 90 degrees (clockwise).
// (You have to rotate the image in-place, which means you have to modify 
// the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.)


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        //First we take the transpose of the matrix, 
        //In transpose , the i and j are interchanged , or flipped accross , i = j ;
        int n = matrix.size();
        for(int i = 0;i<n;i++){
            for(int j=i;j<n;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        
        //then we swap the columns j and n-1-j , by observation!
        for(int i=0;i<n;i++){
            for(int j=0;j<n/2;j++){
                swap(matrix[i][j],matrix[i][n-1-j]);
            }
        }
        
    }
};