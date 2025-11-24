#ifndef PILHA_HIST_H
#define PILHA_HIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // Adicionado para uso em Pilha_hist.c

typedef struct Pilha_hist
{
  // A pilha armazena ate 10 procedimentos de ate 99 caracteres
  char procedimento[10][100];  
  int topo;
}historico;

historico* criar_historico();
historico* abrir_historico(int id);
void consultar_procedimentos(int id);
void inserir_procedimento(historico *h, char procedimento[100], int id);
void desfazer_procedimento(historico *h, int id);
bool historico_vazio(historico *h);
bool historico_cheio(historico *h);

#endif // PILHA_HIST_H