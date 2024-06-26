GrafoPtr G;
int N = 4;

InicializaGrafo(G, N, true);

InsereAresta(G,0,1,0);
InsereAresta(G,1,2,0);
InsereAresta(G,1,3,0);
InsereAresta(G,3,2,0);
InsereAresta(G,3,0,0);

int *Profundidades = new int[N];
BuscaEmProfundidade(G, 0, Profundidades);
