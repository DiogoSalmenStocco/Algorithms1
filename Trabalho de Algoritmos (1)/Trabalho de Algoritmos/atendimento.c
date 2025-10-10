#include "FilaEspera/Fila.h"
#include "ListaSistema/Lista.h"
#include "ListaSistema/Historico/Pilha_hist.h"
#include "atendimento.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  int operacao = 0, id = 0;
  char *nome;
  Fila* espera = criar_fila(10);
  
  do
  {
    printf("Atendimento do hospital\n");
    printf("Escolha qual operação deseja fazer:\n");
    printf("[1] - Registrar paciente.\n");
    printf("[2] - Registrar óbito de paciente.\n");  
    printf("[3] - Adicionar procedimento ao histório.\n");  
    printf("[4] - Desfazer procedimento do histórico.\n");
    printf("[5] - Chamar paciente para atendimento.\n");  
    printf("[6] - Mostrar fila de espera.\n");  
    printf("[7] - Mostrar histórico do paciente.\n");
    printf("[8] - Sair.\n");
    scanf("%d", &operacao);
    switch (operacao)
    {
    case 1: //Registrar paciente
      scanf("Digite o nome do paciente:%s\n", nome);
      scanf("Digite o id do paciente:%d", &id);
      paciente_f novo_paciente;
      novo_paciente.nome = nome;
      novo_paciente.id = id;
      inserir_paciente_f(espera, &novo_paciente);
      break;

    case 2: //Registrar óbito de paciente
    // verificar se ele ta na fila
    // apagar ele fila e seu histórico
      break;

    case 3: //Adicionar procedimento ao histórico médico
      scanf("Digite o id do paciente: %d", &id);
      historico* historico1 = criar_historico();
      char procedimento[100];
      scanf("Digite o procedimento a ser adicionado:%s", procedimento);
      inserir_procedimento(historico1, procedimento, id);
      break;
      
    case 4: //Desfazer procedimento do histórico médico
    // desfaz o último procedimento feito
      scanf("Digite o id do paciente:%d", &id);
      historico* h = abrir_historico(id);
      desfazer_procedimento_historico(h);
      break;

    case 5: //Chamar paciente para atendimento
      scanf("Digite o nome do paciente:%s\n", nome);
      scanf("Digite o id do paciente:%d", &id);
      
      break;

    case 6: //Mostrar fila de espera
    //printf em geral, acho 
      
      break;

    case 7: //Mostrar histórico do paciente
      scanf("Digite o id do paciente:%d", &id);
      consultar_procedimentos(id);
      break;

    case 8: //Sair
      
      break;

    default:
      break;
    }
    getchar();
    getchar();
    system("clear");
  }while(operacao != 8);
}