#include <bits/stdc++.h>
using namespace std;

/*
==========================================
   Sparse Matrix - Basic Operations
   Operations: Addition, Subtraction, Multiplication
   Representation: Triplet (row, col, value)
==========================================
*/

// Structure to store a non-zero element of a sparse matrix
struct Element {
    int row;
    int col;
    int value;
};

// Class to represent a Sparse Matrix
class SparseMatrix {
private:
    int rows, cols;                  // Matrix dimensions
    vector<Element> elements;        // Store only non-zero elements

public:
    // Constructor to initialize the matrix with given rows and columns
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
    }

    // Add a non-zero element to the sparse matrix
    void addElement(int r, int c, int val) {
        if (val != 0) {
            elements.push_back({r, c, val});
        }
    }

    // Print the full matrix (converts sparse → dense for display)
    void print() const {
        vector<vector<int>> full(rows, vector<int>(cols, 0));
        for (const auto &e : elements) {
            full[e.row][e.col] = e.value;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << full[i][j] << " ";
            }
            cout << endl;
        }
    }

    // ------------------------
    // Matrix Addition
    // ------------------------
    SparseMatrix add(const SparseMatrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition.");
        }

        SparseMatrix result(rows, cols);
        int i = 0, j = 0;

        while (i < elements.size() && j < other.elements.size()) {
            int pos1 = elements[i].row * cols + elements[i].col;
            int pos2 = other.elements[j].row * cols + other.elements[j].col;

            if (pos1 < pos2) {
                result.addElement(elements[i].row, elements[i].col, elements[i].value);
                i++;
            } else if (pos1 > pos2) {
                result.addElement(other.elements[j].row, other.elements[j].col, other.elements[j].value);
                j++;
            } else {
                int sum = elements[i].value + other.elements[j].value;
                if (sum != 0) {
                    result.addElement(elements[i].row, elements[i].col, sum);
                }
                i++; j++;
            }
        }

        while (i < elements.size()) {
            result.addElement(elements[i].row, elements[i].col, elements[i].value);
            i++;
        }
        while (j < other.elements.size()) {
            result.addElement(other.elements[j].row, other.elements[j].col, other.elements[j].value);
            j++;
        }

        return result;
    }

    // ------------------------
    // Matrix Subtraction
    // ------------------------
    SparseMatrix subtract(const SparseMatrix &other) const {
        SparseMatrix negOther = other;
        // Negate all values in the second matrix
        for (auto &e : negOther.elements) {
            e.value = -e.value;
        }
        return add(negOther);
    }

    // ------------------------
    // Matrix Multiplication (Naive)
    // ------------------------
    SparseMatrix multiply(const SparseMatrix &other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions are incompatible for multiplication.");
        }

        SparseMatrix result(rows, other.cols);

        // Convert both matrices to full form for easier multiplication
        vector<vector<int>> full1(rows, vector<int>(cols, 0));
        vector<vector<int>> full2(other.rows, vector<int>(other.cols, 0));

        for (const auto &e : elements)
            full1[e.row][e.col] = e.value;

        for (const auto &e : other.elements)
            full2[e.row][e.col] = e.value;

        // Multiply
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += full1[i][k] * full2[k][j];
                }
                if (sum != 0) {
                    result.addElement(i, j, sum);
                }
            }
        }

        return result;
    }
};

// ------------------------
// Main Function - Example Usage
// ------------------------
int main() {
    // Define Matrix A
    SparseMatrix A(3, 3);
    A.addElement(0, 0, 1);
    A.addElement(0, 2, 2);
    A.addElement(1, 1, 3);

    // Define Matrix B
    SparseMatrix B(3, 3);
    B.addElement(0, 0, 4);
    B.addElement(0, 2, 5);
    B.addElement(2, 2, 6);

    cout << "Matrix A:\n";
    A.print();

    cout << "\nMatrix B:\n";
    B.print();

    // Addition
    cout << "\nA + B:\n";
    SparseMatrix C = A.add(B);
    C.print();

    // Subtraction
    cout << "\nA - B:\n";
    SparseMatrix D = A.subtract(B);
    D.print();

    // Multiplication
    cout << "\nA * B:\n";
    SparseMatrix E = A.multiply(B);
    E.print();

    return 0;
}
