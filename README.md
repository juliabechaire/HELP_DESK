# 🛠️ Help Desk - Sistema de Atendimento

Este projeto foi desenvolvido como trabalho prático durante o 2º semestre do curso de **Engenharia de Computação**, para a disciplina de **Estrutura de Dados**. O objetivo principal foi aplicar conceitos teóricos de estruturas de dados na criação de um sistema de gerenciamento de chamados e suporte técnico (Help Desk) utilizando a linguagem **C**.

---

## 🚀 Conceitos de Estrutura de Dados Aplicados

Para resolver os problemas de organização, ordenação e prioridade dos chamados de suporte, foram implementadas as seguintes estruturas:

* **Filas Dinâmicas (Queue):** Utilizadas para gerenciar a ordem de chegada dos chamados de suporte convencionais (atendimento por ordem de chegada - FIFO).
* **Listas Encadeadas (Linked List):** Aplicadas para o armazenamento e manipulação do histórico de chamados concluídos e cadastro de usuários, permitindo inserção e remoção dinâmica sem desperdício de memória.
* **Alocação Dinâmica de Memória:** Uso estratégico de `malloc` e `free` para garantir que o sistema utilize apenas a memória necessária em tempo de execução, evitando *memory leaks*.
* **Ponteiros e Structs:** Base para a construção de nós (*nodes*) que interconectam as informações do sistema de forma eficiente.

---

## 💻 Funcionalidades do Sistema

* **Abertura de Chamados:** Cadastro de novas solicitações com descrição do problema, categoria e dados do usuário.
* **Fila de Atendimento:** Processamento de chamados seguindo a ordem correta de requisição.
* **Histórico de Suporte:** Consulta e listagem de chamados já encerrados ou resolvidos.

---
