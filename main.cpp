#include "libpgm.h"
#include "cell.h"
#include "matriz.h"
#include "maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
void printCaminho(node* aux){
    cout << "CAMINHO ENTRE AS DUAS CELULAS ESCOLHIDAS: COL/ROW "<< endl;
    while(aux != nullptr){
        cout << aux->pt->getCol() << " " << aux->pt->getRow() << endl;
        aux = aux->next;
    }
}
int main() {
    maze x(15,15);
    x.generate();
    cell* a = x.takecell(0, 0);
    cell* b = x.takecell(0,14);
    x.saveAsImage(30, "mymze.pgm");
    node* aux = x.getway(a, b);
    printCaminho(aux);
 }

