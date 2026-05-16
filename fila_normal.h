#ifndef FILA_NORMAL_H
#define FILA_NORMAL_H

#include "chamado.h"

typedef struct NoFila {
    Chamado dado;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaNormal;


FilaNormal* criarFilaNormal();
void liberarFilaNormal(FilaNormal *fila);
int estaVaziaFila(FilaNormal *fila);
void inserirNormal(FilaNormal *fila, Chamado chamado);
Chamado removerNormal(FilaNormal *fila);
void imprimirFila(FilaNormal *fila);

Chamado remover_normal_id(FilaNormal *fila, int id);

#endif