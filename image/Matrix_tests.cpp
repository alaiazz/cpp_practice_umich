// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; 
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_matrix_basic_1) {
// creat a new matrix 
Matrix *mat = new Matrix; 

// fills a 4*6 matrix 
const int width = 4;
const int height = 6; 

// test initiliation function 
Matrix_init(mat, 4, 6);

// test width and height function
ASSERT_EQUAL(Matrix_width(mat), width);
ASSERT_EQUAL(Matrix_height(mat), height);

// fill the matrix with value 1, test fill function and matrix at function 1  
Matrix_fill(mat, 1);

for (int i= 0; i < Matrix_height(mat); ++i){
    for(int j= 0; j < Matrix_width(mat); ++j){
      ASSERT_EQUAL(*Matrix_at (mat, i, j), 1);
    }
  }  

const int * ptr = Matrix_at (mat, 5, 0);
ASSERT_EQUAL(* ptr, 1);

// test matrix row and column 
ASSERT_EQUAL(Matrix_row(mat,ptr), 5);
ASSERT_EQUAL(Matrix_column(mat,ptr), 0);

// test the constant ptr 
const int *ptr_const = Matrix_at(mat, 3, 3); 
ASSERT_EQUAL(*ptr_const, 1);
ASSERT_EQUAL(Matrix_row(mat,ptr_const), 3);
ASSERT_EQUAL(Matrix_column(mat,ptr_const), 3);

// test using the ptr to change the specefic value 
int * ptr1 = Matrix_at (mat, 2, 1); 
* ptr1 = 10; 
const int *ptr_const_1 = Matrix_at(mat, 2, 1);
ASSERT_EQUAL(* ptr_const_1, 10); 

// test the fill border 
Matrix_fill_border(mat, 0);
ASSERT_EQUAL(* Matrix_at(mat, 0, 0), 0); 
ASSERT_EQUAL(* Matrix_at(mat, 5, 3), 0);
ASSERT_EQUAL(* Matrix_at(mat, 2, 3), 0);
ASSERT_EQUAL(* Matrix_at(mat, 5, 0), 0);

// test the max
ASSERT_EQUAL(Matrix_max(mat), 10); 

// test the min 
ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3),0);
ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4),0);
ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 3), 2);
ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 3), 0);
ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 3, 4), 3);

delete mat; 
ptr_const_1 = NULL; 
ptr = NULL; 
ptr1 = NULL;
ptr_const = NULL; 
}

TEST(test_matrix_at_const) {
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 2,2);  
  Matrix_fill(mat, 2); 
  //test the const case
  const Matrix *mat_const = mat; 
  for (int i = 0; i < Matrix_height(mat_const); ++i){
    for (int j = 0; j< Matrix_width(mat_const); ++j){
      ASSERT_EQUAL(*Matrix_at(mat_const, i,j), 2);
    }
  }

  // test max and min 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 2),2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 2), 1);
  ASSERT_EQUAL(Matrix_max(mat), 2); 

  // test print 
  ostringstream expected;
  expected << "2 2\n" << "2 2\n"<< "2 2\n";
  ostringstream actual;
  Matrix_print(mat, actual);

  //
  const int *ptr_const_2 = Matrix_at(mat, 1, 1); 
  ASSERT_EQUAL(*ptr_const_2, 2);
  ASSERT_EQUAL(Matrix_row(mat,ptr_const_2), 1);
  ASSERT_EQUAL(Matrix_column(mat,ptr_const_2), 1);

  delete mat; 
  ptr_const_2 = NULL; 

}

TEST(test_matrix_large_case) {
  Matrix *mat1 = new Matrix; 
  Matrix_init(mat1, 500, 500);

  ASSERT_EQUAL(Matrix_height(mat1), 500);
  ASSERT_EQUAL(Matrix_width(mat1), 500);

  Matrix_fill(mat1,100);
  
  for (int i= 0; i < Matrix_height(mat1); ++i){
    for(int j= 0; j < Matrix_width(mat1); ++j){
      ASSERT_EQUAL(*Matrix_at (mat1, i, j), 100);
    }
  }  

  * Matrix_at(mat1, 0, 499) = 1000;

  ASSERT_EQUAL(Matrix_max(mat1), 1000);
  int *ptr2 = Matrix_at(mat1, 0, 499);
  ASSERT_EQUAL(Matrix_row(mat1,ptr2), 0);
  ASSERT_EQUAL(Matrix_column(mat1,ptr2), 499);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1,0,498,499), 498);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat1,0,498,499), 100);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat1,0,0,500), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat1,0,0,500), 100); 

  Matrix_fill_border(mat1, 0);

  int height = Matrix_height(mat1);
  int width = Matrix_width(mat1);

    for(int j= 0; j < width; ++j){
      ASSERT_EQUAL(*Matrix_at (mat1, 0, j), 0);
      ASSERT_EQUAL(*Matrix_at (mat1, height - 1, j), 0);
    }

    for(int j= 0; j < height; ++j){
      ASSERT_EQUAL(*Matrix_at (mat1,j, 0), 0);
      ASSERT_EQUAL(*Matrix_at (mat1,j, width -1), 0);
    }
    delete mat1; 
}

// test print 
TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1); 
  
  * Matrix_at(mat, 0, 0) = 10;
  ostringstream expected;
  expected << "1 1\n" << "10 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
