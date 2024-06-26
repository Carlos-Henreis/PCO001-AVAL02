// Arquivo: Grafo.h
typedef struct Grafo *GrafoPtr;

// Arquivo: Grafo.cpp
#include "Grafo.h" // Inclui a definicao da TAD Grafo

// Definicao da estrutura Grafo
struct Grafo {
    int NumVertices;
    int NumArestas;
    bool orientado;
    int *Grau;
    NoPtr *ListaAdj;
};

// Programa principal
GrafoPtr G; // Declaracao de um ponteiro para a estrutura Grafo
