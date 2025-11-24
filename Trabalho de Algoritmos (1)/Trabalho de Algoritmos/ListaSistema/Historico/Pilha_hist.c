#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha_hist.h"

void reescrever_historico_disco(historico *h, int id) {
    char filename[256];
    sprintf(filename, "historico_%d.txt", id);
    FILE *file = fopen(filename, "w"); // Usamos "w" para SOBRESCREVER o arquivo
    if (file != NULL) {
        // Escreve apenas os procedimentos que ainda estao na pilha (de 0 ate o novo topo)
        for (int i = 0; i <= h->topo; i++) { 
            fprintf(file, "%s\n", h->procedimento[i]);
        }
        fclose(file);
    } else {
        printf("Erro ao reescrever o arquivo de historico %s.\n", filename);
    }
}

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
    // Copia o procedimento para a pilha na memoria
    strcpy(h->procedimento[h->topo], procedimento);
    
    // Salva o procedimento no arquivo do paciente, usando o ID correto
    char filename[256];
    sprintf(filename, "historico_%d.txt", id); // Correcao: usar o ID do paciente de forma consistente
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", procedimento);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
    }
  } else {
    printf("Historico cheio! Nao e possivel inserir mais procedimentos.\n");
  }
}
historico* abrir_historico(int id){
  char filename[256];  
  sprintf(filename, "historico_%d.txt", id); // Correcao: usar o prefixo consistente
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
      // Se nao houver arquivo, retorna NULL
      return NULL;
  }
  historico* h = criar_historico();
  char procedimento[100];
  while (fgets(procedimento, sizeof(procedimento), file)) {
      procedimento[strcspn(procedimento, "\n")] = 0; 
      // Carrega para a struct na memoria, nao insere no arquivo novamente
      if (h->topo < 9) {
          h->topo++;
          strcpy(h->procedimento[h->topo], procedimento);
      }
  }
  fclose(file);
  return h;
}
bool historico_vazio(historico *h){
  if (h->topo == -1){
    return true;
  } else {
    return false;
  }
}
void desfazer_procedimento(historico *h, int id){
  if(h->topo >= 0){
    h->topo--;
    printf("Ultimo procedimento desfeito na memoria (topo=%d).\n", h->topo);
    reescrever_historico_disco(h, id); // <--- CORREÇÃO: Atualiza o arquivo
  } else if(historico_vazio(h)){
    printf("Historico vazio! Nao e possivel desfazer procedimentos.\n");
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
  historico* h = abrir_historico(id);
  if (h == NULL) {
      printf("Nenhum historico encontrado para o ID %d.\n", id);
      return; 
  }
  printf("Procedimentos do paciente com ID %d:\n", id);
  for (int i = 0; i <= h->topo; i++) {
      printf("%s\n", h->procedimento[i]);
  }
  // Libera a memoria alocada para o historico apos a consulta
  free(h); 
}