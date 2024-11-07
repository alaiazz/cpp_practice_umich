// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  assert(img != NULL); 
  assert(energy != NULL); 
  
  // get the image height and width 
  int height = Image_height(img); 
  int width = Image_width(img); 
  
  // initialize the matrix 
  Matrix_init(energy, width, height);

  // fill the matrix with zero
  Matrix_fill(energy, 0);
  
  // set a ptr to change the value 
  int * ptr = Matrix_at (energy, 0, 0);

  // compute the energy 
  for (int i = 1; i < height - 1 ; ++ i) {
    for (int j = 1; j < width - 1; ++ j) {
      ptr = Matrix_at (energy, i, j);
      int value = 0; 
      Pixel p_N = Image_get_pixel(img,i-1, j);
      Pixel p_S = Image_get_pixel(img,i+1, j);
      Pixel p_W = Image_get_pixel(img,i, j-1);
      Pixel p_E = Image_get_pixel(img,i, j+1);
      value = squared_difference(p_N,p_S) + squared_difference(p_W, p_E);
      * ptr = value; 
    }
  }

  // find the max 
  int Max = Matrix_max(energy);

  // use the max to fill the boarder 
  Matrix_fill_border(energy, Max);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(energy != NULL); 
  assert(cost != NULL); 
  assert(energy != cost); 

  // initailize 
 // int height = Matrix_height(energy); 
  int width = Matrix_width(energy); 
  Matrix_init(cost, Matrix_width(energy),Matrix_height(energy));
  Matrix_fill(cost, 0);
//Matrix_init(Matrix* mat, int width, int height);

//const int* Matrix_at(const Matrix* mat, int row, int column);
  
  for (int i = 0; i < Matrix_width(energy); i++) {
    int value  = * Matrix_at(energy, 0, 0);
    int * ptr_new = Matrix_at(cost, 0, i); 
    *ptr_new = value;
  }

  //Matrix_min_value_in_row(const Matrix* mat, int row,
                            //int column_start, int column_end);
                            //column_start (inclusive) and column_end (exclusive).
  // for loop to fill the rest 
  for (int i = 1; i < Matrix_height(energy); i++) {
    for (int j = 0; j < Matrix_width(energy); j++) {
      // case when it is in column 0 
      int val=  * Matrix_at(energy, i, j);
      if (j == 0){
      * Matrix_at(cost, i, j) = val+ Matrix_min_value_in_row(cost, i - 1,j, j + 2);
      }
      // case when it is in column width -1  
      else if (j == (width -1)){
      * Matrix_at(cost, i, j) = val+ Matrix_min_value_in_row(cost, i - 1,j - 1, j + 1);
      }
      else {
      * Matrix_at(cost,i, j) = val+ Matrix_min_value_in_row(cost, i - 1,j - 1, j + 2);
      }
    }
  }
}

// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  assert(cost != NULL); 
  assert(seam != NULL); 
// no need to check the assert, marked in spefication 
// use a for loop to get the min 

//find the min of the last row 
int height = Matrix_height(cost);
int width = Matrix_width(cost);
seam[height - 1] = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);

// find the above cases 

for (int i = height - 2; i >= 0; --i) {
    
      int Min = 0; 
      int j = seam[i+1];
      // case when it is in column 0 
      if (j == 0){
      Min = Matrix_column_of_min_value_in_row(cost, i, j, j+2);
      seam[i] = Min; 
      }
      // case when it is in column width -1  
      else if (j == (Matrix_width(cost) -1)){
      Min = Matrix_column_of_min_value_in_row(cost, i, j-1, j+1);
      seam[i] = Min; 
      }
      else {
      Min = Matrix_column_of_min_value_in_row(cost, i, j-1, j+2);
      seam[i] = Min;                            
      }
  }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
// check whether each element x in seam satisfies 0 <= x < Image_width(img)
// since size of seam equals to the image_height(img)
assert(img != NULL); 
assert(seam != NULL); 
   for (int i = 0; i < Image_height(img); ++i) {
 assert(0 <= seam[i] && seam[i] < Image_width(img));
  }
 //&& *(&seam + 1) - seam  == Image_height(img)
  assert(Image_width(img) >= 2); 

// create a new image
 Image *img_new = new Image; 
 // make it one column smaller than img 
 Image_init(img_new, Image_width(img) - 1, Image_height(img));

// copy this to the new image 
for (int i = 0; i < Image_height(img_new); ++ i) {
  for (int j = 0; j < Image_width(img_new); ++ j) { 
    if (j < seam[i]) {
    // Image_set_pixel(Image* img, int row, int column, Pixel color)
    //Image_get_pixel(const Image* img, int row, int column)
    Image_set_pixel(img_new, i, j, Image_get_pixel(img, i, j)); 
  }
   else /*if (j >= seam [i])*/ {
    Image_set_pixel(img_new, i, j, Image_get_pixel(img, i,j+1));
  }
}
}

// set the img to the img_new ?? can this equation set if they do not have the same size 
*img = *img_new; 
delete img_new; 

}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {
  assert(img != NULL); 
  assert(0 < newWidth && newWidth <= Image_width(img)); 

  // how many times needed to perform the for loop 
  int a = Image_width(img) - newWidth; 
for (int i = 0; i < a; ++i) {

Matrix * energy = new Matrix; 
compute_energy_matrix(img,energy); 

//compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) 
Matrix * cost = new Matrix; 
compute_vertical_cost_matrix(energy, cost);

//find_minimal_vertical_seam(const Matrix* cost, int seam[])
int seam[500] = {0};
find_minimal_vertical_seam(cost, seam); 

//remove_vertical_seam(Image *img, const int seam[])
remove_vertical_seam(img, seam);
delete cost; 
delete energy; 
}
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(img != NULL); 
  assert(0 < newHeight && newHeight <= Image_height(img)); 

  //Rotate the image left by 90 degrees
  rotate_left(img); 
  //Apply seam_carve_width
  seam_carve_width(img, newHeight); 
  //Rotate the image right by 90 degrees
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(img != NULL); 
  assert(0 < newWidth);
  assert(newWidth <= Image_width(img));
  assert( 0 < newHeight);
  assert(newHeight <= Image_height(img));

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight); 
}
