#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;
//Creates a class template `Matrix`
template <typename T>
class Matrix{

    private:
        T** a;
        int row, col;

    public:
        // constructor for matrix rows and columns.
        Matrix(int r, int c) : row(r), col(c){
            if(r <= 0 || c <= 0) {
                throw invalid_argument("Matrix dimensions must be positive"); //Enforces row/col
            }
            a = new T*[row];  //new memory allocation for row
            for(int i = 0; i < row; ++i){ // for each row...
            a[i] = new T[col](); //new memory allocation for col
            }
        }
        //Destructor
        ~Matrix(){
            for(int i = 0; i < row; ++i){
            delete[] a[i];
            }
        delete[] a; //delete pointer
        }
    //Creates a deep copy
    Matrix(const Matrix& mat2) : row(mat2.row), col(mat2.col){
        a = new T*[row];
            for(int i = 0; i < row; ++i) {
                    a[i] = new T[col];
                        for (int l = 0; l < col; ++l){
                        a[i][l] = mat2.a[i][l];
                        }
               }
    }
    //Overloads << to allow assignment
   Matrix& operator=(const Matrix& mat2){
        if(this == &mat2) return *this;

        // Deallocate current memory
        for(int i = 0; i < row; ++i){
            delete[] a[i];
        }
        delete[] a;

        //Copies 2nd Matrix
        row = mat2.row;
        col = mat2.col;
        a = new T*[row];
        for(int i = 0; i < row; ++i){
            a[i] = new T[col];
            for(int l = 0; l < col; ++l){
                a[i][l] = mat2.a[i][l];
            }
        }
        return *this;
    }
       //Element access
    T& operator()(int r, int c) {
        if(r < 0 || r >= row || c < 0 || c >= col){
            throw out_of_range("Index out of range");
        }
        return a[r][c];
    }
     Matrix operator+(const Matrix& mat2){
        if(row != mat2.row || col != mat2.col){
            throw invalid_argument("Must have same dimensions");
        }
        Matrix result(row, col);
        for(int i = 0; i < row; ++i){
            for(int l = 0; l < col; ++l){
                result(i, l) = a[i][l] + mat2.a[i][l];
            }
        }
        return result;
    }

    //Overload for subtraction
    Matrix operator-(const Matrix& mat2){
        if(row != mat2.row || col != mat2.col){
            throw invalid_argument("Must have the same dimensions");
        }
        Matrix result(row, col);
        for(int i = 0; i < row; ++i) {
            for (int l = 0; l < col; ++l){
                result(i, l) = a[i][l] - mat2.a[i][l];
            }
        }
        return result;
    }

    //Overload for multiplication
    Matrix operator*(const Matrix& mat2){
        if(col != mat2.row) {
            throw invalid_argument("Must be compatible for multiplication");
        }
        Matrix result(row, mat2.col);
        for(int i = 0; i < row; ++i) {
            for(int l = 0; l < mat2.col; ++l) {
                for(int k = 0; k < col; ++k) {
                    result(i, l) += a[i][k] * mat2.a[k][l];
                }
            }
        }
        return result;
    }

    //Overload output operator
    friend ostream& operator<<(ostream& os, const Matrix& matrix){
        for(int i = 0; i < matrix.row; ++i) {
            for(int l = 0; l < matrix.col; ++l){
                os << setw(6) << matrix.a[i][l] << " ";
            }
            os << endl;
        }
        return os;
    }
    
    //Function that takes a matrix and a scalar of any type
    //then multiplies each element of the matrix by the scalar
    friend Matrix scalarMultiply(const Matrix& matrix, T scalar){
        Matrix result(matrix.row, matrix.col);
        for(int i = 0; i < matrix.row; ++i){
            for(int l = 0; l < matrix.col; ++l){
                result(i, l) = matrix.a[i][l] * scalar;
            }
        }
        return result;
    }

    //Transpose function
    friend Matrix transpose(const Matrix& matrix){
        Matrix result(matrix.col, matrix.row);
        for(int i = 0; i < matrix.row; ++i){
            for(int l = 0; l < matrix.col; ++l){
                result(l, i) = matrix.a[i][l];
            }
        }
        return result;

    }
};

int main(){
    try{
        Matrix<int> m1(2, 2), m2(2,2);      //creates m1 and m2 for matrices,
        m1(0,0) = 10; m1(0,1) = 15;
        m1(1,0) = 20; m1(1,1) = 25;
        m2(0,0) = 25; m2(0,1) = 15;
        m2(1,0) = 20; m2(1,1) = 10;
        cout << "Matrix 1:\n" << m1 << endl;
        cout << "Matrix 2:\n" << m2 << endl;    //Rather than setting multiple intergers, I just did it all manually. Looks cleaner
        cout << "Addition:\n" << m1+m2 << endl; //than having m1,m2,m3,m4,m5,m6.
        cout << "Subtraction:\n" << m1-m2 << endl;
        cout << "Multiplication:\n" << m1*m2 <<endl;
    }
    catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }
};