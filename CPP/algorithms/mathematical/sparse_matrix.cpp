#include <iostream>
#include <vector>

using namespace std;

class SparseMatrix {
private:
    vector<int> values;    // Non-zero values
    vector<int> colIndex;  // Column indices of non-zero values
    vector<int> rowPtr;    // Row pointer

    int rows, cols;

public:
    SparseMatrix(int r, int c, vector<vector<int>>& matrix) {
        rows = r;
        cols = c;
        rowPtr.push_back(0);

        for (int i = 0; i < rows; i++) {
            int count = 0;
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] != 0) {
                    values.push_back(matrix[i][j]);
                    colIndex.push_back(j);
                    count++;
                }
            }
            rowPtr.push_back(rowPtr.back() + count);
        }
    }

    void display() {
        cout << "Values: ";
        for (int val : values) cout << val << " ";
        cout << "\nColumn Indices: ";
        for (int idx : colIndex) cout << idx << " ";
        cout << "\nRow Pointer: ";
        for (int ptr : rowPtr) cout << ptr << " ";
        cout << endl;
    }

    int getValue(int r, int c) {
        for (int i = rowPtr[r]; i < rowPtr[r + 1]; i++) {
            if (colIndex[i] == c) return values[i];
        }
        return 0; // Element is zero
    }
};

int main() {
    vector<vector<int>> matrix = {
        {0, 0, 3, 0},
        {22, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 17, 0, 0}
    };

    SparseMatrix sm(4, 4, matrix);
    sm.display();

    cout << "Element at (1,0): " << sm.getValue(1,0) << endl;
    cout << "Element at (2,2): " << sm.getValue(2,2) << endl;

    return 0;
}
