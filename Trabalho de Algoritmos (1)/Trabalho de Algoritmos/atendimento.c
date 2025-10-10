#include "FilaEspera/Fila.h"
#include "ListaSistema/Lista.h"
#include "ListaSistema/Historico/Pilha_hist.h"
#include "atendimento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessario para strdup
#include <unistd.h> // Para a funcao remove() (remover arquivo)

// Funcao auxiliar para obter paciente da fila e move-lo para a lista
void chamar_paciente(Lista* lista_sistema, Fila* fila_espera) {
    if (Fila_vazia(*fila_espera)) {
        printf("Nao ha pacientes na fila de espera para chamar.\n");
        return;
    }
    
    // Remove o paciente mais antigo da fila
    paciente_f paciente_atendido = remover_paciente_f(fila_espera);
    
    // Verifica se ja esta na lista principal. Se nao estiver, insere.
    paciente_h* existente = buscar_paciente_noh(lista_sistema, paciente_atendido.id);
    
    if (existente == NULL) {
        // Assume que o nome em paciente_f e um ponteiro alocado com strdup em case 1.
        bool inserido = inserir_paciente_in(lista_sistema, paciente_atendido.nome, paciente_atendido.id);
        if (inserido) {
            printf("Paciente %s (ID %d) registrado na Lista de Atendimentos.\n", paciente_atendido.nome, paciente_atendido.id);
        } else {
            printf("Erro ao registrar paciente na Lista de Atendimentos.\n");
        }
    } else {
        printf("Paciente %s (ID %d) ja estava registrado, apenas removido da Fila de espera.\n", paciente_atendido.nome, paciente_atendido.id);
    }
    
    // Libera a memoria do nome que foi alocado para o paciente na fila
    if (paciente_atendido.nome) free(paciente_atendido.nome);
}

int main(){
  int operacao = 0, id = 0;
  char nome_input[100]; // Buffer local para leitura (correcao para evitar segfault)
  
  // Estruturas centrais
  Lista lista_sistema;
  inicializar(&lista_sistema); // Inicializa a lista principal
  
  Fila espera = criar_Fila(); // Inicializa a fila

  // Implementacao do LOAD deve vir aqui

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
        operacao = 0; // Entrada invalida
        while (getchar() != '\n'); // Limpa o buffer de entrada
        system("clear");
        continue;
    }
    
    switch (operacao)
    {
    case 1: //Registrar paciente
      printf("Digite o nome do paciente: ");
      scanf("%s", nome_input); 
      printf("Digite o id do paciente: ");
      scanf("%d", &id);

      paciente_f novo_paciente;
      // Aloca e copia o nome para a struct da fila
      novo_paciente.nome = strdup(nome_input); 
      if (novo_paciente.nome == NULL) {
          printf("Erro de alocacao de memoria para o nome.\n");
          break;
      }
      novo_paciente.id = id;
      
      inserir_paciente_f(&espera, novo_paciente);
      break;

    case 2: //Registrar obito de paciente
      printf("Digite o id do paciente a ser removido (obito/saida): ");
      scanf("%d", &id);
      
      // Tenta remover da lista principal
      if (apagar_paciente(&lista_sistema, id)) {
          printf("Paciente %d removido da lista principal e memoria liberada.\n", id);
          
          // Opcional: Remover o arquivo de historico
          char filename[256];
          sprintf(filename, "historico_%d.txt", id);
          if (remove(filename) == 0) {
              printf("Arquivo de historico %s removido.\n", filename);
          } else {
              // Nao e um erro se o arquivo nunca foi criado
              printf("Aviso: Arquivo de historico %s nao encontrado ou nao removido.\n", filename);
          }
      } else {
          printf("Paciente %d nao encontrado na lista principal.\n", id);
      }
      break;

    case 3: //Adicionar procedimento ao historico medico
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      
      paciente_h* paciente_h = buscar_paciente_noh(&lista_sistema, id);
      if (paciente_h == NULL) {
          printf("Paciente nao encontrado na lista principal. Registre o paciente primeiro.\n");
          break;
      }
      
      char procedimento[100];
      printf("Digite o procedimento a ser adicionado (max 99 caracteres, sem espacos): ");
      scanf("%s", procedimento); 
      
      inserir_procedimento(paciente_h->h, procedimento, id);
      break;
      
    case 4: //Desfazer procedimento do historico medico
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      
      paciente_h = buscar_paciente_noh(&lista_sistema, id);
      if (paciente_h == NULL) {
          printf("Paciente nao encontrado na lista principal.\n");
          break;
      }
      
      desfazer_procedimento(paciente_h->h);
      break;

    case 5: //Chamar paciente para atendimento
      chamar_paciente(&lista_sistema, &espera);
      break;

    case 6: //Mostrar fila de espera
      mostrar_todos_f(&espera);
      break;

    case 7: //Mostrar historico do paciente
      printf("Digite o id do paciente: ");
      scanf("%d", &id);
      
      consultar_procedimentos(id); 
      break;

    case 8: //Sair
      // Implementacao do SAVE deve vir aqui
      printf("Saindo do sistema.\n");
      break;

    default:
      printf("Opcao invalida. Tente novamente.\n");
      break;
    }
    
    // Limpar o buffer de entrada apos o scanf
    while (getchar() != '\n'); 
    
    system("clear");
  }while(operacao != 8);
  
  return 0;
}