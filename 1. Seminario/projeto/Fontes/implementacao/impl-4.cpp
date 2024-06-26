// Arquivo Grafo.h
void InsereAresta(GrafoPtr &, int, int, float);

// Programa principal
GrafoPtr G;
int N = 4;

InicializaGrafo(G, N, false);
InsereAresta(G,0,1,0);
InsereAresta(G,1,3,0);
InsereAresta(G,2,4,0);
InsereAresta(G,1,4,0);

LiberaGrafo(G);

//CONTINUA...
