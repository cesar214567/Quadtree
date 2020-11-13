#include <bits/stdc++.h>

using namespace std;

struct nodo{
    int x;
    int y;
    string name;
    nodo* chilren[4];
    nodo(int x1,int y1,string name1):x(x1),y(y1),name(name1){};
};

class QuadTree{
private:
    nodo *root=nullptr;
    int get_cuadrante(int x,int y,nodo *root){
        if(x > root->x && y>root->y) return 3;
        if(x > root->x && y<root->y) return 1;
        if(x < root->x && y>root->y) return 2;
        if(x < root->x && y<root->y) return 0;
    }
    void insert(int x,int y , string name, nodo* &temp){
        if(!temp){
            temp=new nodo(x,y,name);
            return;
        }else{ 
            insert(x,y,name,temp->chilren[get_cuadrante(x,y,temp)]);
        }
    }
public:
    void insert(int x,int y, string name){
        insert(x,y,name,root);
    }
};  



/*
0,0
0               | 1
                |
                |
                |
------------------------------
2               |3
                |
                |
                |
                                x,y 







*/