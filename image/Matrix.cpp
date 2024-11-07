// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
// check the requirement 
assert(mat != NULL); 
assert(0 < width && width <= MAX_MATRIX_WIDTH);
assert(0 < height && height <= MAX_MATRIX_HEIGHT);

// set the value of *mat with the value input 
(* mat).width = width; 
(* mat).height = height; 

//initialize the matrix.data to 0
for (int i = 0; i < width * height; ++i) {
    (*mat).data[i] = 0;
}
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  assert(mat != NULL); 
  //print out the width and height 
  os << (* mat).width << " " << (* mat).height << std::endl;

  // print out the rows with for loop 

  for (int i = 0; i < (* mat).height; ++i) {
    for (int j = 0; j < (* mat).width; ++j) {
      os << (* mat).data [j + i * (* mat).height] << " "; 
    }
   os << std::endl; 
  } 
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(mat != NULL); 
  return (* mat).width; 
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(mat != NULL); 
  return (* mat).height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  assert(mat != NULL); 
  assert(ptr != NULL); 
  // ptr points to a location, the location in array is sequential 
  int diff = ptr - (* mat).data;
  // the diff indicates how many elements between ptr with the 1st element 
  // consider width as the elements diff in location stored 
  int row = diff / (* mat).width;
  return row;  

}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  assert(mat != NULL); 
  assert(ptr != NULL); 
  // similar idea as the function before 
  int diff = ptr - (* mat).data;
  int column = diff % (* mat).width;
  return column;  
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(mat != NULL); 
  assert(0 <= row);
  assert(row < Matrix_height(mat));
  assert( 0 <= column);
  assert(column < Matrix_width(mat));
  // initialize a pointer to the location 
  int *ptr = &(* mat).data[(row) * Matrix_width(mat) + column]; 
  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(mat != NULL); 
  assert(0 <= row);
  assert(row < Matrix_height(mat));
  assert( 0 <= column);
  assert(column < Matrix_width(mat));
  const int * ptr = &(* mat).data[(row) * Matrix_width(mat) + column];
  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  assert(mat != NULL);
   for (int i = 0; i < (* mat).height; ++i ) {
    for (int j = 0; j < (* mat).width; ++j) {
      (* mat).data[j + i * (* mat).width] = value; 
    }
   }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  assert(mat != NULL);
  // set the row 
  for (int i = 0; i < (* mat).width; ++i) {
    * Matrix_at(mat, 0, i) = value; 
    * Matrix_at(mat, (* mat).height - 1, i) = value; 
  }
  // set the column 
   for (int j = 0; j < (* mat).height; ++j) {
    * Matrix_at(mat, j, 0) = value; 
    * Matrix_at(mat, j, (* mat).width - 1) = value; 
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  assert(mat != NULL);
  int max = 0;
  // using two for loop to run all the elements one row at a time 
  for (int i = 0; i < (* mat).height; ++i) {
    for (int j = 0; j < (* mat).width; ++j){
      if (max < (* mat).data[j + i * (* mat).width]) {
        max = (* mat).data[j + i * (* mat).width];
      }
    }
  }
  return max; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(mat != NULL);
  assert(0<= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end); 
  
  int min_regional = column_start;
// check the max using a for loop to compare each element 
    for (int i = column_start; i < column_end; ++i) {
        if (* Matrix_at(mat, row, i) < * Matrix_at(mat, row, min_regional)) {
            min_regional = i;
        }
    }
    return min_regional;
    
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
assert(mat != NULL); 
assert(0<= row && row < Matrix_height(mat));
assert(0 <= column_start && column_end <= Matrix_width(mat));
assert(column_start < column_end); 
  
  int min_regional = * Matrix_at(mat, row, column_start);

// check the min using a for loop to compare each element 
    for (int i = column_start; i < column_end; ++i) {
        if (* Matrix_at(mat, row, i) < min_regional) {
            min_regional = * Matrix_at(mat, row, i);
        }
    }
    return min_regional;
  
}
