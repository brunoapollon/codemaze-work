#include "cell.h"

cell::cell(int col, int row) {
    this->col = col;
    this->row = row;
    for (int k=0; k<4; k++)
        walls[k] = true;
    visited = false;
}

void cell::drop (char d) {
   walls[d] = false;
}

bool cell::isDroped (char d){
    return walls[d]==false;
}

void cell::visit() {
    visited=true;
}

bool cell::isVisited() {
    return visited;
}
void cell::resetVisited(){
    visited = false;
}
int cell::getCol() { return col; }

int cell::getRow() { return row; }



