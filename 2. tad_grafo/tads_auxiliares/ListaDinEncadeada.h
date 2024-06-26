#ifndef LISTADINENCADEADA_H_INCLUDED
#define LISTADINENCADEADA_H_INCLUDED

/**
 * @brief Definicao do ponteiro que sera manipulado fora do modulo.
 *
 * Este typedef define o tipo Lista como um ponteiro para uma estrutura No.
 * Isso permite que Listas sejam manipuladas em outros modulos do programa
 * sem precisar conhecer a implementacao interna da estrutura de no.
 */
typedef struct No *NoPtr;

//prototipos das funcoes da TAD Lista Dinamica Encadeada
void IniciaLista(NoPtr &);
void InsereOrdenadoLista(NoPtr &, int, float);
bool RetiraLista(NoPtr &, int);
void ImprimeLista(NoPtr);

//Funcoes auxiliares
bool ElementoExisteLista(NoPtr, int);
bool ListaVazia(NoPtr);
void LiberaLista(NoPtr &);
void retornaElemento(NoPtr, int &, float &, NoPtr &);



#endif // LISTADINENCADEADA_H_INCLUDED
