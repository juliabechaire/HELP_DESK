#ifndef CHAMADO_H
#define CHAMADO_H

#define MAX_ITENS 5

typedef struct ItemNecessario 
{
    int id_estoque;
    int quantidade;
} ItemNecessario;

typedef struct Chamado {
    int id;
    char descricao[100];
    int prioridade;
    
    ItemNecessario itens[MAX_ITENS];
    int num_itens;
} Chamado;

#endif 