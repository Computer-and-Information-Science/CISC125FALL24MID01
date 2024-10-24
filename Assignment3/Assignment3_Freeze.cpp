#include<iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

/*Task 1: Implement the Matrix Class
1. Create a class template `Matrix` that allows for different numeric data
 types (`int`, `float`, `double`). */
template <typename T> 
class Matrix{

    private:
        T** data;
        int rows;
        int columns;

    public:
        // constructor for matrix rows and columns and data
        //Constructor: Initializes the matrix with a given number of rows and columns
        Matrix(int r, int c) : rows(r), columns(c) {
             if (r <= 0 || c <= 0) {
            throw invalid_argument("Matrix dimensions must be positive."); // must have positive amount of rows and columns
        }
             data = new T*[rows];  //new request for memory allocation for rows
            for (int i = 0; i < rows; ++i) { // for each row...
            data[i] = new T[columns](); //new request for memory allocation for cells by columns
            }
        }
        //Destructor: Deallocates the dynamic memory used by the matrix.
        ~Matrix(){
            for (int i = 0; i < rows; ++i) { 
            delete[] data[i]; // delete data[i]
            }
        delete[] data; //delete pointer
        }
    //Copy Constructor: Creates a deep copy of a matrix.
    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns){
        data = new T*[rows];
            for (int i = 0; i < rows; ++i) {
                    data[i] = new T[columns];
                         for (int j = 0; j < columns; ++j) {
                         data[i][j] = other.data[i][j];
                        }
               }
    }
    //Assignment Operator: Overload the `=` operator to allow matrix assignment.
   Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this; 

        // Deallocate current memory
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;

        // Copy the "other" matrix
        rows = other.rows;
        columns = other.columns;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[columns];
            for (int j = 0; j < columns; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }
       // Element Access
    T& operator()(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= columns) {
            throw out_of_range("Matrix index out of range.");
        }
        return data[r][c];
    }
     Matrix operator+(const Matrix& other) {
        if (rows != other.rows || columns != other.columns) {
            throw invalid_argument("Matrices must have the same dimensions for addition.");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Overload - operator
    Matrix operator-(const Matrix& other) {
        if (rows != other.rows || columns != other.columns) {
            throw invalid_argument("Matrices must have the same dimensions for subtraction.");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result(i, j) = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Overload * operator (Matrix multiplication)
    Matrix operator*(const Matrix& other) {
        if (columns != other.rows) {
            throw invalid_argument("Matrices must be compatible for multiplication.");
        }
        Matrix result(rows, other.columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                for (int k = 0; k < columns; ++k) {
                    result(i, j) += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Overload << operator for output
    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.columns; ++j) {
                os << setw(8) << matrix.data[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    

    /*Task 3: Implement Template Functions
    1. Template Function for Scalar Multiplication: Implement a template 
    function `scalarMultiply` that takes a matrix and a scalar of any numeric
    type and multiplies each element of the matrix by the scalar.
    
    */

    friend Matrix scalarMultiply(const Matrix& matrix, T scalar) {
        Matrix result(matrix.rows, matrix.columns);
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.columns; ++j) {
                result(i, j) = matrix.data[i][j] * scalar;
            }
        }
        return result;
    }

    // Transpose function
    friend Matrix transpose(const Matrix& matrix) {
        Matrix result(matrix.columns, matrix.rows);
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.columns; ++j) {
                result(j, i) = matrix.data[i][j];
            }
        }
        return result;
         
}
};

/*Bonus (Optional):
- Overload the `==` and `!=` operators: Add operator overloads for comparing two matrices for equality and inequality.
Sample Output:*/


int main(){
 try {
        // Test with Matrix of Integers
        Matrix<int> mat1(2, 2);
        Matrix<int> mat2(2, 2);

        mat1(0, 0) = 10; mat1(0, 1) = 15;
        mat1(1, 0) = 20; mat1(1, 1) = 25;

        mat2(0, 0) = 25; mat2(0, 1) = 15;
        mat2(1, 0) = 20; mat2(1, 1) = 10;

        cout << "Matrix 1:\n" << mat1;
        cout << "Matrix 2:\n" << mat2;

        Matrix<int> matSum = mat1 + mat2;
        cout << "Sum:\n" << matSum;

        Matrix<int> matDiff = mat1 - mat2;
        cout << "Difference:\n" << matDiff;

        Matrix<int> matProd = mat1 * mat2;
        cout << "Product:\n" << matProd;

        // Test with Matrix of Doubles
        Matrix<double> matDouble(2, 2);
        matDouble(0, 0) = 1.6; matDouble(0, 1) = 2.6;
        matDouble(1, 0) = 3.6; matDouble(1, 1) = 4.6;

        cout << "Matrix of Doubles:\n" << matDouble;
        double scalar = 2;
        Matrix<double> matScaled = scalarMultiply(matDouble, scalar);
        cout << "Scaled Matrix:\n" << matScaled;

        // Test with Matrix of Floats
        Matrix<float> matFloat(2, 2);
        matFloat(0, 0) = 1.1; matFloat(0, 1) = 2.1;  // to show float
        matFloat(1, 0) = 4.1; matFloat(1, 1) = 5.1; 

        cout << "Matrix of Floats:\n" << matFloat;
        Matrix<float> matTransposed = transpose(matFloat);
        cout << "Transposed Matrix:\n" << matTransposed;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;

}
