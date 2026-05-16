#ifndef BST_TECNICOS
#define BST_TECNICOS

#include "chamado.h"
#include "atendimento.h"

typedef struct Tecnico 
{
    int id;
    char nome[100];
    listaAtendimento *ativos;
} Tecnico;


typedef struct noTecnicos
{
    Tecnico dado;
    struct noTecnicos *direita;
    struct noTecnicos *esquerda;
} noTecnicos;

typedef struct arvoreTecnicos
{
    noTecnicos *raiz;
} arvoreTecnicos;

arvoreTecnicos *criar_tecnicos();
noTecnicos *criar_noTecnicos(Tecnico tecnico);
void inserir_tecnico(arvoreTecnicos* arvore, Tecnico tecnico);
Tecnico* buscar_tecnico(arvoreTecnicos* arvore, int id);
void imprimir_recursivamenteTecnicos(noTecnicos *atual);
void imprimir_tecnicos(arvoreTecnicos* arvore);
void liberar_recursivoTecnicos(noTecnicos* atual);
void liberar_tecnicos(arvoreTecnicos* arvore);

#endif