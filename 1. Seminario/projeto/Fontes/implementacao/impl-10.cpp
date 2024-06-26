void BuscaEmProfundidade(GrafoPtr G, int VerticeInicial, int *Profundidade) {
    if (G == nullptr) {
        return;
    } else if (VerticeInicial < 0 || VerticeInicial >= G->NumVertices) {
        return;
    }

    // Inicializa distancias
    for (int i = 0; i < G->NumVertices; i++) {
        Profundidade[i] = -1; //define todos os vertices como nao visitados
    }

    int cont = 0;
    BuscaEmProfundidadeRecursiva(G, VerticeInicial, Profundidade, cont);
}
