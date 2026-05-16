#include <stdio.h>
#include <stdlib.h>
#include "fila_normal.h"

FilaNormal* criarFilaNormal() {
    FilaNormal *novo = (FilaNormal*) malloc(sizeof(FilaNormal));
    if (novo == NULL) {
        printf("Erro de alocacao para a fila normal!\n");
        return NULL;
    }
    novo->inicio = NULL;
    novo->fim = NULL;
    novo->tamanho = 0;
    return novo;
}

void liberarFilaNormal(FilaNormal *fila) {
    if (fila == NULL) {
        return;
    }
    
    NoFila *atual = fila->inicio;
    while (atual != NULL) {
        NoFila *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(fila);
}

int estaVaziaFila(FilaNormal *fila)
{
    if (fila == NULL)
    {
        return 1;
    }

    if (fila->inicio == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserirNormal(FilaNormal *fila, Chamado chamado) { ///em filas FIFO, sempre se adiona no FINAL
    if (fila == NULL) {
        printf("Erro: Fila normal nao foi criada.\n");
        return;
    }
    
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro de alocacao de no na fila\n");
        return;
    }
    
    novo->dado = chamado;
    novo->proximo = NULL;
    
    if (fila->fim == NULL) { 
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
}

// Remove e retorna o chamado do início da fila 
Chamado removerNormal(FilaNormal *fila)
{
    if (estaVaziaFila(fila)==1) ///se a fila estiver vazia
    {
        Chamado chamado_de_erro;
        chamado_de_erro.id = -1;
        return chamado_de_erro;
    }

    NoFila *no_removido = fila->inicio; 
    Chamado chamado_valido = no_removido->dado;

    fila->inicio = no_removido->proximo;

    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    free(no_removido);
    fila->tamanho--;
    
    return chamado_valido;
}

void imprimirFila(FilaNormal *fila)
{
    if (estaVaziaFila(fila)==1)
    {
        printf("Fila de chamados normais vazia.\n");
        return;
    }

    printf("Fila de chamados normais (inicio -> fim):\n");
    
    NoFila *aux = fila->inicio;

    while (aux != NULL)
    {
        printf("  -> #%d: %s (prio %d)\n", aux->dado.id, aux->dado.descricao, aux->dado.prioridade);
        
        aux = aux->proximo;
    }
}

Chamado remover_normal_id(FilaNormal *fila, int id)
{
    Chamado erro;
    erro.id = -1; 

    if(fila == NULL || fila->inicio == NULL)
    {
        return erro;
    }

    NoFila *atual = fila->inicio;
    NoFila *anterior = NULL;

    while(atual != NULL)
    {
        if(atual->dado.id == id)  //quando achar o chamado 
        {
            Chamado retorno = atual->dado;
            
            if(anterior == NULL) //se for o primeiro
            {
                fila->inicio = atual->proximo;
                if(fila->inicio == NULL) //se ficar vazia
                    fila->fim = NULL;
            } else
            {
                anterior->proximo = atual->proximo; //remove
                if(atual->proximo == NULL)
                    fila->fim = anterior;
            }

            free(atual);
            fila->tamanho--;
            return retorno;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return erro; 
}



