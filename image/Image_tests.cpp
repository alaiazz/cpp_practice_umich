// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_1){
  Pixel a = {23, 134, 32};
  Image *img = new Image;
  Image_init(img, 8, 14);

  ASSERT_EQUAL(Image_width(img), 8);
  ASSERT_EQUAL(Image_height(img), 14);

  Image_fill(img, a);
  for (int i=0; i<Image_height(img); i++){
    for(int j=0; j<Image_width(img); j++){
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, i, j), a));
    }
  }  

  Pixel b = {42, 13, 0};
  Image_set_pixel(img, 13, 7, b);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 13, 7), b));

  delete img;
}

TEST(test_image_2){
  Image *img = new Image;
  Image *img2 = new Image;

  string input = "P3 2 2\t255 25 13 245\n0\n64 74 \n10 233 55 83 45 213 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);
  Image_init(img2, 2, 2);
  const Pixel red = {25, 13, 245};
  const Pixel green = {0, 64, 74};
  const Pixel blue = {10, 233, 55};
  const Pixel white = {83, 45, 213};
  Image_set_pixel(img2, 0, 0, red);
  Image_set_pixel(img2, 0, 1, green);
  Image_set_pixel(img2, 1, 0, blue);
  Image_set_pixel(img2, 1, 1, white);
  string output_correct = "P3\n2 2\n255\n25 13 245 0 64 74 \n10 233 55 83 45 213 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
  ASSERT_TRUE(Image_equal(img, img2));
  delete img;
  delete img2;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
