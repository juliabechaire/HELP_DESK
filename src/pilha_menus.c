#include <stdio.h>
#include <stdlib.h>
#include "pilha_menus.h"

PilhaMenus* criarPilha() {
    PilhaMenus *novo = (PilhaMenus*) malloc(sizeof(PilhaMenus));
    if (novo == NULL) {
        printf("Erro de alocacao para a pilha!\n");
        return NULL;
    }
    novo->topo = NULL;
    novo->tamanho = 0;
    return novo;
}

void liberarPilha(PilhaMenus *pilha) {
    if (pilha == NULL) {
        return;
    }
    
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(pilha);
}

int estaVaziaPilha(PilhaMenus *pilha) {
    if (pilha == NULL)
    {
        return 1;
    }

    if (pilha->topo == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserirMenu(PilhaMenus *pilha, int menu) {
    if (pilha == NULL) {
        return;
    }

    NoPilha *novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("Erro de alocacao para o no da pilha!\n");
        return;
    }
    novo->dado = menu;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
}

int removerMenu(PilhaMenus *pilha) {
    if (estaVaziaPilha(pilha)==1) {
        return -1; // Indica pilha vazia
    }

    NoPilha *temp = pilha->topo;
    int dado_retorno = temp->dado;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->tamanho--;

    return dado_retorno;
}

void imprimirPilha(PilhaMenus *pilha) {
    if (estaVaziaPilha(pilha)==1) {
        printf("Pilha de menus: (vazia)\n");
        return;
    }
    
    printf("Pilha de menus (topo): ");
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}