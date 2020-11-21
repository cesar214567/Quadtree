#include <bits/stdc++.h>
#define cimg_use_jpeg 1 
#include "CImg.h"
using namespace std;
using namespace cimg_library;

struct nodo{
    int x;
    int y;
    int xF;
    int yF;
    int color;
    nodo* chilren[4];
    nodo(int x1,int y1,int xF1,int yF1,int color1):x(x1),y(y1),xF(xF1),yF(yF1),color(color1){};
};

class QuadTree{
private:
    nodo *root=nullptr;
    
    void insert(int x1,int y1,int xF1,int yF1,int color1, nodo* &temp){
        if (!temp) {
            temp=new nodo(x1,y1,xF1,yF1,color1);
            return;
        } else { 
            insert(x1,y1,xF1,yF1,color1,temp->chilren[get_cuadrante(x1,y1,temp)]);
        }
    }

public:    

    int get_cuadrante(int x,int y,nodo *root){
        if (x > root->x && y>root->y) return 3;
        if (x > root->x && y<root->y) return 1;
        if (x < root->x && y>root->y) return 2;
        if (x < root->x && y<root->y) return 0;
    }
    

    void insert(int x1, int y1, int xF1, int yF1, int color1) {
        insert(x1, y1, xF1, yF1, color1, root);
    }
};  



/*
0,0
0    |          | 1
     |          |
------          |
                |
------------------------------
2               |3
                |
                |
                |
                                x,y 







*/