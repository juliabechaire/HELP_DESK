#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_estoque.h"

arvoreEstoque *criar_estoque()
{
    arvoreEstoque *novo=(arvoreEstoque*)malloc(sizeof(arvoreEstoque));
    if(novo == NULL)
    {
        printf("Erro na alocação da bst_estoque\n");
        return NULL;
    }
    novo->raiz=NULL;
    return novo;
}

noEstoque *criar_noEstoque(Item item)
{
    noEstoque *novo=(noEstoque*)malloc(sizeof(noEstoque));
    if(novo == NULL)
    {
        printf("Erro na alocação do noEstoque.\n");
        return NULL;
    }
    novo->dado=item;
    novo->esquerda=NULL;
    novo->direita=NULL;
    return novo;
}


void inserir_item(arvoreEstoque* arvore, Item item) 
{
    noEstoque *novo=criar_noEstoque(item);
    if(novo == NULL)
    {
        printf("Erro na criação de item.\n");
        return;
    }
    
    if(arvore->raiz == NULL)
    {
        arvore->raiz=novo;
        return;
    }
    
    noEstoque *atual= arvore->raiz;
    noEstoque *pai=NULL;
    
    while(atual != NULL)
    {
        pai = atual;
        if(atual->dado.id > item.id)
        {
            atual = atual->esquerda;
        } else if (atual->dado.id < item.id)
        {
            atual = atual->direita;
        } 
    } ///agora atual é nulo, mas o pai ainda existe
    
    if(pai->dado.id > item.id)
    {
        pai->esquerda=novo;
    } else
    {
        pai->direita=novo;
    }
    
}

Item* buscar_item(arvoreEstoque* arvore, int id) 
{
    if (arvore == NULL) {
        return NULL;
    }

    noEstoque *atual = arvore->raiz;

    while (atual != NULL) 
    {
        if (id == atual->dado.id) {
            return &(atual->dado);
        }

        if (id < atual->dado.id) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    return NULL;
}


void imprimir_recursivamente(noEstoque *atual)
{
    if(atual != NULL)
    {
        imprimir_recursivamente(atual->esquerda); //vai ate o menor
        printf("  [ID: %d] %s (Qtd: %d)\n", 
               atual->dado.id, 
               atual->dado.nome, 
               atual->dado.quantidade);
        imprimir_recursivamente(atual->direita); //vai ate o maior
    }
}

void imprimir_estoque(arvoreEstoque* arvore) {
    printf("Itens no estoque:\n");
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Estoque vazio.\n");
        return;
    }
    imprimir_recursivamente(arvore->raiz);
}

void liberar_recursivo(noEstoque* atual) 
{
    if (atual == NULL) {
        return;
    }
    liberar_recursivo(atual->esquerda);
    liberar_recursivo(atual->direita);
    free(atual);
}

void liberar_estoque(arvoreEstoque* arvore) {
    if (arvore == NULL) return;
    liberar_recursivo(arvore->raiz);
    free(arvore);
}
