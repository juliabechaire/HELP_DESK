#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "fila_normal.h"
#include "fila_prioridade_maxima.h"
#include "pilha_menus.h"


typedef struct noAtendimento 
{
    Chamado dado;
    struct noAtendimento *proximo;
    struct noAtendimento *anterior;
}noAtendimento;

typedef struct listaAtendimento
{
    noAtendimento *inicio;
    noAtendimento *fim;
    int tamanho;
}listaAtendimento;

listaAtendimento *criar_listaAtendimento();
void inserir_listaAtendimento(listaAtendimento *lista, Chamado chamado);
Chamado remover_listaAtendimento(listaAtendimento *lista);
void liberar_listaAtendimento(listaAtendimento *lista);
void imprimirListaAtendimento(listaAtendimento *lista);
int listaAtendimentoVazia(listaAtendimento *lista);

void removerAtendimento_id(listaAtendimento *lista, int id);
Chamado *buscar_atendimento_id(listaAtendimento *lista, int id);

#endif