#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_normal.h"
#include "fila_prioridade_maxima.h"
#include "pilha_menus.h"
#include "atendimento.h"
#include "bst_tecnicos.h"
#include "bst_estoque.h"
#include "historico.h"
#include "chamado.h"
#include "menu.h"



int main() {
    FilaNormal *fila = criarFilaNormal();
    PilhaMenus *pilha = criarPilha();
    FilaPrioridadeMaxima *heap = criar_fila_prioridade_maxima(FILA_PRIORIDADE_CAP);
    listaAtendimento *suspensos = criar_listaAtendimento();
    listaAtendimento *atendimento = criar_listaAtendimento();
    arvoreEstoque *estoque = criar_estoque();
    arvoreTecnicos *tecnicos = criar_tecnicos();
    listaHistorico *historico = criarHistorico();
    
    if (fila == NULL || pilha == NULL || heap == NULL || suspensos == NULL || estoque == NULL || tecnicos == NULL || atendimento ==NULL || historico == NULL) {
        printf("Falha critica ao alocar memoria para estruturas de dados. Encerrando.\n");
        liberarFilaNormal(fila);
        liberarPilha(pilha);
        liberar_fila_prioridade(heap);
        liberar_listaAtendimento(suspensos);
        liberar_listaAtendimento(atendimento);
        liberar_tecnicos(tecnicos);
        liberar_estoque(estoque);
        liberarHistorico(historico);
        return 1;
    }

    menuPrincipal(fila, pilha, heap, suspensos, estoque, tecnicos, atendimento, historico);

    liberarFilaNormal(fila);
    liberarPilha(pilha);
    liberar_fila_prioridade(heap);
    liberar_listaAtendimento(suspensos);
    liberar_tecnicos(tecnicos);
    liberar_estoque(estoque);
    liberar_listaAtendimento(atendimento);
    liberarHistorico(historico);
    
    printf("Sistema encerrado com sucesso.\n");
    return 0;
}