#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure to represent a sparse matrix element
struct Element {
    int row, col, value;
    
    Element(int r = 0, int c = 0, int v = 0) : row(r), col(c), value(v) {}
};

class SparseMatrix {
private:
    vector<Element> elements;
    int rows, cols;

public:
    SparseMatrix(int r = 0, int c = 0) : rows(r), cols(c) {}
    
    // Add an element to the sparse matrix
    void addElement(int row, int col, int value) {
        if (value != 0) {
            elements.push_back(Element(row, col, value));
        }
    }
    
    // Get dimensions
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getSize() const { return elements.size(); }
    
    // Get element at specific position
    int getElement(int row, int col) const {
        for (const auto& elem : elements) {
            if (elem.row == row && elem.col == col) {
                return elem.value;
            }
        }
        return 0;
    }
    
    // Get all elements
    const vector<Element>& getElements() const {
        return elements;
    }
    
    // Display sparse matrix in triplet form
    void displayTriplet() const {
        cout << "\nSparse Matrix (Row, Col, Value):\n";
        cout << "Dimensions: " << rows << " x " << cols << endl;
        cout << "Non-zero elements: " << elements.size() << endl;
        cout << "Row\tCol\tValue\n";
        cout << "---\t---\t-----\n";
        for (const auto& elem : elements) {
            cout << elem.row << "\t" << elem.col << "\t" << elem.value << endl;
        }
    }
    
    // Display matrix in full form
    void displayFull() const {
        cout << "\nFull Matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(4) << getElement(i, j) << " ";
            }
            cout << endl;
        }
    }
    
    // Addition of two sparse matrices
    SparseMatrix add(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Matrix dimensions don't match for addition!\n";
            return SparseMatrix();
        }
        
        SparseMatrix result(rows, cols);
        
        // Add all elements from first matrix
        for (const auto& elem : elements) {
            result.addElement(elem.row, elem.col, elem.value);
        }
        
        // Add elements from second matrix
        for (const auto& elem : other.elements) {
            int currentValue = result.getElement(elem.row, elem.col);
            int newValue = currentValue + elem.value;
            
            // Remove existing element if present
            result.elements.erase(
                remove_if(result.elements.begin(), result.elements.end(),
                    [elem](const Element& e) {
                        return e.row == elem.row && e.col == elem.col;
                    }),
                result.elements.end()
            );
            
            // Add new element if non-zero
            if (newValue != 0) {
                result.addElement(elem.row, elem.col, newValue);
            }
        }
        
        return result;
    }
    
    // Subtraction of two sparse matrices
    SparseMatrix subtract(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Matrix dimensions don't match for subtraction!\n";
            return SparseMatrix();
        }
        
        SparseMatrix result(rows, cols);
        
        // Add all elements from first matrix
        for (const auto& elem : elements) {
            result.addElement(elem.row, elem.col, elem.value);
        }
        
        // Subtract elements from second matrix
        for (const auto& elem : other.elements) {
            int currentValue = result.getElement(elem.row, elem.col);
            int newValue = currentValue - elem.value;
            
            // Remove existing element if present
            result.elements.erase(
                remove_if(result.elements.begin(), result.elements.end(),
                    [elem](const Element& e) {
                        return e.row == elem.row && e.col == elem.col;
                    }),
                result.elements.end()
            );
            
            // Add new element if non-zero
            if (newValue != 0) {
                result.addElement(elem.row, elem.col, newValue);
            }
        }
        
        return result;
    }
    
    // Multiplication of two sparse matrices
    SparseMatrix multiply(const SparseMatrix& other) const {
        if (cols != other.rows) {
            cout << "Error: Matrix dimensions don't match for multiplication!\n";
            cout << "First matrix cols: " << cols << ", Second matrix rows: " << other.rows << endl;
            return SparseMatrix();
        }
        
        SparseMatrix result(rows, other.cols);
        
        // For each non-zero element in first matrix
        for (const auto& elem1 : elements) {
            // For each non-zero element in second matrix
            for (const auto& elem2 : other.elements) {
                // If column of first element matches row of second element
                if (elem1.col == elem2.row) {
                    int product = elem1.value * elem2.value;
                    int currentValue = result.getElement(elem1.row, elem2.col);
                    int newValue = currentValue + product;
                    
                    // Remove existing element if present
                    result.elements.erase(
                        remove_if(result.elements.begin(), result.elements.end(),
                            [elem1, elem2](const Element& e) {
                                return e.row == elem1.row && e.col == elem2.col;
                            }),
                        result.elements.end()
                    );
                    
                    // Add new element if non-zero
                    if (newValue != 0) {
                        result.addElement(elem1.row, elem2.col, newValue);
                    }
                }
            }
        }
        
        return result;
    }
    
    // Element-wise division (note: this is not standard matrix division)
    SparseMatrix divide(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Matrix dimensions don't match for element-wise division!\n";
            return SparseMatrix();
        }
        
        SparseMatrix result(rows, cols);
        
        // For each element in the first matrix
        for (const auto& elem : elements) {
            int otherValue = other.getElement(elem.row, elem.col);
            if (otherValue == 0) {
                cout << "Warning: Division by zero at position (" << elem.row << ", " << elem.col << ")\n";
                continue;
            }
            
            int quotient = elem.value / otherValue;
            if (quotient != 0) {
                result.addElement(elem.row, elem.col, quotient);
            }
        }
        
        return result;
    }
    
    // Transpose of sparse matrix
    SparseMatrix transpose() const {
        SparseMatrix result(cols, rows);
        
        for (const auto& elem : elements) {
            result.addElement(elem.col, elem.row, elem.value);
        }
        
        return result;
    }
};

