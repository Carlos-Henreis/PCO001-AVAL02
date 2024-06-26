void ImprimeGrafo(GrafoPtr G) {
    if (G == nullptr) {
        return;
    }

    for (int i = 0; i < G->NumVertices; i++) {
        cout << i << " -> ";
        ImprimeLista(ListaAdjacencia(G, i));
        cout << endl;
    }
}


int GrauVertice(GrafoPtr G, int Vertice) {
    if (G == nullptr) {
        return -1;
    } else if (Vertice < 0 || Vertice >= G->NumVertices) {
        return -1;
    }

    return G->Grau[Vertice];
}
