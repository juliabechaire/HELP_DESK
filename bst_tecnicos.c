#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_tecnicos.h"

arvoreTecnicos *criar_tecnicos()
{
    arvoreTecnicos *novo=(arvoreTecnicos*)malloc(sizeof(arvoreTecnicos));
    if(novo == NULL)
    {
        printf("Erro na alocação da bst_tecnicos\n");
        return NULL;
    }
    novo->raiz=NULL;
    return novo;
}

noTecnicos *criar_noTecnicos(Tecnico tecnico)
{
    noTecnicos *novo=(noTecnicos*)malloc(sizeof(noTecnicos));
    if(novo == NULL)
    {
        printf("Erro na alocação do noTecnicos.\n");
        return NULL;
    }
    novo->dado=tecnico;
    novo->esquerda=NULL;
    novo->direita=NULL;
    return novo;
}

void inserir_tecnico(arvoreTecnicos* arvore, Tecnico tecnico) 
{
    noTecnicos *novo = criar_noTecnicos(tecnico);
    if(novo == NULL)
    {
        printf("Erro na criação do técnico.\n");
        return;
    }
    

    if(arvore->raiz == NULL)
    {
        arvore->raiz=novo;
        return;
    }
    
    noTecnicos *atual=arvore->raiz;
    noTecnicos *pai=NULL;
    
    while(atual != NULL)
    {
        pai=atual;
        if(atual->dado.id > tecnico.id)
        {
            atual = atual->esquerda;
        } else if (atual->dado.id < tecnico.id)
        {
            atual = atual->direita;
        }
    }
    
    if(pai->dado.id > tecnico.id)
    {
        pai->esquerda=novo;
    } else 
    {
        pai->direita=novo;
    }
}

Tecnico* buscar_tecnico(arvoreTecnicos* arvore, int id) 
{
    if (arvore == NULL) {
        return NULL;
    }

    noTecnicos *atual = arvore->raiz;

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


void imprimir_recursivamenteTecnicos(noTecnicos *atual)
{
    if(atual != NULL)
    {
        imprimir_recursivamenteTecnicos(atual->esquerda);
        printf("  [ID: %d] - %s\n", 
               atual->dado.id, 
               atual->dado.nome);
        imprimir_recursivamenteTecnicos(atual->direita);
    }
}

void imprimir_tecnicos(arvoreTecnicos* arvore) {
    printf("Técnicos disponívies:\n");
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Estoque vazio.\n");
        return;
    }
    imprimir_recursivamenteTecnicos(arvore->raiz);
}

void liberar_recursivoTecnicos(noTecnicos* atual) 
{
    if (atual == NULL) {
        return;
    }
    liberar_recursivoTecnicos(atual->esquerda);
    liberar_recursivoTecnicos(atual->direita);
    free(atual);
}

void liberar_tecnicos(arvoreTecnicos* arvore) {
    if (arvore == NULL) return;
    liberar_recursivoTecnicos(arvore->raiz);
    free(arvore);
}
