#ifndef HISTORICO
#define HISTORICO

#include "chamado.h"
#include "bst_tecnicos.h"

typedef struct noHistorico
{
    char registro[100];
    Chamado chamado;
    Tecnico tecnico;
    struct noHistorico *proximo;
}noHistorico;

typedef struct listaHistorico
{
    noHistorico *primeiro;
    noHistorico *ultimo;
    int tamanho;
} listaHistorico;

listaHistorico *criarHistorico();
void inserirHistorico(Chamado chamado, Tecnico tecnico, listaHistorico *lista, const char *status);
void imprimirHistorico(listaHistorico *lista);
void liberarHistorico(listaHistorico *lista);

#endif