#include "FilaEstatica.h"


struct Fila{
    int *Dados;
    int TamMax;
    int Tam;
    int Com;
    int Fim;
};

void IniciaFila(FilaPtr &F, int N){
    F = new Fila;
    F->TamMax = N;
    F->Dados = new int[N];
    F->Tam = 0;
    F->Com = 0;
    F->Fim = -1;
}

bool FilaVazia(FilaPtr F){
    return (F->Tam == 0);
}

bool FilaCheia(FilaPtr F){
    return (F->Tam == F->TamMax);
}

bool Enfileira(FilaPtr &F, int Valor){
    if (FilaCheia(F))
        return false;
    F->Tam++;
    F->Fim = (F->Fim + 1) % F->TamMax;
    F->Dados[F->Fim] = Valor;
    return true;
}

bool RetiraFila(FilaPtr &F, int &Valor){
    if (FilaVazia(F))
        return false;
    F->Tam--;
    Valor = F->Dados[F->Com];
    F->Com = (F->Com + 1) % F->TamMax;
    return true;
}

void LiberaFila(FilaPtr &F){
    delete[] F->Dados;
    delete F;
    F = nullptr;
}
