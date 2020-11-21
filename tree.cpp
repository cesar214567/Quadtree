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
    

    bool checkQuad(int x, int y,int xF,int yF, CImg<char> img ){
        if (x==xF || y==yF)return true;
        int color = img(x,y,0);
        for (int i=x;i<xF;i++) {
            for(int j =y;j<yF;j++) {
                if(abs(img(i,j,0)-color)>10) { 
                    return false;
                }
            }
        }
        return true;
    } 
    void insert(int x1,int y1,int xF1,int yF1,int color1, nodo* &temp){
        if (!temp) {
            temp=new nodo(x1,y1,xF1,yF1,color1);
            return;
        } else { 
            insert(x1,y1,xF1,yF1,color1,temp->chilren[get_cuadrante(x1,y1,temp)]);
        }
    }

public:    

    void megaInsert(int x,int y, int xF,int yF,CImg<char> &img ){
        if (checkQuad( x, y, xF, yF,img)) {
            //insert(x,y,xF,yF,img(x,y,0));
            //
        } else {
            int xmid=(xF-x)/2;
            int ymid=(yF-y)/2;
            megaInsert( x, y, xmid, ymid,img);
            megaInsert( xmid, y, xF, ymid,img);
            megaInsert( x, ymid, xmid, yF,img);
            megaInsert( xmid, ymid, xF, yF,img);
        }

    }
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