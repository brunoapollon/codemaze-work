#include "maze.h"
//
#define COR_FUNDO 255	
#define COR_LINHA 0

maze::maze(int nc, int nr):mat(nc,nr)
{
   ncols = nc;
   nrows = nr;  
   for (int col=0; col < ncols; col++)
      for(int row=0; row < nrows; row++)
         mat(col, row)=new cell(col, row);                           


}

cell* maze::takecell(int col, int row) 
{ 
    static cell x(1,1);
    if (col>=0 && col<ncols &&
        row>=0 && row<nrows)
       return mat(col, row);
    else
       return &x; 
}

void maze::line(pgm* img,
    int x, int y, char ort, 
    int L, char color) 
{ 
    for (int d=0; d<L; d++) { 
      switch(ort) {
      case SUL:
         img->pixel(x+d,y+L) = color;
      break;
      case NORTE:
         img->pixel(x+d,y) =color;
      break;
      case LESTE:
        img->pixel(x+L,y+d)=color;
      break;  
      case OESTE: 
         img->pixel(x,y+d)=color;
      }
    }
}	

void maze::saveAsImage(int L, const char* filename) 
{
    pgm* img = new pgm(COR_FUNDO, ncols*L, nrows*L);
    int cnt = 0;
    for (int col=0; col<ncols; col++)
        for (int row=0; row<nrows; row++) 
           for (char ort=0; ort<4; ort++) {
               int x = L * col; 
               int y = L * row;
               if (!isStriked(col,row,ort)) {
                   line(img, x, y, ort, L, COR_LINHA);
               }                
           }
   img->saveAs(filename);
   delete img;
}

void maze::strike(int col, int row, char ort) 
{ //@@@  
    takecell(col,row)->drop(ort);

    switch(ort) {
    case NORTE: takecell(col,row+1)->drop(SUL);
         break; 
    case SUL:   takecell(col,row-1)->drop(NORTE);
         break;
    case LESTE: takecell(col+1,row)->drop(OESTE);
         break;
    case OESTE: takecell(col-1,row)->drop(LESTE);
    }
}

bool maze::isStriked(int col, int row, char ort) 
{  
  return takecell(col,row)->isDroped(ort);
}