// Function to input a sparse matrix from user
SparseMatrix inputSparseMatrix() {
    int rows, cols, numElements;
    
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> numElements;
    
    SparseMatrix matrix(rows, cols);
    
    cout << "Enter the non-zero elements (row col value):\n";
    for (int i = 0; i < numElements; i++) {
        int row, col, value;
        cout << "Element " << (i + 1) << ": ";
        cin >> row >> col >> value;
        
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            matrix.addElement(row, col, value);
        } else {
            cout << "Invalid indices! Element ignored.\n";
            i--; // Retry this element
        }
    }
    
    return matrix;
}

// Function to display menu
void displayMenu() {
    cout << "\n=== SPARSE MATRIX OPERATIONS ===\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Element-wise Division\n";
    cout << "5. Transpose\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    
    cout << "SPARSE MATRIX OPERATIONS PROGRAM\n";
    cout << "================================\n";
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\n--- MATRIX ADDITION ---\n";
                cout << "Enter first matrix:\n";
                SparseMatrix matrix1 = inputSparseMatrix();
                
                cout << "\nEnter second matrix:\n";
                SparseMatrix matrix2 = inputSparseMatrix();
                
                SparseMatrix result = matrix1.add(matrix2);
                
                cout << "\nFirst Matrix:";
                matrix1.displayTriplet();
                matrix1.displayFull();
                
                cout << "\nSecond Matrix:";
                matrix2.displayTriplet();
                matrix2.displayFull();
                
                cout << "\nResult (Addition):";
                result.displayTriplet();
                result.displayFull();
                break;
            }
            
            case 2: {
                cout << "\n--- MATRIX SUBTRACTION ---\n";
                cout << "Enter first matrix:\n";
                SparseMatrix matrix1 = inputSparseMatrix();
                
                cout << "\nEnter second matrix:\n";
                SparseMatrix matrix2 = inputSparseMatrix();
                
                SparseMatrix result = matrix1.subtract(matrix2);
                
                cout << "\nFirst Matrix:";
                matrix1.displayTriplet();
                matrix1.displayFull();
                
                cout << "\nSecond Matrix:";
                matrix2.displayTriplet();
                matrix2.displayFull();
                
                cout << "\nResult (Subtraction):";
                result.displayTriplet();
                result.displayFull();
                break;
            }
            
            case 3: {
                cout << "\n--- MATRIX MULTIPLICATION ---\n";
                cout << "Enter first matrix:\n";
                SparseMatrix matrix1 = inputSparseMatrix();
                
                cout << "\nEnter second matrix:\n";
                SparseMatrix matrix2 = inputSparseMatrix();
                
                SparseMatrix result = matrix1.multiply(matrix2);
                
                cout << "\nFirst Matrix:";
                matrix1.displayTriplet();
                matrix1.displayFull();
                
                cout << "\nSecond Matrix:";
                matrix2.displayTriplet();
                matrix2.displayFull();
                
                cout << "\nResult (Multiplication):";
                result.displayTriplet();
                result.displayFull();
                break;
            }
            
            case 4: {
                cout << "\n--- ELEMENT-WISE DIVISION ---\n";
                cout << "Enter first matrix (dividend):\n";
                SparseMatrix matrix1 = inputSparseMatrix();
                
                cout << "\nEnter second matrix (divisor):\n";
                SparseMatrix matrix2 = inputSparseMatrix();
                
                SparseMatrix result = matrix1.divide(matrix2);
                
                cout << "\nFirst Matrix (Dividend):";
                matrix1.displayTriplet();
                matrix1.displayFull();
                
                cout << "\nSecond Matrix (Divisor):";
                matrix2.displayTriplet();
                matrix2.displayFull();
                
                cout << "\nResult (Element-wise Division):";
                result.displayTriplet();
                result.displayFull();
                break;
            }
            
            case 5: {
                cout << "\n--- MATRIX TRANSPOSE ---\n";
                cout << "Enter matrix:\n";
                SparseMatrix matrix = inputSparseMatrix();
                
                SparseMatrix result = matrix.transpose();
                
                cout << "\nOriginal Matrix:";
                matrix.displayTriplet();
                matrix.displayFull();
                
                cout << "\nTranspose:";
                result.displayTriplet();
                result.displayFull();
                break;
            }
            
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        
    } while (choice != 6);
    
    return 0;
}