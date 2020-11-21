#include <bits/stdc++.h>

#define cimg_use_jpeg 1 

#include "CImg.h"

using namespace cimg_library;
using namespace std;

CImg<char> Binarizar(CImg<float> & img) {
     CImg<char> R(img.width(),img.height()); 
     for (int i = 0; i < img.width(); i++) {
          for (int j = 0; j < img.height(); j++) {
               int r = img(i,j,0);
               int g = img(i,j,1);
               int b = img(i,j,2);
               R(i, j) = (r+g+b)/3;
               //R(i, j, 1) = (r+g+b)/3;
               //R(i, j, 2) = (r+g+b)/3;
          }    
     }
     return R; 
} 

bool checkQuad(int x, int y, int xF, int yF, const CImg<char>& img) {
     if (x == xF || y == yF) return true;
     int color = img(x, y, 0);
     for (int i = x; i < xF; i++) {
          for(int j = y; j < yF; j++) {
               if (abs(img(i, j, 0) - color) > 10) { 
                    return false;
               }
          }
     }
     return true;
}

void megaInsert(int x, int y, int xF, int yF, CImg<char>& img) {
     if (checkQuad(x, y, xF, yF,img)) {
          ofstream file("compress", ios::binary | ios::app);
          if (file.is_open()) {
               file.write((char *) &x, sizeof(int));
               file.write((char *) &y, sizeof(int));
               file.write((char *) &xF, sizeof(int));
               file.write((char *) &yF, sizeof(int));
               file.write((char *) &(img(x, y, 0)), sizeof(char));
               file.close();
          }
     } else {
          int xmid = (xF+x)/2;
          int ymid = (yF+y)/2;
          megaInsert(x, y, xmid, ymid, img);
          megaInsert(xmid, y, xF, ymid, img);
          megaInsert(x, ymid, xmid, yF, img);
          megaInsert(xmid, ymid, xF, yF, img);
     }
}

void reconstruir(CImg<char>& B) {
     CImg<char> A(B.width(), B.height());
     ifstream file("compress", ios::binary);
     if (file.is_open()) {
          file.seekg(0, ios::end);
          int filesize = file.tellg();
          int coords = filesize/( sizeof(int)*4 + sizeof(char) );
          file.seekg(0, ios::beg);
          
          int x, y, xF, yF;
          char color;

          for (int i = 0; i < coords; ++i) {
               file.read((char*) &x, sizeof(int));
               file.read((char*) &y, sizeof(int));
               file.read((char*) &xF, sizeof(int));
               file.read((char*) &yF, sizeof(int));
               file.read((char*) &color, sizeof(char));
               for (int j = x; j < xF; ++j) {
                    for (int k = y; k < yF; ++k) {
                         A(j, k) = color;
                    }
               }
          }
     }
     B.display();
     A.display();
}

int main() {

     CImg<float> A("benjamin.exe.jpeg");
     CImg<char> R = Binarizar(A);
	cout << "hola" << endl;
     megaInsert(0, 0, R.width(), R.height(), R);

     reconstruir(R);

     return 0;
}