/* IMPLEMENTAR */
int maze::retornaParede(cell* cel){
    bool sorteiaParede = true;
    bool paredes[4];
    int parede;
    if ((cel->getCol()+1) < ncols && mat(cel->getCol()+1, cel->getRow())->isVisited() == false){
        paredes[2] = true;
    }
    else{
        paredes[2] = false;
    }
    if (cel->getCol()-1 > -1 && mat(cel->getCol()-1, cel->getRow())->isVisited() == false) {
        paredes[3] = true;
    }
    else{
        paredes[3] = false;
    }
    if ((cel->getRow()+1) < nrows && mat(cel->getCol(), cel->getRow()+1)->isVisited() == false){
       paredes[1] = true;
    }
    else{
        paredes[1] = false;
    }
    if (cel->getRow()-1 > -1 && mat(cel->getCol(), cel->getRow()-1)->isVisited() == false){
        paredes[0] = true;
    }
    else{
        paredes[0] = false;
    }
    if(!paredes[0] && !paredes[1] && !paredes[2] && !paredes[3]){
        return -1;
    }
    else{
        while (sorteiaParede){
            parede = clock() % 4;
            if (paredes[parede]){
                sorteiaParede = false;
            }
        }
        return parede;
    }
}
void maze::generate(){
    stack<cell*> pilha;
    int parede;
    int colCellFirst = clock() % ncols;
    int rowCellFirst = clock() % nrows;
    mat(colCellFirst, rowCellFirst)->visit();
    pilha.push(mat(colCellFirst, rowCellFirst));
    while (!pilha.empty())
    {
        cell* cellCorrent = pilha.top();
        pilha.pop();
        parede = retornaParede(cellCorrent);
        if (parede > -1){
            pilha.push(cellCorrent);
            switch (parede){
            case 0:
                cellCorrent->drop(NORTE);
                mat(cellCorrent->getCol(), cellCorrent->getRow()-1)->drop(SUL);
                mat(cellCorrent->getCol(), cellCorrent->getRow()-1)->visit(); 
                pilha.push(mat(cellCorrent->getCol(), cellCorrent->getRow()-1));
                break;
            case 1:
                cellCorrent->drop(SUL);
                mat(cellCorrent->getCol(), cellCorrent->getRow()+1)->drop(NORTE);
                mat(cellCorrent->getCol(), cellCorrent->getRow()+1)->visit();
                pilha.push(mat(cellCorrent->getCol(), cellCorrent->getRow()+1));
                break;
            case 2:
                cellCorrent->drop(LESTE);
                mat(cellCorrent->getCol()+1, cellCorrent->getRow())->drop(OESTE);
                mat(cellCorrent->getCol()+1, cellCorrent->getRow())->visit();
                pilha.push(mat(cellCorrent->getCol()+1, cellCorrent->getRow()));
                break;
            case 3:
                cellCorrent->drop(OESTE);
                mat(cellCorrent->getCol()-1, cellCorrent->getRow())->drop(LESTE);
                mat(cellCorrent->getCol()-1, cellCorrent->getRow())->visit();
                pilha.push(mat(cellCorrent->getCol()-1, cellCorrent->getRow()));
                break;
            default:
                break;
            }
        }
    }
}
int maze::retornaParedeCaminho(cell* cel){
    bool sorteiaParede = true;
    bool paredes[4];
    int parede;
    if (cel->getRow()-1 > -1 && !mat(cel->getCol(), cel->getRow()-1)->isVisited() && cel->isDroped(NORTE)){
        paredes[0] = true;
    }
    else{
        paredes[0] = false;
    }
    if (cel->getRow()+1 < nrows && !mat(cel->getCol(), cel->getRow()+1)->isVisited() && cel->isDroped(SUL)) {
        paredes[1] = true;
    }
    else{
        paredes[1] = false;
    }
    if (cel->getCol()+1 < ncols && !mat(cel->getCol()+1, cel->getRow())->isVisited() && cel->isDroped(LESTE)){
       paredes[2] = true;
    }
    else{
        paredes[2] = false;
    }
    if (cel->getCol()-1 > -1 && !mat(cel->getCol()-1, cel->getRow())->isVisited() && cel->isDroped(OESTE)){
        paredes[3] = true;
    }
    else{
        paredes[3] = false;
    }
    if(!paredes[0] && !paredes[1] && !paredes[2] && !paredes[3]){
        return -1;
    }
    else{
        
        while (sorteiaParede){
            parede = clock() % 4;
            if (paredes[parede]){
                sorteiaParede = false;
            }
        }
        return parede;
    }
}
void maze::resetVizinhanca(){
    for (int col = 0; col < ncols; col++){
        for (int row = 0; row < nrows; row++){
            mat(col, row)->resetVisited();
        }
    }
    
}
node* maze::getway(cell* A, cell* B){
    resetVizinhanca();
    stack<cell*> pilha;
    int parede;
    A->visit();
    pilha.push(mat(A->getCol(), A->getRow()));
    while (pilha.top() != mat(B->getCol(), B->getRow())){
        cell* cellCorrent = pilha.top();
        pilha.pop();
        parede = retornaParedeCaminho(cellCorrent);
        if (parede > -1){
            pilha.push(cellCorrent);
            switch (parede){
                case 0:
                    mat(cellCorrent->getCol(), cellCorrent->getRow()-1)->visit();
                    pilha.push(mat(cellCorrent->getCol(), cellCorrent->getRow()-1));
                break;
                case 1:
                    mat(cellCorrent->getCol(), cellCorrent->getRow()+1)->visit();
                    pilha.push(mat(cellCorrent->getCol(), cellCorrent->getRow()+1));
                break;
                case 2:
                    mat(cellCorrent->getCol()+1, cellCorrent->getRow())->visit();
                    pilha.push(mat(cellCorrent->getCol()+1, cellCorrent->getRow()));
                break;
                case 3:
                    mat(cellCorrent->getCol()-1, cellCorrent->getRow())->visit();
                    pilha.push(mat(cellCorrent->getCol()-1, cellCorrent->getRow()));
                break;
                default:
                break;
            }
        }
    }
    cell* vet[pilha.size()];
    int tamanho = pilha.size();
    int i = tamanho, b = tamanho;
    for(i -= 1; i >= 0; i--){
        vet[i] = pilha.top();
        pilha.pop();
    }
    node* head = new node(vet[0]);
     node* temp = new node(vet[1]);
     head->next = temp;
      for(int a = 2; a < b; a++){
        node* aux = new node(vet[a]);
        temp->next = aux;
        temp = temp->next;
    }
    return head;
}






