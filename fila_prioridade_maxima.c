#include "fila_prioridade_maxima.h"
#include <stdio.h>
#include <stdlib.h>

void trocar_chamado(Chamado *a, Chamado *b) { 
    Chamado temp = *a;
    *a = *b;
    *b = temp;
}


 // (indice - 1) / 2 --> fórmula para encontrar o índice do PAI
void arrumar_acima(FilaPrioridadeMaxima *fila, int indice)
{
    
    while (indice > 0 && ((fila->dados[indice].prioridade > fila->dados[(indice - 1) / 2].prioridade) || 
                           (fila->dados[indice].prioridade == fila->dados[(indice - 1) / 2].prioridade && 
                                 fila->dados[indice].id < fila->dados[(indice - 1) / 2].id)))
    {
        trocar_chamado(&fila->dados[(indice - 1) / 2], &fila->dados[indice]);
        indice = (indice - 1) / 2; ///atualizar o indice
    }
}


void arrumar_abaixo(FilaPrioridadeMaxima *fila, int indice)
{
    int maior = indice;
    
    int esquerda = 2 * indice + 1; /// filho esquerda
    int direita = 2 * indice + 2;  /// filho direita


    if (esquerda < fila->tamanho && ((fila->dados[esquerda].prioridade > fila->dados[maior].prioridade) || 
                                      (fila->dados[esquerda].prioridade == fila->dados[maior].prioridade && 
                                       fila->dados[esquerda].id < fila->dados[maior].id)))
    {
        maior = esquerda;
    }

    if (direita < fila->tamanho && ((fila->dados[direita].prioridade > fila->dados[maior].prioridade) || 
                                     (fila->dados[direita].prioridade == fila->dados[maior].prioridade && 
                                     fila->dados[direita].id < fila->dados[maior].id)))
    {
        maior = direita;
    }

    if (maior != indice)
    {
        trocar_chamado(&fila->dados[indice], &fila->dados[maior]);
        arrumar_abaixo(fila, maior);
    }
}

FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade) {
    capacidade = FILA_PRIORIDADE_CAP;
    
    FilaPrioridadeMaxima *fila = (FilaPrioridadeMaxima*) malloc(sizeof(FilaPrioridadeMaxima));
    if (fila == NULL) {
        printf("Erro de alocacao para a estrutura do heap!\n");
        return NULL;
    }

    fila->dados = (Chamado*) malloc(capacidade * sizeof(Chamado));
    if (fila->dados == NULL) {
        printf("Erro de alocacao para os dados do heap!\n");
        free(fila); 
        return NULL;
    }
    
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    return fila;
}

void liberar_fila_prioridade(FilaPrioridadeMaxima *fila) {
    if (fila == NULL) {
        return;
    }
    free(fila->dados);
    free(fila);
}


void inserir_chamado_heap(FilaPrioridadeMaxima *fila, Chamado chamado)
{
    if (fila == NULL || fila->tamanho == fila->capacidade)
    {
        printf("Fila de prioridade cheia ou nao inicializada!\n");
        return;
    }

    fila->dados[fila->tamanho] = chamado; ///chamado é adicionado no final da arvore
    arrumar_acima(fila, fila->tamanho); ///vai posicionar o chamado na ordem de prioridade certa
    fila->tamanho++;
}

Chamado remover_chamado_maximo(FilaPrioridadeMaxima *fila)
{
    if (fila_prioridade_vazia(fila)==1) ///se a fila estiver vazia
    {
        Chamado chamado_de_erro;
        chamado_de_erro.id = -1;
        return chamado_de_erro;
    }

    Chamado maximo = fila->dados[0]; ///chamado de maior prioridade vai ser o removido
    
    fila->dados[0] = fila->dados[fila->tamanho - 1]; ///o 'topo' vai receber o chamado do final, para eliminar o topo
    fila->tamanho--; ///o chamado do final é removido
    
    arrumar_abaixo(fila, 0); ///vai colocar o chamado na posição correta
    
    return maximo; ///valor removido
}

int fila_prioridade_vazia(FilaPrioridadeMaxima *fila)
{
    if (fila == NULL)
    {
        return 1;
    }

    if (fila->tamanho == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void imprimir_heap(FilaPrioridadeMaxima *fila)
{
    if (fila_prioridade_vazia(fila)==1)
    {
        printf("Fila de prioridade (Heap) vazia.\n");
        return;
    }
    
    printf("Fila de prioridade (Heap) - %d chamados urgentes:\n", fila->tamanho);
    
    
    for (int i = 0; i < fila->tamanho; i++)
    {
        printf("  -> #%d: %s (prio %d)\n", fila->dados[i].id, fila->dados[i].descricao, fila->dados[i].prioridade);
    }
}


Chamado remover_heap_por_id(FilaPrioridadeMaxima *heap, int id) 
{
    Chamado retorno;
    retorno.id = -1; 

    if (heap == NULL || heap->tamanho == 0) return retorno;
    
    Chamado *temp_dados = (Chamado*) malloc(heap->capacidade * sizeof(Chamado));
    if (temp_dados == NULL) {
        printf("Erro critico: Sem memoria para backup do heap.\n");
        return retorno;
    }

    FilaPrioridadeMaxima aux;
    aux.tamanho = 0; 
    aux.dados = temp_dados;         
    aux.capacidade = heap->capacidade;
    
    while (fila_prioridade_vazia(heap) == 0) { //se o heap NAO esta vazia
        
        Chamado c = remover_chamado_maximo(heap); 

        if (c.id == id) {
            retorno = c;
        } else {
            inserir_chamado_heap(&aux, c);
        }
    }

    while (aux.tamanho > 0) {
        Chamado c = remover_chamado_maximo(&aux);
        inserir_chamado_heap(heap, c);
    }

    return retorno;
}


