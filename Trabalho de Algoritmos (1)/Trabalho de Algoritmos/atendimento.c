#include "FilaEspera/heap.h" // Inclui o cabeçalho da Fila de Prioridade
#include "ListaSistema/Lista.h"
#include "ListaSistema/Historico/Pilha_hist.h"
#include "SaveLoad/IO1.h" // Inclui as funcoes SAVE/LOAD
#include "atendimento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessario para strdup
#include <unistd.h> // Para a funcao remove() (remover arquivo)

// Função auxiliar para aguardar o usuário pressionar Enter antes de limpar a tela.
void pausa_tela() {
    printf("\n\nPressione ENTER para continuar...");
    // 1. Limpa o buffer de entrada (se houver sobras)
    while (getchar() != '\n' && getchar() != EOF); 
    // 2. Aguarda a próxima tecla ENTER ser pressionada
    getchar(); 
    system("cls"); // Limpa a tela (comando Windows)
}

// Funcao auxiliar para obter paciente do Heap (maior prioridade) e mover para a lista
void chamar_paciente(Lista* lista_sistema, HEAP* Hfila_espera) { 
    if (vazia(Hfila_espera)) {
        printf("Nao ha pacientes na fila de espera para chamar.\n");
        return;
    }
    
    // Remove o paciente de MAIOR PRIORIDADE
    NOH_HEAP paciente_atendido_no = remover_heap(Hfila_espera);
    paciente_h* paciente_atendido = paciente_atendido_no.paciente; // O nó paciente_h*

    // Verifica se ja esta na lista principal.
    paciente_h* existente = buscar_paciente_noh(lista_sistema, paciente_atendido->id); 
    
    if (existente == NULL) {
        // Se nao existe, insere o paciente na Lista Principal
        // O paciente_h* foi criado no case 1 e agora é transferido para a lista.
        bool inserido = inserir_paciente_fim(lista_sistema, paciente_atendido->nome, paciente_atendido->id); 
        if (inserido) {
            printf("Paciente %s (ID %d) registrado na Lista de Atendimentos.\n", paciente_atendido->nome, paciente_atendido->id);
        } else {
            printf("Erro ao registrar paciente na Lista de Atendimentos.\n");
        }
    } else {
        printf("Paciente %s (ID %d) ja estava registrado, apenas removido da Fila de espera.\n", paciente_atendido->nome, paciente_atendido->id);
    }
}

