// Arquivo Grafo.h
#include "ListaDinEncadeada.h"// Tad Auxiliar

void InicializaGrafo(GrafoPtr &, int, bool);

// Grafo.cpp
void InicializaGrafo(GrafoPtr &G, int N, bool orientado) {
    G = new Grafo;
    G->NumVertices = N;
    G->NumArestas = 0;
    G->orientado = orientado;
    G->Grau = new int[N];
    G->ListaAdj = new NoPtr[N];
    for (int i = 0; i < N; i++) {
        G->Grau[i] = 0;
        IniciaLista(G->ListaAdj[i]);
    }
}

// Programa principal
GrafoPtr G; // Declaracaoo de uma variavel do tipo Grafo
InicializaGrafo(G, 4, false); // Inicializa o grafo com 4 vertices e nao orientado

