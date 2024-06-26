#include <iostream>
#include "Grafo.h"

using namespace std;

struct Grafo {
    int NumVertices;
    int NumArestas;
    bool orientado;
    int *Grau;
    NoPtr *ListaAdj;
};

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

bool ExisteAresta(GrafoPtr &G, int Origem, int Destino) {
    if (G == nullptr) {
        return false;
    } else if (Origem < 0 || Origem >= G->NumVertices) {
        return false;
    } else if (Destino < 0 || Destino >= G->NumVertices) {
        return false;
    }

    return (ElementoExisteLista(G->ListaAdj[Origem], Destino));
}

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

int GrauVertice(GrafoPtr G, int Vertice) {
    if (G == nullptr) {
        return -1;
    } else if (Vertice < 0 || Vertice >= G->NumVertices) {
        return -1;
    }

    return G->Grau[Vertice];
}

NoPtr ListaAdjacencia(GrafoPtr G, int Vertice) {
    if (G == nullptr) {
        return nullptr;
    } else if (Vertice < 0 || Vertice >= G->NumVertices) {
        return nullptr;
    }

    return G->ListaAdj[Vertice];
}

void BuscaEmLargura(GrafoPtr G, int Vertice, int *Visitado) {
    if (G == nullptr) {
        return;
    } else if (Vertice < 0 || Vertice >= G->NumVertices) {
        return;
    }

    FilaPtr F;
    IniciaFila(F, G->NumVertices);
    for (int i = 0; i < G->NumVertices; i++) {
        Visitado[i] = -1;// Inicializa todos os vértices como não visitados
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

int MenorDistancia(int *Distancia, bool *Visitado, int NumVertices) {
    int min = INFINITO; // Inicializa com um valor alto (representando infinito)
    int min_index = -1;

    for (int v = 0; v < NumVertices; v++) {
        if (!Visitado[v] && Distancia[v] <= min) {
            min = Distancia[v];
            min_index = v;
        }
    }
    return min_index;
}

void MenorCaminho(GrafoPtr G, int Origem, int *Distancia, int *Precedente) {
    if (G == nullptr || Origem < 0 || Origem >= G->NumVertices) {
        cout << "Erro: Grafo inválido ou vértice de origem fora do intervalo." << endl;
        return;
    }

    bool *Visitado = new bool[G->NumVertices];

    for (int i = 0; i < G->NumVertices; i++) {
        Distancia[i] = INFINITO; // Inicializa a distância como infinito
        Precedente[i] = -1;   // Inicializa o precedente como indefinido
        Visitado[i] = false;  // Inicializa todos os vertices como não visitados
    }

    Distancia[Origem] = 0; // A distância da origem para ela mesma é 0

    for (int i = 0; i < G->NumVertices - 1; i++) {
        int u = MenorDistancia(Distancia, Visitado, G->NumVertices);
        Visitado[u] = true;

        NoPtr Aux = G->ListaAdj[u];
        while (Aux != nullptr) {
            int v;
            float peso;
            NoPtr prox;
            retornaElemento(Aux, v, peso, prox);
            if (peso == 0) peso = 1;
            if (!Visitado[v] && Distancia[u] != 99999 && Distancia[u] + peso < Distancia[v]) {
                Distancia[v] = Distancia[u] + peso;
                Precedente[v] = u;
            }
            Aux = prox;
        }
    }

    delete[] Visitado;
}

void ImprimeCaminho(int *Precedente, int Destino) {
    if (Precedente[Destino] != -1) {
        ImprimeCaminho(Precedente, Precedente[Destino]);
        cout << Precedente[Destino] << " -> ";
    }
}