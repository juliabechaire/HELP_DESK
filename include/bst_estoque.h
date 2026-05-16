#ifndef BST_ESTOQUE
#define BST_ESTOQUE

#include "chamado.h"


typedef struct Item {
    int id;
    char nome[50];
    int quantidade;
} Item;

typedef struct noEstoque 
{
    Item dado;
    struct noEstoque *direita;
    struct noEstoque *esquerda;
} noEstoque;

typedef struct arvoreEstoque
{
    noEstoque *raiz;
} arvoreEstoque;


arvoreEstoque *criar_estoque();
noEstoque *criar_noEstoque(Item item);
void imprimir_recursivamente(noEstoque *atual);
void liberar_recursivo(noEstoque* atual);
void inserir_item(arvoreEstoque* arvore, Item item);
Item* buscar_item(arvoreEstoque* arvore, int id);
void imprimir_estoque(arvoreEstoque* arvore);
void liberar_estoque(arvoreEstoque* arvore);


#endif