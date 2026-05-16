#ifndef PILHA_MENUS_H
#define PILHA_MENUS_H

typedef struct NoPilha {
    int dado;
    struct NoPilha *proximo;
} NoPilha;

typedef struct PilhaMenus {
    NoPilha *topo;
    int tamanho;
} PilhaMenus;


PilhaMenus* criarPilha();
void liberarPilha(PilhaMenus *pilha);
int estaVaziaPilha(PilhaMenus *pilha);
void inserirMenu(PilhaMenus *pilha, int menu);
int removerMenu(PilhaMenus *pilha);
void imprimirPilha(PilhaMenus *pilha);

#endif