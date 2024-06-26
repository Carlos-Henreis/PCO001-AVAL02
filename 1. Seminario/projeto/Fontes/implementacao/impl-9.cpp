void BuscaEmLargura(GrafoPtr G, int Vertice, int *Visitado) {
    FilaPtr F;
    IniciaFila(F, G->NumVertices);
    for (int i = 0; i < G->NumVertices; i++) {
        Visitado[i] = -1;// Inicializa todos os vertices como nao visitados
    }

    Visitado[Vertice] = 0;
    Enfileira(F, Vertice);

    while (!FilaVazia(F)) {
        int V;
        RetiraFila(F, V);
        NoPtr Aux = ListaAdjacencia(G, V);
        while (Aux != nullptr) {
            int Aresta;
            float Peso;
            NoPtr Lig;
            retornaElemento(Aux, Aresta, Peso, Lig);
            if (Visitado[Aresta] == -1) {
                Visitado[Aresta] = Visitado[V] + 1;
                Enfileira(F, Aresta);
            }
            Aux = Lig;
        }
    }
    LiberaFila(F);
}
