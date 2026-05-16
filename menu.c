#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Contador de ID
static int nextChamadoId = 1;
static int nextTecnicoId =1;
static int nextItemId = 1;

static void limparBufferEntrada(void) {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}


void menuPrincipal(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap,
                   listaAtendimento *suspensos, arvoreEstoque *arvore_estoque,
                   arvoreTecnicos *arvore_tecnicos, listaAtendimento *atendimento, listaHistorico *historico)
{
	int opcao;
	int menu_atual = 1;

	inserirMenu(pilha, menu_atual);

	while (opcao != 0) {
		printf("\n=== SISTEMA DE HELP DESK ===\n");
		printf("\n-- Inicializando o sistema: --\n");
		printf("1. Registrar tecnicos\n");
		printf("2. Registrar itens no estoque\n");
		printf("3. Inserir itens ao estoque\n");
		printf("\n");
		printf("=================================\n");
		printf("\n");
		printf("4. Abrir chamado\n");
		printf("5. Atender chamado\n");
		printf("6. Finalizar chamado\n");
		printf("7. Cancelar chamado\n");
		printf("8. Ver histórico\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		printf("\n");
		printf("\n");

		limparBufferEntrada();

		switch (opcao) {
		case 1:
			inserirMenu(pilha, 2);
			registrarTecnicos(arvore_tecnicos, &nextTecnicoId, pilha);
			break;
		case 2:
			inserirMenu(pilha, 3);
			registrarItens(arvore_estoque, pilha, &nextItemId);
			break;
		case 3:
			inserirMenu(pilha, 4);
			abastecerEstoque(arvore_estoque, pilha, suspensos, heap);
			break;
		case 4:
			inserirMenu(pilha, 5);
			menuAbrirChamado(fila, heap, &nextChamadoId, pilha);
			break;
		case 5:
			inserirMenu(pilha, 6);
			menuAtenderChamado(fila, heap, pilha, suspensos, arvore_estoque, arvore_tecnicos, atendimento);
			break;
		case 6:
			inserirMenu(pilha, 6);
			menuFinalizarChamado(pilha, arvore_tecnicos, atendimento, historico);
			break;
		case 7:
			inserirMenu(pilha, 8);
			menuCancelarChamado(fila, pilha, heap, suspensos, atendimento, arvore_tecnicos, historico);
			break;
		case 8:
			inserirMenu(pilha, 9);
			menuVerEstruturas(fila, pilha, heap, atendimento, suspensos, arvore_tecnicos, arvore_estoque, historico);
			break;
		case 0:
			printf("Saindo do sistema...\n");
			removerMenu(pilha);
			break;
		default:
			printf("Opcao invalida!\n");
		}
	}
}

void registrarTecnicos(arvoreTecnicos *arvore, int *nextTecnicoIdId, PilhaMenus *pilha)
{
	Tecnico *novo=(Tecnico *)malloc(sizeof(Tecnico));
	if(novo==NULL)
	{
		printf("Erro ao registrar tecnico. \n");
		return;
	}
	printf("-- Registrando novo tecnico --\n");
	novo->id=(*nextTecnicoIdId)++;
	novo->ativos=criar_listaAtendimento();
	if(novo->ativos == NULL)
	{
	    printf("Erro na alocação de novo->ativos.\n");
	    removerMenu(pilha);
	    return;
	}
	printf("Digite o nome do tecnico: \n");
	fgets(novo->nome, sizeof(novo->nome), stdin);
	inserir_tecnico(arvore, *novo);
	printf("Tecnico %s (ID: %d) ADICIONADO\n", novo->nome, novo->id);
	limparBufferEntrada();
	removerMenu(pilha);
	return;
}

void registrarItens(arvoreEstoque *estoque, PilhaMenus *pilha, int *nextItemId)
{
	Item *novo=(Item*)malloc(sizeof(Item));
	if(novo==NULL)
	{
		printf("Erro ao registrar novo item.\n");
		removerMenu(pilha);
		return;
	}
	printf("-- Registrando novo item no estoque --\n");
	novo->id=(*nextItemId)++;
	printf("Qual item deseja adicionar ao estoque?\n");
	fgets(novo->nome, sizeof(novo->nome), stdin);
	printf("Qual quantidade deseja adicionar?\n");
	int quant=0;
	scanf("%d", &quant);
	novo->quantidade=quant;
	inserir_item(estoque, *novo);
	printf("\n");
	printf("Item %s (quantidade: %d)(ID: %d) ADICIONADO\n", novo->nome, novo->quantidade, novo->id);
	printf("\n");
	limparBufferEntrada();
	removerMenu(pilha);
	return;
}


void verificarSuspensos(arvoreEstoque *arvore, listaAtendimento *suspensos, FilaPrioridadeMaxima *heap)
{
	if(listaAtendimentoVazia(suspensos)==1)
	{
		printf("Lista de suspensos esta vazia.\n");
		return;
	}
	noAtendimento *aux=suspensos->inicio;

	while(aux != NULL)
	{
		int tem_tudo=1;
		noAtendimento *proximo=aux->proximo;
		for(int i=0; i<aux->dado.num_itens; i++)
		{
			Item *item=buscar_item(arvore, aux->dado.itens[i].id_estoque);
			if(item==NULL || item->quantidade < aux->dado.itens[i].quantidade)
			{
				tem_tudo=0;
				break;
			}
		}
		if(tem_tudo==1)
		{
			Chamado removido=aux->dado;
			removido.prioridade=6;
			inserir_chamado_heap(heap, removido);
			removerAtendimento_id(suspensos, aux->dado.id);
			printf("\n");
			printf("Chamado (ID: %d) movido para a fila de prioridade maxima.\n", removido.id);
		}
		aux=proximo;

	}

}

void abastecerEstoque(arvoreEstoque *arvore, PilhaMenus *pilha, listaAtendimento *suspensos, FilaPrioridadeMaxima *heap)
{
	printf("-- Abastecendo o estoque --\n");
	if(arvore->raiz==NULL)
	{
		printf("Estoque esta vazio.\n");
		removerMenu(pilha);
		return;
	}
	printf("Itens no estoque: \n");
	imprimir_estoque(arvore);
	printf("\n");
	printf("Digite o ID do item que deseja abastecer:\n");
	int dig=0;
	scanf("%d", &dig);
	printf("\n");
	Item *item=buscar_item(arvore, dig);
	if(item != NULL)
	{
		printf("Digite a quantidade que deseja ADICIONAR: \n");
		int quant=0;
		scanf("%d", &quant);
		item->quantidade=item->quantidade+quant;
		printf("Item abastecido.\n");
		printf("\n");
		printf("Verificando a lista de suspensos.\n");
		verificarSuspensos(arvore, suspensos, heap);
		limparBufferEntrada();
		removerMenu(pilha);
		return;
	}
	removerMenu(pilha);
	return;
}



void menuAbrirChamado(FilaNormal *fila, FilaPrioridadeMaxima *heap, int *nextChamadoId, PilhaMenus *pilha)
{
	Chamado chamado;

	printf("\n--- Abrir Novo Chamado ---\n");

	chamado.id = (*nextChamadoId)++;
	chamado.num_itens=0;

	printf("Descreva o problema: ");
	fgets(chamado.descricao, sizeof(chamado.descricao), stdin);


	printf("Digite a prioridade (0 = Normal, 1-5 = Urgente): ");
	int prio = 0;
	scanf("%d", &prio);
	limparBufferEntrada();
	if(prio < 0)
	{
		prio=0;
	}
	if (prio > 5)
	{
		prio =5;
	}

	chamado.prioridade=prio;

	if(prio == 0)
	{
		inserirNormal(fila, chamado);
		printf("Chamado (ID: %d) adicionado na fila normal", chamado.id);
	} else
	{
		inserir_chamado_heap(heap, chamado);
		printf("Chamado (ID: %d) adicionado na fila de prioridade", chamado.id);
	}

	limparBufferEntrada();
	printf("\n");
	removerMenu(pilha);
	return;
}


void menuAtenderChamado(FilaNormal *fila, FilaPrioridadeMaxima *heap, PilhaMenus *pilha, listaAtendimento *suspensos, arvoreEstoque *estoque, arvoreTecnicos *tecnicos, listaAtendimento *atendimento)
{
	Chamado chamado;
	printf("\n--- Atender Chamado ---\n");

	if (fila_prioridade_vazia(heap)==0) {
		chamado = remover_chamado_maximo(heap);
		printf("Atendendo URGENTE (prio %d): #%d - %s\n", chamado.prioridade, chamado.id, chamado.descricao);

	} else if (estaVaziaFila(fila)==0) {
		chamado = removerNormal(fila);
		printf("Atendendo NORMAL: #%d - %s\n", chamado.id, chamado.descricao);

	} else {
		printf("Nenhum chamado na fila.\n");
		removerMenu(pilha);
		return;
	}

	printf("Digite qual tecnico (ID) deseja solicitar: \n");
	int id_tecnico=0;
	imprimir_tecnicos(tecnicos);
	scanf("%d", &id_tecnico);
	limparBufferEntrada();
	Tecnico *tecnico = buscar_tecnico(tecnicos, id_tecnico);

	if (tecnico == NULL) {
		printf("ERRO: Tecnico ID %d nao encontrado!\n", id_tecnico);
		printf("O chamado #%d sera enchaminhado para a lista de suspensos por seguranca.\n", chamado.id);
		inserir_listaAtendimento(suspensos, chamado);
		removerMenu(pilha);
		return;
	}
	
	
	if(chamado.num_itens > 0)
	{
	    printf("\nATENCAO: Este chamado ja possui itens solicitados anteriormente:\n");
        for(int i=0; i<chamado.num_itens; i++) {
            Item *it = buscar_item(estoque, chamado.itens[i].id_estoque);
            printf(" - ID %d: %d unidades\n", chamado.itens[i].id_estoque, chamado.itens[i].quantidade);
        }
        printf("Deseja adicionar MAIS itens? (s/n): ");
    } else {
        printf("Esse chamado necessita de algum item do estoque? (s/n)\n");
    }
	
	
	char resp[2];
	fgets(resp, sizeof(resp), stdin);
	if(resp[0] == 's' || resp[0] == 'S')
	{
		imprimir_estoque(estoque);
		for(int i = 0; i < MAX_ITENS; i++) {
			printf("\nDigite o ID do item desejado (0 para encerrar):\n ");
			int id_item = 0;
			scanf("%d", &id_item);
			limparBufferEntrada();

			if(id_item == 0) break;

			Item *item = buscar_item(estoque, id_item);
			if(item == NULL) {
				printf("Item nao encontrado.\n");
				i--;
				continue;
			}

			printf("Digite a quantidade de '%s' que deseja: ", item->nome);
			int quantidade = 0;
			scanf("%d", &quantidade);
			limparBufferEntrada();

			chamado.itens[i].id_estoque = id_item;
			chamado.itens[i].quantidade = quantidade;
			chamado.num_itens++;
		}
	}

	if (chamado.num_itens > 0) {
		printf("\nVerificando disponibilidade no estoque...\n");
		for(int i = 0; i < chamado.num_itens; i++)
		{
			Item *item = buscar_item(estoque, chamado.itens[i].id_estoque);

			if(item == NULL || item->quantidade < chamado.itens[i].quantidade)
			{
				printf("[ESTOQUE INSUFICIENTE] Falta item ID %d.\n", chamado.itens[i].id_estoque);
				printf("Chamado movido para SUSPENSOS.\n");
				inserir_listaAtendimento(suspensos, chamado);
				removerMenu(pilha);
				return;
			}
		}

		for(int i = 0; i < chamado.num_itens; i++)
		{
			Item *item = buscar_item(estoque, chamado.itens[i].id_estoque);
			item->quantidade = item->quantidade - chamado.itens[i].quantidade;
		}
	}

	inserir_listaAtendimento(atendimento, chamado);
	inserir_listaAtendimento(tecnico->ativos, chamado);

	printf("\nSUCESSO: Chamado iniciado pelo tecnico %s.\n", tecnico->nome);

	removerMenu(pilha);
}

void menuFinalizarChamado(PilhaMenus *pilha, arvoreTecnicos *tecnicos, listaAtendimento *atendimento, listaHistorico *historico)
{
	printf("\n--- Finalizar Chamado  ---\n");
	printf("Digite o ID do tecnico que deseja finalizar o chamado:\n");
	int id_tecnico=0;
	imprimir_tecnicos(tecnicos);
	scanf("%d", &id_tecnico);
	limparBufferEntrada();
	Tecnico *tecnico=buscar_tecnico(tecnicos, id_tecnico);

	if (tecnico == NULL) {
		printf("Erro: Tecnico nao encontrado.\n");
		removerMenu(pilha);
		return;
	}

	if(listaAtendimentoVazia(tecnico->ativos)==1)
	{
		printf("Tecnico %s não possui chamados ativos no momento.\n", tecnico->nome);
		removerMenu(pilha);
		return;
	}

	printf("Esses são os chamados ativos atualmente do tecnico %s", tecnico->nome);
	imprimirListaAtendimento(tecnico->ativos);
	int id_chamado=0;
	printf("Digite o ID do chamado que deseja encerrar.\n");
	scanf("%d", &id_chamado);
	limparBufferEntrada();

	Chamado *chamado = buscar_atendimento_id(tecnico->ativos, id_chamado);
    if(chamado == NULL)
    {
        printf("Chamado não encontrado ou não existe.\n");
        removerMenu(pilha);
        return;
    }

	inserirHistorico(*chamado, *tecnico, historico, "Finalizado");
	printf("Chamado %d do tecnico %s arquivado!", chamado->id, tecnico->nome);

	removerAtendimento_id(tecnico->ativos, id_chamado);
	removerAtendimento_id(atendimento, id_chamado);

	printf("\n");
	removerMenu(pilha);
}

void menuCancelarChamado(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap, listaAtendimento *suspensos, listaAtendimento *atendimento, arvoreTecnicos *tecnicos, listaHistorico *historico)
{
	printf("\n--- Cancelar Chamado ---\n");
	printf("Onde o chamado esta atualmente?\n");
	printf("1. Na Fila Normal\n");
	printf("2. Na Fila Heap\n");
	printf("3. Na Lista de Suspensos\n");
	printf("4. Em Atendimento (Com Tecnico)\n");
	printf("0. Voltar\n");
	printf("Opcao: ");

	int opcao;
	scanf("%d", &opcao);
	limparBufferEntrada();

	Tecnico Sistema;
	Sistema.id = 0;
	strcpy(Sistema.nome, "CANCELADO PELO SISTEMA");
	Sistema.ativos = NULL;

	if(opcao == 0) {
		removerMenu(pilha);
		return;
	}

	int id_chamado = 0;

	if(opcao == 1)
	{
		imprimirFila(fila);
		printf("Digite o ID do chamado que deseja cancelar: ");
		scanf("%d", &id_chamado);
		limparBufferEntrada();

		Chamado removido = remover_normal_id(fila, id_chamado);

		if(removido.id == -1) {
			printf("Erro: Chamado nao encontrado.\n");
		} else {
			inserirHistorico(removido, Sistema, historico, "Cancelado (normal)");
		}
	}
	else if (opcao == 2)
	{
		imprimir_heap(heap);
		printf("Digite o ID do chamado que deseja cancelar: ");
		scanf("%d", &id_chamado);
		limparBufferEntrada();

		Chamado removido = remover_heap_por_id(heap, id_chamado);

		if(removido.id == -1) {
			printf("Erro: Chamado nao encontrado.\n");
		} else {
			inserirHistorico(removido, Sistema, historico, "Cancelado (heap)");
		}
	}
	else if (opcao == 3)
	{
		imprimirListaAtendimento(suspensos);
		printf("Digite o ID do chamado que deseja cancelar: ");
		scanf("%d", &id_chamado);
		limparBufferEntrada();

		Chamado *chamado = buscar_atendimento_id(suspensos, id_chamado);

		if(chamado == NULL) {
			printf("Erro: Chamado nao encontrado.\n");
		} else {
			Chamado removido = *chamado;
			inserirHistorico(removido, Sistema, historico, "Cancelado (suspensos)");
			removerAtendimento_id(suspensos, id_chamado);
		}
	}
	else if (opcao == 4)
	{
		imprimir_tecnicos(tecnicos);
		printf("Digite o ID do tecnico: ");
		int id_tecnico = 0;
		scanf("%d", &id_tecnico);
		limparBufferEntrada();

		Tecnico *tecnico = buscar_tecnico(tecnicos, id_tecnico);

		if (tecnico == NULL) {
			printf("Erro: Tecnico nao encontrado.\n");
			removerMenu(pilha);
			return;
		} else {
			imprimirListaAtendimento(tecnico->ativos);
			printf("Digite o ID do chamado: ");
			scanf("%d", &id_chamado);

			Chamado *chamado = buscar_atendimento_id(tecnico->ativos, id_chamado);

			if (chamado == NULL) {
				printf("Erro: Chamado nao encontrado com este tecnico.\n");
				removerMenu(pilha);
				return;
			} else {
				Chamado removido = *chamado;
				inserirHistorico(removido, *tecnico, historico, "Cancelado (atendimento)");
				removerAtendimento_id(tecnico->ativos, id_chamado);
				removerAtendimento_id(atendimento, id_chamado);
			}
		}
	}
	printf("Chamado inserido na lista de histórico com sucesso.\n");
	printf("\n");
	removerMenu(pilha);
}


void menuVerEstruturas(FilaNormal *fila, PilhaMenus *pilha, FilaPrioridadeMaxima *heap, listaAtendimento *atendimento, listaAtendimento *suspensos, arvoreTecnicos *tecnicos, arvoreEstoque *estoque, listaHistorico *historico)
{
	printf("\n--- Visualizacao das Estruturas ---\n");

    imprimirPilha(pilha);
    printf("\n");
    
    printf("[FILA NORMAL]:\n");
    imprimirFila(fila);
    printf("\n");
    
    printf("[HEAP]:\n");
    imprimir_heap(heap);
    printf("\n");
    
    printf("[EM ATENDIMENTO]:\n");
    imprimirListaAtendimento(atendimento);
    printf("\n");
    
    printf("[SUSPENSOS]:\n");
    imprimirListaAtendimento(suspensos);
    printf("\n");
    
    printf("[TECNICOS]:\n");
    imprimir_tecnicos(tecnicos);
    printf("\n");
    
    printf("[ESTOQUE]:\n");
    imprimir_estoque(estoque);
    printf("\n");
    
    imprimirHistorico(historico);

    removerMenu(pilha);
}