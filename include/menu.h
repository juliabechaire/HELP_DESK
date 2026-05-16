
#ifndef MENU_H
#define MENU_H

#include "fila_normal.h"
#include "fila_prioridade_maxima.h"
#include "pilha_menus.h"
#include "atendimento.h"
#include "bst_tecnicos.h"
#include "bst_estoque.h"
#include "historico.h"
#include "chamado.h"


void menuPrincipal(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap, 
                   listaAtendimento *suspensos, arvoreEstoque *arvore_estoque,
                   arvoreTecnicos *arvore_tecnicos, listaAtendimento *atendimento, listaHistorico *historico);
void menuAbrirChamado(FilaNormal *fila, FilaPrioridadeMaxima *heap, int *nextChamadoId, PilhaMenus *pilha);
void menuAtenderChamado(FilaNormal *fila, FilaPrioridadeMaxima *heap, PilhaMenus *pilha, listaAtendimento *suspensos, arvoreEstoque *estoque, arvoreTecnicos *tecnicos, listaAtendimento *atendimento);
void menuVerEstruturas(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap, listaAtendimento *atendimento, listaAtendimento *suspensos, arvoreTecnicos *tecnicos, arvoreEstoque *estoque, listaHistorico *historico);

void registrarTecnicos(arvoreTecnicos *arvore, int *nextTecnicoIdId, PilhaMenus *pilha);
void registrarItens(arvoreEstoque *estoque, PilhaMenus *pilha, int *nextItemId);
void abastecerEstoque(arvoreEstoque *arvore, PilhaMenus *pilha, listaAtendimento *suspensos, FilaPrioridadeMaxima *heap);

void verificarSuspensos(arvoreEstoque *arvore, listaAtendimento *suspensos, FilaPrioridadeMaxima *heap);
void menuFinalizarChamado(PilhaMenus *pilha, arvoreTecnicos *tecnicos, listaAtendimento *atendimento, listaHistorico *historico); 
void menuCancelarChamado(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap, listaAtendimento *suspensos, listaAtendimento *atendimento, arvoreTecnicos *tecnicos, listaHistorico *historico);


#endif 