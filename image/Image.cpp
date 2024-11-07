// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <cstdlib>
using namespace std;


// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  
  // check the requirement 
  assert(img != NULL); 
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
  
  //intialize the dimensions of *img with the input value
  (* img).width = width;
  (* img).height = height; 

  //set the three channels in *img with the same dimensions as *img
  Matrix_init(&(*img).red_channel, width, height);
  Matrix_init(&(*img).green_channel, width, height);
  Matrix_init(&(*img).blue_channel, width, height);
}



// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  assert(img != NULL); 
  string p3;
  string line3;
  int imgwidth, imgheight;
  is >> p3 >> imgwidth >> imgheight >> line3;
  Image_init( img, imgwidth, imgheight);
  for (int i = 0; i < (*img).height; ++i) {
    for (int j = 0; j < (*img).width; ++j) {
      int red, green, blue;
      is >> red >> green >> blue;
      Pixel color {red, green, blue};
      Image_set_pixel(img, i, j, color);
    }
  } 
}



// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  //print out the first three lines
  assert(img != NULL); 
  os << "P3\n" << (*img).width << " " << (*img).height << std::endl << "255\n";

  //print out the rest
  for (int i = 0; i < (*img).height; ++i) {
    for (int j = 0; j < (*img).width; ++j) {
      os << *Matrix_at(&(*img).red_channel, i, j) << " "; 
      os << *Matrix_at(&(*img).green_channel, i, j) << " "; 
      os << *Matrix_at(&(*img).blue_channel, i, j) << " "; 
    }
   os << "\n"; 
  } 
}



// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  assert(img != NULL); 
  return (*img).width;
}



// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  assert(img != NULL); 
  return (*img).height;
}



// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  // check the requirement 
  assert(img != NULL); 
  assert(0 <= row);
  assert(row < Image_height(img));
  assert (0 <= column);
  assert(column < Image_width(img));
  
  //create a pixel that will be returned later
  Pixel target;

  //pack the values at the given row and column into the pixel
  target.r = *Matrix_at(&(*img).red_channel, row, column);
  target.g = *Matrix_at(&(*img).green_channel, row, column);
  target.b = *Matrix_at(&(*img).blue_channel, row, column);
  
  return target;
}



// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  // check the requirement 
  assert(img != NULL); 
  assert(0 <= row && row < Image_height(img) && 0 <= column && column < Image_width(img));

  *Matrix_at(&(*img).red_channel, row, column) = color.r;
  *Matrix_at(&(*img).green_channel, row, column) = color.g;
  *Matrix_at(&(*img).blue_channel, row, column) = color.b;
}



// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  assert(img != NULL); 

  for (int i = 0; i < (*img).height; ++i) {
    for (int j = 0; j < (*img).width; ++j) {
      *Matrix_at(&(*img).red_channel, i, j) = color.r;
      *Matrix_at(&(*img).green_channel, i, j) = color.g;
      *Matrix_at(&(*img).blue_channel, i, j) = color.b;
    }
  } 
}

