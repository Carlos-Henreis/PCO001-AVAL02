#ifndef GRAFO_FILAESTATICA_H
#define GRAFO_FILAESTATICA_H

typedef struct Fila *FilaPtr;

void IniciaFila(FilaPtr &, int);
bool FilaVazia(FilaPtr);
bool FilaCheia(FilaPtr);
bool Enfileira(FilaPtr &, int);
bool RetiraFila(FilaPtr &, int &);
void LiberaFila(FilaPtr &);


#endif //GRAFO_FILAESTATICA_H
