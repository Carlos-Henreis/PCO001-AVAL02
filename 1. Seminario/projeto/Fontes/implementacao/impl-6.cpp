// Arquivo Grafo.h
void RetiraAresta(GrafoPtr &, int, int);

// Arquivo Grafo.cpp
void RetiraAresta(GrafoPtr &G, int Origem, int Destino) {
    if (G == nullptr) {
        return;
    } else if (Origem < 0 || Origem >= G->NumVertices) {
        return;
    } else if (Destino < 0 || Destino >= G->NumVertices) {
        return;
    }

    if (RetiraLista(G->ListaAdj[Origem], Destino)) {
        G->Grau[Origem]--;
        G->Grau[Destino]--;
        if (!G->orientado) {
            RetiraLista(G->ListaAdj[Destino], Origem);
        }
        G->NumArestas--;
    }
}

// Programa principal
GrafoPtr G;
InicializaGrafo(G, 2, true); // Inicializa o grafo com 2 vertices e orientado

InsereAresta(G,0,1,0);
RetiraAresta(G,0,1,0);