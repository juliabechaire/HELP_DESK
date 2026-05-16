#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h" 
#include "chamado.h"

listaAtendimento *criar_listaAtendimento()
{
    listaAtendimento *novo=(listaAtendimento*)malloc(sizeof(listaAtendimento));
    if(novo ==NULL){return NULL;}
    novo->inicio=NULL;
    novo->fim=NULL;
    novo->tamanho=0;
    return novo;
}

void inserir_listaAtendimento(listaAtendimento *lista, Chamado chamado)
{
    noAtendimento *novo=(noAtendimento*)malloc(sizeof(noAtendimento));
    if(novo==NULL)
    {
        printf("Erro na alocação de memoria para a fila de atendimentos. \n");
        return;
    }
    novo->dado=chamado;
    novo->proximo=NULL;
    if(lista->inicio==NULL)
    {
        lista->inicio=novo;
        lista->fim=novo;
        novo->anterior=NULL;
    } else
    {
        lista->fim->proximo=novo;
        novo->anterior=lista->fim;
        lista->fim=novo;
    }
    lista->tamanho++;
}

Chamado remover_listaAtendimento(listaAtendimento *lista)
{
    if (listaAtendimentoVazia(lista) == 1) {
        Chamado erro;
        erro.id = -1; 
        return erro;
    }
    noAtendimento *temp=lista->inicio;
    Chamado chamado_removido=temp->dado;
    lista->inicio=lista->inicio->proximo;
    if(lista->inicio==NULL)
    {
        lista->fim=NULL;
    } else{
        lista->inicio->anterior=NULL;
    }
    free(temp);
    lista->tamanho--;
    return chamado_removido;
}

void liberar_listaAtendimento(listaAtendimento *lista)
{
    if(lista==NULL){return;}
    noAtendimento *temp=lista->inicio;
    while(temp != NULL){
        noAtendimento *aux=temp;
        temp=temp->proximo;
        free(aux);
    }
    free(lista);
}

void imprimirListaAtendimento(listaAtendimento *lista)
{

    if (listaAtendimentoVazia(lista) == 1) { 
        printf("Nenhum chamado em atendimento no momento.\n");
        return;
    }

    noAtendimento *atual = lista->inicio;
    while (atual != NULL) {
        printf("  [ID: %d] (Prio: %d) - %s", 
               atual->dado.id, 
               atual->dado.prioridade, 
               atual->dado.descricao);
        atual = atual->proximo;
    }
    printf("\n");
}

int listaAtendimentoVazia(listaAtendimento *lista)
{
    if (lista == NULL) return 1;
    if(lista->tamanho==0)
    {
        return 1; 
    } else
    {
        return 0;
    }
}

void removerAtendimento_id(listaAtendimento *lista, int id)
{
    if(lista == NULL || lista->inicio == NULL)
    {
        return;
    }
    noAtendimento *atual=lista->inicio;
    while(atual != NULL)
    {
        if(atual->dado.id == id) 
        {
            if(atual->anterior != NULL) 
            {
                atual->anterior->proximo = atual->proximo;
            } 
            else 
            {
                lista->inicio = atual->proximo;
            }
            if(atual->proximo != NULL) 
            {
                atual->proximo->anterior = atual->anterior;
            } 
            else 
            {
                lista->fim = atual->anterior;
            }
            free(atual);
            lista->tamanho--;
            return;
        }
        atual=atual->proximo;
    }
}


Chamado *buscar_atendimento_id(listaAtendimento *lista, int id)
{
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }

    noAtendimento *atual = lista->inicio;

    while(atual != NULL)
    {
        if(atual->dado.id==id)
        {
            return &(atual->dado);
        }
       atual = atual->proximo; 
    } 
    return NULL;
}



