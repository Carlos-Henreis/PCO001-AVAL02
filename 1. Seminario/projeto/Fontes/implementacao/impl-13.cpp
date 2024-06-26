// Arquivo: Grafo.h
#define INFINITO 2147483647
int MenorDistancia(int *, bool *, int);
void MenorCaminho(GrafoPtr, int, int *, int *);
void ImprimeCaminho(int *, int);

// Programa principal
GrafoPtr G;
int N = 6;
InicializaGrafo(G, N, true);// Inicializa um grafo com 6 vertices e orientado
InsereAresta(G,0,1,0);
InsereAresta(G,1,2,0);
InsereAresta(G,1,3,0);
InsereAresta(G,3,2,0);
InsereAresta(G,3,0,0);
InsereAresta(G,3,4,0);
InsereAresta(G,4,5,0);
InsereAresta(G,2,5,0);

int *Distancia = new int[N];
int *Precedente = new int[N];

MenorCaminho(G, 0, Distancia, Precedente);
cout << "Distancias e caminhos a partir do vertice 0:" << endl;
for (int i = 0; i < N; ++i) {
    cout << "Vertice " << i << ": Distancia = " << Distancia[i] << ", Caminho = ";
    ImprimeCaminho(Precedente, i);
    cout << i << endl;
}
