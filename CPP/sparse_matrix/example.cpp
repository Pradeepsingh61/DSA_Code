#include <iostream>
#include <vector>
using namespace std;

// Simplified version for demonstration
struct Element {
    int row, col, value;
    Element(int r, int c, int v) : row(r), col(c), value(v) {}
};

class SparseMatrix {
private:
    vector<Element> elements;
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}
    
    void addElement(int row, int col, int value) {
        if (value != 0) {
            elements.push_back(Element(row, col, value));
        }
    }
    
    void display() const {
        cout << "Sparse Matrix (" << rows << "x" << cols << "):\n";
        cout << "Row\tCol\tValue\n";
        for (const auto& elem : elements) {
            cout << elem.row << "\t" << elem.col << "\t" << elem.value << endl;
        }
        cout << endl;
    }
    
    void displayFull() const {
        cout << "Full Matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int value = 0;
                for (const auto& elem : elements) {
                    if (elem.row == i && elem.col == j) {
                        value = elem.value;
                        break;
                    }
                }
                cout << value << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== SPARSE MATRIX EXAMPLE ===\n\n";
    
    // Create first matrix: 3x3
    // 1  0  2
    // 0  0  0  
    // 3  0  4
    SparseMatrix matrix1(3, 3);
    matrix1.addElement(0, 0, 1);
    matrix1.addElement(0, 2, 2);
    matrix1.addElement(2, 0, 3);
    matrix1.addElement(2, 2, 4);
    
    cout << "Matrix 1:\n";
    matrix1.display();
    matrix1.displayFull();
    
    // Create second matrix: 3x3
    // 0  5  0
    // 6  0  7
    // 0  8  0
    SparseMatrix matrix2(3, 3);
    matrix2.addElement(0, 1, 5);
    matrix2.addElement(1, 0, 6);
    matrix2.addElement(1, 2, 7);
    matrix2.addElement(2, 1, 8);
    
    cout << "Matrix 2:\n";
    matrix2.display();
    matrix2.displayFull();
    
    cout << "For complete operations (addition, multiplication, etc.),\n";
    cout << "please run the main program: sparse_matrix_operations.cpp\n";
    
    return 0;
}