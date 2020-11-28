#include <bits/stdc++.h>

#define cimg_use_jpeg 1 

#include "CImg.h"

using namespace cimg_library;
using namespace std;

/*CImg<char> Binarizar(CImg<float> & img) {
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
} */
struct retorno{
     bool aproved;
     int red;
     int blue;
     int green;
};


retorno checkQuad(int x, int y, int xF, int yF, const CImg<float>& img) {
     retorno return_value;
     if (x == xF && y == yF){
          return_value.aproved=true;
          return_value.red=img(x,y,0);
          return_value.green=img(x,y,1);
          return_value.blue=img(x,y,2);
          return return_value;
     }
     int R = img(x, y, 0);
     int G = img(x, y, 1);
     int B = img(x, y, 2);
     int RR = R;
     int GR = G;
     int BR = B;
     for (int i = x; i <= xF; i++) {
          for(int j = y; j <= yF; j++) {
               if (abs(img(i, j, 0) - R)<25 && abs(img(i, j,1) - G)<25 && abs(img(i, j, 2) - B) < 25) { 
                    cout<<"PIXEL DE IMAGE ES: "<<img(i,j,0)<<endl;
                    RR+=img(i,j,0);
                    GR+=img(i,j,1);
                    BR+=img(i,j,2);
               }else{
                    retorno return_value;
                    return_value.aproved=false;
                    return return_value;
               }
          }
     }
     int size =(xF-x+1)*(yF-y+1);
     cout<<"RR es: "<<RR<<" size es: "<<size<<endl;

     return_value.aproved=true;
     return_value.red = RR/size;
     return_value.green = GR/size;
     return_value.blue = BR/size;
     return return_value;
}

void megaInsert(int x, int y, int xF, int yF, CImg<float>& img) {
     retorno return_value = checkQuad(x, y, xF, yF,img);
     if (return_value.aproved) {
          ofstream file("compress", ios::binary | ios::app);
          if (file.is_open()) {
               file.write((char *) &x, sizeof(int));
               file.write((char *) &y, sizeof(int));
               file.write((char *) &xF, sizeof(int));
               file.write((char *) &yF, sizeof(int));
               file.write((char *) &(return_value.red), sizeof(int));
               file.write((char *) &(return_value.green), sizeof(int));
               file.write((char *) &(return_value.blue), sizeof(int));
               file.close();
          }
     } else {
          int xmid = (xF+x)/2;
          int ymid = (yF+y)/2;
          if(xmid ==x && ymid==y)return;
          megaInsert(x, y, xmid, ymid, img);
          megaInsert(xmid, y, xF, ymid, img);
          megaInsert(x, ymid, xmid, yF, img);
          megaInsert(xmid, ymid, xF, yF, img);
     }
}

void reconstruir(CImg<float> &B) {
     auto reflejo = B;
     //CImg<float> A(B.width(), B.height());
     CImg<float> A = B;
     for (int i = 0; i < A.width(); i++) {
          for (int j = 0; j < A.height(); j++) {
               A(i,j,0)=0;
               A(i,j,1)=0;
               A(i,j,2)=0;     
          }    
     }
     A.display();
     ifstream file("compress", ios::binary);
     if (file.is_open()) {
          file.seekg(0, ios::end);
          int filesize = file.tellg();
          int coords = filesize/( sizeof(int)*7 );
          file.seekg(0, ios::beg);
          
          int x, y, xF, yF;
          int red,green,blue;

          for (int i = 0; i < coords; ++i) {
               cout<<"iter: "<<i<<endl;
               file.read((char*) &x, sizeof(int));
               file.read((char*) &y, sizeof(int));
               file.read((char*) &xF, sizeof(int));
               file.read((char*) &yF, sizeof(int));
               file.read((char*) &red, sizeof(int));
               file.read((char*) &green, sizeof(int));
               file.read((char*) &blue, sizeof(int));
               cout<<"x: "<<x<<" y: "<<y<<" xF:"<<xF<<" yF: "<<yF<<" red: "<<red<<"green: "<<green<<" blue: "<<blue<<endl;
               for (int j = x; j < xF; ++j) {
                    for (int k = y; k < yF; ++k) {
                         A(j, k,0) = red;
                         A(j, k,1) = green;
                         A(j, k,2) = blue;
                         
                    }
               }
          }
     }
     reflejo.display();
     A.display();
}

int main() {

     CImg<float> A("mario.jpeg");
     //CImg<char> R = Binarizar(A);
     megaInsert(0, 0, A.width()-1, A.height()-1, A);
	cout << "hola" << endl;

     reconstruir(A);

     return 0;
}
