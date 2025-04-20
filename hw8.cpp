// Royce Nogales - 4/14/25
#include <iostream>
#include <string>
using namespace std;

class Matrix{
public:
  Matrix();
  Matrix(int a[][2], int numRows, int numCols);
  Matrix(int a[][3], int numRows, int numCols);
  Matrix(Matrix& x); //copy constructor
  ~Matrix(); //destructor
  void clear();
  void mult(int x); //regular multiplication
  Matrix(Matrix& x, Matrix& y); //matrix multiplication
  void add(Matrix& x); //matrix addition
  Matrix& operator=(const Matrix& rhs); //equals operator, similar to copy constructor
  int getMatrix();
  int getRows();
  int getCols();
  void setMatrix(int** matrix);
  void dump();
private:
  int **m_matrix;
  int m_rows;
  int m_columns;
};

int main(){
  int A[2][2] = {{6, 4},{8, 3}};
  int B[2][3];
  int C[2][3] = {{2, 4, 6},{1, 3, 5}};
  int n = 1;
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 3; j++){
      B[i][j] = n;
      n++;
    }
  }
  Matrix matrixA(A, 2, 2);
  Matrix matrixB(B, 2, 3);
  Matrix matrixC(C, 2, 3);

  matrixA.dump();
  matrixB.mult(3);
  matrixB.dump();
  matrixC.dump();
  Matrix matrixD(matrixB, matrixC);
  matrixD.dump();
  matrixD.add(matrixA);
  matrixD.dump();
  return 0;
}

Matrix::Matrix(){
  m_rows = 0;
  m_columns = 0;
  m_matrix = nullptr;
}

Matrix::Matrix(int a[][2], int numRows = 2, int numCols = 2){
  m_rows = numRows;
  m_columns = numCols;
  m_matrix = new int*[2];
  //creates the first array
  for(int i = 0; i < m_rows; i++){
    m_matrix[i] = new int[m_columns];
  }
  //creates the second layer of the 2d array
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] = a[i][j];
    }
  }
}

Matrix::Matrix(int a[][3], int numRows = 2, int numCols = 3){
  m_rows = numRows;
  m_columns = numCols;
  m_matrix = new int*[2];
  //same as before
  for(int i = 0; i < m_rows; i++){
    m_matrix[i] = new int[m_columns];
  }
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] = a[i][j];
    }
  }
}
//copy constructor
Matrix::Matrix(Matrix& x){
  m_rows = x.m_rows;
  m_columns = x.m_columns;
  m_matrix = new int*[m_rows];
  for(int i = 0; i < m_rows; i++){
    m_matrix[i] = new int[m_columns];
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] = x.m_matrix[i][j];
    }
  }
}
//deallocates the matrix
Matrix::~Matrix(){
  if(m_matrix == nullptr){
    //cout << "matrix not deleted" << endl;
    return;
  }
  for(int i = 0; i < m_rows; i++){
    delete []m_matrix[i];
    m_matrix[i] = nullptr;
  }
  delete []m_matrix;
  m_matrix = nullptr;
  m_rows = 0;
  m_columns = 0;
  //cout << "**********************MATRIX DELETED************************" << endl;
}

//manually deallocate matix objects
void Matrix::clear(){
  if(m_matrix == nullptr){
    //cout << "this is bad" << endl;
    return;
  }
  for(int i = 0; i < m_rows; i++){
    delete []m_matrix[i];
    m_matrix[i] = nullptr;
  }
  delete []m_matrix;
  m_matrix = nullptr;
  m_rows = 0;
  m_columns = 0;
  //cout << "**********************MATRIX CLEARED************************" << endl;
}
//does simple multiplication to each element of the 2d array
void Matrix::mult(int x){
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] = x*m_matrix[i][j];
    }
  }
}
//this is matrix multiplication
Matrix::Matrix(Matrix& x, Matrix& y){
  if(x.m_rows != y.m_rows){
    m_rows = 0;
    m_columns = 0;
    m_matrix = 0;
    //cout << "rows and columns do not match" << endl;
    return;
  }
  int newArray[x.m_rows][x.m_rows];
  int rows = 0;
  int cols = 0;
  for(int i = 0; i < x.m_rows; i++){
    while(rows < x.m_rows){
      int count = 0;
      //this loop adds the products of each row into one number, which is then entered into the corresponding spot in the new matrix
      for(int j = 0; j < x.m_columns; j++){
	count += x.m_matrix[i][j]*y.m_matrix[rows][j];
      }
      
      newArray[i][cols] = count;
      rows++;
      cols++;
    }
    rows = 0;
    cols = 0;
  }
  m_rows = x.m_rows;
  m_columns = x.m_rows;
  m_matrix = new int*[m_rows];
  //same as before in regular constructors
  for(int i = 0; i < m_rows; i++){
    m_matrix[i] = new int[m_columns];
  }
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] = newArray[i][j];
    }
  }
}

//matrix addition
void Matrix::add(Matrix& x){
  if(m_rows != x.m_rows or m_columns != x.m_columns){
    //cout << "Error: rows/columns do not match." << endl;
    return;
  }
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      m_matrix[i][j] += x.m_matrix[i][j];
      //adds the matrix x to the original matrix using for loops
    }
  }
}

Matrix& Matrix::operator=(const Matrix& rhs){
  if(this != &rhs){
    //copies the matrix object properties from the rhs matrix
    m_rows = rhs.m_rows;
    m_columns = rhs.m_columns;
    m_matrix = new int*[m_rows];
    for(int i = 0; i < m_rows; i++){
      m_matrix[i] = new int[m_columns];
      for(int j = 0; j < m_columns; j++){
	m_matrix[i][j] = rhs.m_matrix[i][j];
      }
    }
  }
  return *this;  
}

int Matrix::getMatrix(){
  return **m_matrix;
}

int Matrix::getRows(){
  return m_rows;
}

int Matrix::getCols(){
  return m_columns;
}

void Matrix::setMatrix(int** matrix){ 
  m_matrix = matrix;
}

void Matrix::dump(){
  cout << "printing matrix" << endl;
  for(int i = 0; i < m_rows; i++){
    for(int j = 0; j < m_columns; j++){
      if(j == 0){
	cout << "[" << m_matrix[i][j] << ", ";
      }
      else if(j+1 == m_columns){
	cout << m_matrix[i][j] << "]";
      }
      else{
	cout << m_matrix[i][j] << ", ";
      }
    }
    cout << endl;
    }
}
