// Arquivo Grafo.cpp
void InsereAresta(GrafoPtr &G, int Origem, int Destino, float Peso) {
    if (G == nullptr) {
        return;
    } else if (Origem < 0 || Origem >= G->NumVertices) {
        return;
    } else if (Destino < 0 || Destino >= G->NumVertices) {
        return;
    }

    InsereOrdenadoLista(G->ListaAdj[Origem], Destino, Peso);
    G->Grau[Origem]++;
    G->Grau[Destino]++;
    if (!G->orientado && Origem != Destino) {
        InsereOrdenadoLista(G->ListaAdj[Destino], Origem, Peso);
    }
    G->NumArestas++;
}
