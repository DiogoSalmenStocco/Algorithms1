#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha_hist.h"

historico* criar_historico(){
  historico* h = (historico*) malloc(sizeof(historico));
  if(h == NULL){
    printf("Erro ao alocar memoria!\n");
    exit(1);
  }
  h->topo = -1;
  return h;
}
void inserir_procedimento(historico *h, char procedimento[100],int id){
  if(h->topo < 9){
    h->topo++;
    strcpy(h->procedimento[h->topo], procedimento);
    // Salvar procedimento em arquivo
    char filename[256];
    sprintf(filename, "historico_%d.txt", h->topo); // Nome do arquivo baseado no id do paciente
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", procedimento);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
    }
  } else {
    printf("Historico cheio! Não é possivel inserir mais procedimentos.\n");
  }
}
historico* abrir_historico(int id){
  char filename[256];  
  sprintf(filename, "%d.txt", id); // Nome do arquivo baseado no id do paciente  
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return NULL;
  }
  historico* historico = criar_historico();
  char procedimento[100];
  while (fgets(procedimento, sizeof(procedimento), file)) {
      procedimento[strcspn(procedimento, "\n")] = 0; 
      inserir_procedimento(historico, procedimento, id);
}
fclose(file);
return historico;
}
bool historico_vazio(historico *h){
  if (h->topo == -1){
    return true;
  } else {
    return false;
  }
}
void desfazer_procedimento(historico *h){
  if(h->topo >= 0){
    h->topo--;
  } else if(historico_vazio(h)){
    printf("Historico vazio! Não é possivel desfazer procedimentos.\n");
  }
}
bool historico_cheio(historico *h){
  if(h->topo == 9){
    return true;
  } else {
    return false;
  } 
}
void consultar_procedimentos(int id){
  historico* historico = abrir_historico(id);
  if (historico == NULL) {
      printf("Nenhum historico encontrado para o ID %d.\n", id);
      return NULL;
  }
  printf("Procedimentos do paciente com ID %d:\n", id);
  for (int i = 0; i <= historico->topo; i++) {
      printf("%s\n", historico->procedimento[i]);
  }
return historico;
}