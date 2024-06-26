#include <iostream>
#include "ListaDinEncadeada.h"

using namespace std;

//Definicao do tipo do dado No
struct No {
    int Aresta;
    float Peso;
    No *Lig;
};

//Implamentacao das funcoes da TAD Polinimio
void IniciaLista(NoPtr &L) {
    L = nullptr;
}

void InsereOrdenadoLista(NoPtr &L, int Aresta, float Peso) {
    if (ListaVazia(L)) {  // INSERCAO DO PRIMEIRO NO
        L = new No;
        L->Aresta = Aresta;
        L->Peso = Peso;
        L->Lig = nullptr;
    } else {                // AJUSTA PONTEIROS ANT E AUX
        NoPtr Ant = nullptr;
        NoPtr Aux = L;
        while((Aux != nullptr)&&(Aux->Aresta > Aresta)) {//ENCONTRA POSICAO
            Ant = Aux;
            Aux = Aux->Lig;
        }
        Aux = new No;
        Aux->Aresta = Aresta;     // INSERE O NO E AJUSTA PONTEIROS
        Aux->Peso = Peso;
        if (Ant == nullptr) {
            Aux->Lig = L;
            L = Aux;
        } else {
            Aux->Lig = Ant->Lig;
            Ant->Lig = Aux;
        }
    }
}

bool RetiraLista (NoPtr &L, int Aresta) {
    NoPtr Ant = nullptr;
    NoPtr Aux = L;
    while ((Aux != nullptr) && (Aux->Aresta != Aresta)) { // TENTA ENCONTRAR ELEMENTO
        Ant = Aux;
        Aux = Aux->Lig;
    }
    if (Aux == nullptr)
        return false;  // RETORNA FALSO SE NAO ENCONTRA ELEMENTO
    if (Aux == L)        // SE ELEMENTO E O PRIMEIRO, REDIRECIONA O PONTEIRO
        L = L->Lig;
    else
        Ant->Lig = Aux->Lig; // REDIRECIONA O PONTEIRO
    delete Aux;  // APAGA O ELEMENTO
    return true;
}

void ImprimeLista (NoPtr L) {
    NoPtr Aux = L;
    cout << "L -> ";
    while ((Aux != nullptr)) {
        cout << "[ Aresta:" << Aux->Aresta << ", Peso:" << Aux->Peso << "] -> ";
        Aux = Aux->Lig;
    }
    if (Aux == nullptr)
        cout << "nullptr" << endl;
}

bool ListaVazia(NoPtr L) {
    return L == nullptr;
}

void LiberaLista(NoPtr &L) {
    No *no;
    while(!ListaVazia(L)){
        no = L;
        L = L->Lig;
        delete no;
    }
}

bool ElementoExisteLista(NoPtr L, int elem) {
    NoPtr Aux = L;

    while ((Aux != nullptr) && Aux->Aresta != elem) {
        Aux = Aux->Lig;
    }

    return Aux != nullptr;
}

void retornaElemento(NoPtr L, int &Elem, float &Peso, NoPtr &Lig) {
    if (L == nullptr) {
        Elem = -1;
        Peso = -1;
        Lig = nullptr;
        return;
    }

    Elem = L->Aresta;
    Peso = L->Peso;
    Lig = L->Lig;
}