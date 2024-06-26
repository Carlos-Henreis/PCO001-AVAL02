// Arquivo Grafo.h
void LiberaGrafo(GrafoPtr &);

// Programa principal
LiberaGrafo(G); // Libera a memoria alocada para o grafo

// Arquivo Grafo.cpp
void LiberaGrafo(GrafoPtr &G) {
    if (G == nullptr) {
        return;
    }
    for (int i = 0; i < G->NumVertices; i++) {
        LiberaLista(G->ListaAdj[i]);
    }
    delete[] G->Grau;
    delete[] G->ListaAdj;
    delete G;
}
