#ifndef FILA_PRIORIDADE_MAXIMA_H
#define FILA_PRIORIDADE_MAXIMA_H

#include "chamado.h"

#define FILA_PRIORIDADE_CAP 50

typedef struct {
    Chamado *dados;
    int capacidade;
    int tamanho;
} FilaPrioridadeMaxima;

FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade);
void liberar_fila_prioridade(FilaPrioridadeMaxima *fila);
void inserir_chamado_heap(FilaPrioridadeMaxima *fila, Chamado chamado);
Chamado remover_chamado_maximo(FilaPrioridadeMaxima *fila);
int fila_prioridade_vazia(FilaPrioridadeMaxima *fila);
void imprimir_heap(FilaPrioridadeMaxima *fila); 
void trocar_chamado(Chamado *a, Chamado *b);
void arrumar_acima(FilaPrioridadeMaxima *fila, int indice);
void arrumar_abaixo(FilaPrioridadeMaxima *fila, int indice);

Chamado remover_heap_por_id(FilaPrioridadeMaxima *heap, int id); 

#endif