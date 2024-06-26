#include <iostream>
#include "Grafo.h"

using namespace std;

int main() {
    GrafoPtr G;
    int N = 6;

    InicializaGrafo(G, N, true);

    InsereAresta(G,0,1,0);
    InsereAresta(G,1,2,0);
    InsereAresta(G,1,3,0);
    InsereAresta(G,3,2,0);
    InsereAresta(G,3,0,0);
    InsereAresta(G,3,4,0);
    InsereAresta(G,4,5,0);
    InsereAresta(G,2,5,0);

    //RetiraAresta(G, 2, 5);

    if(ExisteAresta(G,1,3))
        cout << "Existe aresta entre 1 e 3" << endl;
    else
        cout << "Nao existe aresta entre 1 e 3" << endl;


    ImprimeGrafo(G);

    for (int i = 0; i < N; ++i) {
        cout << "Grau do vertice " << i << ": " << GrauVertice(G, i) << endl;
    }

    int *Distancias = new int[N];
    BuscaEmLargura(G, 1, Distancias);

    cout << "Distancias a partir do vertice 0:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Distancia para o vertice " << i << ": " << Distancias[i] << endl;
    }

    int *Profundidades = new int[N];

    BuscaEmProfundidade(G, 0, Profundidades);

    cout << "Profundidades a partir do vertice 0:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Profundidade do vertice " << i << ": " << Profundidades[i] << endl;
    }

    int *Distancia = new int[N];
    int *Precedente = new int[N];

    MenorCaminho(G, 0, Distancia, Precedente);

    cout << "Distancias e caminhos a partir do vertice 0:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Vertice " << i << ": Distancia = " << Distancia[i] << ", Caminho = ";
        ImprimeCaminho(Precedente, i);
        cout << i << endl;
    }

    delete[] Distancia;
    delete[] Precedente;

    delete[] Distancias;
    delete[] Profundidades;
    LiberaGrafo(G);

    return 0;

}
