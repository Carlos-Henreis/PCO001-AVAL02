#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H

#define INFINITO 2147483647

#include "tads_auxiliares/ListaDinEncadeada.h"
#include "tads_auxiliares/FilaEstatica.h"


typedef struct Grafo *GrafoPtr;

void InicializaGrafo(GrafoPtr &, int, bool);
void InsereAresta(GrafoPtr &, int, int, float);
bool ExisteAresta(GrafoPtr &, int, int);
//Obtem a lista de vértices adjacentes a um determinado vértice
NoPtr ListaAdjacencia(GrafoPtr, int);

void RetiraAresta(GrafoPtr &, int, int);
void ImprimeGrafo(GrafoPtr);
void LiberaGrafo(GrafoPtr &);

int GrauVertice(GrafoPtr, int);
void BuscaEmLargura(GrafoPtr, int, int *);
void BuscaEmProfundidade(GrafoPtr, int, int *);
void BuscaEmProfundidadeRecursiva(GrafoPtr, int, int *, int &);

int MenorDistancia(int *, bool *, int);
void MenorCaminho(GrafoPtr, int, int *, int *);
void ImprimeCaminho(int *, int);

#endif //GRAFO_GRAFO_H