int main(){
  int operacao = 0, id = 0, prioridade = 0;
  char nome_input[100]; 
  
  // Estruturas centrais
  Lista lista_sistema;
  inicializar(&lista_sistema);
  
  HEAP* espera = criar_heap(); // HEAP*

  // LOAD carrega os dados salvos ao iniciar
  LOAD(&lista_sistema, NULL, espera); 

  do
  {
    printf("\n==================================\n");
    printf("     Atendimento do Hospital\n");
    printf("==================================\n");
    printf("[1] - Registrar paciente (Adiciona a Fila de Espera).\n");
    printf("[2] - Registrar obito de paciente (Remove do Sistema).\n");  
    printf("[3] - Adicionar procedimento ao historico.\n");  
    printf("[4] - Desfazer procedimento do historico.\n");
    printf("[5] - Chamar paciente para atendimento.\n");  
    printf("[6] - Mostrar fila de espera.\n");  
    printf("[7] - Mostrar historico do paciente.\n");
    printf("[8] - Sair.\n");
    printf("Escolha a operacao: ");
    
    if (scanf("%d", &operacao) != 1) {
        operacao = 0; 
        while (getchar() != '\n'); 
        continue;
    }
    
    switch (operacao)
    {
    case 1: //Registrar paciente
    { 
      printf("Digite o nome do paciente: ");
      scanf("%s", nome_input); 
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      printf("Digite o nível de prioridade do paciente: ");
      scanf("%d", &prioridade);

      // 1. VALIDACAO: Checar se o ID ja esta na Lista Principal 
      paciente_h* paciente_existente_lista = buscar_paciente_noh(&lista_sistema, id);
      if (paciente_existente_lista != NULL) {
          printf("\nERRO: Paciente com ID %d ja esta registrado no sistema principal (%s).\n", id, paciente_existente_lista->nome);
          break;
      }
      
      // 2. VALIDACAO: Checar se o ID ja esta na Fila de Espera (HEAP*)
      if (buscar_heap(espera, id) == true) { // Passa HEAP*
          printf("\nERRO: Paciente com ID %d ja se encontra na fila de espera.\n", id);
          break;
      }
      
      // --- CRIAÇÃO DO NÓ paciente_h QUE SERÁ INSERIDO NO HEAP ---
      paciente_h* novo_paciente_node = (paciente_h*)malloc(sizeof(paciente_h));
      if (novo_paciente_node == NULL) { printf("Erro de alocacao de memoria para o paciente.\n"); break; }

      // Inicializa os campos
      novo_paciente_node->nome = strdup(nome_input);
      if (novo_paciente_node->nome == NULL) { free(novo_paciente_node); printf("Erro de alocacao de memoria para o nome.\n"); break; }
      
      novo_paciente_node->id = id;
      novo_paciente_node->prox = NULL; 
      novo_paciente_node->h = criar_historico(); 

      // Inserir paciente_h* no Heap
      inserir_heap(espera, novo_paciente_node, prioridade); 
      break;
    }

    case 2: //Registrar obito de paciente
    { // Bloco de escopo
      printf("Digite o id do paciente a ser removido (obito/saida): ");
      scanf("%d", &id);
      
      if (apagar_paciente(&lista_sistema, id)) {
          printf("Paciente %d removido da lista principal e memoria liberada.\n", id);
          
          char filename[256];
          sprintf(filename, "historico_%d.txt", id);
          if (remove(filename) == 0) {
              printf("Arquivo de historico %s removido.\n", filename);
          } else {
              printf("Aviso: Arquivo de historico %s nao encontrado ou nao removido.\n", filename);
          }
      } else {
          printf("Paciente %d nao encontrado na lista principal.\n", id);
      }
      break;
    }

    case 3: //Adicionar procedimento ao historico medico
    { // Bloco de escopo
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      
      paciente_h* paciente_h_proc = buscar_paciente_noh(&lista_sistema, id);
      if (paciente_h_proc == NULL) {
          printf("Paciente nao encontrado na lista principal. Registre o paciente primeiro.\n");
          break;
      }
      
      char procedimento[100];
      printf("Digite o procedimento a ser adicionado (max 99 caracteres, sem espacos): ");
      scanf("%s", procedimento); 
      
      inserir_procedimento(paciente_h_proc->h, procedimento, id);
      break;
    }
      
    case 4: //Desfazer procedimento do historico medico
    { // Bloco de escopo
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      
      paciente_h* paciente_h_undo = buscar_paciente_noh(&lista_sistema, id);
      if (paciente_h_undo == NULL) {
          printf("Paciente nao encontrado na lista principal.\n");
          break;
      }
      
      // Passa o ID para atualizar o arquivo de persistencia
      desfazer_procedimento(paciente_h_undo->h, id); 
      break;
    }

    case 5: //Chamar paciente para atendimento
      chamar_paciente(&lista_sistema, espera); // Passa HEAP*
      break;

    case 6: //Mostrar fila de espera
      imprimir_ordenado(espera); // Passa HEAP*
      break;

    case 7: //Mostrar historico do paciente
      printf("Digite o id do paciente: ");
      scanf("%d", &id); 
      
      consultar_procedimentos(id); 
      break;

    case 8: //Sair
      SAVE(&lista_sistema, NULL, espera); // Passa HEAP*
      printf("Saindo do sistema. Dados salvos.\n");
      break;

    default:
      printf("Opcao invalida. Tente novamente.\n");
      break;
    }
    
    // Limpa o buffer de entrada (se houver sobras)
    while (getchar() != '\n'); 
    
    // Pausa a tela para que o usuário possa ler as mensagens do case antes de limpar
    if (operacao != 8) { // Não pausa se for sair
        pausa_tela();
    }

  }while(operacao != 8);
  
  liberar_heap(espera); 
  return 0;
}