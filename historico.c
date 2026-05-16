#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

listaHistorico *criarHistorico()
{
    listaHistorico *novo=(listaHistorico*)malloc(sizeof(listaHistorico));
    if(novo==NULL)
    {
        printf("Erro na alocação de memoria do historico. \n");
        return NULL;
    }
    novo->primeiro=NULL;
    novo->ultimo=NULL;
    novo->tamanho=0;
    return novo;
}

void inserirHistorico(Chamado chamado, Tecnico tecnico, listaHistorico *lista, const char *status)
{
    noHistorico *novo=(noHistorico*)malloc(sizeof(noHistorico));
    if(novo==NULL)
    {
        printf("Erro na alocação do noHistorico. \n");
        return;
    }
    novo->tecnico=tecnico;
    novo->chamado=chamado;
    novo->tecnico.ativos = NULL;
    
    strncpy(novo->registro, status, sizeof(novo->registro) - 1);

    if(lista->primeiro==NULL)
    {
        lista->primeiro=novo;
        lista->ultimo=novo;
        novo->proximo=NULL;
    } else //insere no INICIO
    {
        novo->proximo=lista->primeiro;
        lista->primeiro=novo;
    }
    lista->tamanho++;
}

void imprimirHistorico(listaHistorico *lista)
{
    if(lista->primeiro == NULL)
    {
        printf("Lista de históricos esta vazia.\n");
        return;
    }
    noHistorico *temp=lista->primeiro;
    printf("\n=== LISTA DE HISTÓRICO (Total: %d) ===\n", lista->tamanho);
    while(temp!=NULL)
    {
        printf("ID chamado: %d; Tecnico responsável: %s; Registro: %s \n", temp->chamado.id, temp->tecnico.nome, temp->registro);
        temp=temp->proximo;
    }
    printf("======================================\n");
}

void liberarHistorico(listaHistorico *lista)
{
    if(lista == NULL)
    {
        return;
    }
    noHistorico *atual = lista->primeiro;
    while(atual != NULL)
    {
        noHistorico *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}



