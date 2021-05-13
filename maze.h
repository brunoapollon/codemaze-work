#ifndef _MAZE_
#define _MAZE_

//
#include <stdio.h>
#include "matriz.h"
#include "cell.h"
#include "libpgm.h"
#include <stack>
#include <iostream>
#include <ctime>
//
#define COR_FUNDO 255	
#define COR_LINHA 0
using namespace std;

struct node {
    cell* pt;
    node* next; 
    node(){
         pt = nullptr;
         next = nullptr;
    }
    node(cell* cell){
       this->pt = cell;
       this->next = nullptr;
    }
    node(cell* cell, node* next){
       this->pt = cell;
       this->next = next;
    }
};
class maze {
   int nrows, ncols;
   matriz<cell*> mat;
public:
   
   maze(int nc, int nr);
   void generate();
   int retornaParede(cell*);
   cell* takecell(int col, int row);
   int retornaParedeCaminho(cell*);
   void resetVizinhanca();
   void push (cell* x);
   node* getway(cell* A, cell* B);
   void line(pgm* img, 
          int x, int y, char ort, 
          int L, char color);	
   void saveAsImage(int L, const char* filename);
   void strike(int col, int row, char ort);
   bool isStriked(int col, int row, char ort);
};

#endif





