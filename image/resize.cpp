// Project UID af1f95f547e44c8ea88730dfb185559d
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <cassert>
# include "Image.h"
# include "Matrix.h"
# include "processing.h"

using namespace std;

int main (int argc, char * argv[]) {
  if (argc == 4 || argc == 5 ) {
    // read in a file 
    string filename = argv[1];
    ifstream fin;
    fin.open(filename); 
    // check whether the file is open 
    if (!fin.is_open()) {
      cout << "Error opening file: " << filename << endl;
      return 1;
    }
    // output the file 
    ofstream fileout;
    fileout.open (argv[2]);

    // the width and height of the original image 
    string p3,line4;
    int width; 
    int height; 
    fin >> p3 >> width >> height >> line4; 
    fin.close();
    int a3 = atoi(argv[3]);
    int a4 = atoi(argv[4]);

    if ( 0 < a3 && a3 <= width && 0 < a4 && a4 <= height) {
      fin.open(filename);
      Image *img = new Image; 

      Image_init(img, fin);
      fin.close();
      int newWidth = atoi(argv[3]);
      int newHeight = atoi(argv[4]); 
      seam_carve(img, newWidth, newHeight);

      Image_print(img,fileout);
      fileout.close();
      delete img; 
      return 0; 
    }
    //aaaaaaa
    else {
      cout << "aaaaaUsage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
      << "WIDTH and HEIGHT must be less than or equal to original" << endl;
      return 1; 
    }
  }

  else {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1; 
  }
}