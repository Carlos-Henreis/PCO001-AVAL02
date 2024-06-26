void BuscaEmProfundidadeRecursiva(GrafoPtr G, int Vertice, int *Profundidade, int &cont) {
    Profundidade[Vertice] = cont++;

    NoPtr Aux = ListaAdjacencia(G, Vertice);
    while (Aux != nullptr) {
        int Aresta;
        float Peso;
        NoPtr Lig;
        retornaElemento(Aux, Aresta, Peso, Lig);
        if (Profundidade[Aresta] == -1) {
            BuscaEmProfundidadeRecursiva(G, Aresta, Profundidade, cont);
        }
        Aux = Lig;
    }
}
